//
// Created by Radu on 17/05/2022.
//

#ifndef OOP_MENUFACTORY_H
#define OOP_MENUFACTORY_H

#include "../headers/Menu.h"

class MenuFactory {
public:
    static Menu homeScreen();
    static Menu selectScreen();
    static Menu gameScreen();
    static Menu squadScreen();
};


#endif //OOP_MENUFACTORY_H
