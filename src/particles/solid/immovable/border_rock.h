#ifndef BORDER_ROCK_H
#define BORDER_ROCK_H

#include "particles/solid/immovable/immovable_solid_particle.h"

namespace powder_sim
{
	//Indestructible particle made specifically to be on the border of the window.
	//This particle ignores any user commands and cannot be painted or erased.
	class BorderRock final :
		public ImmovableSolidParticle {
	public:
		BorderRock();

		[[nodiscard]] BorderRock* Clone() const override;
	};
}
#endif // BORDER_ROCK_H
