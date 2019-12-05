#pragma once
#include "GameUIManager.h"
#include "TetrisCore.h"
#include "BlockManager.h"
class GameManager {
private:
    GlobalVariant gv;
    BlockManager bm;
    GameUIManager gui;
    TetrisCore tc;
    int fake_y;
    int level;
public:
    GameManager() : gv(), bm(), gui(gv, bm), tc(gui, gv, bm) {
        gui.setCursorView(false);
        //level (0~4)
        //0 : �𽺺�ȣ 
        //1 : �ִ���
        //2 : ����
        //3 : ��Ʈ��
        //4: ����
        //5 : �������

        this->level = 3;
    }
    void test();
    void play();
    void printThis();
};
