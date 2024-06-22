#ifndef WIN_MENUBAR_H
#define WIN_MENUBAR_H

#include <windows.h>

enum class SCALC {
    ADD_FILE = 0,
    CLEAR_DATASET,
    EXIT
};

HMENU MenuBar_create();

#endif