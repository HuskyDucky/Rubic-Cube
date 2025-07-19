/**
    File    : main.cpp
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
#ifdef DEBUG
    void show_initial_positions();
    void showing_colors();
    void change_color_only_once();
    void turning_around();
    void randomizing_step_by_step();
    void resetting();
    void scanning();
#endif

int main()
{
#ifdef DEBUG
    //show_initial_positions();
    //showing_colors();
    //change_color_only_once();
    //turning_around();
    //randomizing_step_by_step();
    //resetting();
    scanning(); //This test works only in DEBUG mode
#endif

    return 0;
}

//
//void show_different_sizes()
//{
//    cout << "\nShow Rubik cube with different sizes:\n" << endl;
//    /// TO DO
//    getch();
//}
//
