#pragma once

struct vec2
{
    float x;
    float y;

    vec2() { x=y=0; }

    vec2(float _x, float _y): x(_x), y(_y) {}

    ~vec2() {}
};

vec2 operator+(vec2 v0, vec2 v1) { return vec2(v0.x+v1.x, v0.y+v1.y); }

vec2 operator-(vec2 v0, vec2 v1) { return vec2(v0.x-v1.x, v0.y-v1.y); }

vec2 operator*(vec2 v, float f) { return vec2(v.x*f, v.y*f); }

vec2 operator*(float f, vec2 v) { return v*f; }

vec2 operator/(vec2 v, float f) { return vec2(v.x/f, v.y/f); }