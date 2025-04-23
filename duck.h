#ifndef DUCK_H

#define DUCK_H

#include <SFML/Graphics.hpp>
#include "entity.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

class duck : public game_entity_inclass {
private:
    sf::Vector2f duck_accel;
    float duck_speed_set;
    bool duck_alive;
    bool duck_moving;
	                                                                  //explained in duck.cpp
public:
    duck();
    ~duck();

    void initialize(const std::string& texturePath, float speed);
    void spawn(float screenWidth, float screenHeight);
    void update(float deltaTime, float screenWidth, float screenHeight) override;
    void render(sf::RenderWindow& window) override;

    bool hit_detect_true(const sf::FloatRect& hitBox);
    bool duck_flying_current() const { return duck_moving; }
    bool isAlive() const { return duck_alive; }
    void kill();
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return position; }
}; 
#endif 
