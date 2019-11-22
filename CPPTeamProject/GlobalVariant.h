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
    StageInformation stage_data[10];

public:
    GlobalVariant();
    void init(int level, int lines, int ab_x, int ab_y);
    int getLevel() const;
    int getAbsoluteX() const;
    int getAbsoluteY() const;
    int getCtr() const;
    int getNextBlockShape() const;
    int getBlockAngle() const;
    int getBlockX() const;
    int getBlockY() const;
    int getBlockShape() const;
    int getLine() const;
    int getScore() const;
    int getGameOver() const;

    // Ptr return - type.
    int* getPtrBlockAngle();
    int* getPtrBlockX();
    int* getPtrBlockY();
    int* getPtrBlockShape();
    int* getPtrNextBlockShape();

    // Array return - type
    char(*getTotalBlock())[14];

    // Special return - type
    StageInformation(*getStageInformation());

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
    void setTotalBlock(int x, int y, int value);
    void setTotalBlock(int x, int y, int value, bool isBitOrOperator);
    void callInitStage(int index, int speed, int stick_rate, int clear_line);
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