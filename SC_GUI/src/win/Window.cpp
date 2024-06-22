#include <file/file_parser.h>
#include <stat/statistical_analysis.h>

#include <win/Window.h>
#include <win/MenuBar.h>



Window::Window() {}

Window::Window(WNDPROC p_hWinProc, HINSTANCE p_hPrev) {
    // Set dataset to null
    m_data = statcalc::Dataset();
    // Create instance
    if (!p_hPrev) {
        WNDCLASS c = { 0 };
        c.lpfnWndProc = p_hWinProc;
        c.hInstance = p_hPrev;
        c.hIcon = LoadIcon(0, IDI_APPLICATION);
        c.hCursor = LoadCursor(0, IDC_ARROW);
        // c.hbrBackground = GetStockObject(WHITE_BRUSH);
        c.lpszClassName = L"MainWindow";
        RegisterClassW(&c);
    }
}

Window::~Window() {
    this->exit();
}

void Window::create(HINSTANCE p_hInst) {
    // Varialbes
    UINT_PTR x      = CW_USEDEFAULT, 
             y      = CW_USEDEFAULT,
             width  = 512,
             height = 512;
    
    // Create a window
    m_window = CreateWindowW(L"MainWindow", L"StatistiCalculator", WS_OVERLAPPEDWINDOW, x, y, width, height, 0, 0, p_hInst, 0);
    m_createMenuBar();
    m_createButtons();
}

void Window::show(int p_showCMD) {
    if (m_window == NULL) {
        throw 1;
    }

    ShowWindow(m_window, p_showCMD);
}

int Window::loop() {
    MSG msg;
    while (GetMessageW(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    
    return 0;
}

void Window::exit() {
    PostQuitMessage(0);
}



void Window::m_createMenuBar() {
    HMENU hMenu = MenuBar_create();
    SetMenu(m_window, hMenu);
    DrawMenuBar(m_window);
}



void Window::m_createButtons() {
    constexpr int BUTTON_PADDING = 10;
    constexpr int BUTTON_WIDTH = 100;
    constexpr int BUTTON_HEIGHT = 20;

    constexpr size_t BUTTON_SIZE = 3;
    constexpr size_t BUTTON_BUFFER = 16;

    const WCHAR BUTTON_NAMES[BUTTON_SIZE][BUTTON_BUFFER] = {
         L"Mean",
         L"Stdev",
         L"Variance"
    };

    HWND button;
    for (size_t i = 0; i < BUTTON_SIZE; i++) {
        const int x = i * (BUTTON_WIDTH + BUTTON_PADDING) + BUTTON_PADDING;
        const int y = BUTTON_PADDING;

        button = CreateWindowW(L"Button", BUTTON_NAMES[i], WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                               x, y, BUTTON_WIDTH, BUTTON_HEIGHT,
                               m_window, NULL, (HINSTANCE)GetWindowLongPtr(m_window, GWLP_HINSTANCE), NULL);
    }

    WCHAR str[32];
    m_data = statcalc::Dataset();
    for (size_t i = 0; i < 256; i++) {
        m_data.data[0].push((double)i);
    }

    swprintf(str, L"%llu", m_data.data[0].size());

    HWND stat = CreateWindowW(L"Static", str, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                             0, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
                             m_window, NULL, (HINSTANCE)GetWindowLongPtr(m_window, GWLP_HINSTANCE), NULL);
    
    swprintf(str, L"%0.3f", statcalc::mean(m_data.data[0]));

         stat = CreateWindowW(L"Static", str, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                             110, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
                             m_window, NULL, (HINSTANCE)GetWindowLongPtr(m_window, GWLP_HINSTANCE), NULL);

    swprintf(str, L"%0.3f", statcalc::stdev(m_data.data[0]));

         stat = CreateWindowW(L"Static", str, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                             220, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
                             m_window, NULL, (HINSTANCE)GetWindowLongPtr(m_window, GWLP_HINSTANCE), NULL);

    swprintf(str, L"%.03f", statcalc::variance(m_data.data[0]));

         stat = CreateWindowW(L"Static", str, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                             330, 30, BUTTON_WIDTH, BUTTON_HEIGHT,
                             m_window, NULL, (HINSTANCE)GetWindowLongPtr(m_window, GWLP_HINSTANCE), NULL);
}

