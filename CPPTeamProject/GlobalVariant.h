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
    char color_block[21][14];
    int jew[5];
    StageInformation stage_data[10];

public:
    GlobalVariant();
    void init(const int& level, const int& lines, const int& ab_x, const int& ab_y);
    int getLevel() const;
    int getAbsoluteX() const;
    int getAbsoluteY() const;
    int getCtr() const;
    int& getNextBlockShape();
    int& getBlockAngle();
    int& getBlockX();
    int& getBlockY();
    int& getBlockShape();
    int getLine() const;
    int getScore() const;
    int getGameOver() const;

    // Ptr return - type.
    int* getPtrBlockAngle();
    int* getPtrBlockX();
    int* getPtrBlockY();
    int* getPtrBlockShape();
    int* getPtrNextBlockShape();
    int* getjew();

    // Array return - type
    char(*getTotalBlock())[14];
    char(*getColorBlock())[14];

    void getlevelXY(const int& level, int& x, int& y) {
        switch (level) {

        case 0:
        case 1:
        case 3:
        case 5:
            x = 4;
            y = 4;
            break;
        case 2:
        case 4:
            x = 8; 
            y = 8;
            break;

        }
    }


    // Special return - type
    StageInformation(*getStageInformation());

    // Something to set.
    void setBlockShape(const int& blockShape);
    void setNextBlockShape(const int& nextBlock);
    void setBlockAngle(const int& blockangle);
    void setBlockX(const int& blox);
    void setCtr(const int& ct);
    void setLine(const int& ln);
    void setScore(const int& sc);
    void setLevel(const int& lvl);
    void setGameOver(const int& val);
    void setTotalBlock(const int& x, const int& y, const int& value);
    void setTotalBlock(const int& x, const int& y, const int& value, const bool& isBitOrOperator);

    void callInitStage(const int& index, const int& speed, const int& stick_rate, const int& clear_line);

    void setColorBlock(const int& x, const int& y, const int& value);
    
    void setjew(int index);
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