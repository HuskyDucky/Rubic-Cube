/**
    File    : rubik.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.25

    Version : 20250625.0

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

#include "../rubik_cube_engine/engine.h"

struct rubik : public rubik_engine
{
    rubik();
    rubik(uint16_t cube_size);

    void show();
};

#endif // RUBIK_CUBE_H
