#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <stat/Dataset.h>
#include <file/file_errors.h>

#include <stat/DataIO.h>
#include <stat/TextIO.h>
#include <stat/StatIO.h>

namespace statcalc {

    namespace files {
        
        void read_input(Dataset& p_dataset, int argc, const char** argv);
        void read_inputFiles(Vector<std::string>& p_files, int argc, const char** argv);

        void read_files(Dataset& p_dataset, const Vector<std::string>& p_files);
        void read_file(Dataset& p_dataset, const Text& p_fileName, bool p_header);
        void read_head(Vector<std::string>& p_header, const std::string& p_line);
        void read_line(Dataset& p_dataset, const Text& p_line, size_t p_row);
        void read_cell(Dataset& p_dataset, const Text& p_line, size_t p_column, size_t p_row, size_t p_start, size_t p_end);

    }

};

#endif