#ifndef MENU_MENU_H
#define MENU_MENU_H

#include <string>
#include <wchar.h>

#include <stat/statistical_analysis.h>
#include <stat/Dataset.h>

namespace statcalc {
    namespace menu {
        void print_banner();

        enum class Options {
            INVALID = 0,

            /// N, Mean, Variance(STDEV), STDERR, MIN-MAX
            SUMMARY,

            /// Students' T-Test (One Sample)
            TTEST_SINGLE,

            /// Students' T-Test (Two Sample)
            TTEST_DOUBLE,

            /// Regression
            REGRESSION,

            /// Pearsons' Coefficent
            PEARSON,

            EXIT
        };

        enum class FileHeaderStatus {
            NO = 0,
            YES,
            NO_DNA,
            YES_DNA
        };
        FileHeaderStatus print_fileHasHeader();

        void print_fileLoading(const std::wstring& p_fileName);
        void print_fileNotFound(const std::wstring& p_fileName);
        void print_fileCannotOutput(const std::wstring& p_fileName);

        void print_fileNoneInput();

        // Menu loop //

        int get_header(const Dataset& p_dataset);

        void print_summary   (const std::wstring& p_name, const DataColumn& p_data);
        void print_ttest     (const std::wstring& p_x, const std::wstring& p_y, const StudentTTest&  p_stat);
        void print_regression(const std::wstring& p_x, const std::wstring& p_y, const Regression&    p_reg);
        void print_pearson   (const std::wstring& p_x, const std::wstring& p_y, const PearsonsCoeff& p_pcc);


        stat_t get_stat();
        bool get_bool();
        Options get_option();

        void print_unexpected();
        void print_endOfProgram();
    }
}

#endif