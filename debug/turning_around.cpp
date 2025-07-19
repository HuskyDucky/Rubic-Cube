/**
    File    : debug_turning_around.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250718.0

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "debug.h"

void turning_around()
{
    rubik cube; // create a 3x3x3 cube

    cout << "\nTurning the Rubik cube around:\n" << endl;

    rubik controller(cube.size());

    struct direction
    {
        string desc;
        colors::to To;
    };

    direction dir[6] = {{"RIGHT", colors::to::right},
                        {"LEFT", colors::to::left},
                        {"UP", colors::to::up},
                        {"DOWN", colors::to::down},
                        {"CLOCKWISE", colors::to::clockwise},
                        {"ANTICLOCKWISE", colors::to::anticlockwise}};

    for (uint8_t d = 0; d < 6; d++)
    {
        for (uint8_t c = 0; c < 3; c++)
        {
            if (c == 0)
            {
                cout << '\n' << string(20, ' ') << "CONTROLLER\n";
                controller.show();
            }
            cout << '\n' << string(20, ' ') << "SPIN TO " << dir[d].desc << "\n\t";
            for (uint8_t s = 0; s < cube.size(); s++) cube.spin(dir[d].To, s);
            cube.show();
            getch();
        }
    }
}
