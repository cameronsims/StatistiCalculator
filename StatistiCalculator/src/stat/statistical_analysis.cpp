#include <stat/statistical_analysis.h>

#include <cmath>
#include <map>

// Singular Variable //////////////////////////////////////////////////

statcalc::stat_t statcalc::total   (const VariableSet& p_data, size_t p_size) {
	if (p_size == 0) {
		p_size = p_data.size();
	}
	
	statcalc::stat_t sum = 0.0;
	for (size_t i = 0; i < p_size; i++) {
		sum += p_data[i];
	}
	return sum;
}

statcalc::stat_t statcalc::mean    (const VariableSet& p_data) {
	return statcalc::total(p_data) / p_data.size();
}

statcalc::stat_t statcalc::median  (const VariableSet& p_data) {
	// Use BST to sort
	return -INFINITY;
}

statcalc::stat_t statcalc::mode    (const VariableSet& p_data) {
	// Get mode
	return -INFINITY;
}

statcalc::stat_t statcalc::min     (const VariableSet& p_data) {
	size_t smallest = 0;
	for (size_t i = 1; i < p_data.size(); i++) {
		if (p_data[i] < p_data[smallest]) {
			smallest = i;
		}
	}
	return p_data[smallest];
}

statcalc::stat_t statcalc::max     (const VariableSet& p_data) {
	size_t biggest = 0;
	for (size_t i = 1; i < p_data.size(); i++) {
		if (p_data[i] > p_data[biggest]) {
			biggest = i;
		}
	}
	return p_data[biggest];
}

statcalc::stat_t statcalc::variance(const VariableSet& p_data) {
	return statcalc::covariance(p_data, p_data);
}

statcalc::stat_t statcalc::stdev   (const VariableSet& p_data) {
	return sqrt(statcalc::variance(p_data));
}

statcalc::stat_t statcalc::stderror(const VariableSet& p_data) {
	return statcalc::stdev(p_data)/sqrt(p_data.size());
}

// Double VariableSet /////////////////////////////////////////////////

statcalc::stat_t statcalc::covariance(const VariableSet& p_x, const VariableSet& p_y) {
	const size_t n = MIN(p_x.size(), p_y.size());
	const stat_t meanX = statcalc::mean(p_x);
	const stat_t meanY = statcalc::mean(p_y);
	
	stat_t sum = 0.0;
	
	for (size_t i = 0; i < n; i++) {
		sum += (p_x[i] - meanX) * (p_y[i] - meanY);
	}
	
	return sum / (n - 1);
}

statcalc::PearsonsCoeff statcalc::pcc(const VariableSet& p_x, const VariableSet& p_y) {
	const size_t n = MIN(p_x.size(), p_y.size());
	const stat_t meanX = statcalc::mean(p_x);
	const stat_t meanY = statcalc::mean(p_y);
	
	stat_t numerSum = 0.0;
	
	stat_t denomXSum = 0.0;
	stat_t denomYSum = 0.0;
	
	for (size_t i = 0; i < n; i++) {
		
		const stat_t left  = p_x[i] - meanX;
		const stat_t right = p_y[i] - meanY;
		
		numerSum += (left) * (right);
		
		denomXSum += (left) * (left);
		denomYSum += (right) * (right);
	}
	
	statcalc::PearsonsCoeff ret;
	
	ret.r = numerSum / sqrt( denomXSum * denomYSum );
	ret.error = sqrt( ( 1 - ret.r * ret.r) / ( n - 2 ) );
	
	return ret;
}

// 2D DataSet /////////////////////////////////////////////////////////

statcalc::Regression statcalc::regression(const VariableSet& p_x, const VariableSet& p_y) {
	
	const size_t n = MIN(p_x.size(), p_y.size());
	const stat_t sumX = statcalc::total(p_x, n);
	const stat_t sumY = statcalc::total(p_y, n);

	const stat_t meanX = statcalc::mean(p_x);
	const stat_t meanY = statcalc::mean(p_y);
	
	const stat_t varX = variance(p_x);
	const stat_t covarXY = covariance(p_x, p_y);
	
	const stat_t b1 = covarXY / varX;
	const stat_t b0 = (sumY / n) - b1 * (sumX/n);
	
	stat_t sumXSq = 0.0;
	stat_t sumXY  = 0.0;

	stat_t sumOfResX = 0.0;
	stat_t sumOfResY = 0.0;
	
	for (size_t i = 0; i < n; i++) {
		sumXSq += p_x[i] * p_x[i];
		sumXY += p_x[i] * p_y[i];
		
		//const double ypredict = b0 + b1 * p_x[i];
		sumOfResX += (p_x[i] - meanX) * (p_x[i] - meanX);
		sumOfResY += (p_y[i] - meanY) * (p_y[i] - meanY);
	}
	
	// Regression
	statcalc::Regression ret{};

	// Y-intercept
	ret.b.coeff = (n*sumXY-sumX*sumY)/(n*sumXSq-sumX*sumX);
	ret.b.error = sqrt(sumOfResY / ((n - 2)*(sumOfResX)));
	ret.b.t = (ret.b.coeff / ret.b.error);
	ret.b.p = -INFINITY;	// TODO: ADD P-VALUE

	// Scale Co-efficent (a)
	ret.a.coeff = ((sumY * sumXSq) -( sumX * sumXY)) / ( n*sumXSq - sumX * sumX);
	ret.a.error = ret.b.error * sqrt(sumXSq/n);
	ret.a.t = (ret.a.coeff / ret.a.error);
	ret.b.p = -INFINITY;	// TODO: ADD P-VALUE
	
	// P-Value
	//ret.p = 2*(1 - (0.5 * erfc(-fabs(ret.t) / sqrt(2))));
	
	// Residual Sum of Squares
	//ret.rss = resSumOfSquares;

	// Error
	//ret.error = sqrt(ret.rss / (n - 2) );
	
	// T-Stat
	//ret.t = b1 / (ret.error / sqrt(varX * (n -1)));
	
	
	return ret;
}