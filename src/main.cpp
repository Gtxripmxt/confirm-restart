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
        m_fields->checkbox = checkbox;
        checkbox->toggle(savedConfirmReset);
        checkbox->setPosition({ 25.f, 25.f });
        checkbox->setAnchorPoint({ 0.f, 0.f });

        auto menu = CCMenu::create();
        menu->addChild(checkbox);
        menu->setPosition({ 0.f, 0.f });
        this->addChild(menu);
    }

    void onCheckbox(CCObject*) {
        if (m_fields->checkbox) {
            bool isChecked = m_fields->checkbox->isOn();
            Mod::get()->setSavedValue("confirm-reset", isChecked);
            if (auto playLayer = GameManager::sharedState()->getPlayLayer()) {
                playLayer->resetLevel();
                this->onResume(nullptr);
            }
            if (auto playLayer = GameManager::sharedState()->getPlayLayer()) {
                 playLayer->pauseGame(bool p0));
            }
        }
    }
      void onRestart(CCObject* sender) {
          if (m_fields->checkbox) {
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
