#include <Geode/Geode.hpp>

using namespace geode::prelude;

std::vector<enumKeyCodes> p1Keys = {
    KEY_One, KEY_Two, KEY_Three, KEY_Four,
    KEY_Five, KEY_Q, KEY_W, KEY_E,
    KEY_R, KEY_T, KEY_A, KEY_S,
    KEY_D, KEY_F, KEY_G, KEY_Z,
    KEY_X, KEY_C, KEY_V, KEY_B
};

std::vector<enumKeyCodes> p2Keys = {
    KEY_Six, KEY_Seven, KEY_Eight, KEY_Nine,
    KEY_Zero, KEY_Y, KEY_U, KEY_I,
    KEY_O, KEY_P, KEY_H, KEY_J,
    KEY_K, KEY_L, KEY_N, KEY_M,
    KEY_OEMComma, KEY_OEMPeriod, KEY_Enter
};

#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(EKJKeyboardDispatcher, CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool repeat) {
        if (!repeat && Mod::get()->getSettingValue<bool>("ekj-enabled")) {
            auto gameLayer = GameManager::sharedState()->m_gameLayer;
            if (!gameLayer) goto LABEL_RETURN;

            auto player1 = std::find(p1Keys.begin(), p1Keys.end(), key) != p1Keys.end();
            if (!player1 && std::find(p2Keys.begin(), p2Keys.end(), key) == p2Keys.end()) goto LABEL_RETURN;

            if (gameLayer->m_levelSettings->m_platformerMode && (key == KEY_W || key == KEY_A || key == KEY_D)) goto LABEL_RETURN;
            if (gameLayer->m_isPracticeMode && (key == KEY_W || key == KEY_Z)) goto LABEL_RETURN;

            gameLayer->handleButton(down, 1, player1);
        }
        LABEL_RETURN:
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat);
    }
};
