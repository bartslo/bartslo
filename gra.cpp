#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

const int WIDTH = 60;
const int HEIGHT = 20;

struct Player
{
    float y;
    float velocity;
};

int main()
{
    srand((unsigned)time(nullptr));

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Ukrycie kursora
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    Player player;
    player.y = HEIGHT / 2;
    player.velocity = 0;

    vector<int> gapCenter(WIDTH, HEIGHT / 2);

    int score = 0;
    int frame = 0;
    bool gameOver = false;

    while (!gameOver)
    {
        frame++;

        // Sterowanie
        if (_kbhit())
        {
            char key = _getch();

            if (key == 'w' || key == 'W')
            {
                player.velocity -= 0.7f;

                if (player.velocity < -1.5f)
                    player.velocity = -1.5f;
            }
        }

        // Grawitacja
        player.velocity += 0.08f;
        player.y += player.velocity;

        // Przesuwanie tunelu
        for (int i = 0; i < WIDTH - 1; i++)
        {
            gapCenter[i] = gapCenter[i + 1];
        }

        if (frame < 80) // oko³o 5 sekund spokoju
        {
            gapCenter[WIDTH - 1] = HEIGHT / 2;
        }
        else
        {
            int newGap = gapCenter[WIDTH - 2] + (rand() % 3 - 1);

            if (newGap < 6)
                newGap = 6;

            if (newGap > HEIGHT - 7)
                newGap = HEIGHT - 7;

            gapCenter[WIDTH - 1] = newGap;
        }

        // Rysowanie
        string screen;

        for (int y = 0; y < HEIGHT; y++)
        {
            for (int x = 0; x < WIDTH; x++)
            {
                int gapTop = gapCenter[x] - 5;
                int gapBottom = gapCenter[x] + 5;

                if (x == 10 && y == (int)player.y)
                {
                    screen += ">";
                }
                else if (y < gapTop || y > gapBottom)
                {
                    screen += "#";
                }
                else
                {
                    screen += " ";
                }
            }

            screen += '\n';
        }

        COORD pos = {0, 0};
        SetConsoleCursorPosition(hConsole, pos);

        cout << screen;
        cout << "Punkty: " << score << "\n";
        cout << "Sterowanie: W = gora\n";

        // Kolizja
        int playerX = 10;

        int gapTop = gapCenter[playerX] - 5;
        int gapBottom = gapCenter[playerX] + 5;

        if (player.y < gapTop || player.y > gapBottom)
            gameOver = true;

        if (player.y < 0 || player.y >= HEIGHT)
            gameOver = true;

        score++;

        Sleep(60);
    }

    system("cls");

    cout << "=================================\n";
    cout << "         GAME OVER\n";
    cout << "=================================\n";
    cout << "Twoj wynik: " << score << "\n\n";

    system("pause");
    return 0;
}
