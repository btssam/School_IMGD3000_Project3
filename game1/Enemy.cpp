#include "Enemy.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventStep.h"

#include <cstdlib>

Enemy::Enemy() {
    setType("enemy");
    setSprite("enemy");

    m_hp = 100;

    m_moveCooldown = 2;
    m_move_countdown = m_moveCooldown;

    m_flash_slowdown = 4;
    m_flash_counter = 0;
    m_flash = 0;

    registerInterest(df::STEP_EVENT);

    setPosition(df::Vector(40, 10));
}

Enemy::~Enemy() {
    //
}

int Enemy::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        // Enemy sprite returns to normal red
        if (m_flash_counter > 0) {
            m_flash_counter--;
            if (m_flash_counter == 0) {
                setSprite("enemy"); // Revert back to normal when counter reaches 0
            }
        }


        // if (m_flash > 0) {
        //     setSprite("enemy");
        //     m_flash = 0;
        // }

        move();

        return 1;
    }

    return 0;
}

void Enemy::move() {
    if (m_move_countdown > 0) {
        m_move_countdown--;
        return;
    }

    m_move_countdown = m_moveCooldown;

    int direction = rand() % 4;

    df::Vector pos = getPosition();

    switch (direction) {
        case 0:
            pos.setX(pos.getX() + 6);
            break;
        case 1:
            pos.setX(pos.getX() - 6);
            break;
        case 2:
            pos.setY(pos.getY() + 4);
            break;
        case 3:
            pos.setY(pos.getY() - 4);
            break;
    }

    if (pos.getX() < 15)
        pos.setX(15);

    if (pos.getX() > 65)
        pos.setX(65);

    if (pos.getY() < 3)
        pos.setY(3);

    if (pos.getY() > 14)
        pos.setY(14);

    setPosition(pos);
}

void Enemy::setHP(int hp) {
    m_hp = hp;
}

int Enemy::getHP() const {
    return m_hp;
}

void Enemy::flash() {
    setSprite("enemy-hit");
    m_flash_counter = m_flash_slowdown;
    // m_flash = 1;
}