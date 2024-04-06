#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <random>
#include "CinErrorHandler.h"

using namespace std;

void Menu1Print(int option);
void PrintBoard(int Xlocation, int Ylocation, vector<vector<vector<int> > > board, int sizeX, int sizeY);
void GenerateBombsLocation(int AmoutOfBombs, int StartXlocation, int StartYlocation, vector<vector<vector<int> > >& board, int sizeX, int sizeY);
void Unrevel(int Xlocation, int Ylocation, vector<vector<vector<int> > >& board, int sizeX, int sizeY);
bool BombHit(int Xlocation, int Ylocation, vector<vector<vector<int> > >& board);
void EndScreen(bool code);

int main() {
    int input;
    int Menu1Option=0;
    while(true) {
        Menu1Print(Menu1Option);
        input=getch();
        if(input==224) //arrow
        {
            Menu1Option++;
            if(Menu1Option>1)
                Menu1Option=0;
        } else if (input==32)
            break;
    }
    if(Menu1Option==1)
        system("exit");
    int sizeX=0, sizeY, BombsN;
    while(true) {
        while (true) {
            try {
                cout << "Enter the width (range 0-40) of the board: ";
                cin >> sizeX;
                if (!CEH::CinErrorHandlerInt(sizeX, true, 0, 40))
                    continue;
            }
            catch (CEH::CinError) {
                continue;
            }
            break;
        }
        while (true) {
            try {
                cout << "Enter the rows (range 0-40) of the board: ";
                cin >> sizeY;
                if (!CEH::CinErrorHandlerInt(sizeY, true, 0, 40))
                    continue;
            }
            catch (CEH::CinError) {
                continue;
            }
            break;
        }
        while (true) {
            try {
                cout << "Enter the columns of bombs to spawn (range 0-" << sizeX * sizeY - 1 << ": ";
                cin >> BombsN;
                if (!CEH::CinErrorHandlerInt(BombsN, true, 0, sizeX * sizeY - 1))
                    continue;
            }
            catch (CEH::CinError) {
                continue;
            }
            break;
        }
        vector<vector<vector<int> > > board(sizeX, vector<vector<int> >(sizeY, vector<int>(2, 0)));
        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                board[x][y][0] = 254;
            }
        }
        int crosLocation[2]{sizeX / 2, sizeY / 2};
        int EndOfGame = sizeX * sizeY - BombsN;
        bool EndCode;
        PrintBoard(crosLocation[0], crosLocation[1], board, sizeX, sizeY);
        input = getch();
        if (input == 'w') //arrow
        {
            crosLocation[1]--;
            if (crosLocation[1] < 0)
                crosLocation[1] = sizeY - 1;
            if (crosLocation[1] >= sizeY)
                crosLocation[1] = 0;
        } else if (input == 's') {
            crosLocation[1]++;
            if (crosLocation[1] >= sizeY)
                crosLocation[1] = 0;
        } else if (input == 'a') {
            crosLocation[0]--;
            if (crosLocation[0] < 0)
                crosLocation[0] = sizeX - 1;
        } else if (input == 'd') {
            crosLocation[0]++;
            if (crosLocation[0] >= sizeY)
                crosLocation[0] = 0;
        } else if (input == ' ') {
            EndOfGame--;
            if (EndOfGame != 0) {
                GenerateBombsLocation(BombsN, crosLocation[0], crosLocation[1], board, sizeX, sizeY);
                Unrevel(crosLocation[0], crosLocation[1], board, sizeX, sizeY);
            }

        }
        while (1) {
            if (EndOfGame == 0) {
                EndCode = 1;
                break;
            }
            PrintBoard(crosLocation[0], crosLocation[1], board, sizeX, sizeY);
            input = getch();
            if (input == 'w') //arrow
            {
                crosLocation[1]--;
                if (crosLocation[1] < 0)
                    crosLocation[1] = sizeY - 1;
                if (crosLocation[1] >= sizeY)
                    crosLocation[1] = 0;
            } else if (input == 's') {
                crosLocation[1]++;
                if (crosLocation[1] >= sizeY)
                    crosLocation[1] = 0;
            } else if (input == 'a') {
                crosLocation[0]--;
                if (crosLocation[0] < 0)
                    crosLocation[0] = sizeX - 1;
            } else if (input == 'd') {
                crosLocation[0]++;
                if (crosLocation[0] >= sizeY)
                    crosLocation[0] = 0;
            } else if (input == ' ') {
                if (board[crosLocation[0]][crosLocation[1]][0] != 254)
                    continue;
                if (BombHit(crosLocation[0], crosLocation[1], board)) {
                    EndCode = 0;
                    break;
                }
                EndOfGame--;
                Unrevel(crosLocation[0], crosLocation[1], board, sizeX, sizeY);
            } else if (input == 'f') {
                if (board[crosLocation[0]][crosLocation[1]][0] == 70)
                    board[crosLocation[0]][crosLocation[1]][0] = 254;
                else if (board[crosLocation[0]][crosLocation[1]][0] == 254)
                    board[crosLocation[0]][crosLocation[1]][0] = 70;
            } else if (input == 27) {
                break;
            }
        }
        EndScreen(EndCode);
    }
    return 0;
}

void Menu1Print(int option)
{
    string pointer="-> ";
    system("cls");
    cout<<" /$$      /$$ /$$$$$$$$ /$$        /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$       /$$$$$$$$ /$$$$$$         /$$$$$$   /$$$$$$  /$$$$$$$  /$$$$$$$$ /$$$$$$$ "<<endl;
    cout<<"| $$  /$ | $$| $$_____/| $$       /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/      |__  $$__//$$__  $$       /$$__  $$ /$$__  $$| $$__  $$| $$_____/| $$__  $$"<<endl;
    cout<<"| $$ /$$$| $$| $$      | $$      | $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$               | $$  | $$  \\ $$      | $$  \\__/| $$  \\ $$| $$  \\ $$| $$      | $$  \\ $$"<<endl;
    cout<<"| $$/$$ $$ $$| $$$$$   | $$      | $$      | $$  | $$| $$ $$/$$ $$| $$$$$            | $$  | $$  | $$      |  $$$$$$ | $$$$$$$$| $$$$$$$/| $$$$$   | $$$$$$$/"<<endl;
    cout<<"| $$$$_  $$$$| $$__/   | $$      | $$      | $$  | $$| $$  $$$| $$| $$__/            | $$  | $$  | $$       \\____  $$| $$__  $$| $$____/ | $$__/   | $$__  $$"<<endl;
    cout<<"| $$$/ \\  $$$| $$      | $$      | $$    $$| $$  | $$| $$\\  $ | $$| $$               | $$  | $$  | $$       /$$  \\ $$| $$  | $$| $$      | $$      | $$  \\ $$"<<endl;
    cout<<"| $$/   \\  $$| $$$$$$$$| $$$$$$$$|  $$$$$$/|  $$$$$$/| $$ \\/  | $$| $$$$$$$$         | $$  |  $$$$$$/      |  $$$$$$/| $$  | $$| $$      | $$$$$$$$| $$  | $$"<<endl;
    cout<<"|__/     \\__/|________/|________/ \\______/  \\______/ |__/     |__/|________/         |__/   \\______/        \\______/ |__/  |__/|__/      |________/|__/  |__/"<<endl;
    cout<<endl;
    if(option==0)
    {
        cout<<pointer<<"Start game"<<endl;
        cout<<"Exit"<<endl;
    }
    else if (option==1)
    {
        cout<<"Start game"<<endl;
        cout<<pointer<<"Exit"<<endl;
    }
}

void PrintBoard(int Xlocation, int Ylocation, vector<vector<vector<int> > > board, int sizeX, int sizeY)
{
    system("cls");
    board[Xlocation][Ylocation][0]=111;
    for(int y=0; y<sizeY; y++)
    {
        for(int x=0; x<sizeX; x++) {
            cout << (char) board[x][y][0]<<" ";
        }
        cout<<endl;
    }
    cout<<"Controls: w-up, s-down, d-right, a-left, space-check, f-place flag, Esc-exit"<<endl;
}

void GenerateBombsLocation(int AmoutOfBombs, int StartXlocation, int StartYlocation, vector<vector<vector<int> > >& board, int sizeX, int sizeY)
{
    for(int i=0; i<AmoutOfBombs; i++)
    {
        int x,y;
        random_device rx;   //numer generator for x axis
        mt19937 xgen(rx());
        uniform_int_distribution<> dxr(0, sizeX-1);
        random_device ry;   //numer generator for x axis
        mt19937 rgen(rx());
        uniform_int_distribution<> dyr(0, sizeX-1);
        while(true) {
            x = dxr(rx);
            y = dyr(ry);
            if (board[x][y][1] == 0 and x!=StartXlocation and y!=StartYlocation) {
                board[x][y][1] = 1;
                break;
            }
        }
    }
}

bool BombHit(int Xlocation, int Ylocation, vector<vector<vector<int> > >& board)
{
    if(board[Xlocation][Ylocation][1]==1)
        return true;
    else
        return false;
}

void Unrevel(int Xlocation, int Ylocation, vector<vector<vector<int> > >& board, int sizeX, int sizeY)
{
    int BombsNear=0;
    if(Xlocation!=0)
        if(BombHit(Xlocation-1, Ylocation, board))
            BombsNear++;
    if(Xlocation+1!=sizeX)
        if(BombHit(Xlocation+1, Ylocation, board))
            BombsNear++;
    if(Ylocation!=0)
        if(BombHit(Xlocation, Ylocation-1, board))
            BombsNear++;
    if(Ylocation+1!=sizeY)
        if(BombHit(Xlocation, Ylocation+1, board))
            BombsNear++;

    if(Xlocation!=0 and Ylocation!=0)
        if(BombHit(Xlocation-1, Ylocation-1, board))
            BombsNear++;
    if(Xlocation!=0 and Ylocation+1!=sizeY)
        if(BombHit(Xlocation-1, Ylocation+1, board))
            BombsNear++;
    if(Xlocation+1!=sizeX and Ylocation!=0)
        if(BombHit(Xlocation+1, Ylocation-1, board))
            BombsNear++;
    if(Xlocation+1!=sizeX and Ylocation+1!=sizeY)
        if(BombHit(Xlocation+1, Ylocation+1, board))
            BombsNear++;

    if(BombsNear==0)
        BombsNear=255;
    else
        BombsNear+=48;
    board[Xlocation][Ylocation][0]=BombsNear;
}

void EndScreen(bool code)
{
    int input;
    int EndMenuOption=0;
    while (true) {
        system("cls");
        if (code == 0) {
            cout << " /$$     /$$ /$$$$$$  /$$   /$$       /$$        /$$$$$$   /$$$$$$  /$$$$$$$$" << endl;
            cout << "|  $$   /$$//$$__  $$| $$  | $$      | $$       /$$__  $$ /$$__  $$| $$_____/" << endl;
            cout << "\\  $$ /$$/| $$  \\ $$| $$  | $$      | $$      | $$  \\ $$| $$  \\__/| $$      " << endl;
            cout << "  \\  $$$$/ | $$  | $$| $$  | $$      | $$      | $$  | $$|  $$$$$$ | $$$$$   " << endl;
            cout << "   \\  $$/  | $$  | $$| $$  | $$      | $$      | $$  | $$ \\____  $$| $$__/   " << endl;
            cout << "    | $$   | $$  | $$| $$  | $$      | $$      | $$  | $$ /$$  \\ $$| $$      " << endl;
            cout << "    | $$   |  $$$$$$/|  $$$$$$/      | $$$$$$$$|  $$$$$$/|  $$$$$$/| $$$$$$$$" << endl;
            cout << "    |__/    \\______/  \\______/       |________/ \\______/  \\______/ |________/" << endl;
        } else if (code == 1) {
            cout << " /$$     /$$ /$$$$$$  /$$   /$$       /$$      /$$ /$$ /$$   /$$" << endl;
            cout << "|  $$   /$$//$$__  $$| $$  | $$      | $$  /$ | $$|__/| $$$ | $$" << endl;
            cout << " \\  $$ /$$/| $$  \\ $$| $$  | $$      | $$ /$$$| $$ /$$| $$$$| $$" << endl;
            cout << "  \\  $$$$/ | $$  | $$| $$  | $$      | $$/$$ $$ $$| $$| $$ $$ $$" << endl;
            cout << "   \\  $$/  | $$  | $$| $$  | $$      | $$$$_  $$$$| $$| $$  $$$$" << endl;
            cout << "    | $$   | $$  | $$| $$  | $$      | $$$/ \\  $$$| $$| $$\\  $$$" << endl;
            cout << "    | $$   |  $$$$$$/|  $$$$$$/      | $$/   \\  $$| $$| $$ \\  $$" << endl;
            cout << "    |__/    \\______/  \\______/       |__/     \\__/|__/|__/  \\__/" << endl;
        }
        cout<<"Do you wanna play again?"<<endl;
        if(EndMenuOption==0)
        {
            cout<<"->Yes"<<endl;
            cout<<"No"<<endl;
        }
        if(EndMenuOption==1)
        {
            cout<<"Yes"<<endl;
            cout<<"->No"<<endl;
        }
        input = getch();
        if (input == 224 or input==119 or input==115) //arrow
        {
            EndMenuOption++;
            if (EndMenuOption > 1)
                EndMenuOption = 0;
        }else if (input== 32 )
        {
            if (EndMenuOption==1)
                exit(0);
            else
                break;
        }
    }
}