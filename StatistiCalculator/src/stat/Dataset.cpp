#include <stat/Dataset.h>

int statcalc::Dataset_hasHeader(const Dataset& p_dataset, const std::string& p_hName) {
    // If there is no values
    if (p_dataset.header.size() < 1) {
        return -1;
    }

    for (size_t i = 0; i < p_dataset.header.size(); i++) {
        if (p_dataset.header[i] == p_hName) {
            return (int)i;
        }
    }
    return -1;
}