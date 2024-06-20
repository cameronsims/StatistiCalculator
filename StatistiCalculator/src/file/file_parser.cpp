#include <file/file_parser.h>
#include <settings/options.h>

#include <fstream>
#include <string>

#include <menu/menu.h>

void statcalc::files::read_input(Dataset& p_dataset, int argc, const char** argv) {
    // Check if there is files
    if (argc > 1) {
        // Add files to vector
        Vector<std::string> files(argc - 1);
        statcalc::files::read_inputFiles(files, argc, argv);

        // Input files were provided //
        statcalc::files::read_files(p_dataset, files);
    }
    // If no input files were provided //
    else {
        statcalc::menu::print_fileNoneInput();
    }
}

void statcalc::files::read_inputFiles(Vector<std::string>& p_files, int argc, const char** argv) {
    // Loop all files
    for (int i = 1; i < argc; i++) {
        p_files[i - 1] = argv[i];
        // Removing this line crashes the program????
       p_files[i - 1];
    }
}

void statcalc::files::read_files(statcalc::Dataset& p_dataset, const Vector<std::string>& p_files) {
    // This is the status of whether we are getting a header
    statcalc::menu::FileHeaderStatus status = statcalc::menu::FileHeaderStatus::NO;
    
    // This is whether we are going to get the header
    bool wantHeader = false;

    // Size of files
    const size_t SIZE = p_files.size();

    // Read in files
    for (int i = 0; i < SIZE; i++) {
        // File name
        statcalc::Text fileName = p_files[i];
        statcalc::menu::print_fileLoading(fileName.str());

        // Check if the status isn't a DNA
        if (status != statcalc::menu::FileHeaderStatus::NO_DNA && status != statcalc::menu::FileHeaderStatus::YES_DNA) {
            status = statcalc::menu::print_fileHasHeader();
            wantHeader = (status == statcalc::menu::FileHeaderStatus::YES || status == statcalc::menu::FileHeaderStatus::YES_DNA);
        }

        try {
            read_file(p_dataset, fileName, wantHeader);
        } catch (const FileNotFound&) {
            statcalc::menu::print_fileNotFound(fileName.str());
        } catch (const Exception&) {
            statcalc::menu::print_unexpected();
        }
    }
}

void statcalc::files::read_file(statcalc::Dataset& p_dataset, const Text& p_fileName, bool p_header) {
    // The input stream
    std::ifstream in(p_fileName.str());
    
    // If istream is bad
    if (!in.good()) {
        throw FileNotFound();
    }

    // Read the first line
    std::string line;
    if (p_header) {
        std::getline(in, line);
        read_head(p_dataset.header, line);
    }

    size_t i = 0;
    // Read line by line
    while (!in.eof()) {
        // Get line
        std::getline(in, line);
        read_line(p_dataset, line, i);
        i++;
    }
}

void statcalc::files::read_head(Vector<std::string>& p_header, const std::string& p_line) {
    // Important variables
    const size_t SIZE = p_line.size();
    size_t start = 0;
    size_t end = -1;
    // Read the line per delimeter
    for (size_t i = 0; i < SIZE; i++) {
        if (p_line[i] == statcalc::options::seperator) {
            // Set our current start to where we left off...
            start = end + 1;

            // Set the end to where we found the seperator
            end = i;

            const std::string str = p_line.substr(start, end - start);
            p_header.push(str);
        }
    }

    if (end != SIZE) {
        p_header.push(p_line.substr(end + 1, SIZE));
    }
}

void statcalc::files::read_line(statcalc::Dataset& p_dataset, const statcalc::Text& p_line, size_t p_row) {
    // Length of string
    const std::string& STR  = p_line.str();
    const size_t       SIZE = STR.size();

    // The beginning and end of a cell
    size_t col = 0;
    size_t start = 0;
    size_t end   = -1;    // -1 so we can overflow and be set to 0 for start

    // Read line
    for (size_t i = 0; i < SIZE; i++) {
        if (STR[i] == statcalc::options::seperator) {
            // Set our current start to where we left off...
            start = end + 1;

            // Set the end to where we found the seperator
            end = i;
        
            // Read the cell
            read_cell(p_dataset, p_line, col, p_row, start, end);
            col++;
        }
    }

    if (end != SIZE) {
        read_cell(p_dataset, p_line, col, p_row, end + 1, SIZE);
        col++;
    }
}

void statcalc::files::read_cell(statcalc::Dataset& p_dataset, const statcalc::Text& p_line, size_t p_column, size_t p_row, size_t p_start, size_t p_end) {
    // Check if the data we have is a number
    const std::string& STR = p_line.str();
    const std::string SUBSTR = STR.substr(p_start, p_end-p_start);

    try {
        // Floating Point standard non sense
        #ifdef STAT_T_DOUBLE
        stat_t value = std::stod(SUBSTR);
        #else
        stat_t value = std::stof(SUBSTR);
        #endif

        // Add value
        p_dataset.data[p_column][p_row] = value;
    }

    // IF IT IS A NUMBER ////////////////////////
    
    // If the number is too big...
    catch (const std::overflow_error&) {
        // Positive Infinity
        p_dataset.data[p_column][p_row] = INFINITY;
    } catch (const std::underflow_error&) {
        // Set to negative infinity
        p_dataset.data[p_column][p_row] = -INFINITY;
    } 

    // IF IT IS A STRING ////////////////////////

    // Exception 
    catch (const std::exception&) {
        p_dataset.data[p_column][p_row] = NAN;
    }
}