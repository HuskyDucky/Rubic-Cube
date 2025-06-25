/**
    File    : rubic.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250625.0

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "lib/getch.h"
#include "rubik_cube/rubik.h"

int main()
{
    uint16_t cube_size = 3;

    rubik cube(cube_size);
    rubik controller;       // same as controller(3);

    struct direction
    {
        string desc;
        to To;
    };

    // move the cube to all directions
    direction dir[6] = {{"RIGHT", to::right},
                        {"LEFT", to::left},
                        {"UP", to::up},
                        {"DOWN", to::down},
                        {"CLOCKWISE", to::clockwise},
                        {"ANTICLOCKWISE", to::anticlockwise}};

    const char spaces[] = "\n                    ";
    for (uint16_t d = 0; d < 6; d++)
    {
        for (uint16_t c = 0; c < 3; c++)
        {
            if (c == 0)
            {
                cout << spaces << "CONTROLLER\n";
                controller.show();
            }
            cout << spaces << "SPIN TO " << dir[d].desc << "\n\t";
            for (uint16_t s = 0; s < cube_size; s++) cube.spin(dir[d].To, s);
            cube.show();
            getch();
        }
    }

    return 0;
}
