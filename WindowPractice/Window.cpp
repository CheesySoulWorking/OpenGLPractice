#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "triangle.h"
#include "grid.h"
#include "matrix4.h"
#include "camera.h"
#include "math.h"
#include "load_shader.h"
#include "model.h"
#include "custom_model.h"

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

    // Set up 3D scene
    // ===========================================================================================================
    
    // Load Shaders
    std::string cubePhongVertSrc = LoadShaderSource("Shaders/phong.vert");
    std::string cubePhongFragSrc = LoadShaderSource("Shaders/phong.frag");
    const char* cubePhongVertShader = cubePhongVertSrc.c_str();
    const char* cubePhongFragShader = cubePhongFragSrc.c_str();

    std::string legoshiPhongVertSrc = LoadShaderSource("Shaders/phong.vert");
    std::string legoshiPhongFragSrc = LoadShaderSource("Shaders/phong.frag");
    const char* legoshiPhongVertShader = legoshiPhongVertSrc.c_str();
    const char* legoshiPhongFragShader = legoshiPhongFragSrc.c_str();

    std::string rainbowVertSrc = LoadShaderSource("Shaders/rainbow.vert");
    std::string rainbowFragSrc = LoadShaderSource("Shaders/rainbow.frag");
    const char* rainbowVertShader = rainbowVertSrc.c_str();
    const char* rainbowFragShader = rainbowFragSrc.c_str();


    std::string gridVertSrc = LoadShaderSource("Shaders/flat.vert");
    std::string gridFragSrc = LoadShaderSource("Shaders/flat.frag");
    const char* gridVertShader = gridVertSrc.c_str();
    const char* gridFragShader = gridFragSrc.c_str();
    
    
    // Set up scene projection method (in this case, perspective projection)
    float aspectRatio = (float)WIDTH / (float)HEIGHT;
    Matrix4 projectionMatrix = Matrix4();
    projectionMatrix.makePerspective(45.0f, aspectRatio, 0.1, 1000.0);

    // Create Camera
    Camera camera = Camera();
    camera.cameraPosition = Vector3(0, 0, 20);

    // Create Light Sources (Directional = sun, positional = point light)
    Vector3 directionalLightDirection = Vector3(0.5, 2, 1);
    Vector3 positionalLightSrc = Vector3(2, 0, 2);
    
    // Initialize 3D Objects
    Model legoshiData = loadOBJ("Models/legoshi.obj");
    Model cubeData = loadOBJ("Models/cube.obj");
    OpenGLModel cube = InitModel(cubeData, cubePhongVertShader, cubePhongFragShader);
    OpenGLModel legoshi = InitModel(legoshiData, legoshiPhongVertShader, legoshiPhongFragShader);
    OpenGLResourcesGrid grid = InitGrid(gridVertShader, gridFragShader);

    legoshi.worldMatrix.makeIdentity().multiply(Matrix4().makeTranslation(1, 0, 0)).multiply(Matrix4().makeScale(0.3, 0.3, 0.3));
    cube.worldMatrix.makeIdentity().multiply(Matrix4().makeTranslation(-1, 0, 0));
    camera.cameraWorldMatrix.makeIdentity();
    camera.cameraWorldMatrix.multiply(Matrix4().makeRotationY(45));
    camera.cameraWorldMatrix.multiply(Matrix4().makeTranslation(0, 0, 5));


    // Set background color, and enable depth test for objects being rendered in front or back.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Loop to draw triangle
    // ===========================================================================================================
    MSG msg = {};
    while (true)
    {
        float time = GetTickCount() / 1000.0f;

        /*camera.cameraWorldMatrix.makeIdentity();
        camera.cameraWorldMatrix.multiply(Matrix4().makeRotationY(time * 50));
        camera.cameraWorldMatrix.multiply(Matrix4().makeTranslation(0, 0, 5));*/

        /*directionalLightDirection.x = sin(time) * 10;
        directionalLightDirection.z = cos(time) * 50;*/

        positionalLightSrc.x = sin(time) * 5;
        positionalLightSrc.z = cos(time) * 5;

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //DrawTriangle(glr, hdc, camera, projectionMatrix, time);
        DrawGrid(grid, hdc, camera, projectionMatrix);
        DrawModel(cube, hdc, camera, projectionMatrix, time, directionalLightDirection, positionalLightSrc);
        DrawModel(legoshi, hdc, camera, projectionMatrix, time, directionalLightDirection, positionalLightSrc);

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