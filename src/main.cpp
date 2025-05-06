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

        auto checkbox = CCMenuItemToggler::create(
            checkboxOff,
            checkboxOn,
            this,
            menu_selector(ConfirmRestart::onCheckbox)
        );
        checkbox->setPosition({ 25.f, 25.f });
        checkbox->setAnchorPoint({ 0.f, 0.f });

        bool saved = Mod::get()->getSavedValue("confirm-reset", true);

        if (checkbox->isOn() != saved) {
            checkbox->toggle(false);
        }

        m_fields->checkbox = checkbox;

        auto menu = CCMenu::create();
        menu->addChild(checkbox);
        menu->setPosition({ 0.f, 0.f });
        this->addChild(menu);

        if (auto restartBtn = static_cast<CCMenuItemSpriteExtra*>(this->getChildByIDRecursive("restart-button"))) {
            restartBtn->setTarget(this, menu_selector(ConfirmRestart::onRestart));
        } else {
        }
    }

    void onCheckbox(CCObject*) {
        if (m_fields->checkbox) {
            bool isChecked = m_fields->checkbox->isOn();
            Mod::get()->setSavedValue("confirm-reset", isChecked);
            log::info("Checkbox toggled: {}", isChecked);
        }
    }

    void onRestart(CCObject* sender) {
        bool shouldConfirm = Mod::get()->getSavedValue("confirm-reset", true);
        if (shouldConfirm) {
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
        } else {
            if (auto pl = GameManager::sharedState()->getPlayLayer()) {
                pl->resetLevel();
                this->onResume(nullptr);
            }
        }
    }
};
