#include "LoanTransfer.h"

void LoanTransfer::makeTransfer(int transferSum, int length){
    ///se transfera de la team1 la team2 contra transferSum bani
    this->player.setTeam(team2);
    this->team1.modifyBudget(transferSum);
    this->team2.modifyBudget(-transferSum);
    this->loanLength = length;
}

LoanTransfer::LoanTransfer(Team &team1, Team &team2, Player &player) :
    Transfer(team1, team2, player){}
