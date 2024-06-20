#include <stat/Stat.h>

#include <settings/options.h>

statcalc::Stat::Stat() {
	this->m_data = 0.0;
}
statcalc::Stat::Stat(stat_t s) {
	this->m_data = s;
}
statcalc::Stat::~Stat() {}

bool statcalc::operator==(const Stat& p_left, stat_t p_right) {
	// For clean code
	const statcalc::stat_t& left = p_left;
	const statcalc::stat_t& right = p_right;

	// Check difference first
	statcalc::stat_t difference = fabs(left - right);

	// If a value that'll screw with relative error
	if (difference == 0.0 || left == 0 || right == 0) {
		return difference == 0.0;
	}

	// Do relative errror
	return (difference / MIN(left + right, INFINITY)) < statcalc::options::precision;
}
bool statcalc::operator!=(const Stat& p_left, stat_t p_right) { return !((stat_t)p_left == p_right); }
bool statcalc::operator< (const Stat& p_left, stat_t p_right) { return   (stat_t)p_left < p_right; }
bool statcalc::operator> (const Stat& p_left, stat_t p_right) { return   (stat_t)p_left > p_right; }
bool statcalc::operator<=(const Stat& p_left, stat_t p_right) { return !((stat_t)p_left > p_right); }
bool statcalc::operator>=(const Stat& p_left, stat_t p_right) { return !((stat_t)p_left < p_right); }

statcalc::Stat  statcalc::operator+ (const Stat& p_left, stat_t p_right) { return ((stat_t)p_left + p_right); }
statcalc::Stat  statcalc::operator- (const Stat& p_left, stat_t p_right) { return ((stat_t)p_left - p_right); }
statcalc::Stat  statcalc::operator* (const Stat& p_left, stat_t p_right) { return ((stat_t)p_left * p_right); }
statcalc::Stat  statcalc::operator/ (const Stat& p_left, stat_t p_right) { return ((stat_t)p_left / p_right); }

statcalc::Stat& statcalc::operator+=(Stat& p_left, stat_t p_right) { p_left = (stat_t)p_left + p_right; return p_left; }
statcalc::Stat& statcalc::operator-=(Stat& p_left, stat_t p_right) { p_left = (stat_t)p_left - p_right; return p_left; }
statcalc::Stat& statcalc::operator*=(Stat& p_left, stat_t p_right) { p_left = (stat_t)p_left * p_right; return p_left; }
statcalc::Stat& statcalc::operator/=(Stat& p_left, stat_t p_right) { p_left = (stat_t)p_left / p_right; return p_left; }
statcalc::Stat& statcalc::operator++(Stat& p_left) { p_left = p_left + 1.0; return p_left; }
statcalc::Stat& statcalc::operator--(Stat& p_left) { p_left = p_left + 1.0; return p_left; }


statcalc::Stat::Type statcalc::Stat::type() const { return statcalc::Stat::Type::NUMERICAL; }

#ifdef STAT_T_DOUBLE
statcalc::Stat::operator double() const {
	return m_data;
}
#else
statcalc::Stat::operator float() const { return (float)m_data; }
#endif