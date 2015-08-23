#include <bandit/bandit.h>

#include <entityx/entityx.h>
#include "Systems.h"

using namespace bandit;
namespace ex = entityx;

using namespace Flight::Components;
using namespace Flight::Systems;

go_bandit([](){
    describe("LifeSystem", [&](){
        ex::EntityX em;
        em.systems.add<LifeSystem>();
        em.systems.configure();
        
        describe("when dealing with Health component it", [&]() {
            ex::Entity entity;
            
            before_each([&]() {
                entity = em.entities.create();
            });
            
            after_each([&]() {
                entity.destroy();
                em.entities.reset();
            });
            
            it("should mark as dead if health points less then or equal to zero", [&](){
                entity.assign<Health>(0.0f);
                em.systems.update<LifeSystem>(1.0f);
                
                AssertThat(entity.component<Health>()->isAlive, Is().False());
            });
            
            it("should not mark as dead if health points less then or equal to zero but killImmediately equals to false", [&]() {
                entity.assign<Health>(0.0f, false);
                em.systems.update<LifeSystem>(1.0f);
                
                AssertThat(entity.component<Health>()->isAlive, Is().True());
            });
            
            it("should mark as dying if health points less then or equal to zero but killImmediately equals to false", [&]() {
                entity.assign<Health>(0.0f, false);
                em.systems.update<LifeSystem>(1.0f);
                
                AssertThat(entity.component<Health>()->isDying, Is().True());
            });
        });
        
        describe("when dealing with LifeTime component it", [&]() {
            ex::Entity entity;
            
            before_each([&]() {
                entity = em.entities.create();
                
                // Life system depends on Health component
                entity.assign<Health>(100.0f);
            });
            
            after_each([&]() {
                entity.destroy();
                em.entities.reset();
            });
            
            it("should decrase the remaining life time as delta time", [&]() {
                entity.assign<LifeTime>(5.0f);
                em.systems.update<LifeSystem>(1.0f);
                
                AssertThat(entity.component<LifeTime>()->lifeTime, Is().EqualTo(4.0f));
            });
            
            it("should make zero of health points if life time less than or equals to zero", [&]() {
                entity.assign<LifeTime>(5.0f);
                em.systems.update<LifeSystem>(5.0f);
                
                AssertThat(entity.component<LifeTime>()->lifeTime, IsLessThanOrEqualTo(0));
                AssertThat(entity.component<Health>()->healthPoints, Equals(0));
                AssertThat(entity.component<Health>()->isAlive, Is().False());
            });
        });
    });
    
});