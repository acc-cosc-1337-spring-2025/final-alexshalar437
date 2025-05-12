#ifndef POINTPHASE_H
#define POINTPHASE_H

#include "phase.h"

class PointPhase : public Phase {
public:
    PointPhase(int p) : point(p) {}
    RollOutcome get_outcome(Roll* roll) override;

private:
    int point;
};

#endif