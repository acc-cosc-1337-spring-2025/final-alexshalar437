// File: src/Phase.h
#ifndef PHASE_H
#define PHASE_H

#include "roll.h"

enum class RollOutcome {
    natural, craps, point, seven_out, nopoint
};

class Phase {
public:
    virtual RollOutcome get_outcome(Roll* roll) = 0;
    virtual ~Phase() = default;
};

#endif