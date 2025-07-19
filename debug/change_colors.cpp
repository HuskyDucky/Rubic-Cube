/**
    File    : debug_change_colors.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250704.0

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "debug.h"

void change_color_only_once()
{
    rubik cube; // create a 3x3x3 cube

    cout << "\nShow the Rubik cube color only once:\n\n" << endl;

    cout << '\n' << string(20, ' ') << "Default colors (colored_letters)\n\n";
    cube.show();

    cout << '\n' << string(20, ' ') << "Cube's colors changed to colored_position\n";
    cube.show(term_color::colored_positions);

    cout << '\n' << string(20, ' ') << "Default colors was restored automatically\n\n";
    cube.show();
    getch();
}

void showing_colors()
{
    rubik cube; // create a 3x3x3 cube

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
