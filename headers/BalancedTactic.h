//
// Created by Radu on 19/05/2022.
//

#ifndef OOP_BALANCEDTACTIC_H
#define OOP_BALANCEDTACTIC_H

#include "../headers/Tactic.h"

class BalancedTactic : public Tactic{
    void afisare(std::ostream &os) const override;
public:
    explicit BalancedTactic(int points);
    BalancedTactic (const BalancedTactic& other);
    BalancedTactic& operator=(BalancedTactic other);
    friend void swap(BalancedTactic& obj1, BalancedTactic& obj2);
    void applyTactic(Team& team) override;
    [[nodiscard]] std::shared_ptr<Tactic> clone() const override;
    friend std::ostream &operator<<(std::ostream &os, const BalancedTactic &tactic);
    ~BalancedTactic() override;
};


#endif //OOP_BALANCEDTACTIC_H
