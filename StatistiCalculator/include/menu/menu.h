#ifndef MENU_MENU_H
#define MENU_MENU_H

#include <string>

#include <stat/statistical_analysis.h>
#include <stat/Dataset.h>

namespace statcalc {
    namespace menu {
        void print_banner();

        enum class Options {
            INVALID = 0,
            /// N, Mean, Variance(STDEV), STDERR, MIN-MAX
            SUMMARY,
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

        void print_fileLoading(const std::string& p_fileName);
        void print_fileNotFound(const std::string& p_fileName);
        void print_fileCannotOutput(const std::string& p_fileName);
        void print_fileNoneInput();

        // Menu loop //

        int get_header(const Dataset& p_dataset);

        void print_summary   (const std::string& p_name, const DataColumn& p_data);
        void print_regression(const std::string& p_x, const std::string& p_y, const Regression& p_reg);


        Options get_option();

        void print_unexpected();
        void print_endOfProgram();
    }
}

#endif