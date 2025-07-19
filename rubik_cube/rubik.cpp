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
#include "rubik.h"

rubik::rubik() : rubik_engine(), applyTermColor(colored_letters) {};
rubik::rubik(uint8_t cube_size) : rubik_engine(cube_size), applyTermColor(colored_letters) {};

void rubik::randomize()
{
    randomize(pow(this->size(), this->size()));
}

void rubik::randomize(uint8_t nofTimes)
{
    if (nofTimes)
    {
        mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
        uniform_int_distribution<uint8_t> dir_to_spin(0, 5); // size of enum 'to'
        uniform_int_distribution<uint8_t> what_to_spin(0, this->size() - 1);

        for (uint8_t spinning = 0; spinning < nofTimes; spinning++)
            spin(static_cast<colors::to>(dir_to_spin(rd)), what_to_spin(rd));
    }
}

void rubik::setTermColor(term_color op)
{
    applyTermColor = op;
}

void rubik::show() const
{
    show(true);
}

#ifdef DEBUG
    void rubik::show_Scan_mem() const
    {
        show(false);
    }
#endif // DEBUG


void rubik::show(bool showMainCube) const
{
#ifndef DEBUG
    if (this->size() <= 10)
#else
    uint16_t Sz = this->size();

    if (!showMainCube)
        Sz = this->DebugScan_size();

    if (Sz <= 10)
#endif
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
                    for (uint16_t c = 0; c < 6; ++c)
                    {
                        char clr = this->block(lin, col, lyr).in[c];

                        #ifdef DEBUG
                            if (!showMainCube)
                                clr = this->blockDebugScan(lin, col, lyr).in[c];
                        #endif

                        if (clr == ' ')
                            cout << ' ';
                        else
                            cout << coloring(clr, applyTermColor);
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

void rubik::show(const term_color only_for_this_time)
{
    term_color curr_color = applyTermColor;
    setTermColor(only_for_this_time);

    show(true);

    setTermColor(curr_color);
}

void rubik::show_initial_positions()
{
    term_color curr_color = applyTermColor;
    applyTermColor = term_color::colored_positions;

    cout << " " << coloring(colors::For::Top, applyTermColor) << "   <- top"
         << '\n' << coloring(colors::For::Left, applyTermColor)
                 << coloring(colors::For::Front, applyTermColor)
                 << coloring(colors::For::Right, applyTermColor)
                 << coloring(colors::For::Back, applyTermColor) << " <- left, front, right and back"
         << "\n " << coloring(colors::For::Bottom, applyTermColor) << "   <- bottom" << endl;

    applyTermColor = curr_color;
}
