#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

TEST_CASE("Verify Test Configuration", "verification") {
	REQUIRE(true == true);
}

enum class RollOutcome { natural, craps, point, seven_out, nopoint };
// ------------------ Die Class ------------------
class Die {
public:
    int roll() {
        return rand() % sides + 1;
    }
private:
    int sides {6};
};
// ------------------ Roll Class ------------------
class Roll {
public:
    Roll(Die& d1, Die& d2) : die1(d1), die2(d2) {}

    void roll_dice() {
        int v1 = die1.roll();
        int v2 = die2.roll();
        rolled_value = v1 + v2;
    }

    int roll_value() const {
        return rolled_value;
    }

private:
    Die& die1;
    Die& die2;
    int rolled_value {0};
};
// ------------------ Shooter Class ------------------
class Shooter {
public:
    Roll* throw_dice(Die& d1, Die& d2) {
        Roll* roll = new Roll(d1, d2);
        roll->roll_dice();
        rolls.push_back(roll);
        return roll;
    }

    void display_rolled_values() {
        for (auto roll : rolls) {
            std::cout << roll->roll_value() << "\n";
        }
    }

    ~Shooter() {
        for (auto roll : rolls) {
            delete roll;
        }
        rolls.clear();
    }

private:
    std::vector<Roll*> rolls;
};
// ------------------ Abstract Phase Class ------------------
class Phase {
public:
    virtual RollOutcome get_outcome(Roll* roll) = 0;
    virtual ~Phase() = default;
};
// ------------------ ComeOutPhase Class ------------------
class ComeOutPhase : public Phase {
public:
    RollOutcome get_outcome(Roll* roll) override {
        int val = roll->roll_value();
        if (val == 7 || val == 11) return RollOutcome::natural;
        else if (val == 2 || val == 3 || val == 12) return RollOutcome::craps;
        else return RollOutcome::point;
    }
};
// ------------------ PointPhase Class ------------------
class PointPhase : public Phase {
public:
    PointPhase(int p) : point(p) {}

    RollOutcome get_outcome(Roll* roll) override {
        int val = roll->roll_value();
        if (val == point) return RollOutcome::point;
        else if (val == 7) return RollOutcome::seven_out;
        else return RollOutcome::nopoint;
    }

private:
    int point;
};

// ------------------ Tests ------------------
void test_die() {
    Die die;
    for (int i = 0; i < 10; ++i) {
        int roll = die.roll();
        assert(roll >= 1 && roll <= 6);
    }
    std::cout << "Die test passed\n";
}

void test_roll() {
    Die d1, d2;
    for (int i = 0; i < 10; ++i) {
        Roll r(d1, d2);
        r.roll_dice();
        int v = r.roll_value();
        assert(v >= 2 && v <= 12);
    }
    std::cout << "Roll test passed\n";
}

void test_shooter() {
    Die d1, d2;
    Shooter shooter;
    for (int i = 0; i < 10; ++i) {
        Roll* r = shooter.throw_dice(d1, d2);
        assert(r->roll_value() >= 2 && r->roll_value() <= 12);
    }
    std::cout << "Shooter test passed\n";
}

void test_phases() {
    Die d1, d2;
    Shooter shooter;
    ComeOutPhase come_out;

    for (int i = 0; i < 10; ++i) {
        Roll* r = shooter.throw_dice(d1, d2);
        int val = r->roll_value();
        RollOutcome out = come_out.get_outcome(r);
        assert(out == RollOutcome::natural || out == RollOutcome::craps || out == RollOutcome::point);
    }
    // PointPhase test
    PointPhase point_phase(5);
    for (int i = 0; i < 10; ++i) {
        Roll* r = shooter.throw_dice(d1, d2);
        int val = r->roll_value();
        RollOutcome out = point_phase.get_outcome(r);
        assert(out == RollOutcome::point || out == RollOutcome::seven_out || out == RollOutcome::nopoint);
    }

    std::cout << "Phase test passed\n";
}
// ------------------ Main Program (Question 5) ------------------
int main() {
    srand(static_cast<unsigned>(time(0)));

    // Run tests
    test_die();       // Question 1
    test_roll();      // Question 2
    test_shooter();   // Question 3
    test_phases();    // Question 4
    // Game logic
    std::cout << "\n--- Starting Dice Game ---\n";
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