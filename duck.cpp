#include "duck.h"
duck::duck() :
    duck_accel(0, 0),
    duck_speed_set(0),
    duck_alive(true),                       //initializing with default values
    duck_moving(false) {
 
}

duck::~duck() {
    //destructor
}

void duck::initialize(const std::string& texturePath, float initialSpeed) {
    game_entity_inclass::initialize(texturePath);
    duck_speed_set = initialSpeed; // initial speed set
    sprite.setScale(0.3f, 0.3f); // scale down the duck, to make smaller

    
    sprite.setOrigin(0, 0);  
    duck_moving = true;      
    duck_alive = true;              //true intiializers 
    active = true;           
}



void duck::spawn(float screenWidth, float screenHeight) {
    position.x = -25;


    position.y = static_cast<float>(std::rand() % static_cast<int>(screenHeight));

    duck_accel.x = 200.0f;
    duck_accel.y = 0;
    duck_moving = true;
    duck_alive = true;
    active = true;

    sprite.setPosition(position); // this updates the sprite position

    std::cout << "(debugstatement) duck spawn pos" << position.x << ", " << position.y << "____ with acceleration_____"
        << duck_accel.x << ", " << duck_accel.y << "_" << std::endl;
}

void duck::update(float deltaTime, float screenWidth, float screenHeight) {
    if (!duck_moving || !duck_alive) {
        return; 
    }
    position.x += duck_accel.x * deltaTime;      //horizontal and vertical updates
    position.y += duck_accel.y * deltaTime; 
	sprite.setPosition(position); // sprite position update

   
	game_entity_inclass::update(deltaTime, screenWidth, screenHeight); //calls base class update

    std::cout << "sprite position updated to (debugstatement)" << position.x << "___ " << position.y << "_\n";
    if (position.x > screenWidth) {
        duck_moving = false;
        active = false;
    }
}

void duck::render(sf::RenderWindow& window) { //checks for duck alive and moving 
    if (duck_moving && duck_alive) {
        game_entity_inclass::render(window);  //base class render

    }
}

bool duck::hit_detect_true(const sf::FloatRect& hitBox) {
    return duck_moving && duck_alive && getBounds().intersects(hitBox);
}

void duck::kill() { //kills the duck and stops movement, also makes it disapear
    duck_moving = false;
    duck_alive = false;
    active = false;
    duck_accel = sf::Vector2f(0, 0);
    // no death animation at the moment
}

sf::FloatRect duck::getBounds() const { //ducks collision box
    return game_entity_inclass::getBounds();
}
