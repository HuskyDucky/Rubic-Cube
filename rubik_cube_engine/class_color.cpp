/**
    File    : class_color.cpp
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
#include "class_color.h"

void color::spinColor(to direction)
{
    switch (direction) {
        case to::up : auxSpin = in[position::Front];
                      in[position::Front]  = in[position::Bottom];
                      in[position::Bottom] = in[position::Back];
                      in[position::Back]   = in[position::Top];
                      in[position::Top] = auxSpin;
                      break;
        case to::down : auxSpin = in[position::Front];
                        in[position::Front]  = in[position::Top];
                        in[position::Top]    = in[position::Back];
                        in[position::Back]   = in[position::Bottom];
                        in[position::Bottom] = auxSpin;
                        break;
        case to::left : auxSpin = in[position::Front];
                        in[position::Front] = in[position::Right];
                        in[position::Right] = in[position::Back];
                        in[position::Back]  = in[position::Left];
                        in[position::Left]  = auxSpin;
                        break;
        case to::right : auxSpin = in[position::Front];
                         in[position::Front] = in[position::Left];
                         in[position::Left]  = in[position::Back];
                         in[position::Back]  = in[position::Right];
                         in[position::Right] = auxSpin;
                         break;
        case to::clockwise : auxSpin = in[position::Top];
                             in[position::Top]    = in[position::Left];
                             in[position::Left]   = in[position::Bottom];
                             in[position::Bottom] = in[position::Right];
                             in[position::Right]  = auxSpin;
                             break;
        case to::anticlockwise : auxSpin = in[position::Top];
                                 in[position::Top]    = in[position::Right];
                                 in[position::Right]  = in[position::Bottom];
                                 in[position::Bottom] = in[position::Left];
                                 in[position::Left]  = auxSpin;
                                 break;
    }
}
