//
//  Components.h
//  Flight
//
//  Created by Umur Gedik on 17/08/15.
//
//
#ifndef  _COMPONENTS_H_
#define  _COMPONENTS_H_

#include "entityx/entityx.h"
#include "cocos2d.h"

#include "InputData.h"

namespace Flight {
    namespace Components {
        struct Health : entityx::Component<Health> {
            Health(float healthPoints = 100.0f, bool killImmediately = true) : healthPoints(healthPoints),  killImmediately(killImmediately) {}

            float healthPoints;
            bool killImmediately = true;
            bool isAlive = true;
            bool isDying = false;
        };

        // @param lifeTime life time in seconds
        struct LifeTime : entityx::Component<LifeTime> {
            LifeTime (float lifeTime = 10.0f) : lifeTime(lifeTime) {}

            float lifeTime;
        };

        struct Position : entityx::Component<Position> {
            Position(const cocos2d::Vec2 position) : position(position) {}

            cocos2d::Vec2 position;
        };

        struct Sprite : entityx::Component<Sprite> {
            Sprite(cocos2d::Sprite *sprite) :sprite(sprite) {}

            cocos2d::Sprite *sprite;
        };

        struct Input : entityx::Component<Input> {
            Input (InputData *inputData) : inputData(inputData) {}

            InputData *inputData;
        };

        struct Player : entityx::Component<Player> {
            Player () {}
        };

        struct Collideable : entityx::Component<Collideable> {
            Collideable () {}
        };

        struct DyingAnimation : entityx::Component<DyingAnimation> {
            DyingAnimation (std::string spriteName, float duration) : spriteName(spriteName) {}

            std::string spriteName;
            float duration;
            bool isPlaying = false;
        };
    }
}

#endif

