#pragma once

#include <vector>
#include "Color.h"
#include <string>

class Framebuffer
{
    public:
        Framebuffer(int width, int height);

        void setPixel(int width, int height, Color color);
        Color getPixel(int width, int height);

        bool savePPM(const std::string& filename);

    private:
        int width;
        int height;
        std::vector<Color> pixels;
    
};
