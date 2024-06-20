#include <file/file_errors.h>

const char* FileNotFound::what() const { return "\nFile not found!\n"; }
const char* FileBadFormat::what() const { return "\nFile has bad formatting!\n"; }