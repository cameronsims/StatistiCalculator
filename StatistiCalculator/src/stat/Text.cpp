#include <stat/Text.h>

statcalc::Text::Text() {}
statcalc::Text::Text(const char* const p_str) {
	m_data = p_str;
}
statcalc::Text::Text(const std::string& p_str) {
	m_data = p_str;
}
statcalc::Text::~Text() {}
statcalc::Text::Type statcalc::Text::type() const {
	return statcalc::Text::Type::TEXTUAL;
}

statcalc::Text& statcalc::Text::operator= (const char* const p_str) {
	m_data = p_str;
	return *this;
}
statcalc::Text& statcalc::Text::operator= (const std::string& p_str) {
	m_data = p_str;
	return *this;
}

const std::string& statcalc::Text::str() const { return m_data; }
statcalc::Text::operator std::string()   const { return m_data; };
statcalc::Text::operator const char* ()   const { return m_data.c_str(); };