/**
    File    : debug_resetting.cpp
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
