#include <stat/statistical_analysis.h>

#define _USE_MATH_DEFINES
#include <math.h>	// Need for PI

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

statcalc::stat_t statcalc::minimum(const VariableSet& p_data) {
	size_t smallest = 0;
	for (size_t i = 1; i < p_data.size(); i++) {
		if (p_data[i] < p_data[smallest]) {
			smallest = i;
		}
	}
	return p_data[smallest];
}

statcalc::stat_t statcalc::maximum(const VariableSet& p_data) {
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
	return statcalc::stdev(p_data)/sqrt((stat_t)p_data.size());
}

#include <iostream>
statcalc::stat_t statcalc::intNormalDist(stat_t p_mean, stat_t p_sd, stat_t p_df, stat_t p_tstat, bool p_twoTailed) {
	// OLD VALUES TO GET A POINT ON THE NORMAL DISTRIBUTION
	// 
	//constexpr stat_t sqrtPI2 = M_SQRT2 * (2 / M_2_SQRTPI);	// sqrt(2*PI)
	//constexpr stat_t euler = M_E;
	//const stat_t var = p_sd* p_sd;
	//
	//stat_t x = 0.0;
	//
	//const stat_t xMuSq = (x - p_mean)*(x - p_mean);
	//
	//stat_t bell = pow(euler, -0.5 * xMuSq / var) / (p_sd * sqrtPI2);

	// This is the integral of a normal distribution's bell curve (shown above)
	auto F = [&](stat_t x) { return fabs(0.5 * erf((x - p_mean) / (M_SQRT2 * p_sd))); };

	// https://www.desmos.com/calculator/r9jut8vgnn
	
	const stat_t upper = F(p_mean - 4*p_sd);
	const stat_t lower = F(p_mean - p_tstat);
	std::cout << lower << "\n";
	const stat_t multi = (p_twoTailed) ? 2.0 : 1.0;
	const stat_t sum = multi * fabs(lower - upper);
	return sum;
}

statcalc::stat_t statcalc::pvalue(stat_t p_df, stat_t p_tstat, bool p_twoTailed) {
	return intNormalDist(0.0, sqrt(p_df / (p_df - 2)), p_df, p_tstat, p_twoTailed);
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


statcalc::StudentTTest statcalc::studentTTest(const VariableSet& p_data, stat_t p_assumeMean, bool p_twoTails) {
	const stat_t n = p_data.size();
	const stat_t mean = statcalc::mean(p_data);
	const stat_t err = stderror(p_data);

	StudentTTest ttest{};
	ttest.t = (mean - p_assumeMean) / err;
	ttest.p = pvalue((stat_t)(n - 1), ttest.t, p_twoTails);
	ttest.error = err;

	return ttest;
}

statcalc::StudentTTest statcalc::studentTTest(const VariableSet& p_x, const VariableSet& p_y, bool p_twoTails) {
	const stat_t n = MIN(p_x.size(), p_y.size());
	const stat_t meanX = statcalc::mean(p_x);
	const stat_t meanY = statcalc::mean(p_y);
	const stat_t err   = sqrt((stdev(p_x) * stdev(p_x)) / p_x.size() + (stdev(p_y) * stdev(p_y)) / p_y.size());

	StudentTTest ttest{};
	ttest.t = (meanX - meanY) / err;
	ttest.p = pvalue((stat_t)(n - 1), ttest.t, p_twoTails);
	ttest.error = err;

	return ttest;
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
	ret.b.p = pvalue((stat_t)(n - 1), ret.b.t, true);

	// Scale Co-efficent (a)
	ret.a.coeff = ((sumY * sumXSq) -( sumX * sumXY)) / ( n*sumXSq - sumX * sumX);
	ret.a.error = ret.b.error * sqrt(sumXSq/n);
	ret.a.t = (ret.a.coeff / ret.a.error);
	ret.a.p = pvalue((stat_t)(n - 1), ret.a.t, true);
	
	
	return ret;
}