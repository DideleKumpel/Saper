//
// Created by CEM on 27.03.2024.
//
#include "CinErrorHandler.h"

#include <iostream>
#include <cmath>

    void CEH::CinErrorHandler() {
        if (std::cin.fail()) {
            std::cout << "Please enter the number." << std::endl;
            system("pause");
            system("CLS");
            std::cin.clear();
            std::cin.ignore();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            CEH::CinError flaga;
            throw flaga;
        }
    }

    bool CEH::CinErrorHandlerInt(long long int odpowiedz,bool range, long long int zakresP, long long int zakresK) {
        try {
            CEH::CinErrorHandler();
        }
        catch (CEH::CinError) {
            return false;
        }
        if (range== true and (odpowiedz < zakresP or odpowiedz > zakresK)) {
            std::cout << "An out of range number was entered." << std::endl;
            system("pause");
            system("CLS");
            return false;
        }
        return true;
    }