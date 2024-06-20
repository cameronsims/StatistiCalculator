#include <stat/Data.h>

namespace statcalc {
	    /**
	     * @author Cameron Sims
	     *
	     * @struct DataPoint
	     * @brief Used to store a point
	     */
	typedef struct {
		/// X-Position
		stat_t x;

		/// Y-Position
		stat_t y;
	} DataPoint;
}