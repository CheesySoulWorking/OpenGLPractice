#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "triangle.h"
#include "grid.h"
//#include "vector3.h"
//#include "vector4.h"
#include "matrix4.h"
#include "camera.h"
#include "math.h"

extern int WIDTH = 1920;
extern int HEIGHT = 1080;


// Handles messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Similar to main, but special
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

    // Register the window class.
    // ===========================================================================================================
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Some App",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    HDC hdc = GetDC(hwnd);

    // Context setup for OpenGL using glew
    // ===========================================================================================================
    // Pixel Format
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);

    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);

    glewInit();

    // Loop to draw triangle
    // ===========================================================================================================
    Matrix4 projectionMatrix = Matrix4();
    Camera camera = Camera();
    camera.cameraPosition = Vector3(0, 0, 20);
    OpenGLResources glr = InitTriangle();
    OpenGLResourcesGrid grid = InitGrid();
    //OpenGLResources grid = InitGrid();

    float aspectRatio = (float)WIDTH / (float)HEIGHT;
    projectionMatrix.makePerspective(45.0f, aspectRatio, 0.1, 1000.0);

    // Set background color, and enable depth test for objects being rendered in front or back.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    MSG msg = {};
    while (true)
    {
        float time = GetTickCount() / 1000.0f;
        camera.cameraWorldMatrix.makeIdentity();
        camera.cameraWorldMatrix.multiply(Matrix4().makeRotationY(time * 50));
        //camera.cameraWorldMatrix.multiply(Matrix4().makeRotationX(time * 50));
        camera.cameraWorldMatrix.multiply(Matrix4().makeTranslation(0, 0, 5));
        //glr.worldMatrix.makeIdentity().multiply(Matrix4().makeTranslation(0, 0, -(sin(time))));
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        DrawTriangle(glr, hdc, camera, projectionMatrix, time);
        DrawGrid(grid, hdc, camera, projectionMatrix);

        SwapBuffers(hdc);
    }


    // Clean up wgl when done here for now?
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        HBRUSH brush = CreateSolidBrush(RGB(100, 149, 237));
        FillRect(hdc, &ps.rcPaint,brush);
        DeleteObject(brush);

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}