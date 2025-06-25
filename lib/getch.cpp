/**
    File    : getch.cpp
    Author  : Menashe Rosemberg
    Created : 2025.06.22

    Version : 20250622.0

    getch() wait for the user press any character to continue.
    This function is used on terminal on Linux.

    Copyright [2025] [HuskyDucky (Menashe Rosemberg)] rosemberg@ymail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0
**/
#include "getch.h"

int getch()
{
  struct termios t_old, t_new;
  int ch;

  tcgetattr(STDIN_FILENO, &t_old);

  t_new = t_old;

  t_new.c_lflag &= ~(ICANON | ECHO);

  tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &t_old);

  return ch;
}
