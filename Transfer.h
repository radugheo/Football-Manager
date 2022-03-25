#ifndef OOP_TRANSFER_H
#define OOP_TRANSFER_H

#include <ostream>
#include "Team.h"
#include "Player.h"

class Transfer {
protected:
    Team& team1;
    Team& team2;
    Player& player;
public:
    Transfer(Team &team1, Team &team2, Player &player);
    Transfer(const Transfer& other);
    Transfer& operator=(const Transfer& other);
    friend std::ostream &operator<<(std::ostream &os, const Transfer &transfer);
    ~Transfer();

    void makeTransfer(int transferSum);
};


#endif //OOP_TRANSFER_H
