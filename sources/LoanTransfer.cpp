#include "../headers/LoanTransfer.h"

LoanTransfer::LoanTransfer(unsigned int team1, unsigned int team2, Player &player/*, unsigned int loanLength*/) :
    Transfer(team1, team2, player)/*,
    loanLength(loanLength)*/ {}

/*void LoanTransfer::makeTransfer(unsigned int length){
    ///se transfera de la team1 la team2 contra transferSum bani
    this->player.setTeam(team2);
    this->loanLength = length;
}

unsigned int LoanTransfer::getLoanLength() const {
    return loanLength;
}*/
