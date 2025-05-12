#include "die.h"
#include <cstdlib>

int Die::roll() {
    return rand() % sides + 1;
}