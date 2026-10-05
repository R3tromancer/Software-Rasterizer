#include "Display.h"

#include <cstdint>
#include <stdexcept>

#include "Color.h"
#include "Framebuffer.h"

Display::Display(int width, int height)
    :width(width),
    height(height),
    window(nullptr),
    renderer(nullptr),
    texture(nullptr),
    running(false)
{
    if (!SDL_CreateWindowAndRenderer(
        "Software Rasterizer",
        width,
        height,
        0,
        &window,
        &renderer))
    {
        SDL_Quit();
        throw std::runtime_error(SDL_GetError());
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );

    if (texture == nullptr)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        throw std::runtime_error(SDL_GetError());
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    running = true;

}

Display::~Display()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Display::isRunning() const
{
    return running;
}

void Display::processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
        {
            running = false;
        }
    }
}

void Display::present(const Framebuffer& framebuffer)
{
    if (framebuffer.getWidth() != width ||
        framebuffer.getHeight() != height)
    {
        throw std::runtime_error(
            "Framebuffer dimensions do not match the display."
        );
    }

    void* texturePixels = nullptr;
    int pitch = 0;

    if (!SDL_LockTexture(
            texture,
            nullptr,
            &texturePixels,
            &pitch))
    {
        throw std::runtime_error(SDL_GetError());
    }

    auto* destination =
        static_cast<std::uint8_t*>(texturePixels);

    const auto& source = framebuffer.getPixels();

    for (int y = 0; y < height; ++y)
    {
        std::uint8_t* row =
            destination + y * pitch;

        for (int x = 0; x < width; ++x)
        {
            const Color& color =
                source[y * width + x];

            row[x * 3 + 0] = color.r;
            row[x * 3 + 1] = color.g;
            row[x * 3 + 2] = color.b;
        }
    }

    SDL_UnlockTexture(texture);

    SDL_RenderTexture(
        renderer,
        texture,
        nullptr,
        nullptr
    );

    SDL_RenderPresent(renderer);
}