#ifndef DATASET_H
#define DATASET_H

#include <structures/Vector.h>

#include <stat/DataPoint.h>
#include <stat/Data.h>
#include <stat/Stat.h>
#include <stat/Text.h>

#include <memory>
#include <vector>
#include <list>

namespace statcalc {
	

	/// Column of some data
	typedef Vector<Stat>       DataColumn;
						       
	/// Variable Set Data      
	typedef Vector<Stat>       VariableSet;
						       
	/// Textual Set Data       
	typedef Vector<Text>       TextualSet;

	/// DotPlot Data
	typedef Vector<DataPoint> DotPlot;




		/**
		 * @author Cameron Sims
		 *
		 * @struct Dataset
		 * @brief Used to store a some amount of data
		 */
	typedef struct {
		Vector<std::wstring> header;
		Vector<DataColumn> data;
	} Dataset;

	int Dataset_hasHeader(const Dataset& p_dataset, const std::wstring& p_hName);
}

#endif