#include <stat/statistical_analysis.h>

#include <win/Window.h>
#include <win/MenuBar.h>

static LRESULT CALLBACK WindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp);

// Public so that we can access it in other functions (I know a great sin, but the WINAPI library is not great.
Window* win = nullptr;

static int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

    // Create a window instance
    Window window(WindowProc, hPrevInstance);
    window.create(hInstance);
    window.show(nCmdShow);

    // Assign to pointer
    win = &window;
    if (win == nullptr) {
        return 1;
    }

    int status = window.loop();
    return status;
}

/* NOTES
 1. when googling for api docs, etc. prefix everything with msdn.  e.g: msdn winmain
 2. prefer msdn docs to stack overflow for most things.
    When in doubt look for Raymond Chen's blog "The Old New Thing."

 3. Overview of the event loop is at [1].
 4. This event-loop spins when no events are available, consuming all available cpu.
    Also see GetMessage, which blocks until the next message is received.

    Use PeekMessage when you want your application loop to do something while not recieving
    events from the message queue.  You would do that work after the while(PeekMessage(...))
    block.
*/
/* REFERENCES
  [1] : https://msdn.microsoft.com/en-us/library/windows/desktop/ms644927%28v=vs.85%29.aspx
  [2]: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633570(v=vs.85).aspx#designing_proc
*/


static LRESULT CALLBACK WindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    /* More info at [2] */
    switch (msg) {
        /*                                                              *
         * Add a win32 push button and do something when it's clicked.  *
         * Google will help you with the other widget types.  There are *
         * many tutorials.                                              *
         *                                                              */

        case WM_CREATE: {
            break;
        } 

        case WM_COMMAND: {
            switch (LOWORD(wp)) {

            case (UINT_PTR)SCALC::ADD_FILE: {
                break;
            }
                                         
            case (UINT_PTR)SCALC::CLEAR_DATASET: {
                break;
            }
            
            case (UINT_PTR)SCALC::EXIT: {
                PostQuitMessage(0);
                break;
            }
            
            // IF there is no code
            default: {
                break;
            }

            }
        } break;


        /*                                 */
        /* Minimally need the cases below: */
        /*                                 */
        case WM_CLOSE:
        {
            PostQuitMessage(0); break;
        }
        default:
        {
            return DefWindowProc(h, msg, wp, lp);
        }
    }
    return 0;
}