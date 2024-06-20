#ifndef FILE_ERRORS_H
#define FILE_ERRORS_H

#include <structures/Exception.h>

class FileError : public Exception {};

class FileNotFound : public FileError {
public:
    const char* what() const;
};

class FileBadFormat : public FileError {
public:
    const char* what() const;
};

#endif