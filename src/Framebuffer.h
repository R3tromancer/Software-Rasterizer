#pragma once

#include <vector>
#include "Color.h"
#include <string>

class Framebuffer
{
    public:
        Framebuffer(int width, int height);

        void setPixel(int width, int height, Color color);
        Color getPixel(int width, int height) const;

        bool savePPM(const std::string& filename) const;
        
        void clear(Color color);

        int getWidth() const;
        int getHeight() const;

        const std::vector<Color>& getPixels() const;

    private:
        int width;
        int height;
        std::vector<Color> pixels;
    
};
