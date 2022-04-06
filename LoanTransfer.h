#ifndef OOP_LOANTRANSFER_H
#define OOP_LOANTRANSFER_H

#include "Transfer.h"

class LoanTransfer : public Transfer{
    int loanLength;
public:
    LoanTransfer(int team1, int team2, Player &player, int loanLength);

    //void makeTransfer(int loanLength);
};


#endif //OOP_LOANTRANSFER_H
