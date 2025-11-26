//main.h
#include <GLFW/glfw3.h>

namespace setting {
	inline bool m_VSync = true;
}

bool CreateDeviceD3D();
void CleanupDeviceD3D();
bool CreateRenderResources(UINT w, UINT h);
void CleanupRenderResources();
void RenderAndUpdateLayeredWindow();

extern ImFont* G_DefaultFont;
extern ImFont* G_HugeFont;

//extern GLFWwindow* g_Window;