#ifndef SHOOTER_H
#define SHOOTER_H

#include "roll.h"
#include <vector>

class Shooter {
public:
    Roll* throw_dice(Die& d1, Die& d2);
    void display_rolled_values();
    ~Shooter();

private:
    std::vector<Roll*> rolls;
};

#endif
