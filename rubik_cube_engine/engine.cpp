/**
    File    : engine.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250716.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "engine.h"

rubik_engine::rubik_engine() : CS(3),
                               auxSpin(),
                               spin_history(),
                               CUBE(3, vector<vector<colors>>(3, vector<colors>(3))),
                               scan_facesScanned(0),
                               scan_cube_validation(), //8),    // CS ^ 3 - (CS -2) ^ 3
                               Sube(3, vector<vector<colors>>(3, vector<colors>(3))) {
    CS--;

    reset();
}

rubik_engine::rubik_engine(uint8_t Cube_Size) : CS(Cube_Size),
                                                auxSpin(),
                                                spin_history(),
                                                CUBE(CS, vector<vector<colors>>(CS, vector<colors>(CS))),
                                                scan_facesScanned(0),
                                                scan_cube_validation(), //(CS ^ 3) - ((CS - 2) ^ 3)),
                                                Sube(CS, vector<vector<colors>>(CS, vector<colors>(CS))) {
    if (CS >= 3)
    {
        CS--;
        reset();
    } else
        recreate(CS);
}

const list<history>& rubik_engine::get_Spin_history() const
{
    return spin_history;
}

uint16_t rubik_engine::size() const
{
    return CUBE.size();
}

void rubik_engine::reset()
{
    spin_history.clear();
    scan_cube_validation.clear();

    //scan_cube_validation.resize(pow(CUBE.size(), 3) - pow((CUBE.size() - 2), 3));

    for (uint8_t lyr = 0; lyr <= CS; lyr++)
        for (uint8_t lin = 0; lin <= CS; lin++)
            for (uint8_t col = 0; col <= CS; col++)
            {
                colors& C = CUBE[lyr][lin][col];

                memset(C.in, ' ', 6 * sizeof(char)); // 6 colors (size of 'in')

                if (lyr == 0)       C.in[position::Front] = colors::For::Front;
                else if (lyr == CS) C.in[position::Back] = colors::For::Back;

                if (col == 0)       C.in[position::Left] = colors::For::Left;
                else if (col == CS) C.in[position::Right] = colors::For::Right;

                if (lin == 0)       C.in[position::Top]  = colors::For::Top;
                else if (lin == CS) C.in[position::Bottom] = colors::For::Bottom;

                uint8_t c = 0;
                do {
                    if (C.in[c] != ' ')
                    {
                        scan_cube_validation.emplace_front(C.in);
                        break;
                    }
                } while (++c != 6);
            }
}

void rubik_engine::recreate(const uint8_t Cube_Size)
{
    if (Cube_Size >= 3)
        CS = Cube_Size;
    else
    {
        CS = 3;
        cerr << "\n\nWarning: The size of Rubik cube must be bigger than 2.\nA Rubik cube with size of 3 was created.\n\n" << endl;
    }

    CUBE.clear();
    CUBE = vector<vector<vector<colors>>>(CS, vector<vector<colors>>(CS, vector<colors>(CS)));

    CS--;

    reset();
}

colors rubik_engine::block(const uint8_t line, uint8_t column, uint8_t layer) const
{
    return CUBE[layer][line][column];
}

#ifdef DEBUG
    colors rubik_engine::blockDebugScan(uint8_t line, uint8_t column, uint8_t layer) const
    {
        return Sube[layer][line][column];
    }

    uint16_t rubik_engine::DebugScan_size() const
    {
        return Sube.size();
    }
#endif // DEBUG
