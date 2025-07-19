/**
    File    : debug.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250704.1

    Execute some tests on Rubik cube simulation

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "debug.h"

const char* desc(colors::to dir) {
    switch (dir)
    {
        case colors::to::up            : return "up";
        case colors::to::down          : return "down";
        case colors::to::left          : return "left";
        case colors::to::right         : return "right";
        case colors::to::clockwise     : return "clockwise";
        case colors::to::anticlockwise : return "anticlockwise";
        default : return "err";
    }
}

const char* pos(colors::to dir) {
    switch (dir)
    {
        case colors::to::up            :
        case colors::to::down          : return "COLUMN";
        case colors::to::left          :
        case colors::to::right         : return "LINE";
        case colors::to::clockwise     :
        case colors::to::anticlockwise : return "LAYER";
        default : return "err   ";
    }
}
