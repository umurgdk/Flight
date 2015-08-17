//
//  Systems.cpp
//  Flight
//
//  Created by Umur Gedik on 17/08/15.
//
//

#include "entityx/entityx.h"
#include "Components.h"

namespace Flight {
    namespace Systems {
        using namespace Components;

        struct MovementSystem : public entityx::System<MovementSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
                es.each<Position>([dt](entityx::Entity entity, Position &position) {
                });
            };
        };
    }
}