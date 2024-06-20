#include <menu/menu.h>

#include <iostream>
#include <stat/Dataset.h>
#include <stat/statistical_analysis.h>

void statcalc::menu::print_banner() {
    std::cout << "############################################\n"
              << "#                                          #\n"
              << "#            StatistiCalculator            #\n"
              << "#                                          #\n"
              << "############################################\n\n";
}

statcalc::menu::FileHeaderStatus statcalc::menu::print_fileHasHeader() {
    // Get the status
    int status = -1;
    while (status < 0 || status > 3) {
        std::cout << "Does this file have a header line?\n  0 = No\n  1 = Yes\n  2 = No (Do not ask me again)\n  3 = Yes (Do not ask me again)\n";
        try {
            std::cin >> status;
            if (status < 0 || status > 3) {
                std::cout << "Please enter a number from 0-3.\n";
            }
        } catch (const std::exception&) {
            std::cout << "Please enter a number from 0-3.\n";
        }
    }

    // Return the status
    return (FileHeaderStatus)status;
}

void statcalc::menu::print_fileLoading(const std::string& p_fileName) {
    std::cout << "Loading file: " << p_fileName << "\n";
}

void statcalc::menu::print_fileNotFound(const std::string& p_fileName) {
    std::cout << "File \"" << p_fileName << "\" not found!\n\n";
}

void statcalc::menu::print_fileNoneInput() {
    std::cout << "No files were found!\n\n";
}

void statcalc::menu::print_fileCannotOutput(const std::string& p_fileName) {
    std::cout << "Cannot output to the file \"" << p_fileName << "\"\n";
}

int statcalc::menu::get_header(const Dataset& p_dataset) {
    std::string name;
    int column = -1;
    while (column < 0 || column > p_dataset.header.size() - 1) {
        // Ask for column
        std::cout << "Enter Column/Variable Name:";
        try {
            std::cin >> name;
            column = statcalc::Dataset_hasHeader(p_dataset, name);
        } catch (const std::exception&) {
            column = -1;
        }
        if (column < 0 || column > p_dataset.header.size() - 1) {
            std::cout << "Invalid column name\n";
        }
    }
    return column;
}

void statcalc::menu::print_summary(const std::string& p_name, const statcalc::DataColumn& p_data) {
    std::cout << p_name << "\n  n = " << p_data.size() << "\n  mean = " << statcalc::mean(p_data)
                        << "\n  var = " << statcalc::variance(p_data)
                        << "\n  stdev = " << statcalc::stdev(p_data)
                        << "\n  stderr = " << statcalc::stderror(p_data)
                        << "\n  min = " << statcalc::min(p_data)
                        << "\n  max = " << statcalc::max(p_data) << "\n";
}

void statcalc::menu::print_regression(const std::string& p_x, const std::string& p_y, const Regression& p_reg) {
    std::cout << p_x << " - " << p_y

              << "\n  a = " << p_reg.a.coeff
              << "\n  | error = " << p_reg.a.error
              << "\n  | t-stat = " << p_reg.a.t
              << "\n  | p-value = " << p_reg.a.p

              << "\n  b = " << p_reg.b.coeff
              << "\n  | error = " << p_reg.b.error
              << "\n  | t-stat = " << p_reg.b.t
              << "\n  | p-value = " << p_reg.b.p
              << "\n\n"
        ;
}


statcalc::menu::Options statcalc::menu::get_option() {
    // Get option
    int option = -1;

    // Loop until valid
    while (option <= (int)statcalc::menu::Options::INVALID || option > (int)statcalc::menu::Options::EXIT) {
        std::cout << "Input the statistical analysis: ";
        try {
            std::cin >> (int&)option;
        } catch (const std::exception&) {
            option = (int)statcalc::menu::Options::INVALID;
        }

        // Check
        if (option <= (int)statcalc::menu::Options::INVALID && option > (int)statcalc::menu::Options::EXIT) {
            std::cout << "Invalid statistical analysis\n";
        }
    }

    // Return option
    return (statcalc::menu::Options)option;
}


void statcalc::menu::print_unexpected() {
    std::cout << "An unexpected error has occured!\n\n";
}

void statcalc::menu::print_endOfProgram() {
    std::cout << "\nProgram has been finished!\n";
}