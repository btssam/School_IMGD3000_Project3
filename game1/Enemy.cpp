//System includes
#include <cstdlib>
#include <algorithm>
//Engine includes
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventStep.h"
//Game includes
#include "Enemy.h"

Enemy::Enemy() {

    setType("enemy");
    setSprite("enemy");

    m_hp = 100;

    m_moveCooldown = 4;
    m_move_countdown = m_moveCooldown;
    m_spawn_countdown = 15;

    m_flash_slowdown = 4;
    m_flash_counter = 0;

    registerInterest(df::STEP_EVENT);

    setPosition(df::Vector(40, 10));

    setAltitude(3);

    m_name = "Clayhead";
    m_sprite_normal = "enemy";
    m_sprite_hit = "enemy-hit";
    m_sound_damage = "enemy-damage";
    m_sound_death = "enemy-death";

    m_step_x = 6;
    m_step_y = 3;

    m_min_x = 15;
    m_max_x = 65;
    m_min_y = 3;
    m_max_y = 14;
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
                setSprite(m_sprite_normal); // Revert back to normal when counter reaches 0
            }
        }

        // Pause movement for half a second to let player prepare
        if (m_spawn_countdown > 0) {
            m_spawn_countdown--;
            return 1;
        }

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
            pos.setX(pos.getX() + m_step_x);
            break;
        case 1:
            pos.setX(pos.getX() - m_step_x);
            break;
        case 2:
            pos.setY(pos.getY() + m_step_y);
            break;
        case 3:
            pos.setY(pos.getY() - m_step_y);
            break;
    }

    if (pos.getX() < m_min_x)
        pos.setX(m_min_x);

    if (pos.getX() > m_max_x)
        pos.setX(m_max_x);

    if (pos.getY() < m_min_y)
        pos.setY(m_min_y);

    if (pos.getY() > m_max_y)
        pos.setY(m_max_y);

    setPosition(pos);
}

void Enemy::setHP(int hp) {
    m_hp = std::max(0, hp);
}

int Enemy::getHP() const {
    return m_hp;
}

void Enemy::flash() {
    setSprite(m_sprite_hit);
    m_flash_counter = m_flash_slowdown;
}

void Enemy::setName(std::string name) {
    m_name = name;
}

void Enemy::setSpriteNormal(std::string sprite) {
    m_sprite_normal = sprite;
    setSprite(sprite);
}

void Enemy::setSpriteHit(std::string sprite) {
    m_sprite_hit = sprite;
}

void Enemy::setSoundDamage(std::string sound) {
    m_sound_damage = sound;
}

void Enemy::setSoundDeath(std::string sound) {
    m_sound_death = sound;
}

std::string Enemy::getName() const {
    return m_name;
}

std::string Enemy::getSpriteNormal() const {
    return m_sprite_normal;
}

std::string Enemy::getSpriteHit() const {
    return m_sprite_hit;
}

std::string Enemy::getSoundDamage() const {
    return m_sound_damage;
}

std::string Enemy::getSoundDeath() const {
    return m_sound_death;
}

void Enemy::setMoveCooldown(int cooldown) {
    m_moveCooldown = cooldown;
    m_move_countdown = cooldown;
}

int Enemy::getMoveCooldown() const {
    return m_moveCooldown;
}

void Enemy::setStepSize(int step_x, int step_y) {
    m_step_x = step_x;
    m_step_y = step_y;
}

void Enemy::setBounds(int min_x, int max_x, int min_y, int max_y) {
    m_min_x = min_x;
    m_max_x = max_x;
    m_min_y = min_y;
    m_max_y = max_y;
}

int Enemy::getSpawnCountdown() const {
    return m_spawn_countdown;
}

void Enemy::setSpawnCountdown(int countdown) {
    m_spawn_countdown = countdown;
}