#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#define UNICODE
#include <windows.h>

#include <stat/Dataset.h>

class Window {
public:

    Window();
    Window(WNDPROC p_hWinProc, HINSTANCE p_hPrev);
    ~Window();

    void create(HINSTANCE p_hInst);
    void show(int p_showCMD);

    int loop();
    void exit();
private:

    void m_createMenuBar();
    void m_createButtons();

    HWND m_window;
    statcalc::Dataset m_data;
};

#endif