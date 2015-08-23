#include <bandit/bandit.h>
#include <fakeit.hpp>

#include <entityx/entityx.h>
#include "Systems.h"

using namespace bandit;
using namespace fakeit;

namespace ex = entityx;

using namespace Flight::Components;
using namespace Flight::Systems;

namespace cc = cocos2d;

go_bandit([](){
    describe("DestroySystem", [&](){
        ex::EntityX em;
        em.systems.add<DestroySystem>();
        em.systems.configure();
        
        ex::Entity entity;
        
        before_each([&]() {
            entity = em.entities.create();
        });
        
        after_each([&]() {
            entity.destroy();
            em.entities.reset();
        });

        it("should destroy the entity if Health component is markes as dead", [&]() {
            entity.assign<Health>(0.0f);
            
            auto health = entity.component<Health>();
            health->isAlive = false;
            
            em.systems.update<DestroySystem>(1.0f);
            
            // calling destroy invalidates the entity
            AssertThat(entity.valid(), IsFalse());
        });
        
        it("should remove the cocos2d sprite from it's parent only if entity has Sprite component", [&]() {
            // Add Health component
            entity.assign<Health>(0.0f);
            auto health = entity.component<Health>();
            health->isAlive = false;
            
            auto originalsprite = cc::Sprite::create("ships/small.png");
            
            // Mock cocos2d Sprite class
            Mock<cc::Sprite> mockedSprite(*originalsprite);
            When(Method(mockedSprite,removeFromParentAndCleanup)).Return();
            
            auto &sprite = mockedSprite.get();
            
            // Add Sprite component
            entity.assign<Sprite>(&sprite);
            
            em.systems.update<DestroySystem>(1.0f);
            
            // Throws exception if it can't verify.
            // When it happens test fails there is no need to write any assertion!
            Verify(Method(mockedSprite, removeFromParentAndCleanup));
        });
    });
    
});