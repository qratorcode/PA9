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
	duck_speed_set = initialSpeed;                        //initizalizing the duck with movement speed and the texture loaded
}

void duck::spawn(float screenWidth, float screenHeight) {
    position.x = -25; 
    position.y = std::rand() % static_cast<int>(screenHeight);
    duck_accel.x = duck_speed_set; //move right at the set speed
    duck_accel.y = 0; //no vertical movement at the moment
    duck_moving = true; 
    duck_alive = true;
	active = true; //entitiy is active

	sprite.setPosition(position); //update the sprite position
}

void duck::update(float deltaTime, float screenWidth, float screenHeight) {
	if (!duck_moving || !duck_alive) return;   //if inactive no need to update

	position.x += duck_accel.x * deltaTime;   //update position based on the acceleration and delta
    if (position.x > screenWidth) {       //check if the duck exits off the screen
        duck_moving = false;
		active = false;                      //sets the duck to inactive., essentially removing it/killing it. but no points given
    }

    game_entity_inclass::update(deltaTime, screenWidth, screenHeight);  //update base class
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
