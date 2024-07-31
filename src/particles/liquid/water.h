#ifndef WATER_H
#define WATER_H

#include "particles/liquid/liquid_particle.h"

namespace powder_sim
{
    class Water final :
        public LiquidParticle
    {
    public:
        Water();


        Water* Clone() const override;
    };
}
#endif // WATER_H
