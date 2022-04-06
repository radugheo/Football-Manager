#include "LoanTransfer.h"

LoanTransfer::LoanTransfer(int team1, int team2, Player &player, int loanLength) :
    Transfer(team1, team2, player),
    loanLength(loanLength) {}

/*void LoanTransfer::makeTransfer(int length){
    ///se transfera de la team1 la team2 contra transferSum bani
    this->player.setTeam(team2);
    this->loanLength = length;
}
*/