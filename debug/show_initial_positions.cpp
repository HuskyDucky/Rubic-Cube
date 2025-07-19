/**
    File    : debug_show_initial_positions.cpp
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

void show_initial_positions()
{
    rubik cube; // create a 3x3x3 cube

    cout << "\nRubik cube's initial positions:\n" << endl;
    cube.show_initial_positions();
    getch();
}
