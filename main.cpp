#include "include/GraphicsWindow.h"
#include <windows.h>

// ========================================
// MAIN FUNCTION - DEMO USAGE
// ========================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Create and run the graphics window
    GraphicsWindow* window = CreateGraphicsWindow(hInstance, nCmdShow, "2D Graphics Demo");
    if (!window) {
        MessageBox(NULL, "Failed to create graphics window!", "Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    return RunGraphicsProgram(window);
} 