#ifndef OOP_LOANTRANSFER_H
#define OOP_LOANTRANSFER_H

#include "Transfer.h"

class LoanTransfer : public Transfer{
    int loanLength;
public:
    LoanTransfer(Team &team1, Team &team2, Player &player);

    void makeTransfer(int transferSum, int loanLength);
};


#endif //OOP_LOANTRANSFER_H
