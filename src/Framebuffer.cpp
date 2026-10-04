#include "Framebuffer.h"
#include <stdexcept>
#include <fstream>

Framebuffer::Framebuffer(int width, int height)
    :
        width(width),
        height(height),
        pixels(width * height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Framebuffer dimentions must be positive");
    }
}

void Framebuffer::setPixel(int x, int y, Color color)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
    {
        throw std::out_of_range("Pixel coordinates are outside the framebuffer.");
    }

    int index = y * width + x;
    pixels[index] = color;
}

Color Framebuffer::getPixel(int x, int y)
{
    if(x < 0 || x >= width || y < 0 || y >= height)
    {
        throw std::out_of_range("Pixel coordinates are outside the framebuffer.");
    }

    int index = y * width + x;
    return pixels[index];
}

bool Framebuffer::savePPM(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file)
    {
        return false;
    }

    file << "P3\n";
    file << width << ' ' << height << '\n';
    file << "255\n";

    for (int i = 0; i < height; ++i)
    {

        for (int j = 0; j < width; ++j)
            {
                Color color = getPixel(j, i);

                file << static_cast<int>(color.r) << ' '
                     << static_cast<int>(color.g) << ' '
                     << static_cast<int>(color.b) << ' ' << ' ';
            }

            file << '\n';

    }

    return true;
}

void Framebuffer::clear(Color color)
{
    for (Color& pixel : pixels)
    {
        pixel = color;
    }
}
