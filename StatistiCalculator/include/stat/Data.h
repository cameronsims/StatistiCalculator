#ifndef STAT_DATA_H
#define STAT_DATA_H

#include <string>

namespace statcalc {
	/////////////////////////////////////////////////////////
	//													   //
	// This is our floating point standard for the program //
	//													   //
	/////////////////////////////////////////////////////////

	#ifdef _WIN64
	
	#define STAT_T_DOUBLE 1
	/// Statistical Floating Point Data
		typedef double stat_t;
	#else
	#define STAT_T_FLOAT  1
	/// Statistical Double Precision Floating Point Data
		typedef float stat_t;
	#endif



		/**
		 * @author Cameron Sims
		 *
		 * @class Data
		 * @brief Used to store some sort of data
		 */
	class Data {
	public:
		Data();
		virtual ~Data();

		enum class Type {
			TEXTUAL = 0,
			NUMERICAL
		};

		virtual Type type() const = 0;
	private:
		/// Text Data
		std::string m_data;
	};
}

#endif