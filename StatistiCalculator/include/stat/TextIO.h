#ifndef STAT_TEXTIO_H
#define STAT_TEXTIO_H

#include "Text.h"

#include <iostream>

namespace statcalc {

    std::istream& operator>>(std::istream&, Text&);
    std::ostream& operator<<(std::ostream&, const Text&);

}

#endif