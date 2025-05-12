#include "shooter.h"
#include <iostream>

Roll* Shooter::throw_dice(Die& d1, Die& d2) {
    Roll* roll = new Roll(d1, d2);
    roll->roll_dice();
    rolls.push_back(roll);
    return roll;
}

void Shooter::display_rolled_values() {
    for (Roll* roll : rolls) {
        std::cout << roll->roll_value() << "\n";
    }
}

Shooter::~Shooter() {
    for (Roll* roll : rolls) {
        delete roll;
    }
    rolls.clear();
}
