#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(ConfirmRestart, PauseLayer) {
    CCMenuItemToggler* m_checkbox = nullptr;

    bool init(bool fromReplay) {
        if (!PauseLayer::init(fromReplay)) return false;

        auto checkboxOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
        auto checkboxOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

        m_checkbox = CCMenuItemToggler::create(
            checkboxOff,
            checkboxOn,
            this,
            menu_selector(ConfirmRestart::onCheckbox)
        );
        m_checkbox->setPosition({ 25.f, 25.f }); // Bottom-left corner
        m_checkbox->setAnchorPoint({ 0.f, 0.f });

        auto menu = CCMenu::create();
        menu->addChild(m_checkbox);
        menu->setPosition({ 0.f, 0.f });
        this->addChild(menu);

        return true;
    }

    void onCheckbox(CCObject*) {
        // Optional: logic when checkbox toggled
    }

    void onRestart(CCObject* sender) override {
        if (m_checkbox && m_checkbox->isOn()) {
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
