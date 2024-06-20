#include <stat/TextIO.h>

std::istream& statcalc::operator>>(std::istream& is, Text& txt) {
    std::string str;
    is >> str;
    txt = str;
    return is;
}

std::ostream& statcalc::operator<<(std::ostream& os, const Text& txt) {
    const std::string& str = txt.str();
    os << str;
    return os;
}