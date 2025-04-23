#include "entity.h"
#include <iostream>

game_entity_inclass::game_entity_inclass() :
    position(0, 0),                              //set to zero / base values
    active(false) {
}

game_entity_inclass::~game_entity_inclass() {

}          //destructor



/*

initializes entity with texture
 texturePath File path to texture asset
 prints error message if texture fails to load
 all entities must be initialized before use

*/
void game_entity_inclass::initialize(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        std::cout << "failed to load texture: " << texturePath << std::endl;
    }
    sprite.setTexture(texture);
}
// screenwidth and screen height are used to set the position of the entity
void game_entity_inclass::update(float deltaTime, float screenWidth, float screenHeight) {
    sprite.setPosition(position);
}

void game_entity_inclass::render(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);   //draw at current position
    }
}
