#ifndef STATISTICAL_ANALYSIS_H
#define STATISTICAL_ANALYSIS_H

#include "Dataset.h"

namespace statcalc {
	
	/////////////////////////////////////////////////
	//											   //
	//              Singular Variable              //
	//											   //
	/////////////////////////////////////////////////
	
		/**
		 * @author Cameron Sims
		 * 
		 * @fn statcalc::total
		 * @brief Gets the total from a data set
		 * @param p_data The data we're getting the total from
		 * @param p_size The size of the data we're reading
		 * @returns The total of the data
		 */
	stat_t total   (const VariableSet& p_data, size_t p_size = 0);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::mean
		 * @brief Gets the mean from the dataset
		 * @param p_data The data we're getting the mean from
		 * @returns The mean of the data
		 */
	stat_t mean    (const VariableSet& p_data);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::median
		 * @brief Gets the median from a dataset
		 * @param p_data The data we're getting the median from
		 * @returns The median of the data
		 */
	stat_t median  (const VariableSet& p_data);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::mode
		 * @brief Gets the mode of all the data
		 * @param p_data The data we're getting the mode from
		 * @returns The mode of the data
		 */
	stat_t mode    (const VariableSet& p_data);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::min
		 * @brief Gets the lowest value in the p_data
		 * @param p_data Gets the lowest data
		 * @returns The lowest value in the data
		 */
	stat_t minimum  (const VariableSet& p_data);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::max
		 * @brief Gets the highest value in the p_data
		 * @param p_data Gets the highest data
		 * @returns The highest value in the data
		 */
	stat_t maximum  (const VariableSet& p_data);
	
		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::variance
		 * @brief Gets the variance from the data
		 * @param p_data Used for the variance
		 * @returns The variance of the data
		 */
	stat_t variance(const VariableSet& p_data);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::stdev
		 * @brief Gets the standard deviation from the dataset
		 * @param p_data Used to get the standard deviation
		 * @returns Standard Deviation of the data
		 */
	stat_t stdev   (const VariableSet& p_data);
	
		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::stderror
		 * @brief The standard error of a data set
		 * @param p_data Used to get the standard error
		 * @returns Standard Error of the data
		 */
	stat_t stderror(const VariableSet& p_data);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::intNormalDist
		 * @brief Integral of Normal Distribution
		 * @param p_mean The mean we're using
		 * @param p_sd The standard deviation
		 * @param p_df The degrees of freedom
		 * @param p_tstat The t-statistic
		 * @param p_twoTailed If the statistic needs two tails
		 * @returns Area under the bell curve
		 */
	stat_t intNormalDist(stat_t p_mean, stat_t p_sd, stat_t p_df, stat_t p_tstat, bool p_twoTailed);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::pvalue
		 * @brief Gets the p-value from factors
		 * @param p_df The degrees of freedom
		 * @param p_tstat The t-statistic
		 * @param p_twoTailed If the statistic needs two tails
		 * @returns Area under the bell curve
		 */
	stat_t pvalue(stat_t p_df, stat_t p_tstat, bool p_twoTailed);
	



	/////////////////////////////////////////////////
	//											   //
	//               Double Variable               //
	//											   //
	/////////////////////////////////////////////////
	
		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::covariance
		 * @brief Gets the covariance between two data sets
		 * @param p_x First half of the data
		 * @param p_y Second half of the data
		 * @returns Co-Variance of p_x and p_y
		 */
	stat_t covariance(const VariableSet& p_x, const VariableSet& p_y);

		/**
		 * @author Cameron Sims
		 *
		 * @struct statcalc::PearsonsCoeff
		 * @brief A collection of data related to the pearsons' coefficient
		 */
	typedef struct {
		/// T value
		stat_t t;

		/// P-Value
		stat_t p;

		/// Standard Error
		stat_t error;

		

	} StudentTTest;

		
		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::studentTTest
		 * @brief Gets the students t-test between one variable
		 * @param p_data The sample
		 * @param p_assumeMean The assumed mean
		 * @param p_twoTails If we have two tails or not
		 * @returns A struct of variables for the students' t-test
		 */
	StudentTTest studentTTest(const VariableSet& p_data, stat_t p_assumeMean, bool p_twoTails);

		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::studentTTest
		 * @brief Gets the students t-test between two variables
		 * @param p_x First half of the data
		 * @param p_y Second half of the data
		 * @param p_twoTails If we have two tails or not
		 * @returns A struct of variables for the students' t-test
		 */
	StudentTTest studentTTest(const VariableSet& p_x, const VariableSet& p_y, bool p_twoTails);
		
		/**
		 * @author Cameron Sims
		 * 
		 * @struct statcalc::PearsonsCoeff
		 * @brief A collection of data related to the pearsons' coefficient
		 */
	typedef struct {
		/// The error associated with the pearsons' coefficient
		stat_t error;

		/// Relation variable
		stat_t r;
	} PearsonsCoeff;
	
		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::pcc
		 * @brief Pearsons' Coefficent
		 * @param p_x First half of data
		 * @param p_y Second half of data
		 * @returns Pearsons' Co-efficient struct
		 */
	PearsonsCoeff pcc(const VariableSet& p_x, const VariableSet& p_y);
	
	
	// 2D DataSet ////////////////////////////////
	
		/**
		 * @author Cameron Sims
		 *
		 * @struct statcalc::RegressionCoefficent
		 * @brief A collection of data related to a part in a regression test (a/b)
		 */
	typedef struct {
		/// Value of a or b
		stat_t coeff;

		/// Standard Errror
		stat_t error;

		/// P-Value
		stat_t p;

		/// T-Statistic
		stat_t t;
	} RegressionVariable;

		/**
		 * @author Cameron Sims
		 *
		 * @struct statcalc::Regression
		 * @brief A collection of data related to the regression test
		 */
	typedef struct {
		/// Y-intercept
		RegressionVariable a;
		
		/// Coefficent
		RegressionVariable b;
	} Regression;
	
		/**
		 * @author Cameron Sims
		 *
		 * @fn statcalc::regression
		 * @brief Regression function, performs regression test
		 * @param p_x First half of data
		 * @param p_y Second half of data
		 * @returns Regression data
		 */
	Regression regression(const VariableSet& p_x, const VariableSet& p_y);
}

#endif