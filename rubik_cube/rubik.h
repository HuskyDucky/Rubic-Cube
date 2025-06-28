/**
    File    : rubik.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.25

    Version : 20250628.0

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

#include "../rubik_cube_engine/engine.h"

enum term_color
{
    black_white,
    colored_letters,
    colored_positions
};

struct rubik : public rubik_engine
{
    rubik();
    rubik(uint16_t cube_size);

    void show_initial_positions();

    void show();
    void show(term_color only_for_this_time);

    void randomize();
    void randomize(uint16_t nofTimes);

    void setTermColor(term_color op);

    private:
        term_color applyTermColor;  // default is colored_letters

        const char* colorize (const char c) const;
};

#endif // RUBIK_CUBE_H
