#include "../headers/LoanTransfer.h"

LoanTransfer::LoanTransfer(unsigned int team1, unsigned int team2, Player &player, unsigned int loanLength) :
    Transfer{team1, team2, player},
    loanLength(loanLength) {}

LoanTransfer::LoanTransfer(const LoanTransfer& other) :
Transfer(other),
loanLength(other.loanLength) {}

LoanTransfer& LoanTransfer::operator=(const LoanTransfer& other){
    team1 = other.team1;
    team2 = other.team2;
    player = other.player;
    loanLength = other.loanLength;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const LoanTransfer &loanTransfer) {
    os << "team1: " << loanTransfer.team1 << "\nteam2: " << loanTransfer.team2 << "\nplayer: " << loanTransfer.player << "\nlength: " << loanTransfer.loanLength;
    return os;
}

LoanTransfer::~LoanTransfer() {}

std::shared_ptr<Transfer> LoanTransfer::clone() const {
    return std::make_shared<LoanTransfer>(*this);
}

void LoanTransfer::f() {
    //std::cout << "FFFF ";
}
