#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

void gotoxy(int x, int y) //고1투 XY 제어함수를소환하다
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void newcls()
{
    for (short newcls = 2; newcls <= 18; newcls++) //화면초기화
    {
        gotoxy(3, newcls);
        std::cout << "                                                      ";
    }
}

void summonbox()
{
    gotoxy(2, 1); //사각박스소1234567890환
    std::cout << "┌───────────────────────────────────────────────────────┐";

    for (short i = 2; i <= 18; i++)
    {
        gotoxy(2, i);
        std::cout << "│                                                       │";
    }
    gotoxy(2, 19);
    std::cout << "└───────────────────────────────────────────────────────┘";
}

int main()
{
    system("title Taget_Shooting");

    CONSOLE_CURSOR_INFO cursorInfo = { 0, }; //커서 투명화
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    short key = 0; //키입력
    short px = 0; //플레2어X
    short py = 0;//플레2어Y

    short hp = 0; //HP
    int hpgod = 0;
    int hpgodview = 0;
    int score = 0; //스코어

    bool bullet = 0; //히히총알발싸트리12거
    short bulletx[16] = { 0, }; //총알들X
    short bullety[16] = { 0, }; //총알들Y
    int bulletCooldown = 0; //발싸쿨1타임

    short tgtype[8] = { 0, };
    short tgxr = 0;
    short tgyr = 0;
    short tgX[8] = { 0, };
    short tgY[8] = { 0, };
    short tgbulletx[8][16] = { 0, };
    short tgbullety[8][16] = { 0, };
    bool tgspawn = 0;
    int tgspawnCooldown = 0;
    int tgbt[8][16] = { 0, };
    int tgcd[8] = { 0, };
    short tgtr[8] = { 0, };
    short tgbrt = 2;
    short tgrandmove[8] = { 0, };
    int tgrandmovecd[8] = { 0, };
    bool tgon[8] = { 0, };
    short tgrandhp = 0;
    int tgrandhpmove = 0;
    short hpballX = 0;
    short hpballY = 0;

    int bosstime = 0;
    bool bossalert = 0; //추가예정
    bool boss = 0;
    short bossX = 0;
    short bossY = 0;
    short bosshp = 0;
    short bossbulletx[2][16] = { 0, };
    short bossbullety[2][16] = { 0, };

    short timetohard = 0;
    int timetohardcd = 0;

    int startblank = 0; //프레스투스타트깜빡임제어시간변수

    clock_t bt[16]{};
    summonbox();

    gotoxy(24, 10);
    startblank = clock(); //프레스투스타트깜빡임제어

    while (1)
    {
        if (clock() - startblank < 500){gotoxy(24, 10);std::cout << "PRESS TO START";}
        if (clock() - startblank >= 500){gotoxy(24, 10);std::cout << "              ";if (clock() - startblank > 1000)startblank = clock();}
        if (_kbhit())break;} //눌러서시작
    system("cls"); //게임설정

    srand((unsigned int)time(NULL) + clock());

    px = 30;
    py = 10;

    hp = 3;

    tgyr = 2;
    timetohard = 500;
    timetohardcd = (unsigned int)time(NULL) + 2;
    summonbox();

    while (1) //게임시작
    {
        if (hp <= 0) {
            system("cls");
            printf("\a");
            gotoxy(2, 1); //사각박스소1234567890환2
            summonbox();
            newcls();
            gotoxy(3, 0);
            std::cout << "Score:" << score;
            std::cout << " (esc to exit)";
            while (1)
            {
                if (clock() - startblank < 500)
                {
                    gotoxy(26, 10);
                    std::cout << "GAME OVER";
                }
                if (clock() - startblank >= 500)
                {
                    gotoxy(26, 10);
                    std::cout << "              ";

                    if (clock() - startblank > 1000)
                        startblank = clock();
                }
                if (_kbhit())
                {
                    key = _getch(); //키 인식
                    switch (key)
                        case 27: return 0;
                }
            }
        }

        if (timetohardcd - (unsigned int)time(NULL) <= 0)
        {
            timetohardcd = (unsigned int)time(NULL) + 2;
            if (timetohard > 1)
                timetohard--;
        }

        if (px >= hpballX - 2 && px <= hpballX + 2 && py == hpballY && hpballX != 0 && hpballY != 0)
        {
            hpballX = 0;
            hpballY = 0;
            hp++;
        }

        if (hp > 3)
            hp = 3;

        if (_kbhit())
        {
            key = _getch(); //키 인식
            switch (key)
            {
            case 72: py--; break;
            case 75: px -= 2; break;
            case 77: px += 2; break;
            case 80: py++; break;
            case 32: bullet = 1; break;
            case 104: tgrandhp = 1; break;
            case 27: return 0;
            }

            if (px < 6){px = 6;}
            if (px > 54){px = 54;}
            if (py < 2){py = 2;}
            if (py > 18){py = 18;}

            newcls(); //화면초기화
        }

        gotoxy(3, 0);
        std::cout << "Score:" << score << " HP: ";//상태창
        if (hp == 0)
            std::cout << "○○○    ";
        if (hp == 1)
            std::cout << "●○○    ";
        if (hp == 2)
            std::cout << "●●○    ";
        if (hp == 3)
            std::cout << "●●●    ";
        std::cout << "[{debug} key:" << key << "]";

        srand((unsigned int)time(NULL) + clock());

        if (tgspawn == 1 && tgspawnCooldown - clock() <= 0)
        {
            tgxr = (rand() % 23) * 2 + 6;
            for (short i = 0; i <= 7; i++)
            {
                if (tgspawnCooldown - clock() > 0)
                {
                    break;
                }

                if (tgX[i] == 0 && tgY[i] == 0 || tgon[i] == 0)
                {
                    srand((unsigned int)time(NULL) + clock());
                    tgon[i] = 1;
                    tgX[i] = tgxr; tgY[i] = tgyr;
                    tgtype[i] = rand() % 5;
                    tgspawn = rand() % 8;
                    i = 9;
                }
            }
            tgspawnCooldown = clock() + 500;
        }
        else if (tgspawnCooldown - clock() <= 0)
        {
            srand((unsigned int)time(NULL) + clock());
            tgspawn = rand() % 4;
            tgspawnCooldown = clock() + timetohard;
        }

        for (short i = 0; i <= 7; i++)
        {
            for (short j = 0; j <= 15; j++)
            {
                for (short ib = 0; ib <= 15; ib++)
                {
                    if (tgX[i] != 0 && tgY[i] != 0)
                    {
                        if (tgX[i] >= bulletx[ib] - 2 && tgX[i] <= bulletx[ib] + 2 && tgY[i] == bullety[ib] && bulletx[ib] != 0 && bullety[ib] != 0)
                        {
                            gotoxy(tgX[i] - 2, tgY[i]);
                            std::cout << " ◆◆◆ ";
                            gotoxy(tgX[i] - 2, tgY[i]);
                            std::cout << "     ";

                           
                            if (tgrandhp == 1 && hpballX != 0 && hpballY != 0)
                            {
                                hpballX = tgX[i];
                                hpballY = tgY[i];
                            }
                            tgrandhp = rand() % 16;

                            tgX[i] = 0;
                            tgY[i] = 0;
                            tgon[i] = 0;
                            score++;

                        }
                    }
                }

                if (px >= tgbulletx[i][j] - 2 && px <= tgbulletx[i][j] + 2 && py == tgbullety[i][j] && hpgod - clock() <= 0)
                {
                    hpgod = clock() + 5000;
                    hp --;
                }

                if (tgcd[i] - clock() <= 0)
                {
                    srand((unsigned int)time(NULL) + clock());
                    tgtr[i] = rand() % tgbrt;
                }
                if (tgtr[i] == 1 && tgcd[i] - clock() <= 0 && tgbulletx[i][j] == 0 && tgbullety[i][j] == 0 && tgon[i] == 1)
                {

                    tgcd[i] = clock() + 200; //히히 터25겟 총1알 발싸 쿨타임
                    tgbulletx[i][j] = tgX[i];
                    tgbullety[i][j] = tgY[i];
                    tgcd[i] = clock();
                    tgtr[i] = 0;
                }

                if (clock() - tgbt[i][j] >= 100)
                {
                        tgbullety[i][j] += 1;
                        tgbt[i][j] = clock();
                }

                if (tgbullety[i][j] > 18 && tgbullety[i][j] != 0) //타깃총알나간거 초1기화
                {
                    gotoxy(tgbulletx[i][j], tgbullety[i][j] - 1);
                    std::cout << " ";
                    tgbulletx[i][j] = 0;
                    tgbullety[i][j] = 0;
                }

                if (tgbulletx[i][j] != 0 && tgbullety[i][j] != 0) //타깃총알 화면에출력
                {
                    gotoxy(tgbulletx[i][j], tgbullety[i][j]);
                    std::cout << "☆";
                    if (tgbullety[i][j] > 2)
                    {
                        gotoxy(tgbulletx[i][j], tgbullety[i][j] - 1);
                        std::cout << " ";
                    }
                }

            }

            if (clock() - tgrandhpmove >= 400)
            {
                hpballY ++;
                tgrandhpmove = clock();
            }

            srand((unsigned int)time(NULL) + clock());
            tgrandmove[i] = rand() % 9;

            if (tgrandmovecd[i] - clock() <= 0 && tgX[i] != 0 && tgY[i] != 0 && tgon[i] == 1)
            {

                if (tgrandmove[i] >= 0 && tgrandmove[i] <= 2)
                {
                    newcls();
                    tgX[i] ++;
                }
                if (tgrandmove[i] >= 3 && tgrandmove[i] <= 6)
                {
                    newcls();
                    tgX[i] --;
                }
                if (tgrandmove[i] == 7 && tgY[i] <= 3)
                {
                    newcls();
                    tgY[i] ++;
                }
                if (tgrandmove[i] == 8)
                {
                    newcls();
                    tgY[i] --;
                }
                tgrandmovecd[i] = clock() + 500;
            }

            if (tgX[i] != 0 && tgY[i] != 0)
            {
                if (tgX[i] < 6)
                    tgX[i] = 6;
                if (tgX[i] > 54)
                    tgX[i] = 54;
                if (tgY[i] < 2)
                    tgY[i] = 2;
                if (tgY[i] > 18)
                    tgY[i] = 18;
            }
            if (hpballX != 0 && hpballY != 0 && hpballY >= 19)
            {
                hpballX = 0;
                hpballY = 0;
            }
        }

        if (bullet == 1 && bulletCooldown - clock() <= 0)
        {
            bulletCooldown = clock() + 60; //히히 총1알 발싸 쿨타임
            for (short i = 0; i <= 15; i++)
            {
                if (bulletx[i] == 0 && bullety[i] == 0)
                {
                    bulletx[i] = px;
                    bullety[i] = py;
                    bt[i] = clock();
                    i = 17;
                }
            }
            bullet = 0;
        }

        for (short i = 0; i <= 15; i++) //총알이동
        {
            if (clock() - bt[i] >= 50)
            {
                bullety[i] -= 1;
                bt[i] = clock();

            }

            if (bullety[i] < 2 && bullety[i] != 0) //총알나간거 초1기화
            {
                gotoxy(bulletx[i], bullety[i] + 1);
                std::cout << "   ";
                bulletx[i] = 0;
                bullety[i] = 0;
            }

            if (bulletx[i] != 0 && bullety[i] != 0 ) //총알 화면에출력
            {
                gotoxy(bulletx[i], bullety[i]);
                std::cout << "★";
                if (bullety[i] < 18)
                {
                    gotoxy(bulletx[i], bullety[i] + 1);
                    std::cout << "   ";
                }
            }

        }

        for (short i = 0; i <= 7; i++)
        {
            if (tgX[i] > 1 && tgY[i] > 1 && tgon[i] == 1) //타깃 화면에출력
            {
                gotoxy(tgX[i] - 2, tgY[i]);
                if (tgtype[i] == 0)
                    std::cout << "(-@-)";
                if (tgtype[i] == 1)
                    std::cout << "{-+-}";
                if (tgtype[i] == 2)
                    std::cout << "[-$-]";
                if (tgtype[i] == 3)
                    std::cout << ":-!-:";
                if (tgtype[i] == 4)
                    std::cout << "|-=-|";
                if (tgtype[i] >= 5)
                    std::cout << "0-^-0";
            }
        }

        if (hpballX != 0 && hpballY != 0)
        {
            if (hpballY > 3)
            {
                gotoxy(hpballX, hpballY -2);
                std::cout << " ";
            }

            gotoxy(hpballX, hpballY);
            std::cout << "●";
        }

        if (hpgod - clock() > 0) {
            hpgodview++;
            if (hpgodview < 50)
            {
                gotoxy(px - 2, py);
                std::cout << "     ";

            }
            if (hpgodview >= 50)
            {
                gotoxy(px - 2, py);
                std::cout << "◀-■-▶";
                if (hpgodview > 100)
                    hpgodview = 0;
            }

        }
        else
        {
            gotoxy(px - 2, py);
            std::cout << "◀-■-▶";
        }

    }
    return 0;
}