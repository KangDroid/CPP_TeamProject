#pragma once
#include "GameUIManager.h"
#include "TetrisCore.h"
#include "BlockManager.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
class GameManager {
private:
    GlobalVariant gv;
    BlockManager bm;
    GameUIManager gui;
    TetrisCore tc;
    int fake_y;
    int level;
    int save; // 0 - prologue, 1 - morse
public:
    GameManager() : gv(), bm(), gui(gv, bm), tc(gui, gv, bm) {
        gui.setCursorView(false);
    }
    void test();
    bool play(int level);
    void printThis();

    void getInput() {
        gui.SetColor(WHITE);
        gui.gotoxy(40, 25);
        cout << "Please Press Any Key~!";
        getche();
    }

    void money() {
        gui.gotoxy(90, 3);
        cout << "MONEY : " << gv.getScore();
    }

    void story() {

        bool flag;
        tc.init();

        gui.show_logo();
        // <è�� ���>
        PlaySound(TEXT("Champs_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

        //<��¥ ���� ���>

        while (true) {
            int x = 17;
            int y = 5;
            if (save <= 0) {
                //prologue
                gui.SetColor(WHITE);
                money();
                gui.gotoxy(x, y);
                cout << "�츮 ȸ��� �Ǳ����б� 19�й� ����Ʈ�����а� ������� �̷���� �Ż���� Green Company�̴�.";
                gui.gotoxy(x, (y += 2));
                cout << "���� 1��� ������ ���� 1������ ��ǰ� �ִ�.";
                gui.gotoxy(x, (y += 2));
                cout << "���� Green Company�� �ڱ��� ���� ������ �Ż�����̴�.";
                gui.gotoxy(x, (y += 2));
                cout << "�׸��Ͽ� ���� ȸ�Ǹ� ���� ��Ʈ���� ������ ����� ���� �� ��ȹ�� �����.";
                gui.gotoxy(x, (y += 2));
                cout << "�׷��� �Ż�����̶� ���� ������ ����� ���� �������� �ұ��ϰ� �ڵ带 ���� �����Ѵ�. ";
                gui.gotoxy(x, (y += 2));
                cout << "�̸� �˰Ե� ���� ��� BLue Company�� Green Company�� ���� ��Ʈ���� ���� �ڵ带";
                gui.gotoxy(x, (y += 2));
                cout << "���İ� ���׸� �ܶ� ���ܳ��� ������.";
                gui.gotoxy(x, (y += 2));
                cout << "�Ͽ��� ��Ȳ �ӿ��� ������ ��Ʈ���� ������ �����غ���.";

                getInput();

                //���� 1 (�𽺺�ȣ)
                //<���� 1 ���>
                system("cls");
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game1BGM.wav"), NULL, SND_LOOP | SND_ASYNC);
                this->level = 0;
                money();
                flag = play(0);

                if (flag) {
                    //<���� oh ���>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    gui.gotoxy(28, 12);
                    cout << "������ �����̾�. ���ݾ� ���׸� ���ĳ�������." << endl;
                    save = 1;
                } else {
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");
                    gui.SetColor(WHITE);
                    //<GG ȿ����, ������ ȿ����, ��Ŀ ���>
                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 14);
                    cout << "�̷� ���� �ڵ����� �ذ����� ���ϴٴ�,,,,";
                    gui.gotoxy(28, 16);
                    cout << "�Ļ�. �ٽ� �õ��غ��ڽ��ϱ�?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
                getInput();
                // Clear CMD
                system("cls");
            }

            if (save <= 1) {
                x = 17;
                y = 9;
                money();
                //���� ���� ��
                gui.gotoxy(x, y);
                cout << "�ڱ��� ������ ����� �츮�� ���� ������ ���� ����;� �ϴ� ��Ȳ�� �Ǿ���.";
                gui.gotoxy(x, (y += 2));
                cout << "������ �ᱹ �ܱⰣ ��ҵ��� �������� ���� �������� ĳ�� ���� �Ƹ�����Ʈ�� �ϰ� �Ǿ���.";
                gui.gotoxy(x, (y += 2));
                cout << "���ΰ� �����;��� �������� ������ �������ְ�, �װ��� �������Ѿ� �޿��� ���� �� �ִ�.";
                gui.gotoxy(x, (y += 2));
                cout << "�׷��� ������ ȸ�縦 �츮�ڴٴ� �ϳ� �Ͽ� ���꿡 ����.";
                getInput();

                system("cls");
                x = 17;
                y = 9;
                money();
                gui.SetColor(RED);
                gui.gotoxy(x, y);
                cout << "��Ʈ���� ���İ� ������, �������� ������ ���� ȸ���� �Ұ����ϴ�. " << endl;
                gui.gotoxy(x, (y += 2));
                cout << "���� ���� ������ 4�� �̻� �پ��־�� ä���� �����ϴ�." << endl;
                gui.gotoxy(x, (y += 2));
                cout << "5���� ������ 5���� ���� ��ƾ� ������ �Ϸ��� �� �ִ�." << endl;

                getInput();


                //����2 (�������)
                //<���� 2, 5 ���>
                system("cls");
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game2_5_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);
                this->level = 1;
                //flag = play(1);
                money();
                flag = play(1);

                if (flag) {
                    //<���� oh ���>
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    x = 17;
                    y = 9;
                    gui.gotoxy(x, y);
                    cout << "���ΰ� ������ ������ �������� ������ �޿��� �ް� �Ƹ�����Ʈ�� ��ĥ �� �־���.";
                    gui.gotoxy(x, (y += 2));
                    cout << "�׶� ���ΰ� ���꿡�� ���� ���Ǵ� ��ź�� ������ ���̶�� �ϸ� ��ź�� ���忡�� �־���.";
                    gui.SetColor(GREEN);
                    gui.gotoxy(x, (y += 2));
                    cout << "��ź ������ : ������ ��ġ���� 4*4 ũ���� ����� �Ҹ��Ų��.";

                    //��ź ������ �� ��� ===> ��ź ������ 1 ȿ����, ��ź ȿ���� 2, �丮�� oh
                    gui.gotoxy(x, (y += 2));
                    cout << "���꿡�� �� ������ ������ ������ ������ ���ش�," << endl;
                    save = 2;

                } else {
                    //<GG ȿ����, ������ ȿ����, ��Ŀ ���>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");
                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 12);
                    cout << "�� ����� ������ �Ǿ� �̷� �ϵ� �ذ����� ���ϴٴ�,,";
                    gui.gotoxy(28, 14);
                    cout << "�Ļ�. �ٽ� �õ��غ��ڽ��ϱ�?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }

                getInput();
                // Clear CMD
                system("cls");
            }

            if (save <= 2) {
                x = 10;
                y = 9;
                money();
                gui.gotoxy(x, y);
                cout << "������ ���ٿ� ������ �ڵ� ���� �۾��� ū ������ �־���, ����� �������� �����س�����" << endl;
                gui.SetColor(GREEN);
                gui.gotoxy(x, (y += 2));
                cout << "����� ������ : ������ ��ġ�� 4*4 �迭�� �����Ѵ�. �� �������� ��ſ��� ����� �� ���� �ƹ��� �𸨴ϴ�." << endl;
                gui.SetColor(WHITE);
                gui.gotoxy(x, (y += 2));
                cout << "�������� ����Ͽ� �ڵ带 �����س����� ������ �����غ���." << endl;

                getInput();

                // Clear CMD
                system("cls");

                //����� ������ �� ��� ===> ����ī�� ���

                //����3 (����,����)
                //<���� 3,6 ���>
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game3_6_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

                this->level = 2;
                //flag = play(2);
                money();
                flag = play(2);

                if (flag) {
                    //<���� oh���>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    x = 17;
                    y = 12;
                    gui.gotoxy(x, y);
                    cout << "ȥ�������� �ڵ� �ӿ����� ������ �ϼ��Ͽ� ������ ��ó��� �ȵ��Ͽ���.";
                    gui.gotoxy(x, (y += 2));
                    cout << "������ ����Ͽ� ������ �ڵ忡�� ���� ���� ����� ������ �������� ȥ���� ������.";
                    save = 3;
                } else {
                    //<GG ȿ����, ������ ȿ����, ��Ŀ ���>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");

                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 12);
                    cout << "�ڽ��� �ڵ带 ������ �÷������� ���ϴٴ�,,,," << endl;
                    gui.gotoxy(28, 14);
                    cout << "�Ļ�. �ٽ� �õ��غ��ڽ��ϱ�?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
                getInput();

                // Clear CMD
                system("cls");
            }

            if (save <= 3) {
                x = 17;
                y = 10;
                money();
                gui.gotoxy(x, y);
                cout << "�׷��� �� ������ ���η� ���� ������ ������ �Ƿ����� �ȴ�.";
                gui.gotoxy(x, (y += 2));
                cout << "ȸ���� ����� ���� ������ �־�� �ϱ⿡ ������ ������Ѵ�";
                gui.gotoxy(x, (y += 2));
                cout << "������ ���� ������ �ǰ��� �������� ��ƴ���� ä���־�� �Ѵ�.";

                getInput();

                system("cls");
                x = 17;
                y = 9;
                money();
                gui.SetColor(RED);
                gui.gotoxy(x, y);
                cout << "��Ʈ������ �������� �״� ��������" << endl;
                gui.gotoxy(x, (y += 2));
                cout << "�ܺ��� �ٸ������� ĥ���� ���Ѽ����� ��� ä���������� ������ ����ȴ�." << endl;
                gui.gotoxy(x, (y += 2));
                cout << "���� ä�� ��, ��ĭ�� ���� ���� �� �����̸� ������ Ŭ�����ϰ� �ȴ�." << endl;

                getInput();

                system("cls");


                //����4 (��Ʈ��)
                //<����4 ���>
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game4_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

                this->level = 3;
                money();
                flag = play(3);

                if (flag) {
                    //<���� oh ���>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("real oh.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    system("cls");
                    gui.SetColor(WHITE);
                    money();
                    x = 17;
                    y = 13;
                    gui.gotoxy(x, y);
                    cout << "������ ���� ��Ƴ���, �̴� ȸ�� ���� �����⸦ �÷� �۾� �ӵ��� �� ������ ���־���. ";
                    gv.setScore(gv.getScore() + 3000);
                    save = 4;
                } else {
                    //<GG ȿ����, ������ ȿ����, ��Ŀ ���>
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gameover();
                    system("cls");
                    gui.SetColor(WHITE);
                    gui.gotoxy(28, 12);
                    cout << "������ �׷��� ���ƿ��� ���� ������ �������ϴ�.";
                    gui.gotoxy(28, 14);
                    cout << "�Ļ�. �ٽ� �õ��غ��ڽ��ϱ�?(y/n)";
                    char t = getchar();
                    while (getchar() != '\n');
                    system("cls");

                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
                getInput();
                system("cls");
            }

            x = 17;
            y = 6;
            money();
            gui.gotoxy(x, y);
            cout << "������ �� �̻��� ������ ���� �ڵ带 ���� ȸ��� ������ ������.";
            gui.gotoxy(x, (y += 2));
            cout << "�̶�, �Ǳ����б� ����Ʈ�����а��� �������� J�������� ";
            gui.gotoxy(x, (y += 2));
            cout << "������ �������� �Ƿ��� �ҽ��� ������ Green Company�� ��Ȳ�� �˰� �Ǿ���. ";
            gui.gotoxy(x, (y += 2));
            cout << "�̿� J�������� ����� 9�� 20�� C++ ������ ����� �����Ͽ���. ";
            gui.gotoxy(x, (y += 2));
            cout << "����� �������� �� ������ ��� �ڵ��� �������� �ľ��ϰ� �ǰ�, ";
            gui.gotoxy(x, (y += 2));
            cout << "�߰������� ������ ������ �ڵ� ���� ������ �� �ְ� �Ǿ���.";
            gui.SetColor(GREEN);
            gui.gotoxy(x, (y += 2));
            cout << "Ÿ�뽺 ������ : ��ü ��� ũ���� ���ݿ� �ִ� ��ϵ��� �Ҹ��Ų��";

            getInput();

            system("cls");

            //Ÿ�뽺 ������ �� ��� ===> �ѹ� ���, legend never die ���

            //<���� ���>
            PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
            PlaySound(TEXT("Joker.wav"), NULL, SND_FILENAME | SND_ASYNC);

            x = 17;
            y = 10;
            money();
            gui.SetColor(GREEN);
            gui.gotoxy(x, y);
            cout << "���� �ϼ��� �ڵ带 �����Ͽ� �÷��̸� �ϸ� �ȴ�. �̶����� ��ƿ� �����۵��� �� ����ؾ� �Ѵ�.";
            gui.gotoxy(x, (y += 2));
            cout << "�������� �ѹ� ����Ҷ����� �׸����� ���Ḧ �����ؾ��Ѵ�. " << endl;
            gui.gotoxy(x, (y += 2));
            cout << "������ �Ϸ��ϱ� ���ؼ� �̶����� ��ƿ� ���� ȿ�������� ����ؾ� �Ѵ�." << endl;
            gui.gotoxy(x, (y += 2));
            cout << "���� �ϼ��� �� �տ� �ٰ��Դ�. ";

            getInput();

            system("cls");


            x = 10;
            y = 8;
            money();
            gui.SetColor(GREEN);  //������ ��
            gui.gotoxy(x, y);
            cout << "��ź ������ : ������ ��ġ���� 4*4 ũ���� ����� �Ҹ��Ų��.";
            gui.SetColor(WHITE);
            gui.gotoxy(x, (y += 2));
            cout << "U Ű�� ���� ����ϰ� ����� �� 2000���� �����ȴ�." << endl;
            gui.SetColor(GREEN);
            gui.gotoxy(x, (y += 2));
            cout << "����� ������ : ������ ��ġ�� 4*4 �迭�� �����Ѵ�. �� �������� ��ſ��� ����� �� ���� �ƹ��� �𸨴ϴ�. " << endl;
            gui.SetColor(WHITE);
            gui.gotoxy(x, (y += 2));
            cout << "I Ű�� ���� ����ϰ� ����� �� 1000���� �����ȴ�." << endl;
            gui.SetColor(GREEN);
            gui.gotoxy(x, (y += 2));
            cout << "Ÿ�뽺 ������ : ��ü ��� ũ���� ���ݿ� �ִ� ��ϵ��� �Ҹ��Ų��" << endl;
            gui.SetColor(WHITE);
            gui.gotoxy(x, (y += 2));
            cout << "O Ű�� ���� ����ϰ� ����� �� 10000���� �����ȴ�." << endl;
            getInput();
            system("cls");


            if (save <= 4) {
                //���� 5
    //<���� 2,5 ���>
                PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                PlaySound(TEXT("Game2_5_Bgm.wav"), NULL, SND_LOOP | SND_ASYNC);

                this->level = 5;
                money();
                flag = play(5);


                if (flag) {
                    PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
                    PlaySound(TEXT("LGND.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    gui.show_gamesuccess();
                    gui.SetColor(WHITE);
                    system("cls");
                    x = 17;
                    y = 9;
                    gui.gotoxy(x, y);
                    cout << "���� ���׵��� �����Ͽ� ���� �ڵ带 �ϼ��Ͽ� Ŭ�����س´�.";
                    gui.gotoxy(x, (y += 2));
                    cout << "�� ������ �� ��Ʈ���� �ε��� 1�� �������� �ڸ���Ұ�, ";
                    gui.gotoxy(x, (y += 2));
                    cout << "�ڱ��� �����ߴ� ����� �� ��û�� �ں��� ������ �Ǿ���.";
                    gui.gotoxy(x, (y += 2));
                    cout << "������ ���� �ڵ带 ���İ� ����縦 �Ҽ��Ͽ���, ";
                    gui.gotoxy(x, (y += 2));
                    cout << "����ڵ��� ��̰� �� ���ӵ��� ����Ͽ� ���� ��ȹ�� �����.";

                    save = 4;

                    getInput();

                    system("cls");

                } else {
                    gui.show_gameover();
                    system("cls");
                    x = 28;
                    y = 13;
                    gui.gotoxy(x, y);
                    cout << "�� ���� ��ȸ�� ��ġ�� ���Ҵ�. ��Ÿ��� ��Ȳ������, �Ƿ��� ���̰� �ٽ� �õ��غ���.(y/n)" << endl;
                    //Sleep(1000);
                    //getch();
                    char t = getchar();
                    system("cls");
                    while (getchar() != '\n');
                    if (t == 'y') {
                        continue;
                    } else {
                        break;
                    }
                }
            }

            if (level == 5) {
                //���� ũ����
                break;
            }
        }
    }
};