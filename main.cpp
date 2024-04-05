#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "CinErrorHandler.h"

using namespace std;

void Menu1Print(int option);
void PrintBoard(int Xlocation, int Ylocation, vector<vector<vector<int> > > board, int sizeX, int sizeY);

int main() {
    int input=0;
    int Menu1Option=0;
    while(1) {
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
        try {
            cout << "Enter the width (range 0-40) of the board: ";
            cin >> sizeX;
            if(!CEH::CinErrorHandlerInt(sizeX, true, 0, 40))
                continue;
        }
        catch (CEH::CinError)
        {
            continue;
        }
        break;
    }
    while(true) {
        try {
            cout << "Enter the rows (range 0-40) of the board: ";
            cin >> sizeY;
            if(!CEH::CinErrorHandlerInt(sizeY, true, 0, 40))
                continue;
        }
        catch (CEH::CinError)
        {
            continue;
        }
        break;
    }
    while(true) {
        try {
            cout << "Enter the columns of bombs to spawn (range 0-"<<sizeX*sizeY-1<<": ";
            cin >> BombsN;
            if(!CEH::CinErrorHandlerInt(BombsN, true, 0, sizeX*sizeY-1))
                continue;
        }
        catch (CEH::CinError)
        {
            continue;
        }
        break;
    }
    vector<vector<vector<int> > > board (sizeX,vector<vector<int> >(sizeY,vector <int>(2,0)));
    for(int y=0; y<sizeY; y++)
    {
        for(int x=0; x<sizeX; x++)
        {
            board[x][y][0]=254;
        }
    }
    PrintBoard(0,0,board,sizeX,sizeY);
    system("pause");
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
    board[Xlocation][Ylocation][0]=233;
    for(int y=0; y<sizeY; y++)
    {
        for(int x=0; x<sizeX; x++)
        {
            cout<<(char)board[x][y][0];
        }
    }
}