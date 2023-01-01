#ifndef VECHICLE_HDR
#define VECHICLE_HDR

#include "MovingEntity.h"

#include <string>

namespace game 
{
    class Vechicle : public MovingEntity 
    {
    public:
        Vechicle(int id);

        void loadTexture();
        virtual void onUpdate(Tempest::TimeStep timeStep) override;
    protected:
        virtual void onRender() override;
    private:
        Tempest::ref<Tempest::Texture2D> _arrowTexture;
    };
}

#endif // !VECHICLE_HDR
