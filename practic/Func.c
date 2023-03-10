#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>

clock_t startDropT, endT, startGroundT; // time.h 라이브러리에 있는 타입
int x = 8, y = 0;
RECT blockSize;
int blockForm;
int blockRotation = 0;
int key;

int block[7][4][4][4] = {
	{ // T모양 블럭
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // 번개 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 번개 블럭 반대
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형 블럭
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭 반대
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 네모 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};

int space[15 + 1][10 + 2] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)칸  
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};


void Init() {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL)); // srand에 time(NULL)을 줘야 rand()가 고정적으로 나오지 않음
}

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CreateRandomForm() {
	blockForm = rand() % 7; //rand()%7을 해주면 0~6의 랜덤한 값이 나옴
}

bool CheckCrash(int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int t = space[i + y][j + x / 2]; // x좌표는 2당 1칸의 크기를 가지기 때문에 x*2
				if (t == 1 || t == 2) {
					return true;
				}
			}
		}
	}
	return false;
}  // 매개변수에 위치값을 넣고 블럭이 그 위치에 있어 충돌하면 true 아니면 false


void DropBlock() {
	endT = clock(); //clock()은 시간 측정 함수
	if ((float)(endT - startDropT) >= 800) {
		if (CheckCrash(x, y + 1) == true) return;

		y++; //블럭을 내리고
		startDropT = clock();
		startGroundT = clock();
		system("cls"); // 블럭을 지우고
	}
} //0.8초마다 블럭을 한칸씩 밑으로 내리는 함수

void BlockToGround() {
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 1500) {
			//현재 블록 저장
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			x = 8;
			y = 0;
			CreateRandomForm();
		}
	}
}// 블럭이 1.5초 동안 땅에 닿아있을 때 아무 동작이 없다면 땅으로 변함
// 그리고 랜덤한 블럭을 만들고 위로 올린다. (위에서 블럭이 내려옴)


void RemoveLine() {
	for (int i = 15; i >= 0; i--) { // 벽라인 제외한 값
		int cnt = 0;
		for (int j = 1; j < 11; j++) { // 양 옆에 테두리 제외한 값
			if (space[i][j] == 2) {
				cnt++;
			}
		}
		if (cnt >= 10) { // 벽돌이 다 차있다면
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0) // 밑 줄에 빈공간이 있어 블럭을 한칸 내림
						//문제는 빈 공간이 n줄이어도 블럭이 한칸 밖에 안내려 간다는것
						space[i - j][x] = space[i - j - 1][x];
					else {
						// 밑 줄에 빈공간이 없을 때 블럭 지우고 맵에 0 삽입
						space[i - j][x] = 0;
						
					}   
				}
			}
		}
	}
}

void DrawMap() {
	gotoxy(0, 0);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			if (space[i][j] == 1) {
				gotoxy(j * 2, i);
				printf("□");
			}
			else if (space[i][j] == 2) {
				gotoxy(j * 2, i);
				printf("■");
			}
		}
	}
} //맵의 형태와 쌓인 블럭

void DrawBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				printf("■");
			}
		}
	}
}
//[7] : 7개의 블럭
//[4] : 4개의 회전모양
//[4] : 세로 모양
//[4] : 가로 모양

//[7] 부분에 랜덤으로 숫자를 주면 랜덤한 블럭이 나타나게 됩니다.(blockForm)
//[4] 회전키를 누를 때마다 증감해주면 모양이 회전하게 됩니다.(blockRotation)

void InputKey() {
	if (_kbhit()) {  // conio.h / _kbhit으로 입력을 감지, _getch로 입력
		//_getch만 사용하면 입력을 받을 때까지 대기하게 된다.
		key = _getch();
		switch (key) {
		case 32: // space
			blockRotation++;
			if (blockRotation >= 4) blockRotation = 0;
			startGroundT = clock();
			break;
		case 75: // left
			if (CheckCrash(x - 2, y) == false) {
				x -= 2;
				startGroundT = clock();
			}
			break;
		case 77: // right
			if (CheckCrash(x + 2, y) == false) {
				x += 2;
				startGroundT = clock();
			}
			break;
		case 80: // down
			if (CheckCrash(x, y + 1) == false)
				y++;
			break;
		}
		system("cls");
	}
}

// case 마다 StartGrounT = clock()을 하는 이유는 StartGrounT의 시간을 갱신해서
// 블럭이 땅으로 변하지 않게 하기 위해서 
// 이 코드가 없다면 아무리 블럭을 이동, 모양을 바꿔도 땅에 닿으면 바로 다음 블럭이 나올 것이다.

// system("cls")는 실행하는데 시간이 약간 걸리므로 사용을 최소화 하기 위해
// 키를 누를 때나 땅에 떨어질 때만 실행됨

