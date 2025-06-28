/**
    File    : class_color.h
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
#ifndef CUBECOLOR_H
#define CUBECOLOR_H

#include <cinttypes>
#include "general.h"

struct color {
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

        char in[6]; // the index is the colors' positions (general.h -> enum position)

        void spinColor(to direction);

    private:
        char auxSpin = ' ';
};

#endif // CUBECOLOR_H
