#include "Window.h"
#include <Windows.h>

int main(void)
{
	if(!Window::Render())
		return 0;
}