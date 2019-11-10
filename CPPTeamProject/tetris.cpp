// Bug3(VS-Specific): _kbhit / kbhit
// CMD: cl /wd4996 /wd4819 tetris.cpp || nvcc -Xcompiler /wd4996 /wd4819 tetris.cpp
#pragma warning(disable:4996)

#include <cstdio>
#include <iostream>
#include <conio.h>
#include <string>

// Bug 1. Windows.h is NOT Included
// Bug 2. time.h is NOT Included.
#include <Windows.h>
#include <time.h>

using namespace std;

//*********************************
//상수 선언
//*********************************

#define EXT_KEY			0xffffffe0	//확장키 인식값 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

//*********************************
//구조체 선언
//*********************************

class StageInformation {
private:
    int	speed;	//숫자가 낮을수록 속도가 빠르다
    int stick_rate;		//막대가 나오는 확률 0~99 , 99면 막대기만 나옴
    int clear_line;
public:
    void init(int speed, int stick_rate, int clear_line) {
        this->speed = speed;
        this->stick_rate = stick_rate;
        this->clear_line = clear_line;
    }
    int getSpeed() {
        return this->speed;
    }
    int getStickRate() {
        return this->stick_rate;
    }
    int getClearLine() {
        return this->clear_line;
    }
    void setSpeed(int speed) {
        this->speed = speed;
    }
    void setStickRate(int stick_rate) {
        this->stick_rate = stick_rate;
    }
    void setClearLine(int clear_line) {
        this->clear_line = clear_line;
    }
};

class SystemUIManager {
public:
    static int gotoxy(int x, int y) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.Y = y;
        pos.X = x;
        SetConsoleCursorPosition(hConsole, pos);
        return 0;
    }
    static void SetColor(int color) {
        static HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(std_output_handle, color);
    }
};

enum {
    BLACK,      /*  0 : 까망 */
    DARK_BLUE,    /*  1 : 어두운 파랑 */
    DARK_GREEN,    /*  2 : 어두운 초록 */
    DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
    DARK_RED,    /*  4 : 어두운 빨강 */
    DARK_VOILET,  /*  5 : 어두운 보라 */
    DARK_YELLOW,  /*  6 : 어두운 노랑 */
    GRAY,      /*  7 : 회색 */
    DARK_GRAY,    /*  8 : 어두운 회색 */
    BLUE,      /*  9 : 파랑 */
    GREEN,      /* 10 : 초록 */
    SKY_BLUE,    /* 11 : 하늘 */
    RED,      /* 12 : 빨강 */
    VOILET,      /* 13 : 보라 */
    YELLOW,      /* 14 : 노랑 */
    WHITE,      /* 15 : 하양 */
};

//*********************************
//전역변수선언
//*********************************
int level;
int ab_x, ab_y;	//화면중 블럭이 나타나는 좌표의 절대위치
int block_shape, block_angle, block_x, block_y;
int next_block_shape;
int score;
int lines;
int ctr;
char total_block[21][14];		//화면에 표시되는 블럭들
StageInformation stage_data[10];

/**
 * 7-shape, 4 rotation(by 90 deg), 4 * 4 matrix of data.
 */
char block[7][4][4][4] = {
    //막대모양
    1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

    //네모모양
    1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

    //'ㅓ' 모양
    0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

    //'ㄱ'모양
    1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

    //'ㄴ' 모양
    1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

    //'Z' 모양
    1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

    //'S' 모양
    0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0

};
//*********************************
//함수 선언
//*********************************
int init();					//각종변수 초기화
int show_cur_block(int shape, int angle, int x, int y);	//진행중인 블럭을 화면에 표시한다
int erase_cur_block(int shape, int angle, int x, int y);	//블럭 진행의 잔상을 지우기 위한 함수
int show_total_block();	//쌓여져있는 블럭을 화면에 표시한다.
int show_next_block(int shape);
int make_new_block();	//return값으로 block의 모양번호를 알려줌
int strike_check(int shape, int angle, int* x, int y, int isRot);	//블럭이 화면 맨 아래에 부닥쳤는지 검사 부닥치면 1을리턴 아니면 0리턴
int merge_block(int shape, int angle, int x, int y);	//블럭이 바닥에 닿았을때 진행중인 블럭과 쌓아진 블럭을 합침
int block_start(int* angle, int* x, int* y);	//블럭이 처음 나올때 위치와 모양을 알려줌
int move_block(int* shape, int* angle, int* x, int* y, int* next_shape);	//게임오버는 1을리턴 바닥에 블럭이 닿으면 2를 리턴
int show_gameover();
int show_gamestat();
int show_logo();
int input_data();
int check_full_line();


int main(int argc, char* argv[]) {
    int i; // Iterator variable?
    int is_gameover = 0; // The Boolean type check variable.
    char keytemp;
    srand((unsigned)time(NULL));
    init(); // Initiate.
    show_logo();
    while (1) {

        input_data();
        score = 0;
        is_gameover = 0;
        show_total_block();
        block_shape = make_new_block();
        next_block_shape = make_new_block(); // Something different from previous one.
        show_next_block(next_block_shape); // Show next block
        block_start(&block_angle, &block_x, &block_y); // Start from first block. - block_shape = first block. Inits coord/angle.
        show_gamestat();
        for (i = 1; 1; i++) {
            if (kbhit()) {
                keytemp = getche();
                if (keytemp == EXT_KEY) {
                    keytemp = getche();
                    switch (keytemp) {
                    case KEY_UP:		//회전하기
                        ctr = 0;
                        if (strike_check(block_shape, (block_angle + 1) % 4, &block_x, block_y, 1) == 0) {
                            erase_cur_block(block_shape, block_angle, block_x + ctr, block_y);
                            block_angle = (block_angle + 1) % 4;
                            show_cur_block(block_shape, block_angle, block_x, block_y);
                        }
                        break;
                    case KEY_LEFT:		//왼쪽으로 이동
                        if (block_x > 1) {
                            erase_cur_block(block_shape, block_angle, block_x, block_y);
                            block_x--;
                            if (strike_check(block_shape, block_angle, &block_x, block_y, 0) == 1)
                                block_x++;

                            show_cur_block(block_shape, block_angle, block_x, block_y);
                        }
                        break;
                    case KEY_RIGHT:		//오른쪽으로 이동
                        if (block_x < 14) {
                            erase_cur_block(block_shape, block_angle, block_x, block_y);
                            block_x++;
                            if (strike_check(block_shape, block_angle, &block_x, block_y, 0) == 1) {
                                block_x--;
                            }
                            show_cur_block(block_shape, block_angle, block_x, block_y);
                        }
                        break;
                    case KEY_DOWN:		//아래로 이동
                        is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
                        show_cur_block(block_shape, block_angle, block_x, block_y);
                        break;
                    }
                } else if (keytemp == 32) { //스페이스바를 눌렀을때
                    while (is_gameover == 0) {
                        is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);
                    }
                    show_cur_block(block_shape, block_angle, block_x, block_y);
                } else {
                    // Clear out 
                    erase_cur_block(block_shape, block_angle, block_x, block_y);
                    show_cur_block(block_shape, block_angle, block_x, block_y);
                }
            }
            if (i % stage_data[level].getSpeed() == 0) {
                is_gameover = move_block(&block_shape, &block_angle, &block_x, &block_y, &next_block_shape);

                show_cur_block(block_shape, block_angle, block_x, block_y);
            }

            if (is_gameover == 1) {
                show_gameover();
                SystemUIManager::SetColor(GRAY);
                break;
            }

            SystemUIManager::gotoxy(77, 23);
            Sleep(15);
            SystemUIManager::gotoxy(77, 23);
        }
        init();
    }
    return 0;
}

/**
 * The Questions.
 * 1. Why init should return 0? Seems like nothing is taking return value of init.
 */
int init() {
    int i, j; // The Iterator variable. it really doesnt have to be in this line.

    /**
     * So, This iteration does:
     * 1. Every i, for j = 0, j = 13, set its var to 1.
     */
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 14; j++) {
            if ((j == 0) || (j == 13)) {
                total_block[i][j] = 1;
            } else {
                total_block[i][j] = 0;
            }
        }
    }

    for (j = 0; j < 14; j++)			//화면의 제일 밑의 줄은 1로 채운다.
        total_block[20][j] = 1;
    // Afterall, those Iteration could minimize(or combine)
    // And those two for-operation does make some kind of beaker-shape array.

    //전역변수 초기화
    level = 0;
    lines = 0;
    ab_x = 5; /*So, is it starting from 1, 5? */
    ab_y = 1;

    // Initiate stage level data.
    stage_data[0].init(40, 20, 20);
    stage_data[1].init(38, 18, 20);
    stage_data[2].init(35, 18, 20);
    stage_data[3].init(30, 17, 20);
    stage_data[4].init(25, 16, 20);
    stage_data[5].init(20, 14, 20);
    stage_data[6].init(15, 14, 20);
    stage_data[7].init(10, 13, 20);
    stage_data[8].init(6, 12, 20);
    stage_data[9].init(4, 11, 99999);
    return 0;
}


/**
 * Shows shape-angle from point.
 * shape: Could be random, but anyway, its shape of block.
 * angle: Could be random, but also, its rotation of block.
 * x/y: Could be random, absolute starting point.
 */
int show_cur_block(int shape, int angle, int x, int y) {
    int i, j; // The iteration variable. - Could be localized.

    // Set Color based on block shape.
    switch (shape) {
    case 0:
        SystemUIManager::SetColor(RED);
        break;
    case 1:
        SystemUIManager::SetColor(BLUE);
        break;
    case 2:
        SystemUIManager::SetColor(SKY_BLUE);
        break;
    case 3:
        SystemUIManager::SetColor(WHITE);
        break;
    case 4:
        SystemUIManager::SetColor(YELLOW);
        break;
    case 5:
        SystemUIManager::SetColor(VOILET);
        break;
    case 6:
        SystemUIManager::SetColor(GREEN);
        break;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if ((j + y) < 0) // Absolute starting point of y + j < 0
                continue;

            // Somewhat print damn thing
            if (block[shape][angle][j][i] == 1) {
                SystemUIManager::gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
                cout << "■";

            }
        }
    }
    SystemUIManager::SetColor(BLACK);
    SystemUIManager::gotoxy(77, 23);
    return 0;
}

//Erase current block information(More likely, override with spaces)
int erase_cur_block(int shape, int angle, int x, int y) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (block[shape][angle][j][i] == 1) {
                SystemUIManager::gotoxy((i + x) * 2 + ab_x, j + y + ab_y);
                cout << "  ";
                //break;

            }
        }
    }
    return 0;
}

int show_total_block() {
    int i, j;
    SystemUIManager::SetColor(DARK_GRAY);
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 14; j++) {
            if (j == 0 || j == 13 || i == 20)		//레벨에 따라 외벽 색이 변함
            {
                SystemUIManager::SetColor((level % 6) + 1);

            } else {
                SystemUIManager::SetColor(DARK_GRAY);
            }

            // Not checked from now.
            SystemUIManager::gotoxy((j * 2) + ab_x, i + ab_y);
            if (total_block[i][j] == 1) {
                cout << "■";
            } else {
                cout << "  ";
            }

        }
    }
    SystemUIManager::SetColor(BLACK);
    SystemUIManager::gotoxy(77, 23);
    return 0;
}

int make_new_block() {
    int shape;
    int i;
    i = rand() % 100;
    if (i <= stage_data[level].getStickRate())		//막대기 나올확률 계산
        return 0;							//막대기 모양으로 리턴

    shape = (rand() % 6) + 1;		//shape에는 1~6의 값이 들어감
    return shape;
}

//Check wheter block is touching elswhere.
//Returns 1 if they are touching anything, 0 when not.
int strike_check(int shape, int angle, int* x, int y, int isRot) {
    int i, j;
    int block_dat;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (((*x + j) == 0) || ((*x + j) == 13))
                block_dat = 1;
            else {
                if ((y + i) < 0) continue;
                block_dat = total_block[y + i][*x + j];
            }
            if ((block_dat == 1) && (block[shape][angle][i][j] == 1)) {
                if (isRot) {
                    if ((*x + j) == 13) {
                        (*x)--;
                        ctr++;
                        continue;
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

int merge_block(int shape, int angle, int x, int y) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            total_block[y + i][x + j] |= block[shape][angle][i][j];
        }
    }
    check_full_line();
    show_total_block();

    return 0;
}

// Set initial state for first-block start.
int block_start(int* angle, int* x, int* y) {
    *x = 5;
    *y = -3;
    *angle = 0;
    return 0;
}

int show_gameover() {
    SystemUIManager::SetColor(RED);
    SystemUIManager::gotoxy(15, 8);
    cout << "┏━━━━━━━━━━━━━┓";
    SystemUIManager::gotoxy(15, 9);
    cout << "┃**************************┃";
    SystemUIManager::gotoxy(15, 10);
    cout << "┃*        GAME OVER       *┃";
    SystemUIManager::gotoxy(15, 11);
    cout << "┃**************************┃";
    SystemUIManager::gotoxy(15, 12);
    cout << "┗━━━━━━━━━━━━━┛";
    fflush(stdin);
    Sleep(1000);

    getche();
    system("cls");

    return 0;
}

int move_block(int* shape, int* angle, int* x, int* y, int* next_shape) {
    erase_cur_block(*shape, *angle, *x, *y);

    (*y)++;	//블럭을 한칸 아래로 내림
    if (strike_check(*shape, *angle, x, *y, 0) == 1) {
        (*y)--;
        if (*y <= 0)	//게임오버
        {
            return 1;
        }
        merge_block(*shape, *angle, *x, *y);
        *shape = *next_shape;
        *next_shape = make_new_block();

        block_start(angle, x, y);	//angle,x,y는 포인터임
        show_next_block(*next_shape);
        return 2;
    }
    return 0;
}

int check_full_line() {
    int i, j, k;
    for (i = 0; i < 20; i++) {
        for (j = 1; j < 13; j++) {
            if (total_block[i][j] == 0)
                break;
        }
        if (j == 13) { //한줄이 다 채워졌음
            lines++;
            show_total_block();
            SystemUIManager::SetColor(BLUE);
            SystemUIManager::gotoxy(1 * 2 + ab_x, i + ab_y);
            for (j = 1; j < 13; j++) {
                cout << "□";
                Sleep(10);
            }
            SystemUIManager::gotoxy(1 * 2 + ab_x, i + ab_y);
            for (j = 1; j < 13; j++) {
                cout << "  ";
                Sleep(10);
            }

            for (k = i; k > 0; k--) {
                for (j = 1; j < 13; j++)
                    total_block[k][j] = total_block[k - 1][j];
            }
            for (j = 1; j < 13; j++)
                total_block[0][j] = 0;
            score += 100 + (level * 10) + (rand() % 10);
            if (stage_data[level].getClearLine() <= lines) { //클리어 스테이지
                level++;
                lines = 0;
            }
            show_gamestat();
        }
    }
    return 0;
}


/**
 * Show next block on Top-Right.
 * It basically make box and IN THAT BOX, they show next block.
 * Shape is previously created by make_new_block();
 */
int show_next_block(int shape) {
    int i, j;
    SystemUIManager::SetColor((level + 1) % 6 + 1);
    for (i = 1; i < 7; i++) {
        SystemUIManager::gotoxy(33, i);
        for (j = 0; j < 6; j++) {
            if (i == 1 || i == 6 || j == 0 || j == 5) {
                cout << "■";
            } else {
                cout << "  ";
            }

        }
    }
    // So it would show block created by make_new_block();
    show_cur_block(shape, 0, 15, 1);
    return 0;
}

int show_gamestat() {
    static int printed_text = 0;
    SystemUIManager::SetColor(GRAY);
    if (printed_text == 0) {
        SystemUIManager::gotoxy(35, 7);
        cout << "STAGE";

        SystemUIManager::gotoxy(35, 9);
        cout << "SCORE";

        SystemUIManager::gotoxy(35, 12);
        cout << "LINES";
    }
    SystemUIManager::gotoxy(41, 7);
    cout << level + 1;
    SystemUIManager::gotoxy(35, 10);
    cout << score;
    SystemUIManager::gotoxy(35, 13);
    cout << stage_data[level].getClearLine() - lines;
    return 0;
}

int input_data() {
    int i = 0; // checking variable for input(level)
    SystemUIManager::SetColor(GRAY);
    SystemUIManager::gotoxy(10, 7);
    cout << "┏━━━━<GAME KEY>━━━━━┓";
    Sleep(10);
    SystemUIManager::gotoxy(10, 8);
    cout << "┃ UP   : Rotate Block        ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 9);
    cout << "┃ DOWN : Move One-Step Down  ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 10);
    cout << "┃ SPACE: Move Bottom Down    ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 11);
    cout << "┃ LEFT : Move Left           ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 12);
    cout << "┃ RIGHT: Move Right          ┃";
    Sleep(10);
    SystemUIManager::gotoxy(10, 13);
    cout << "┗━━━━━━━━━━━━━━┛";

    // i is checking variable for input(level)
    while (i < 1 || i>8) {
        SystemUIManager::gotoxy(10, 3);
        cout << "Select Start level[1-8]:       \b\b\b\b\b\b\b";
        scanf("%d", &i);
        while (getchar() != '\n');
    }

    level = i - 1; // For index.
    system("cls");
    return 0;
}

int show_logo() {
    int i, j;
    SystemUIManager::gotoxy(13, 3);
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━┓";
    Sleep(100);
    SystemUIManager::gotoxy(13, 4);
    cout << "┃◆◆◆  ◆◆◆  ◆◆◆   ◆◆     ◆   ◆  ◆ ┃";
    Sleep(100);
    SystemUIManager::gotoxy(13, 5);
    cout << "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃";
    Sleep(100);
    SystemUIManager::gotoxy(13, 6);
    cout << "┃  ◆    ◆◆◆    ◆     ◆◆     ◆     ◆   ┃";
    Sleep(100);
    SystemUIManager::gotoxy(13, 7);
    cout << "┃  ◆    ◆        ◆     ◆ ◆    ◆    ◆◆  ┃";
    Sleep(100);
    SystemUIManager::gotoxy(13, 8);
    cout << "┃  ◆    ◆◆◆    ◆     ◆  ◆   ◆   ◆  ◆ ┃";
    Sleep(100);
    SystemUIManager::gotoxy(13, 9);
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━┛";

    SystemUIManager::gotoxy(28, 20);
    cout << "Please Press Any Key~!";

    for (i = 0; 1; i++) {
        if (i % 40 == 0) { // So this is the change-rate(Refresh rate) of Logo

            for (j = 0; j < 5; j++) {
                SystemUIManager::gotoxy(6, 14 + j);
                cout << "                                                          ";
            }

            show_cur_block(rand() % 7, rand() % 4, 6, 14);
            show_cur_block(rand() % 7, rand() % 4, 12, 14);
            show_cur_block(rand() % 7, rand() % 4, 19, 14);
            show_cur_block(rand() % 7, rand() % 4, 24, 14);
        }
        if (kbhit()) // maybe able to change kbhit to getche?
            break;

        /**
         * The fresh-rate
         * 30ms + (The time in Counter which exceeds 40 * something)
         */
        Sleep(30); // in ms
    }

    // We Entered something. Clear it in buffer.
    getche();
    system("cls");

    return 0;
}