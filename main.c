#include <stdio.h>
#include <windows.h>



int main() {
    HDC hdc = GetDC(NULL);

    const int centerX = GetSystemMetrics(SM_CXSCREEN) / 2 - 1;
    const int centerY = GetSystemMetrics(SM_CYSCREEN) / 2 - 1;
    COLORREF currentColor = GetPixel(hdc, centerX, centerY);
    COLORREF color;


    printf("Press F2 to capture initial color and monitor changes...\n");

    while (1) {
        if (GetAsyncKeyState(VK_XBUTTON1) & 0x8001) {
            currentColor = GetPixel(hdc, centerX, centerY);
            printf("Initial color remembered\n");
            while (GetAsyncKeyState(VK_XBUTTON1) & 0x8001) {
                color = GetPixel(hdc, centerX, centerY);

                if (abs((GetRValue(color) - GetRValue(currentColor)) * (GetGValue(color) - GetGValue(currentColor)) * (GetBValue(color) - GetBValue(currentColor))) > 1000) {
                    printf("SHOT!!!");
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    Sleep(250);
                    currentColor = GetPixel(hdc, centerX, centerY);
                }
            }
        }
    }

    return 0;
}
