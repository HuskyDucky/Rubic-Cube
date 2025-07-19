/**
    File    : class_color.h
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250711.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef CUBECOLOR_H
#define CUBECOLOR_H

#include <cinttypes>
#include <cstring>

#include "general.h"

struct colors {
        enum For : char
        {
            None   = ' ',
            Front  = 'W',
            Back   = 'Y',
            Left   = 'B',
            Right  = 'G',
            Top    = 'R',
            Bottom = 'O'
        };

        enum to : uint8_t
        {
            up,
            down,
            left,
            right,
            clockwise,
            anticlockwise
        };

        colors();
        colors(const char* lcolors);

        char in[6] = {' ', ' ', ' ', ' ', ' ', ' '}; // the index is the colors' positions (general.h -> enum position)

        void spin(to direction);
};

#endif // CUBECOLOR_H
