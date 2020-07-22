//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_HELPERS_HH
#define FGUI_HELPERS_HH

// This is used to supress unused variable warnings
template <typename T>
inline void IGNORE(T &&){};

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// These keys defaults to virtual key-codes from WindowsAPI (GetAsyncKeyState)
#define MOUSE_1 1
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_LSHIFT 160
#define KEY_RSHIFT 161
#define KEY_DELETE 46
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define KEY_PAGEUP 33
#define KEY_PAGEDOWN 34
#else
// These keys defaults to virtual key-codes from Source Engine (IInputSystem)
#define MOUSE_1 107
#define KEY_ESCAPE 70
#define KEY_ENTER 64
#define KEY_BACKSPACE 66
#define KEY_LSHIFT 79
#define KEY_RSHIFT 80
#define KEY_DELETE 73
#define KEY_LEFT 89
#define KEY_RIGHT 91
#define KEY_PAGEUP 76
#define KEY_PAGEDOWN 77
#endif

#ifdef FGUI_USE_D3D9
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace FGUI
{
  using FONT = ID3DXFont *;
}
#elif defined(FGUI_USE_D3D10)
#include <d3d10.h>
#include <d3dx10.h>

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")

namespace FGUI
{
  using FONT = ID3DX10Font *;
}
#elif defined(FGUI_USE_OPENGL)

// TODO: OpenGL support

#else
namespace FGUI
{
  using FONT = unsigned long;
}
#endif

#endif // FGUI_HELPERS_HH