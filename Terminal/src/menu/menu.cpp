#include <menu/menu.h>

#include <iostream>
#include <stat/Dataset.h>
#include <stat/statistical_analysis.h>

void statcalc::menu::print_banner() {
    std::wcout << "############################################\n"
               << "#                                          #\n"
               << "#            StatistiCalculator            #\n"
               << "#                                          #\n"
               << "############################################\n\n";
}

statcalc::menu::FileHeaderStatus statcalc::menu::print_fileHasHeader() {
    // Get the status
    int status = -1;
    while (status < 0 || status > 3) {
        std::wcout << "Does this file have a header line?\n  0 = No\n  1 = Yes\n  2 = No (Do not ask me again)\n  3 = Yes (Do not ask me again)\n";
        try {
            std::wcin >> status;
            if (status < 0 || status > 3) {
                std::wcout << "Please enter a number from 0-3.\n";
            }
        } catch (const std::exception&) {
            std::wcout << "Please enter a number from 0-3.\n";
        }
    }

    // Return the status
    return (FileHeaderStatus)status;
}

void statcalc::menu::print_fileLoading(const std::wstring& p_fileName) {
    std::wcout << L"Loading file: " << p_fileName << L"\n";
}

void statcalc::menu::print_fileNotFound(const std::wstring& p_fileName) {
    std::wcout << L"File \"" << p_fileName << "\" not found!\n\n";
}

void statcalc::menu::print_fileNoneInput() {
    std::wcout << L"No files were found!\n\n";
}

void statcalc::menu::print_fileCannotOutput(const std::wstring& p_fileName) {
    std::wcout << L"Cannot output to the file \"" << p_fileName << L"\"\n";
}

int statcalc::menu::get_header(const Dataset& p_dataset) {
    std::wstring name;
    int column = -1;
    while (column < 0 || column > p_dataset.header.size() - 1) {
        // Ask for column
        std::wcout << L"Enter Column/Variable Name:";
        try {
            std::wcin >> name;
            column = statcalc::Dataset_hasHeader(p_dataset, name);
        } catch (const std::exception&) {
            column = -1;
        }
        if (column < 0 || column > p_dataset.header.size() - 1) {
            std::wcout << L"Invalid column name\n";
        }
    }
    return column;
}

void statcalc::menu::print_summary(const std::wstring& p_name, const statcalc::DataColumn& p_data) {
    std::wcout << p_name << L"\n  n = " << p_data.size() << L"\n  mean = " << statcalc::mean(p_data)
                         << L"\n  var = " << statcalc::variance(p_data)
                         << L"\n  stdev = " << statcalc::stdev(p_data)
                         << L"\n  stderr = " << statcalc::stderror(p_data)
                         << L"\n  min = " << statcalc::minimum(p_data)
                         << L"\n  max = " << statcalc::maximum(p_data) << "\n";
}

void statcalc::menu::print_ttest(const std::wstring& p_x, const std::wstring& p_y, const StudentTTest& p_stat) {
    std::wcout << p_x;
    if (p_y.size() != 0) {
        std::wcout << L" - " << p_y;
    }

    std::wcout << L"\n  t = " << p_stat.t
               << L"\n  p = " << p_stat.p
               << L"\n  error = " << p_stat.error << L"\n\n";
}

void statcalc::menu::print_regression(const std::wstring& p_x, const std::wstring& p_y, const Regression& p_reg) {
    std::wcout << p_x << L" - " << p_y
               << L"\n  a = " << p_reg.a.coeff
               << L"\n  | error = " << p_reg.a.error
               << L"\n  | t-stat = " << p_reg.a.t
               << L"\n  | p-value = " << p_reg.a.p
               << L"\n  b = " << p_reg.b.coeff
               << L"\n  | error = " << p_reg.b.error
               << L"\n  | t-stat = " << p_reg.b.t
               << L"\n  | p-value = " << p_reg.b.p
               << L"\n\n"
        ;
}

void statcalc::menu::print_pearson(const std::wstring& p_x, const std::wstring& p_y, const PearsonsCoeff& p_pcc) {
    std::wcout << p_x << L" - " << p_y 
               << L"\n  r = " << p_pcc.r
               << L"\n  error = " << p_pcc.error << L"\n\n";
}

statcalc::stat_t statcalc::menu::get_stat() {
    try {
        stat_t stat;
        std::wstring input;
        std::wcin >> input;
    #ifdef STAT_T_DOUBLE
        stat = std::stod(input);
    #else
        stat = std::stof(input);
    #endif
        return stat;
    } catch (const std::exception&) {
        std::wcout << L"Please put in a valid value\n";
        return get_stat();
    }
}

bool statcalc::menu::get_bool() {
    std::wcout << L"(Y/N) = ";
    wchar_t c = 0;
    while ((c != 'Y' && c != 'y') && (c != 'N' && c != 'n')) {
        try {
            std::wcin >> c;
            if ((c != 'Y' && c != 'y') && (c != 'N' && c != 'n')) {
                std::wcout << L"Please put in a valid value\n";
            }
        } catch (const std::exception&) {
            std::wcout << L"Please put in a valid value\n";
        }
    }
    
    return (c == 'Y' || c == 'y');
}

statcalc::menu::Options statcalc::menu::get_option() {
    // Get option
    int option = -1;

    // Loop until valid
    while (option <= (int)statcalc::menu::Options::INVALID || option > (int)statcalc::menu::Options::EXIT) {
        std::wcout << L"Input the statistical analysis: ";
        try {
            std::wcin >> (int&)option;
        } catch (const std::exception&) {
            option = (int)statcalc::menu::Options::INVALID;
        }

        // Check
        if (option <= (int)statcalc::menu::Options::INVALID && option > (int)statcalc::menu::Options::EXIT) {
            std::wcout << L"Invalid statistical analysis\n";
        }
    }

    // Return option
    return (statcalc::menu::Options)option;
}


void statcalc::menu::print_unexpected() {
    std::wcout << L"An unexpected error has occured!\n\n";
}

void statcalc::menu::print_endOfProgram() {
    std::wcout << L"\nProgram has been finished!\n";
}