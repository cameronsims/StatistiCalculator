#include <win/MenuBar.h>

HMENU MenuBar_create() {
    // Menu bar names 
    constexpr size_t MENUBAR_STRING_BUFFER = 16;
    constexpr size_t MENUBAR_ITEMS = 2;
    const WCHAR hMenuBarNames[MENUBAR_ITEMS][MENUBAR_STRING_BUFFER] = {
        L"&File",
        L"&Help"
    };

    // FILE ///////////////////////////////////////////////////////////////////

    constexpr size_t MENUBAR_FILE_ITEMS = 3;
    const WCHAR hMenuFileNames[MENUBAR_FILE_ITEMS][MENUBAR_STRING_BUFFER] = {
        L"Add File",
        L"Clear Dataset",
        L"Exit"
    };

    // Add New Menubar
    HMENU hMenuBar = CreateMenu();
    HMENU hMenuFile = CreateMenu();

    // Add file items
    for (size_t i = 0; i < MENUBAR_FILE_ITEMS; i++) {
        AppendMenuW(hMenuFile, MF_STRING, (UINT_PTR)i, hMenuFileNames[i]);
    }

    ///////////////////////////////////////////////////////////////////////////

    AppendMenuW(hMenuBar, MF_POPUP, (UINT_PTR)hMenuFile, hMenuBarNames[0]);

    return hMenuBar;
}