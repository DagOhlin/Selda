#pragma once 

#include <raylib.h>

#include <string>

struct Text
{
    /* data */
    Color color;
    std::string text;
    Vector2 pos;
    float fontSize;
};
