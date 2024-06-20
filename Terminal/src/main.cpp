#include <iostream>
#include <fstream>

#include <menu/menu.h>

#include <stat/Dataset.h>
#include <stat/statistical_analysis.h>
#include <file/file_parser.h>

int main(int argc, const char** argv) {
    // Print the banner
    statcalc::menu::print_banner();
    
    // This is the data tht the entire program revolves around
    statcalc::Dataset frame;   

    // Add files to a vector
    statcalc::files::read_input(frame, argc, argv);

    if (frame.header.size() < 1) {
        std::cout << "No Header!\n";
    } else {
        // Option input
        statcalc::menu::Options option = statcalc::menu::Options::INVALID;
        while (option != statcalc::menu::Options::EXIT) {
            // Get option
            option = statcalc::menu::get_option();

            switch (option) {

              // SUMMARY
              case statcalc::menu::Options::SUMMARY: {
                // Get column
                int column = statcalc::menu::get_header(frame);
                statcalc::menu::print_summary(frame.header[column], frame.data[column]);
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