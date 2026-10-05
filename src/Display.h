#pragma once

#include <SDL3/SDL.h>

class Framebuffer;

class Display
{
    public:
    Display(int width, int height);
    ~Display();

    bool isRunning() const;

    void present(const Framebuffer& framebuffer);


    private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    bool running;


};