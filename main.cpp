/**
    File    : rubic.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250628.0

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "lib/getch.h"
#include "rubik_cube/rubik.h"

void show_initial_positions();
void showing_colors();
void change_color_only_once();
void turning_around();
void randomizing_step_by_step();
void resetting();

const char* desc(to dir) {
    switch (dir)
    {
        case to::up            : return "up";
        case to::down          : return "down";
        case to::left          : return "left";
        case to::right         : return "right";
        case to::clockwise     : return "clockwise";
        case to::anticlockwise : return "anticlockwise";
        default : return "err";
    }
}

const char* pos(to dir) {
    switch (dir)
    {
        case to::up            :
        case to::down          : return "COLUMN";
        case to::left          :
        case to::right         : return "LINE";
        case to::clockwise     :
        case to::anticlockwise : return "LAYER";
        default : return "err   ";
    }
}

const char spaces[] = "\n                    ";

rubik cube; // create a 3x3x3 cube

int main()
{
    show_initial_positions();

    showing_colors();

    change_color_only_once();

    //turning_around();

    randomizing_step_by_step();

    resetting();

    return 0;
}

void resetting()
{
    cout << "\nResetting the cube and check its history:\n";

    rubik cube_2;

    cube_2.randomize(25);
    auto stats = cube_2.get_Spin_history();
    cout << "\n\nThe cube was spinned 25 times and the size of history kept is: " << stats.size();

    cube_2.randomize(15);
    stats = cube_2.get_Spin_history();
    cout << "\nThe cube was spinned 15 more times and the size of history kept is: " << stats.size() << " (it is expected 40)\n\n";

    cube_2.show();
    getch();

    cube_2.reset();
    stats = cube_2.get_Spin_history();
    cout << "\n\nThe cube was reset. The size of history kept is: " << stats.size() << " (it is expected to have no history)\n\n";

    cube_2.show();
    getch();
}

void show_different_sizes()
{
    cout << "\nShow Rubik cube with different sizes:\n" << endl;
    /// TO DO
    getch();
}

void show_initial_positions()
{
    cout << "\nRubik cube's initial positions:\n" << endl;
    cube.show_initial_positions();
    getch();
}

void randomizing_step_by_step()
{
    cout << "\nRubik cube before start randomizing\n" << endl;
    cube.show();
    getch();

    cout << "\nLet's randomize the Rubik cube."
          << "\nPress 'x' to finish randomize." << endl;

    do {
        cube.randomize(1);

        auto stat = cube.get_Spin_history().back();

        //for (auto stat : stats)
            cout << '\n' << pos(stat.direction) << " number " << stat.xyz << " was spinned " << desc(stat.direction);

        cout << "\n\n";

        cube.show();

    } while (getch() != 'x');
}

void change_color_only_once()
{
    cout << "\nShow the Rubik cube color only once:\n\n" << endl;

    cout << spaces << "Default colors (colored_letters)\n\n";
    cube.show();

    cout << spaces << "Cube's colors changed to colored_position\n";
    cube.show(term_color::colored_positions);

    cout << spaces << "Default colors was restored automatically\n\n";
    cube.show();
    getch();
}

void showing_colors()
{
    cout << "\nShow the Rubik cube in black/white:\n" << endl;
    cube.setTermColor(term_color::black_white);
    cube.show();
    getch();

    cout << "\nShow the Rubik cube in colored positions:\n" << endl;
    cube.setTermColor(term_color::colored_positions);
    cube.show();
    getch();

    cube.setTermColor(term_color::colored_letters);
}

void turning_around()
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
