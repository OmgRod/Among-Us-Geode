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
            CCNode* child = dynamic_cast<CCNode*>(obj);
            if (child) {
                child->setVisible(false);
            }
        }

        // FMOD Setup
        FMOD::System* system = nullptr;
        FMOD::Sound* sound = nullptr;
        FMOD::Channel* channel = nullptr;

        // Create the FMOD system
        FMOD::System_Create(&system);
        system->init(512, FMOD_INIT_NORMAL, nullptr);

        // If a sound is already playing, stop it
        if (channel != nullptr) {
            bool isPlaying = false;
            channel->isPlaying(&isPlaying);
            if (isPlaying) {
                channel->stop();
            }
        }

        // Load the new sound (ensure the path to "amogus.mp3" is correct)
        system->createSound("amogus.mp3", FMOD_DEFAULT, nullptr, &sound);

        // Play the new sound
        system->playSound(sound, nullptr, false, &channel);

        // Cleanup - To be handled during application shutdown or when sound is no longer needed
        // sound->release();
        // system->close();
        // system->release();

        return true;
    }
};