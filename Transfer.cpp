#include "Transfer.h"

Transfer::Transfer(Team &team1, Team &team2, Player &player) :
    team1(team1),
    team2(team2),
    player(player) {}


Transfer::Transfer(const Transfer& other) :
    team1(other.team1),
    team2(other.team2),
    player(other.player){}

Transfer& Transfer::operator=(const Transfer& other){
    team1 = other.team1;
    team2 = other.team2;
    player = other.player;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Transfer &transfer) {
    os << "team1: " << transfer.team1 << "\nteam2: " << transfer.team2 << "\nplayer: " << transfer.player;
    return os;
}

Transfer::~Transfer() {}

void Transfer::makeTransfer(int transferSum){
    ///se transfera de la team1 la team2 contra transferSum bani
    this->player.setTeam(team2);
    this->team1.modifyBudget(transferSum);
    this->team2.modifyBudget(-transferSum);
}
