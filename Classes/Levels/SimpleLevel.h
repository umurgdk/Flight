//
//  SimpleLevel.h
//  Flight
//
//  Created by Umur Gedik on 17/08/15.
//
//

#ifndef __Flight__SimpleLevel__
#define __Flight__SimpleLevel__

#include <iostream>
#include <string>
#include <entityx/entityx.h>
#include "cocos2d.h"

#include "Components.h"
#include "Systems.h"

#include "InputData.h"

namespace Flight {
    namespace Levels {
        using namespace Components;
        using namespace Systems;

        class SimpleLevel : public entityx::EntityX {
            InputData *_inputData;
            cocos2d::Layer *_scene;
            cocos2d::EventDispatcher *_eventDispatcher;

        public:
            explicit SimpleLevel(cocos2d::Layer *scene) {
                this->_scene = scene;
                _eventDispatcher = _scene->getEventDispatcher();

                _inputData = new InputData();

                // Register event listeners
                auto mouseListener = cocos2d::EventListenerMouse::create();
                mouseListener->onMouseDown = CC_CALLBACK_1(SimpleLevel::onMouseDown, this);
                mouseListener->onMouseMove = CC_CALLBACK_1(SimpleLevel::onMouseMove, this);
                mouseListener->onMouseUp = CC_CALLBACK_1(SimpleLevel::onMouseUp, this);
                _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, _scene);

                // Initialize systems
                systems.add<PlayerMovement>();
                systems.add<CocosSprite>();
                systems.add<LifeSystem>();
                systems.add<DestroySystem>();
                systems.configure();

                auto *playerSprite = cocos2d::Sprite::create("ships/small.png");
                playerSprite->setScale(0.25f);
                _scene->addChild(playerSprite);

                auto textureCache = cocos2d::Director::getInstance()->getTextureCache();
                textureCache->addImage("");

                auto player = entities.create();
                player.assign<Position>(cocos2d::Vec2(0.0f, 0.0f));
                player.assign<Player>();
                player.assign<Input>(_inputData);
                player.assign<Sprite>(playerSprite);
                player.assign<Health>(100.0f, false);
                player.assign<LifeTime>();
            }

            void update(entityx::TimeDelta delta) {
                systems.update<PlayerMovement>(delta);
                systems.update<CocosSprite>(delta);
                systems.update<LifeSystem>(delta);
                systems.update<DestroySystem>(delta);
            }

            void onMouseDown(cocos2d::Event *event) {
                auto *e = (cocos2d::EventMouse *)event;
                _inputData->pointerPosition = e->getDelta();
                _inputData->pointerIsDown = true;
            }

            void onMouseMove(cocos2d::Event *event) {
                auto *e = (cocos2d::EventMouse *) event;
                _inputData->pointerPosition = e->getDelta();
            }

            void onMouseUp(cocos2d::Event *event) {
                auto *e = (cocos2d::EventMouse *)event;
                _inputData->pointerPosition = e->getDelta();
                _inputData->pointerIsDown = false;
            }
        };
    };
};

#endif /* defined(__Flight__SimpleLevel__) */
