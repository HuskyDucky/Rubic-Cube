/**
    File    : coloring.cpp
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
#include "coloring.h"

const char* coloring(const char c, const term_color tc)
{
    switch (c) {
        case 'w' :
        case 'W' : return tc == term_color::colored_letters ? "\x1B[97mW\033[0m" : tc == term_color::colored_positions ? "\033[3;107;97mW\033[0m" : "W";
        case 'y' :
        case 'Y' : return tc == term_color::colored_letters ? "\x1B[93mY\033[0m" : tc == term_color::colored_positions ? "\033[3;103;93mY\033[0m" : "Y";
        case 'b' :
        case 'B' : return tc == term_color::colored_letters ? "\x1B[94mB\033[0m" : tc == term_color::colored_positions ? "\033[3;104;94mB\033[0m" : "B";
        case 'g' :
        case 'G' : return tc == term_color::colored_letters ? "\x1B[92mG\033[0m" : tc == term_color::colored_positions ? "\033[3;102;92mG\033[0m" : "G";
        case 'r' :
        case 'R' : return tc == term_color::colored_letters ? "\x1B[91mR\033[0m" : tc == term_color::colored_positions ? "\033[3;101;91mR\033[0m" : "R";
        case 'o' :
        case 'O' : return tc == term_color::colored_letters ? "\x1B[33mO\033[0m" : tc == term_color::colored_positions ? "\033[3;43;33mO\033[0m"  : "O";
        default  : return "-";
    }
}
