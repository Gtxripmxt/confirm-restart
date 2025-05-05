#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(ConfirmRestart, PauseLayer) {
    CCMenuItemToggler* checkbox = nullptr;

    bool init() {
        auto checkboxOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto checkboxOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

        checkbox = CCMenuItemToggler::create(
            checkboxOff,
            checkboxOn,
            this,
            menu_selector(ConfirmRestart::onCheckbox)
        );

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        checkbox->setPosition({ 25.f, 25.f }); // Padding from bottom-left corner
        checkbox->setAnchorPoint({ 0.f, 0.f }); // Anchor to bottom-left
        this->m_buttonMenu->addChild(checkbox);

        return true;
    }

    void onCheckbox(CCObject * sender) {
        // You can handle checkbox toggle here if needed
    }

    void onRestart(CCObject * sender) {
        if (checkbox && checkbox->isOn()) {
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
        }
        else {
            if (auto playLayer = GameManager::sharedState()->getPlayLayer()) {
                playLayer->resetLevel();
                this->onResume(nullptr);
            }
        }
    }
};
