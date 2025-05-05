#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(ConfirmRestart, PauseLayer) {
    struct Fields {
        CCMenuItemToggler* checkbox = nullptr;
    };

    void customSetup() {
        PauseLayer::customSetup();

        auto checkboxOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto checkboxOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

        bool savedConfirmReset = Mod::get()->getSavedValue<bool>("confirm-reset", true);      
        
        auto checkbox = CCMenuItemToggler::create(
            checkboxOff,
            checkboxOn,
            this,
            menu_selector(ConfirmRestart::onCheckbox)
        );
        checkbox->toggle(savedConfirmReset);
        checkbox->setPosition({ 25.f, 25.f });
        checkbox->setAnchorPoint({ 0.f, 0.f });

        m_fields->checkbox = checkbox;

        auto menu = CCMenu::create();
        menu->addChild(checkbox);
        menu->setPosition({ 0.f, 0.f });
        this->addChild(menu);
    }

    void onCheckbox(CCObject*) {
        bool newState = !m_fields->checkbox->isOn();
        m_fields->checkbox->toggle(newState);
        Mod::get()->setSavedValue("confirm-reset", newState);
    }

    void onRestart(CCObject* sender) {
        bool confirmReset = Mod::get()->getSavedValue<bool>("confirm-reset", true);

        if (m_fields->checkbox && confirmReset) {
            geode::createQuickPopup(
                "Restart",
                "Are you sure you want to restart?",
                "No", "Yes",
                [this](auto, bool btn2) {
                    if (btn2) {
                        if (auto playLayer = GameManager::sharedState()->getPlayLayer()) {
                            playLayer->resetLevel();
                            this->onResume(nullptr);
                        }
                    }
                }
            );
        } else {
            if (auto playLayer = GameManager::sharedState()->getPlayLayer()) {
                playLayer->resetLevel();
                this->onResume(nullptr);
            }
        }
    }
};
