/**
    File    : rubic.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250626.0

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "lib/getch.h"
#include "rubik_cube/rubik.h"

void showing_the_cube_colors(rubik& cube);
void turning_the_cube_around(rubik& cube);

int main()
{
    rubik cube; // create a 3x3x3 cube

    showing_the_cube_colors(cube);

    turning_the_cube_around(cube);

    return 0;
}

void showing_the_cube_colors(rubik& cube)
{
    cout << "\nShow the Rubik cube in black/white:\n" << endl;
    cube.applyTermColor = term_color::black_white;
    cube.show();
    getch();

    cout << "\nShow the Rubik cube in colored positions:\n" << endl;
    cube.applyTermColor = term_color::colored_positions;
    cube.show();
    getch();

    cube.applyTermColor = term_color::colored_letters;
}

void turning_the_cube_around(rubik& cube)
{
    cout << "\nTurning the Rubik cube around:\n" << endl;

    rubik controller(cube.size());

    struct direction
    {
        string desc;
        to To;
    };

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
            for (uint16_t s = 0; s < cube.size(); s++) cube.spin(dir[d].To, s);
            cube.show();
            getch();
        }
    }
}
