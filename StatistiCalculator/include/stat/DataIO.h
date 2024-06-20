#ifndef STAT_DATAIO_H
#define STAT_DATAIO_H

#include "Data.h"

#include <iostream>

namespace statcalc {
    
    std::istream& operator>>(std::istream&, Data&);
    std::ostream& operator<<(std::ostream&, const Data&);

}

#endif