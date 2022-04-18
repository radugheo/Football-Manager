#ifndef OOP_LOANTRANSFER_H
#define OOP_LOANTRANSFER_H

#include "../headers/Transfer.h"

class LoanTransfer : public Transfer{
    unsigned int loanLength;
public:
    LoanTransfer(unsigned int team1, unsigned int team2, Player &player, unsigned int loanLength);
    //void makeTransfer(unsigned int loanLength);

    //unsigned int getLoanLength() const;
};


#endif //OOP_LOANTRANSFER_H
