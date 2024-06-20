#include <stat/DataIO.h>
#include <stat/TextIO.h>
#include <stat/StatIO.h>

std::istream& statcalc::operator>>(std::istream& is, Data& data) {
    switch (data.type()) {
      case statcalc::Data::Type::NUMERICAL: {
        is >> (Stat&)data;
        break;
      }
      
      case statcalc::Data::Type::TEXTUAL: {
        is >> (Text&)data;
        break;
      }
    }
    return is;
}

std::ostream& statcalc::operator<<(std::ostream& os, const Data& data) {
    switch (data.type()) {
      case statcalc::Data::Type::NUMERICAL: {
        os << (Stat&)data;
        break;
      }
      
      case statcalc::Data::Type::TEXTUAL: {
        os << (Text&)data;
        break;
      }
    }
    return os;
}