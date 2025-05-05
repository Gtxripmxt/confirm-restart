#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// bool confirmReset = true;

class $modify(ConfirmRestart, PauseLayer) {
    struct Fields {
        bool confirmReset = true;
    };
    CCMenuItemToggler* checkbox = nullptr; 

    void customSetup() {
        PauseLayer::customSetup();

        auto checkboxOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto checkboxOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

        checkbox = CCMenuItemToggler::create(
            checkboxOff,
            checkboxOn,
            this,
            menu_selector(ConfirmRestart::onCheckbox)
        );
        checkbox->setPosition({ 25.f, 25.f });
        checkbox->setAnchorPoint({ 0.f, 0.f });
        checkbox->toggle(m_fields->confirmReset);
            
        auto menu = CCMenu::create();
        menu->addChild(checkbox);
        menu->setPosition({ 0.f, 0.f });
        this->addChild(menu);
    }
    void onCheckbox(CCObject*) {
        m_fields->confirmReset = !m_fields->confirmReset;
        m_fields->checkbox->toggle(m_fields->confirmReset);
    }

    void onRestart(CCObject* sender) {
        if (checkbox) {
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
