#ifndef STAT_STAT_H
#define STAT_STAT_H

#include <stat/Data.h>

#define MIN(l, r) ((l < r) ? l : r)


namespace statcalc {
		/**
		 * @author Cameron Sims
		 *
		 * @class Stat
		 * @brief Used to store numerical data
		 */
	class Stat : public Data {
	public:
		Stat();
		Stat(stat_t s);
		virtual ~Stat();

	#ifdef STAT_T_DOUBLE
		operator double() const;
	#else
		operator float() const;
	#endif


		Type type() const;

	private:
		/// Statistic Data
		stat_t m_data;
	};




	bool  operator==(const Stat& p_left, stat_t p_right);
	bool  operator!=(const Stat& p_left, stat_t p_right);
	bool  operator< (const Stat& p_left, stat_t p_right);
	bool  operator> (const Stat& p_left, stat_t p_right);
	bool  operator<=(const Stat& p_left, stat_t p_right);
	bool  operator>=(const Stat& p_left, stat_t p_right);

	Stat  operator+ (const Stat& p_left, stat_t p_right);
	Stat  operator- (const Stat& p_left, stat_t p_right);
	Stat  operator* (const Stat& p_left, stat_t p_right);
	Stat  operator/ (const Stat& p_left, stat_t p_right);

	Stat& operator+=(Stat& p_left, const stat_t p_right);
	Stat& operator-=(Stat& p_left, const stat_t p_right);
	Stat& operator*=(Stat& p_left, const stat_t p_right);
	Stat& operator/=(Stat& p_left, const stat_t p_right);
	Stat& operator++(Stat& p_left);
	Stat& operator--(Stat& p_left);
}

#endif