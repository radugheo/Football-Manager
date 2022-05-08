#ifndef OOP_TRANSFER_H
#define OOP_TRANSFER_H

#include <ostream>
#include "../headers/Player.h"

class Transfer {
protected:
    unsigned int team1;
    unsigned int team2;
    Player& player;
public:
    Transfer(unsigned int team1, unsigned int team2, Player &player);
    Transfer(const Transfer& other);
    Transfer& operator=(const Transfer& other);
    friend std::ostream &operator<<(std::ostream &os, const Transfer &transfer);
    virtual ~Transfer();

    [[nodiscard]] virtual std::shared_ptr<Transfer> clone() const = 0;

    virtual void f() = 0;
};


#endif //OOP_TRANSFER_H
