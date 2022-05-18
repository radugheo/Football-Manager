#ifndef OOP_LOANTRANSFER_H
#define OOP_LOANTRANSFER_H

#include <memory>
#include <utility>
#include "../headers/Transfer.h"

class LoanTransfer : public Transfer{
    unsigned int loanLength{};
public:
    LoanTransfer(unsigned int team1, unsigned int team2, Player &player, unsigned int loanLength);
    LoanTransfer(const LoanTransfer& other);
    friend std::ostream &operator<<(std::ostream &os, const LoanTransfer &loanTransfer);
    ~LoanTransfer() override;

    [[nodiscard]] std::shared_ptr<Transfer> clone() const override;

    void f() override;
};


#endif //OOP_LOANTRANSFER_H
