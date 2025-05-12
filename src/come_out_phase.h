#ifndef COMOUTPHASE_H
#define COMOUTPHASE_H

#include "phase.h"

class ComeOutPhase : public Phase {
public:
    RollOutcome get_outcome(Roll* roll) override;
};

#endif