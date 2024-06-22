#include <menu/menu.h>

void statcalc::menu::print_banner() {}

statcalc::menu::FileHeaderStatus statcalc::menu::print_fileHasHeader() {
    return statcalc::menu::FileHeaderStatus::YES_DNA;
}

void statcalc::menu::print_fileLoading(const std::string& p_fileName) {}

void statcalc::menu::print_fileNotFound(const std::string& p_fileName) {}

void statcalc::menu::print_fileCannotOutput(const std::string& p_fileName) {}

void statcalc::menu::print_fileNoneInput() {}

// Menu loop //

int statcalc::menu::get_header(const Dataset& p_dataset) {
    return -1;
}

void statcalc::menu::print_summary(const std::string& p_name, const DataColumn& p_data) {}

void statcalc::menu::print_regression(const std::string& p_x, const std::string& p_y, const Regression& p_reg) {}


statcalc::menu::Options statcalc::menu::get_option() {
    return statcalc::menu::Options::INVALID;
}

void statcalc::menu::print_unexpected() {}

void statcalc::menu::print_endOfProgram() {}