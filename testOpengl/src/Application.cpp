#include "Window.h"
#include <Windows.h>

int main(void)
{
	FreeConsole();
	if(!Window::Render())
		return 0;
}