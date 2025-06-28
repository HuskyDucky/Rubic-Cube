/**
    File    : spin.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.24

    Version : 20250628.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "engine.h"

void rubik_engine::spin(to direction, uint16_t xyz)
{
    if (xyz <= CS)
    {
        switch (direction)
        {
            case to::up        : spin_up(xyz); break;
            case to::left      : spin_left(xyz); break;
            case to::down      : spin_down(xyz); break;
            case to::right     : spin_right(xyz); break;
            case to::clockwise : spin_clockwise(xyz); break;
            default            : spin_anticlockwise(xyz);
        }

        spin_history.push_back({direction, xyz});
    }
}

inline void rubik_engine::spin_right(uint16_t x)
{
    for (uint16_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][x][idx];      auxSpin.spinColor(to::right);
        CUBE[0][x][idx]     = CUBE[CS-idx][x][0];   CUBE[0][x][idx].spinColor(to::right);
        CUBE[CS-idx][x][0]  = CUBE[CS][x][CS-idx];  CUBE[CS-idx][x][0].spinColor(to::right);
        CUBE[CS][x][CS-idx] = CUBE[idx][x][CS];     CUBE[CS][x][CS-idx].spinColor(to::right);
        CUBE[idx][x][CS]    = auxSpin;
    }
}

inline void rubik_engine::spin_down(uint16_t y)
{
    for (uint16_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][idx][y];      auxSpin.spinColor(to::down);
        CUBE[0][idx][y]     = CUBE[CS-idx][0][y];   CUBE[0][idx][y].spinColor(to::down);
        CUBE[CS-idx][0][y]  = CUBE[CS][CS-idx][y];  CUBE[CS-idx][0][y].spinColor(to::down);
        CUBE[CS][CS-idx][y] = CUBE[idx][CS][y];     CUBE[CS][CS-idx][y].spinColor(to::down);
        CUBE[idx][CS][y]    = auxSpin;
    }
}

inline void rubik_engine::spin_clockwise(uint16_t z)
{
    for (uint16_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[z][0][idx];      auxSpin.spinColor(to::clockwise);
        CUBE[z][0][idx]     = CUBE[z][CS-idx][0];   CUBE[z][0][idx].spinColor(to::clockwise);
        CUBE[z][CS-idx][0]  = CUBE[z][CS][CS-idx];  CUBE[z][CS-idx][0].spinColor(to::clockwise);
        CUBE[z][CS][CS-idx] = CUBE[z][idx][CS];     CUBE[z][CS][CS-idx].spinColor(to::clockwise);
        CUBE[z][idx][CS]    = auxSpin;
    }
}

inline void rubik_engine::spin_left(uint16_t x)
{
    for (uint16_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][x][idx];      auxSpin.spinColor(to::left);
        CUBE[0][x][idx]     = CUBE[idx][x][CS];     CUBE[0][x][idx].spinColor(to::left);
        CUBE[idx][x][CS]    = CUBE[CS][x][CS-idx];  CUBE[idx][x][CS].spinColor(to::left);
        CUBE[CS][x][CS-idx] = CUBE[CS-idx][x][0];   CUBE[CS][x][CS-idx].spinColor(to::left);
        CUBE[CS-idx][x][0]  = auxSpin;
    }
}

inline void rubik_engine::spin_up(uint16_t y)
{
    for (uint16_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[0][idx][y];      auxSpin.spinColor(to::up);
        CUBE[0][idx][y]     = CUBE[idx][CS][y];     CUBE[0][idx][y].spinColor(to::up);
        CUBE[idx][CS][y]    = CUBE[CS][CS-idx][y];  CUBE[idx][CS][y].spinColor(to::up);
        CUBE[CS][CS-idx][y] = CUBE[CS-idx][0][y];   CUBE[CS][CS-idx][y].spinColor(to::up);
        CUBE[CS-idx][0][y]  = auxSpin;
    }
}

inline void rubik_engine::spin_anticlockwise(uint16_t z)
{
    for (uint16_t idx = 0; idx != CS; idx++)
    {
        auxSpin             = CUBE[z][0][idx];      auxSpin.spinColor(to::anticlockwise);
        CUBE[z][0][idx]     = CUBE[z][idx][CS];     CUBE[z][0][idx].spinColor(to::anticlockwise);
        CUBE[z][idx][CS]    = CUBE[z][CS][CS-idx];  CUBE[z][idx][CS].spinColor(to::anticlockwise);
        CUBE[z][CS][CS-idx] = CUBE[z][CS-idx][0];   CUBE[z][CS][CS-idx].spinColor(to::anticlockwise);
        CUBE[z][CS-idx][0]  = auxSpin;
    }
}
