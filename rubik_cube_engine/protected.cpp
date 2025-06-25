/**
    File    : protected.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.25

    Version : 20250625.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "engine.h"

uint16_t rubik_engine::size() { return CS + 1; };

color rubik_engine::block(uint16_t line, uint16_t column, uint16_t layer) { return CUBE[layer][line][column]; };
