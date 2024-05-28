#include <Geode/Geode.hpp>

using namespace geode::prelude;

std::vector<enumKeyCodes> p1Keys = {
    enumKeyCodes::KEY_One,
    enumKeyCodes::KEY_Two,
    enumKeyCodes::KEY_Three,
    enumKeyCodes::KEY_Four,
    enumKeyCodes::KEY_Five,
    enumKeyCodes::KEY_Q,
    enumKeyCodes::KEY_W,
    enumKeyCodes::KEY_E,
    enumKeyCodes::KEY_R,
    enumKeyCodes::KEY_T,
    enumKeyCodes::KEY_A,
    enumKeyCodes::KEY_S,
    enumKeyCodes::KEY_D,
    enumKeyCodes::KEY_F,
    enumKeyCodes::KEY_G,
    enumKeyCodes::KEY_Z,
    enumKeyCodes::KEY_X,
    enumKeyCodes::KEY_C,
    enumKeyCodes::KEY_V,
    enumKeyCodes::KEY_B
};

std::vector<enumKeyCodes> p2Keys = {
    enumKeyCodes::KEY_Six,
    enumKeyCodes::KEY_Seven,
    enumKeyCodes::KEY_Eight,
    enumKeyCodes::KEY_Nine,
    enumKeyCodes::KEY_Zero,
    enumKeyCodes::KEY_Y,
    enumKeyCodes::KEY_U,
    enumKeyCodes::KEY_I,
    enumKeyCodes::KEY_O,
    enumKeyCodes::KEY_P,
    enumKeyCodes::KEY_H,
    enumKeyCodes::KEY_J,
    enumKeyCodes::KEY_K,
    enumKeyCodes::KEY_L,
    enumKeyCodes::KEY_N,
    enumKeyCodes::KEY_M,
    enumKeyCodes::KEY_OEMComma,
    enumKeyCodes::KEY_OEMPeriod,
    enumKeyCodes::KEY_Enter
};

#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(EKJKeyboardDispatcher, CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool repeat) {
        if (Mod::get()->getSettingValue<bool>("ekj-enabled") && !repeat) {
            auto gameManager = GameManager::sharedState();
            auto player1 = std::find(p1Keys.begin(), p1Keys.end(), key) != p1Keys.end();
            if (gameManager->m_playLayer && (player1 || std::find(p2Keys.begin(), p2Keys.end(), key) != p2Keys.end())) {
                if (!gameManager->m_playLayer->m_levelSettings->m_platformerMode ||
                    (key != enumKeyCodes::KEY_W && key != enumKeyCodes::KEY_A && key != enumKeyCodes::KEY_S && key != enumKeyCodes::KEY_D)) {
                    if (!gameManager->m_playLayer->m_isPracticeMode || (key != enumKeyCodes::KEY_X && key != enumKeyCodes::KEY_Z))
                        gameManager->m_playLayer->handleButton(down, 1, player1);
                }
            }
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat);
    }
};
