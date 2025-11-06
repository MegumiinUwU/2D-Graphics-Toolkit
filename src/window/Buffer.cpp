#include "../../include/Window.h"

// Create offscreen buffer for double buffering
void GraphicsWindow::CreateOffscreenBuffer(int width, int height) {
    CleanupOffscreenBuffer();
    
    m_canvasWidth = width;
    m_canvasHeight = height;
    
    HDC hdc = GetDC(m_hwnd);
    m_offscreenDC = CreateCompatibleDC(hdc);
    m_offscreenBitmap = CreateCompatibleBitmap(hdc, width, height);
    m_oldBitmap = (HBITMAP)SelectObject(m_offscreenDC, m_offscreenBitmap);
    ReleaseDC(m_hwnd, hdc);
    
    ClearOffscreenBuffer();
}

// Cleanup offscreen buffer
void GraphicsWindow::CleanupOffscreenBuffer() {
    if (m_offscreenDC) {
        if (m_oldBitmap) {
            SelectObject(m_offscreenDC, m_oldBitmap);
            m_oldBitmap = nullptr;
        }
        DeleteDC(m_offscreenDC);
        m_offscreenDC = nullptr;
    }
    if (m_offscreenBitmap) {
        DeleteObject(m_offscreenBitmap);
        m_offscreenBitmap = nullptr;
    }
}

// Clear offscreen buffer with background color
void GraphicsWindow::ClearOffscreenBuffer() {
    if (m_offscreenDC) {
        RECT rect = {0, 0, m_canvasWidth, m_canvasHeight};
        FillRect(m_offscreenDC, &rect, m_backgroundBrush);
    }
}
