#pragma once


struct Vec2
{
    float x;
    float y;
};

Vec2 operator-(const Vec2& a, const Vec2& b);

Vec2 operator+(const Vec2& a, const Vec2& b);

float dot(const Vec2& a, const Vec2& b);