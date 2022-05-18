#include "../headers/LoanTransfer.h"

LoanTransfer::LoanTransfer(unsigned int team1, unsigned int team2, Player &player, unsigned int loanLength) :
    Transfer{team1, team2, player},
    loanLength(loanLength) {}

LoanTransfer::LoanTransfer(const LoanTransfer& other) :
Transfer(other),
loanLength(other.loanLength) {}

std::ostream &operator<<(std::ostream &os, const LoanTransfer &loanTransfer) {
    os << static_cast<const Transfer &>(loanTransfer) << "\nLength: " << loanTransfer.loanLength;
    return os;
}

LoanTransfer::~LoanTransfer() {}

std::shared_ptr<Transfer> LoanTransfer::clone() const {
    return std::make_shared<LoanTransfer>(*this);
}

void LoanTransfer::f() {
    //std::cout << "FFFF ";
}
