#include <iostream>
#include <fstream>

#include <menu/menu.h>

#include <stat/Dataset.h>
#include <stat/statistical_analysis.h>
#include <file/file_parser.h>

int wmain(size_t argc, const wchar_t** argv) {
    // Print the banner
    statcalc::menu::print_banner();
    
    // This is the data tht the entire program revolves around
    statcalc::Dataset frame;   

    // Add files to a vector
    statcalc::files::read_input(frame, argc, argv);

    if (frame.header.size() < 1) {
        std::wcout << L"No Header!\n";
    } else {
        // Option input
        statcalc::menu::Options option = statcalc::menu::Options::INVALID;
        while (option != statcalc::menu::Options::EXIT) {
            std::wcout << L"\nEnter Option:\n" << "  1. Statistical Summary\n  2. Students' T-Test (Single Sample)\n  3. Students' T-Test (Double Sample)\n  4. Regression Test\n  5. Pearson's Co-efficent\n  6. Exit Program\n";
            
            // Get option
            option = statcalc::menu::get_option();
            std::wcout << "\n";

            switch (option) {

              // SUMMARY
              case statcalc::menu::Options::SUMMARY: {
                // Get column
                int column = statcalc::menu::get_header(frame);
                statcalc::menu::print_summary(frame.header[column], frame.data[column]);
                break;
              }

              // T-Test Single
              case statcalc::menu::Options::TTEST_SINGLE: {
                // Get columns
                const int col = statcalc::menu::get_header(frame);
                std::wcout << L"Input Assumed Mean = ";
                statcalc::stat_t assumedMean = statcalc::menu::get_stat();

                std::wcout << L"Two Tails? ";
                bool twotails = statcalc::menu::get_bool();

                statcalc::StudentTTest t = statcalc::studentTTest(frame.data[col], assumedMean, twotails);
                statcalc::menu::print_ttest(frame.header[col], L"", t);
                break;
              }

              // T-Test Double
              case statcalc::menu::Options::TTEST_DOUBLE: {
                // Get columns
                const int xCol = statcalc::menu::get_header(frame);
                const int yCol = statcalc::menu::get_header(frame);

                std::wcout << L"Two Tails? ";
                bool twotails = statcalc::menu::get_bool();

                statcalc::StudentTTest t = statcalc::studentTTest(frame.data[xCol], frame.data[yCol], twotails);
                statcalc::menu::print_ttest(frame.header[xCol], frame.header[yCol], t);
                break;
              }
              
              // Regression
              case statcalc::menu::Options::REGRESSION: {
                // Get columns
                const int xCol = statcalc::menu::get_header(frame);
                const int yCol = statcalc::menu::get_header(frame);
                const statcalc::Regression r = statcalc::regression(frame.data[xCol], frame.data[yCol]);
                statcalc::menu::print_regression(frame.header[xCol], frame.header[yCol], r);
              
                break;
              }

              // Pearsons' Co-eff
              case statcalc::menu::Options::PEARSON: {
                  const int xCol = statcalc::menu::get_header(frame);
                  const int yCol = statcalc::menu::get_header(frame);
                  const statcalc::PearsonsCoeff r = statcalc::pcc(frame.data[xCol], frame.data[yCol]);
                  statcalc::menu::print_pearson(frame.header[xCol], frame.header[yCol], r);
              }
              
              case statcalc::menu::Options::EXIT: {
                std::cout << "Exiting...\n";
                break;
              }

              default: {
                std::cout << "Unknown Command!\n";
                break;
              }
            }
        }
    }

    // End of program
    statcalc::menu::print_endOfProgram();
    return 0;
}