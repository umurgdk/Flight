//
//  Systems.cpp
//  Flight
//
//  Created by Umur Gedik on 17/08/15.
//
//
#ifndef  _SYSTEMS_H_
#define  _SYSTEMS_H_

#include <iostream>

#include "entityx/entityx.h"
#include "Components.h"

using namespace Flight::Components;

namespace Flight {
    namespace Systems {
        struct PlayerMovement : public  entityx::System<PlayerMovement> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
                es.each<Player, Input, Position>([dt](entityx::Entity entity, Player &player, Input &input, Position &position) {
                    position.position = cocos2d::Vec2(input.inputData->pointerPosition.x, -input.inputData->pointerPosition.y);
                });
            }
        };

        struct CocosSprite : public entityx::System<CocosSprite> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
                es.each<Position, Sprite>([dt](entityx::Entity entity, Position &position, Sprite &sprite) {
                    sprite.sprite->setPosition(cocos2d::Vec2(position.position));
                });
            }
        };

        struct LifeSystem : public entityx::System<LifeSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
                es.each<Health>([dt](entityx::Entity entity, Health &health) {
                    if (entity.has_component<LifeTime>()) {
                        auto lifeTime = entity.component<LifeTime>();
                        lifeTime->lifeTime -= dt;

                        if(lifeTime->lifeTime <= 0) {
                            health.healthPoints = 0;
                        }
                    }

                    if (health.healthPoints <= 0) {
                        health.isAlive = !health.killImmediately;
                        health.isDying = !health.killImmediately;
                    }
                });
            }
        };

        struct DestroySystem : public entityx::System<DestroySystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
                es.each<Health>([dt](entityx::Entity entity, Health &health) {
                    if (!health.isAlive) {
                        if (entity.has_component<Sprite>()) {
                            auto sprite = entity.component<Sprite>();
                            sprite->sprite->removeFromParentAndCleanup(true);
                        }

                        entity.destroy();
                    }
                });
            }
        };

        struct DyingAnimationSystem : public entityx::System<DyingAnimationSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
                es.each<Health, DyingAnimation, Sprite>([dt](entityx::Entity entity, Health &health, DyingAnimation &dyingAnimation, Sprite &sprite) {
                    if (health.isDying) {
                        if (!dyingAnimation.isPlaying) {
                            sprite.sprite->setSpriteFrame(dyingAnimation.spriteName);
                        }

                        dyingAnimation.duration -= dt;

                        if (dyingAnimation.duration <= 0) {
                            health.isDying = false;
                            health.isAlive = false;
                        }
                    }
                });
            }
        };
    }
}

#endif