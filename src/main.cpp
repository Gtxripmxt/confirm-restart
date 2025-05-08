#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;

class $modify(ConfirmRestart, PauseLayer) {
    void onRestart(CCObject*) {
            geode::createQuickPopup(
                "Restart",
                "Are you sure you want to restart?",
                "No", "Yes",
                [this](auto, bool btn2) {
                    if (btn2) {
                        if (auto pl = GameManager::sharedState()->getPlayLayer()) {
                            pl->resetLevel();
                            this->onResume(nullptr);
                        }
                    }
                }
            );
        } 
    }
};
