#ifndef STAT_STATIO_H
#define STAT_STATIO_H

#include "Stat.h"

#include <iostream>

namespace statcalc {

    std::istream& operator>>(std::istream&, Stat&);
    std::ostream& operator<<(std::ostream&, const Stat&);

}

#endif