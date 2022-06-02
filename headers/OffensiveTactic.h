//
// Created by Radu on 19/05/2022.
//

#ifndef OOP_OFFENSIVETACTIC_H
#define OOP_OFFENSIVETACTIC_H

#include "Tactic.h"

class OffensiveTactic : public Tactic{
    void afisare(std::ostream &os) const override;
public:
    explicit OffensiveTactic(int points);
    OffensiveTactic (const OffensiveTactic& other);
    OffensiveTactic& operator=(OffensiveTactic other);
    friend void swap(OffensiveTactic& obj1, OffensiveTactic& obj2);
    void applyTactic(Team& team) override;
    [[nodiscard]] std::shared_ptr<Tactic> clone() const override;
    friend std::ostream &operator<<(std::ostream &os, const OffensiveTactic &tactic);
    virtual ~OffensiveTactic();
};


#endif //OOP_OFFENSIVETACTIC_H
