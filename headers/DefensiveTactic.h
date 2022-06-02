//
// Created by Radu on 18/05/2022.
//

#ifndef OOP_DEFENSIVETACTIC_H
#define OOP_DEFENSIVETACTIC_H

#include <ostream>
#include "../headers/Tactic.h"

class DefensiveTactic : public Tactic{
    void afisare(std::ostream &os) const override;
public:
    explicit DefensiveTactic(int points);
    DefensiveTactic (const DefensiveTactic& other);
    DefensiveTactic& operator=(DefensiveTactic other);
    friend void swap(DefensiveTactic& obj1, DefensiveTactic& obj2);
    void applyTactic(Team &team) override;
    [[nodiscard]] std::shared_ptr<Tactic> clone() const override;
    friend std::ostream &operator<<(std::ostream &os, const DefensiveTactic &tactic);
    ~DefensiveTactic() override;
};


#endif //OOP_DEFENSIVETACTIC_H
