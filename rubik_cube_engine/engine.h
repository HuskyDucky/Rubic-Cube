/**
    File    : engine.h
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250628.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef ENGINE_H
#define ENGINE_H

#include <cinttypes>
#include <cstring>
#include <vector>
#include <list>

#include <iostream>

#include "general.h"
#include "class_color.h"

using namespace std;

struct history
{
    to direction;
    uint16_t xyz;
};

struct rubik_engine
{
    rubik_engine();
    rubik_engine(uint16_t Cube_Size);

    void spin(to direction, uint16_t xyz);   // xyz starts at 0 and the last value is the cube size -1.
                                             // (ex.: for cube(3) xyz must be >= 0 and < 3)

    uint16_t size() const;

    const list<history>& get_Spin_history() const;

    void reset();
    void recreate(uint16_t Cube_Size);

    protected:

        color block(uint16_t line, uint16_t column, uint16_t layer) const;

    private:
        uint16_t CS;    // cube size

        color auxSpin;  // help the spin_ functions
        inline void spin_right(uint16_t x);
        inline void spin_left(uint16_t x);
        inline void spin_up(uint16_t y);
        inline void spin_down(uint16_t y);
        inline void spin_clockwise(uint16_t z);
        inline void spin_anticlockwise(uint16_t z);

        list<history> spin_history;

        vector<vector<vector<color>>> CUBE;
};

#endif // ENGINE_H
