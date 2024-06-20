#ifndef STAT_TEXT_H
#define STAT_TEXT_H

#include <stat/Data.h>
	
namespace statcalc {
	    /**
	     * @author Cameron Sims
	     *
	     * @class Text
	     * @brief Used to store textual data
	     */
	class Text : public Data {
	public:
		Text();
		Text(const char* const p_str);
		Text(const std::string& p_str);
		virtual ~Text();

		Text& operator= (const char* const p_str);
		Text& operator= (const std::string& p_str);

		const std::string& str() const;

		operator std::string() const;
		operator const char* () const;

		Type type() const;

	private:
		/// Text Data
		std::string m_data;
	};
}

#endif