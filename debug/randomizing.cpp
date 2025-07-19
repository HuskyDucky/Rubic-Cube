/**
    File    : debug_randomizing.cpp
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

void randomizing_step_by_step()
{
    rubik cube; // create a 3x3x3 cube

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
