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
#include "rubik.h"

rubik::rubik() : rubik_engine(), applyTermColor(colored_letters) {};
rubik::rubik(uint16_t cube_size) : rubik_engine(cube_size), applyTermColor(colored_letters) {};

void rubik::randomize()
{
    randomize(this->size() ^ this->size());
}

void rubik::randomize(uint16_t nofTimes)
{
    if (nofTimes)
    {
        mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint16_t> dir_to_spin(0, 5); // size of enum 'to'
        uniform_int_distribution<uint16_t> what_to_spin(0, this->size() - 1);

        for (uint16_t spinning = 0; spinning < nofTimes; spinning++)
            spin(static_cast<to>(dir_to_spin(rd)), what_to_spin(rd));
    }
}

void rubik::setTermColor(term_color op)
{
    applyTermColor = op;
}

const char* rubik::colorize(const char c = ' ') const
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
    if (this->size() <= 10)
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

        cout << "   column:";
        for (uint16_t col = 0; col < CS; col++)
            cout << "    " << setfill(' ') << setw(4) << col;

        cout << "\n    color:   ";
        for (uint16_t col = 0; col < CS; col++)
            cout << " 123456 ";
        cout << '\n';

        for (uint16_t lyr = 0; lyr < CS; lyr++)
        {
            cout << "layer " << setfill(' ') << setw(3) << lyr << ": ";

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
    else
        cerr << "\n\nSorry for the inconvenient,\nbut only cubes with maximum edges of 10 blocks can be shown.\n\n";
}

void rubik::show(term_color only_for_this_time)
{
    term_color curr_color = applyTermColor;
    setTermColor(only_for_this_time);

    show();

    setTermColor(curr_color);
}

void rubik::show_initial_positions()
{
    term_color curr_color = applyTermColor;
    applyTermColor = term_color::colored_positions;

    cout << " " << colorize(color::For::Top) << color::For::Top << colorize() << "   <- top"
         << '\n' << colorize(color::For::Left) << color::For::Left
                 << colorize(color::For::Front) << color::For::Front
                 << colorize(color::For::Right) << color::For::Right
                 << colorize(color::For::Back) << color::For::Back << colorize() << " <- left, front, right and back"
         << "\n " << colorize(color::For::Bottom) << color::For::Bottom << colorize()   << "   <- bottom" << endl;

    applyTermColor = curr_color;
}
