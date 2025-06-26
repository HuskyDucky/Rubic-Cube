/**
    File    : general.h
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250626.0

    Rubik cube simulation engine

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#ifndef CUBEGENERAL_H
#define CUBEGENERAL_H

enum to
{
    up,
    down,
    left,
    right,
    clockwise,
    anticlockwise
};

enum position
{
    Left,
    Top,
    Front,
    Back,
    Bottom,
    Right
};

#endif // CUBEGENERAL_H
