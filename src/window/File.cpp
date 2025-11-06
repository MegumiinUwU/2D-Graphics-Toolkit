#include "../../include/Window.h"

// Save to file
void GraphicsWindow::SaveToFile() {
    OPENFILENAME ofn;              
    char szFile[MAX_PATH] = "";   

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hwnd;  
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);

    ofn.lpstrFilter = "binary Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = "bin";
    ofn.lpstrTitle = "Save Drawing As";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileName(&ofn)) {
        std::ofstream outFile(szFile, std::ios::binary);
        if (!outFile) {
            MessageBox(m_hwnd, "Failed to open file for writing.", "Error", MB_OK | MB_ICONERROR);
            return;
        }

        int shapeCnt = m_shapes.size();
        outFile.write(reinterpret_cast<const char*>(&shapeCnt), sizeof(shapeCnt));

        for(auto& shape:m_shapes) {
            outFile.write(reinterpret_cast<const char*>(&shape.mode), sizeof(shape.mode));
            outFile.write(reinterpret_cast<const char*>(&shape.color), sizeof(shape.color));
            outFile.write(reinterpret_cast<const char*>(&shape.fillMode), sizeof(shape.fillMode));
            outFile.write(reinterpret_cast<const char*>(&shape.thickness), sizeof(shape.thickness));

            int pointCnt = shape.points.size();
            outFile.write(reinterpret_cast<const char*>(&pointCnt), sizeof(pointCnt));

            if (pointCnt > 0) {
                outFile.write(reinterpret_cast<const char*>(shape.points.data()), pointCnt * sizeof(Point));
            }
        }
        
        outFile.close();
    }
}

// Load from file
void GraphicsWindow::LoadFromFile() {
    OPENFILENAME ofn;
    char szFile[MAX_PATH] = "";

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = m_hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);

    ofn.lpstrFilter = "Binary Files (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = "bin";
    ofn.lpstrTitle = "Open Drawing";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        std::ifstream inFile(szFile, std::ios::binary);
        if (!inFile) {
            MessageBox(m_hwnd, "Failed to open file for reading.", "Error", MB_OK | MB_ICONERROR);
            return;
        }

        ClearCanvas();

        int shapeCnt = 0;
        inFile.read(reinterpret_cast<char*>(&shapeCnt), sizeof(shapeCnt));
        for (int i = 0; i < shapeCnt; ++i) {
            Shape shape;

            inFile.read(reinterpret_cast<char*>(&shape.mode), sizeof(shape.mode));
            inFile.read(reinterpret_cast<char*>(&shape.color), sizeof(shape.color));
            inFile.read(reinterpret_cast<char*>(&shape.fillMode), sizeof(shape.fillMode));
            inFile.read(reinterpret_cast<char*>(&shape.thickness), sizeof(shape.thickness));

            int pointCnt = 0;
            inFile.read(reinterpret_cast<char*>(&pointCnt), sizeof(pointCnt));

            shape.points.resize(pointCnt);
            if (pointCnt > 0) {
                inFile.read(reinterpret_cast<char*>(shape.points.data()), pointCnt * sizeof(Point));
            }
            m_shapes.push_back(shape);
        }
        inFile.close();
        InvalidateRect(m_hwnd, nullptr, TRUE);
        RedrawAll();
        RebuildOffscreenBuffer();
        InvalidateRect(m_hwnd, NULL, TRUE);
    }
}
