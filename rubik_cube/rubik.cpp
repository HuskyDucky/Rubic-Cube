/**
    File    : rubik.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.25

    Version : 20250626.0

    Extends functionalities for Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "rubik.h"

rubik::rubik() : rubik_engine(), applyTermColor(colored_letters) {};
rubik::rubik(uint16_t cube_size) : rubik_engine(cube_size), applyTermColor(colored_letters) {};

const char* rubik::colorize (const char c = ' ') const
{
    switch (applyTermColor)
    {
        case term_color::colored_letters:   switch (c) {
                                                case 'W' : return "\x1B[97m"; break;
                                                case 'Y' : return "\x1B[93m"; break;
                                                case 'B' : return "\x1B[94m"; break;
                                                case 'G' : return "\x1B[92m"; break;
                                                case 'R' : return "\x1B[91m"; break;
                                                case 'O' : return "\x1B[33m"; break;
                                                default  : return "\033[0m";
                                            }
                                            break;
        case term_color::colored_positions: switch (c) {
                                                case 'W' : return "\033[3;107;97m"; break;
                                                case 'Y' : return "\033[3;103;93m"; break;
                                                case 'B' : return "\033[3;104;94m"; break;
                                                case 'G' : return "\033[3;102;92m"; break;
                                                case 'R' : return "\033[3;101;91m"; break;
                                                case 'O' : return "\033[3;43;33m"; break;
                                                default  : return "\033[0m";
                                            }
                                            break;
        default : return "";
    }
}

void rubik::show()
{
    cout << "\rColors schematics: [123456] => ";
    for (uint16_t pos = 0; pos < 6; pos++)
    {
        cout << pos + 1 << " - ";
        switch (pos)
        {
            case position::Front  : cout << "front";  break;
            case position::Back   : cout << "back";   break;
            case position::Right  : cout << "right";  break;
            case position::Left   : cout << "left";   break;
            case position::Top    : cout << "top";    break;
            case position::Bottom : cout << "bottom"; break;
        }

        if (pos != 5)
            cout << ", ";
    }
    cout << '\n';

    string spc = "           ";

    uint16_t CS = this->size();

    cout << "   column:   ";
    for (uint16_t col = 0; col < CS; col++)
        cout << "    " << col << "   ";

    cout << "\n    color:   ";
    for (uint16_t col = 0; col < CS; col++)
        cout << " 123456 ";
    cout << '\n';

    for (uint16_t lyr = 0; lyr < CS; lyr++)
    {
        cout << "layer " << setfill('0') << setw(3) << lyr << ": ";

        for (uint16_t lin = 0; lin < CS; lin++)
        {
            cout << lin << ' ';
            for (uint16_t col = 0; col < CS; col++)
            {
                cout << '[';
                for (auto c = 0; c < 6; ++c)
                {
                    char clr = (this->block(lin, col, lyr)).in[c];
                    cout << colorize(clr) << clr << colorize();
                }
                cout << ']';
            }
            cout << '\n' << spc;
        }

        if (lyr != CS - 1)
            cout << '\n';
    }

    cout << flush;
}
