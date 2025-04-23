#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <string>

class game_entity_inclass {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    bool active;

public:
    game_entity_inclass();
    virtual ~game_entity_inclass();
                                                                        //explained in the entity.cpp
    virtual void initialize(const std::string& texturePath);
    virtual void update(float deltaTime, float screenWidth, float screenHeight);
    virtual void render(sf::RenderWindow& window);

    bool isActive() const { return active; }
    sf::FloatRect getBounds() const { return sprite.getter_areabounds(); }
    sf::Vector2f getPosition() const { return position; }
};
#endif // ENTITY_H
