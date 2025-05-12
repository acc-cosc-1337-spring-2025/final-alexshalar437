#include "die.h"
#include "shooter.h"
#include "come_out_phase.h"
#include "point_phase.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    srand(static_cast<unsigned>(time(0)));

    Die die1, die2;
    Shooter shooter;
    Roll* roll = shooter.throw_dice(die1, die2);
    int rolled_value = roll->roll_value();

    ComeOutPhase come_out_phase;
    RollOutcome outcome = come_out_phase.get_outcome(roll);

    while (outcome == RollOutcome::natural || outcome == RollOutcome::craps) {
        std::cout << "Rolled " << rolled_value << " roll again\n";
        roll = shooter.throw_dice(die1, die2);
        rolled_value = roll->roll_value();
        outcome = come_out_phase.get_outcome(roll);
    }

    std::cout << "Rolled " << rolled_value << " start of point phase\n";
    std::cout << "Roll until " << rolled_value << " or a 7 is rolled\n";

    int point = rolled_value;
    PointPhase point_phase(point);

    roll = shooter.throw_dice(die1, die2);
    outcome = point_phase.get_outcome(roll);

    while (outcome != RollOutcome::seven_out && outcome != RollOutcome::point) {
        std::cout << "Rolled " << roll->roll_value() << " roll again\n";
        roll = shooter.throw_dice(die1, die2);
        outcome = point_phase.get_outcome(roll);
    }

    std::cout << "Rolled " << roll->roll_value() << " end of point phase\n";
    shooter.display_rolled_values();

    return 0;
}