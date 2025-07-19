/**
    File    : spin.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.24

    Version : 20250628.3

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "engine.h"

void rubik_engine::spin(const colors::to direction, const uint8_t xyz)
{
    if (xyz <= CS)
    {
        switch (direction)
        {
            case colors::to::up        : spin_up(xyz); break;
            case colors::to::left      : spin_left(xyz); break;
            case colors::to::down      : spin_down(xyz); break;
            case colors::to::right     : spin_right(xyz); break;
            case colors::to::clockwise : spin_clockwise(xyz); break;
            default                    : spin_anticlockwise(xyz);
        }

        spin_history.push_back({direction, xyz});
    }
}

inline void rubik_engine::spin_right(const uint8_t x)
{
    for (uint8_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][x][idx];      auxSpin.spin(colors::to::right);
        CUBE[0][x][idx]     = CUBE[CS-idx][x][0];   CUBE[0][x][idx].spin(colors::to::right);
        CUBE[CS-idx][x][0]  = CUBE[CS][x][CS-idx];  CUBE[CS-idx][x][0].spin(colors::to::right);
        CUBE[CS][x][CS-idx] = CUBE[idx][x][CS];     CUBE[CS][x][CS-idx].spin(colors::to::right);
        CUBE[idx][x][CS]    = auxSpin;
    }
}

inline void rubik_engine::spin_down(const uint8_t y)
{
    for (uint8_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][idx][y];      auxSpin.spin(colors::to::down);
        CUBE[0][idx][y]     = CUBE[CS-idx][0][y];   CUBE[0][idx][y].spin(colors::to::down);
        CUBE[CS-idx][0][y]  = CUBE[CS][CS-idx][y];  CUBE[CS-idx][0][y].spin(colors::to::down);
        CUBE[CS][CS-idx][y] = CUBE[idx][CS][y];     CUBE[CS][CS-idx][y].spin(colors::to::down);
        CUBE[idx][CS][y]    = auxSpin;
    }
}

inline void rubik_engine::spin_clockwise(const uint8_t z)
{
    for (uint8_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[z][0][idx];      auxSpin.spin(colors::to::clockwise);
        CUBE[z][0][idx]     = CUBE[z][CS-idx][0];   CUBE[z][0][idx].spin(colors::to::clockwise);
        CUBE[z][CS-idx][0]  = CUBE[z][CS][CS-idx];  CUBE[z][CS-idx][0].spin(colors::to::clockwise);
        CUBE[z][CS][CS-idx] = CUBE[z][idx][CS];     CUBE[z][CS][CS-idx].spin(colors::to::clockwise);
        CUBE[z][idx][CS]    = auxSpin;
    }
}

inline void rubik_engine::spin_left(const uint8_t x)
{
    for (uint8_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][x][idx];      auxSpin.spin(colors::to::left);
        CUBE[0][x][idx]     = CUBE[idx][x][CS];     CUBE[0][x][idx].spin(colors::to::left);
        CUBE[idx][x][CS]    = CUBE[CS][x][CS-idx];  CUBE[idx][x][CS].spin(colors::to::left);
        CUBE[CS][x][CS-idx] = CUBE[CS-idx][x][0];   CUBE[CS][x][CS-idx].spin(colors::to::left);
        CUBE[CS-idx][x][0]  = auxSpin;
    }
}

inline void rubik_engine::spin_up(const uint8_t y)
{
    for (uint8_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][idx][y];      auxSpin.spin(colors::to::up);
        CUBE[0][idx][y]     = CUBE[idx][CS][y];     CUBE[0][idx][y].spin(colors::to::up);
        CUBE[idx][CS][y]    = CUBE[CS][CS-idx][y];  CUBE[idx][CS][y].spin(colors::to::up);
        CUBE[CS][CS-idx][y] = CUBE[CS-idx][0][y];   CUBE[CS][CS-idx][y].spin(colors::to::up);
        CUBE[CS-idx][0][y]  = auxSpin;
    }
}

inline void rubik_engine::spin_anticlockwise(const uint8_t z)
{
    for (uint8_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[z][0][idx];      auxSpin.spin(colors::to::anticlockwise);
        CUBE[z][0][idx]     = CUBE[z][idx][CS];     CUBE[z][0][idx].spin(colors::to::anticlockwise);
        CUBE[z][idx][CS]    = CUBE[z][CS][CS-idx];  CUBE[z][idx][CS].spin(colors::to::anticlockwise);
        CUBE[z][CS][CS-idx] = CUBE[z][CS-idx][0];   CUBE[z][CS][CS-idx].spin(colors::to::anticlockwise);
        CUBE[z][CS-idx][0]  = auxSpin;
    }
}
