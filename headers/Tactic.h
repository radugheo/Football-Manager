//
// Created by Radu on 18/05/2022.
//

#ifndef OOP_TACTIC_H
#define OOP_TACTIC_H

#include <memory>

class Team;

class Tactic {
protected:
    int points;
    virtual void afisare(std::ostream& os) const;
public:
    explicit Tactic(int points);
    Tactic(const Tactic& other);
    Tactic& operator=(const Tactic& other);
    virtual void applyTactic(Team& team) = 0;
    virtual std::shared_ptr<Tactic> clone() const = 0;
    friend std::ostream &operator<<(std::ostream &os, const Tactic &tactic);
    virtual ~Tactic();
};


#endif //OOP_TACTIC_H
