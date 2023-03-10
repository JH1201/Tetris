#pragma once
#include <stdbool.h>

void Init();
void gotoxy(int x, int y);
void CreateRandomForm();
bool CheckCrash(int x, int y);
void DropBlock();
void BlockToGround();
void RemoveLine();
void DrawMap();
void DrawBlock();
void InputKey();
