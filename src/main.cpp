#include "Color.h"
#include "Display.h"
#include "Framebuffer.h"
#include "Rasterizer.h"

int main()
{
    constexpr int width = 800;
    constexpr int height = 600;

    Framebuffer framebuffer(width, height);
    Display display(width, height);

    Color black{0, 0, 0};
    Color white{255, 255, 255};

    while (display.isRunning())
    {
        display.processEvents();

        framebuffer.clear(black);

        display.present(framebuffer);
    }

    return 0;
}