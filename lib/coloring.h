/**
    File    : coloring.h
    Author  : Menashe Rosemberg
    Created : 2025.06.25

    Version : 20250718.0

    getch() wait for the user press any character to continue.
    This function is used on terminal on Linux.

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef COLORING_H
#define COLORING_H

enum term_color
{
    black_white,
    colored_letters,
    colored_positions
};

const char* coloring(const char c, const term_color tc = term_color::colored_letters);

#endif // COLORING_H
