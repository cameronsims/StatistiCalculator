#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <framework.h>

#include <stat/Dataset.h>
#include <file/file_errors.h>

#include <stat/DataIO.h>
#include <stat/TextIO.h>
#include <stat/StatIO.h>

namespace statcalc {

    namespace files {

        void read_input(Dataset& p_dataset, size_t argc, const wchar_t** argv);
        void read_inputFiles(Vector<std::wstring>& p_files, size_t argc, const wchar_t** argv);
        void read_files(Dataset& p_dataset, const Vector<std::wstring>& p_files);
        void read_file(Dataset& p_dataset, const std::wstring& p_fileName, bool p_header);
        void read_head(Vector<std::wstring>& p_header, const std::wstring& p_line);
        void read_line(Dataset& p_dataset, const std::wstring& p_line, size_t p_row);
        void read_cell(Dataset& p_dataset, const std::wstring& p_line, size_t p_column, size_t p_row, size_t p_start, size_t p_end);

    }

};

#endif