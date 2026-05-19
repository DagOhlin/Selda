#pragma once 

#include <raylib.h>

struct BoxCollider
{
    /* data */
    Vector2 size;
    Vector2 offset;
    bool solid;
};
