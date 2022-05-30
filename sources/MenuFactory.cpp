//
// Created by Radu on 17/05/2022.
//

#include "../headers/MenuFactory.h"

Menu MenuFactory::homeScreen() { return Menu(1); }

Menu MenuFactory::selectScreen() { return Menu(2); }

Menu MenuFactory::gameScreen() { return Menu(3); }

Menu MenuFactory::squadScreen() { return Menu(4); }

Menu MenuFactory::onlyBack() { return Menu(5);}

Menu MenuFactory::playerTransferScreen() { return Menu(6); }

Menu MenuFactory::transferMarketScreen() {return Menu(7); }