#ifndef BORDER_ROCK_H
#define BORDER_ROCK_H
#include "../../immovable_solid_particle.h"


//Indestructible particle made specifically to be on the border of the window.
//This particle ignores any user commands and cannot be painted or erased.
class BorderRock final :
    public ImmovableSolidParticle
{
public:
    BorderRock();
};

#endif // BORDER_ROCK_H
