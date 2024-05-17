#include <Geode/Geode.hpp>

using namespace geode::prelude;

//#define MBO(type, clazz, offset) *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(clazz) + offset)

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
    enumKeyCodes::KEY_B,
    enumKeyCodes::KEY_LeftShift
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
    enumKeyCodes::KEY_RightShift,
    enumKeyCodes::KEY_OEMComma,
    enumKeyCodes::KEY_OEMPeriod,
    enumKeyCodes::KEY_Enter
};

#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(EKJKeyboardDispatcher, CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool repeat) {
        auto gameManager = GameManager::sharedState();
        auto player1 = std::find(p1Keys.begin(), p1Keys.end(), key) != p1Keys.end();
        if (gameManager->m_playLayer && !gameManager->m_playLayer->m_levelSettings->m_platformerMode && (player1 || std::find(p2Keys.begin(), p2Keys.end(), key) != p2Keys.end())) {
            if (!gameManager->m_playLayer->m_isPracticeMode || (key != enumKeyCodes::KEY_X && key != enumKeyCodes::KEY_Z))
                gameManager->m_playLayer->handleButton(down, 1, player1);
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, repeat);
    }
};

/*#include <Geode/modify/GJBaseGameLayer.hpp>
class $modify(EKJBaseGameLayer, GJBaseGameLayer) {
    void handleButton(bool down, int button, bool player1) {
        log::info("Run the function ok");
        if (button == 100) {
            log::info("Running this stupid override");
            auto twoPlayer = m_levelSettings->m_twoPlayerMode;
            auto isPlayer1 = player1;
            if (!MBO(bool, this, 0x29c6) && !MBO(bool, this, 0x2a44)) {
                if (GameManager::sharedState()->getGameVariable("0010")) isPlayer1 = !player1;
            }

            auto hasActiveDualTouch = false;
            for (char* p = MBO(char*, this->m_effectManager, 0x160); p != MBO(char*, this->m_effectManager, 0x164); p += 0x2c) {
                if (MBO(bool, p, 0x1c) && *p == 0) {
                    hasActiveDualTouch = true;
                    break;
                }
            }

            if (down) MBO(bool, this, 0x29a4) = hasActiveDualTouch;
            else if (!MBO(bool, this, 0x29a4)) hasActiveDualTouch = false;

            auto randomBool = false;
            if (!hasActiveDualTouch) {
                if (!isPlayer1) hasActiveDualTouch = twoPlayer;

                if (isPlayer1 || (!isPlayer1 && !twoPlayer)) {
                    randomBool = hasActiveDualTouch;
                    if (down) m_player1->pushButton(PlayerButton::Jump);
                    else m_player1->releaseButton(PlayerButton::Jump);
                }
                
                auto otherBool = false;
                if ((!MBO(bool, this, 0x29a4) && m_gameState.m_isDualMode) && (!isPlayer1 || !twoPlayer)) {
                    randomBool = twoPlayer;
                    otherBool = true;
                    if (down) m_player2->pushButton(PlayerButton::Jump);
                    else m_player2->releaseButton(PlayerButton::Jump);
                }

                if (randomBool) {
                    hasActiveDualTouch = twoPlayer || otherBool;
                    gameEventTriggered(down ? GJGameEvent::JumpPush : GJGameEvent::JumpRelease, 0, hasActiveDualTouch ? 2 : 1);
                }
            }

            if (!m_player1->m_isDead) m_effectManager->playerButton(down, isPlayer1);
            if (!MBO(bool, this, 0x2a44)) recordAction(1, down, twoPlayer && isPlayer1);
            if (down) {
                MBO(int, this, 0x29a8) += 1;
                MBO(int, this, 0x29b0) = 1;
            }
        }
        else GJBaseGameLayer::handleButton(down, button, player1);
    }
};*/
