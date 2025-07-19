/**
    File    : rubik.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.25

    Version : 20250718.0

    Extends functionalities for Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef RUBIK_CUBE_H
#define RUBIK_CUBE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>

#include "../rubik_cube_engine/engine.h"

#include "../lib/coloring.h"

struct rubik : public rubik_engine
{
    rubik();
    rubik(uint8_t cube_size);

    void show_initial_positions();

    void show() const;
    void show(const term_color only_for_this_time);

    #ifdef DEBUG
        void show_Scan_mem() const;
    #endif

    void randomize();
    void randomize(uint8_t nofTimes);

    void setTermColor(term_color op);

    private:
        term_color applyTermColor;  // default is colored_letters

        void show(bool showMainCube) const;
};

#endif // RUBIK_CUBE_H
