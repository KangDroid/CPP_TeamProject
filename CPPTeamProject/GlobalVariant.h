#pragma once
#include "StageInformation.h"

#define EXT_KEY			0xffffffe0	//Ȯ��Ű �νİ� 
#define KEY_LEFT		0x4b
#define KEY_RIGHT		0x4d
#define KEY_UP			0x48
#define KEY_DOWN		0x50

class GlobalVariant {
private:
    int level;
    int ab_x, ab_y;	//ȭ���� ���� ��Ÿ���� ��ǥ�� ������ġ
    int block_shape, block_angle, block_x, block_y;
    int next_block_shape;
    int score;
    int lines;
    int ctr;
    int is_gameover; // The Boolean type check variable.
    void initTotalBlock();
    char total_block[21][14];		//ȭ�鿡 ǥ�õǴ� ����

public:
    GlobalVariant();
    StageInformation stage_data[10];
    void init(int level, int lines, int ab_x, int ab_y);
    int getLevel();
    int getAbsoluteX();
    int getAbsoluteY();
    int getCtr();
    int getNextBlockShape();
    int getBlockAngle();
    int getBlockX();
    int getBlockY();
    int getBlockShape();
    int getLine();
    int getScore();
    int getGameOver();

    // Ptr return - type.
    int* getPtrBlockAngle();
    int* getPtrBlockX();
    int* getPtrBlockY();
    int* getPtrBlockShape();
    int* getPtrNextBlockShape();

    // Array return - type
    char(*getTotalBlock())[14]{
        return this->total_block;
    }

    // Something to set.
    void setBlockShape(int blockShape);
    void setNextBlockShape(int nextBlock);
    void setBlockAngle(int blockangle);
    void setBlockX(int blox);
    void setCtr(int ct);
    void setLine(int ln);
    void setScore(int sc);
    void setLevel(int lvl);
    void setGameOver(int val);
    void setTotalBlock(int x, int y, int value) {
        this->total_block[y][x] = value;
    }
    void setTotalBlock(int x, int y, int value, bool isBitOrOperator) {
        this->total_block[y][x] |= value;
    }
};

enum {
    BLACK,      /*  0 : ��� */
    DARK_BLUE,    /*  1 : ��ο� �Ķ� */
    DARK_GREEN,    /*  2 : ��ο� �ʷ� */
    DARK_SKY_BLUE,  /*  3 : ��ο� �ϴ� */
    DARK_RED,    /*  4 : ��ο� ���� */
    DARK_VOILET,  /*  5 : ��ο� ���� */
    DARK_YELLOW,  /*  6 : ��ο� ��� */
    GRAY,      /*  7 : ȸ�� */
    DARK_GRAY,    /*  8 : ��ο� ȸ�� */
    BLUE,      /*  9 : �Ķ� */
    GREEN,      /* 10 : �ʷ� */
    SKY_BLUE,    /* 11 : �ϴ� */
    RED,      /* 12 : ���� */
    VOILET,      /* 13 : ���� */
    YELLOW,      /* 14 : ��� */
    WHITE,      /* 15 : �Ͼ� */
};