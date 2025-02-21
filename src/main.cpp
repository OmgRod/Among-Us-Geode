#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/fmod/fmod.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        CCArray* children = this->getChildren();
        CCObject* obj = nullptr;
        CCARRAY_FOREACH(children, obj) {
            CCNode* child = typeinfo_cast<CCNode*>(obj);
            if (child) {
                child->setVisible(false);
            }
        }

        FMOD::System* system = nullptr;
        FMOD::Sound* sound = nullptr;
        FMOD::Channel* channel = nullptr;

        FMOD::System_Create(&system);
        system->init(512, FMOD_INIT_NORMAL, nullptr);

        if (channel != nullptr) {
            bool isPlaying = false;
            channel->isPlaying(&isPlaying);
            if (isPlaying) {
                channel->stop();
            }
        }

        system->createSound("amogus.mp3", FMOD_DEFAULT, nullptr, &sound);

        system->playSound(sound, nullptr, false, &channel);

        return true;
    }
};