#ifndef OPTIONS_H
#define OPTIONS_H

#include <stat/Dataset.h>

namespace statcalc {

	namespace options {

		/// The precision that we want the floating point system to be
		extern stat_t precision;

		/// File Seperator character
		extern char seperator;

		/// The default depth we want the program to be 
		extern size_t frame_depth;

		/// The default width of the columns
		extern size_t frame_width;
	}

}

#endif