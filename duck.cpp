#include "duck.h"

duck::duck() :
    duck_accel(0, 0),
    duck_speed_set(0),
	duck_alive(true),                       //initializing with default values
    duck_moving(false) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

duck::~duck() {
	//destructor
}

void duck::initialize(const std::string& texturePath, float initialSpeed) {
    game_entity_inclass::initialize(texturePath);
    duck_speed_set = initialSpeed; // set the initial speed
    sprite.setScale(0.3f, 0.3f); // scale down the duck
}

void duck::spawn(float screenWidth, float screenHeight) {
    position.x = -25; 


    position.y = static_cast<float>(std::rand() % static_cast<int>(screenHeight));

    duck_accel.x = 200.0f; 
    duck_accel.y = 0; 
    duck_moving = true; 
    duck_alive = true;
    active = true; 

    sprite.setPosition(position); // update the sprite's position

    std::cout << "Duck spawned at position: (" << position.x << ", " << position.y << ") with acceleration: (" 
              << duck_accel.x << ", " << duck_accel.y << ")" << std::endl;
}

void duck::update(float deltaTime, float screenWidth, float screenHeight) {
    if (!duck_moving || !duck_alive) return; // ff inactive, no need to update

    position.x += duck_accel.x * deltaTime; // update horizontal position
    position.y += duck_accel.y * deltaTime; // update vertical position (should be 0)

    std::cout << "Duck updated to position: (" << position.x << ", " << position.y << ") with acceleration: (" 
              << duck_accel.x << ", " << duck_accel.y << ")" << std::endl;

    if (position.x > screenWidth) { 
        duck_moving = false;
        active = false; 
    }

    sprite.setPosition(position); 
    game_entity_inclass::update(deltaTime, screenWidth, screenHeight); 
}

void duck::render(sf::RenderWindow& window) { //check for hit detect
    if (duck_moving && duck_alive) {
        game_entity_inclass::render(window);  //base class render

    }
}

bool duck::hit_detect_true(const sf::FloatRect& hitBox) {
    return duck_moving && duck_alive && getBounds().intersects(hitBox);
}

void duck::kill() { //kills the duck and stops movement
    duck_moving = false;
    duck_alive = false;
    active = false;
    duck_accel = sf::Vector2f(0, 0);
    // Add death animation here when ready
}

sf::FloatRect duck::getBounds() const { //ducks collision box
    return game_entity_inclass::getBounds();
}
