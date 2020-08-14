//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_HELPERS_HH
#define FGUI_HELPERS_HH

// This is used to supress unused variable warnings
template <typename T>
inline void IGNORE_ARG(T&&) {};

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// These keys defaults to virtual key-codes from the Windows API (GetAsyncKeyState)
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
#define KEY_LCONTROL 162
#define KEY_RCONTROL 163
#define KEY_A 65
#define KEY_SPACE 32

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
#define KEY_LCONTROL 83
#define KEY_RCONTROL 84
#define KEY_A 11
#define KEY_SPACE 65
#endif

#ifdef FGUI_USE_D3D9
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace FGUI
{
  using FONT = ID3DXFont*;
}
#elif defined(FGUI_USE_D3D10)
#include <d3d10.h>
#include <d3dx10.h>

#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dx10.lib")

namespace FGUI
{
  using FONT = ID3DX10Font*;
}
#elif defined(FGUI_USE_OPENGL)

// TODO: OpenGL support
#elif defined(FGUI_USE_D2D)
#include <D2D1.h>
#include <unordered_map>
#include <dwrite_1.h>
#include <string_view>
#pragma comment( lib, "dxgi" )
#pragma comment( lib, "d2d1" )
#pragma comment( lib, "dcomp" )
#pragma comment( lib, "dwrite" )

typedef DWORD D3DCOLOR;

#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)

namespace FGUI {
  
  struct CFont {
    std::wstring name;
    float size;
    IDWriteTextFormat* textFmt;
  };

  using FONT = CFont*;
}
#else
namespace FGUI
{
  using FONT = unsigned long;
}
#endif

#endif // FGUI_HELPERS_HH
