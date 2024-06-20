#include <structures/Exception.h>

const char* OutOfRange::what() const { return "\nERROR: Out of Range!\n"; }
const char* BadAlloc::what() const { return "\nERROR: Bad Memory Allocation!\n"; };