#include <iostream>

using namespace std;

// Funkcja rysująca planszę
void wyswietlPlansze(char plansza[3][3])
{
    cout << "\n";

    for(int i = 0; i < 3; i++)
    {
        cout << " ";

        for(int j = 0; j < 3; j++)
        {
            cout << plansza[i][j];

            if(j < 2)
            {
                cout << " | ";
            }
        }

        cout << "\n";

        if(i < 2)
        {
            cout << "---+---+---\n";
        }
    }

    cout << "\n";
}

// Funkcja sprawdzająca zwycięstwo
bool czyWygrana(char plansza[3][3], char gracz)
{
    // Wiersze
    for(int i = 0; i < 3; i++)
    {
        if(plansza[i][0] == gracz &&
           plansza[i][1] == gracz &&
           plansza[i][2] == gracz)
        {
            return true;
        }
    }

    // Kolumny
    for(int j = 0; j < 3; j++)
    {
        if(plansza[0][j] == gracz &&
           plansza[1][j] == gracz &&
           plansza[2][j] == gracz)
        {
            return true;
        }
    }

    // Przekątna główna
    if(plansza[0][0] == gracz &&
       plansza[1][1] == gracz &&
       plansza[2][2] == gracz)
    {
        return true;
    }

    // Przekątna poboczna
    if(plansza[0][2] == gracz &&
       plansza[1][1] == gracz &&
       plansza[2][0] == gracz)
    {
        return true;
    }

    return false;
}

// Funkcja sprawdzająca remis
bool czyRemis(char plansza[3][3])
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(plansza[i][j] == ' ')
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    char plansza[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char aktualnyGracz = 'X';

    int wiersz;
    int kolumna;

    cout << "=== KOLKO I KRZYZYK ===\n";

    while(true)
    {
        wyswietlPlansze(plansza);

        cout << "Gracz " << aktualnyGracz << "\n";
        cout << "Podaj wiersz (1-3): ";
        cin >> wiersz;

        cout << "Podaj kolumne (1-3): ";
        cin >> kolumna;

        wiersz--;
        kolumna--;

        // Sprawdzenie zakresu
        if(wiersz < 0 || wiersz > 2 ||
           kolumna < 0 || kolumna > 2)
        {
            cout << "\nNieprawidlowe pole!\n\n";
            continue;
        }

        // Sprawdzenie zajętego pola
        if(plansza[wiersz][kolumna] != ' ')
        {
            cout << "\nTo pole jest juz zajete!\n\n";
            continue;
        }

        plansza[wiersz][kolumna] = aktualnyGracz;

        if(czyWygrana(plansza, aktualnyGracz))
        {
            wyswietlPlansze(plansza);
            cout << "Gracz " << aktualnyGracz << " wygrywa!\n";
            break;
        }

        if(czyRemis(plansza))
        {
            wyswietlPlansze(plansza);
            cout << "Remis!\n";
            break;
        }

        if(aktualnyGracz == 'X')
        {
            aktualnyGracz = 'O';
        }
        else
        {
            aktualnyGracz = 'X';
        }
    }

    return 0;
}