#include <stat/StatIO.h>

std::istream& statcalc::operator>>(std::istream& is, Stat& s) {
    stat_t f;
    is >> f;
    s = f;
    return is;
}

std::ostream& statcalc::operator<<(std::ostream& os, const Stat& s) {
    stat_t f = s;
    os << f;
    return os;
}