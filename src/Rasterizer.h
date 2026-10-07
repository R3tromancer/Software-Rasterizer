#pragma once

class Framebuffer;

struct Color;

void drawLine(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    Color color
);

void drawTriangle(
    Framebuffer& framebuffer,
    int x0,
    int y0,
    int x1,
    int y1,
    int x2,
    int y2,
    Color color
);