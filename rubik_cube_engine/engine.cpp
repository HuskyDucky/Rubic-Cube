/**
    File    : engine.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250625.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "engine.h"

rubik_engine::rubik_engine() :  CS(3),
                                auxSpin(),
                                CUBE(3, vector<vector<color>>(3, vector<color>(3))) {
    CS--;
    paintCube();
}

rubik_engine::rubik_engine(uint16_t Cube_Size)  :   CS(Cube_Size),
                                                    auxSpin(),
                                                    CUBE(CS, vector<vector<color>>(CS, vector<color>(CS))) {
    if (CS >= 3)
    {
        CS--;
        paintCube();
    } else
        recreate(CS);
}

void rubik_engine::paintCube()
{
    color* C = nullptr;
    for (uint16_t lyr = 0; lyr <= CS; lyr++)
        for (uint16_t lin = 0; lin <= CS; lin++)
            for (uint16_t col = 0; col <= CS; col++)
            {
                C = &CUBE[lyr][lin][col];
                if (lyr == 0)       (*C).in[position::Front] = color::For::Front;
                else if (lyr == CS) (*C).in[position::Back] = color::For::Back;

                if (col == 0)       (*C).in[position::Left] = color::For::Left;
                else if (col == CS) (*C).in[position::Right] = color::For::Right;

                if (lin == 0)       (*C).in[position::Top]  = color::For::Top;
                else if (lin == CS) (*C).in[position::Bottom] = color::For::Bottom;
            }
}

void rubik_engine::recreate(uint16_t Cube_Size)
{
    if (Cube_Size >= 3)
        CS = Cube_Size;
    else
    {
        CS = 3;
        cerr << "\n\nWarning: The size of Rubik cube must be bigger than 2.\nA Rubik cube with size of 3 was created.\n\n" << endl;
    }

    CUBE.clear();
    CUBE = vector<vector<vector<color>>>(CS, vector<vector<color>>(CS, vector<color>(CS)));

    CS--;

    paintCube();
}
