#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "duck.h"  

class class_handle_user_input;

enum class ControlScheme {
    MOUSE_KEYBOARD,
    HAND_GESTURE
};

class hunt_game_class {
private:
    sf::RenderWindow* window;
    sf::Sprite backgroundSprite;
    sf::Texture landscape_texture_asset;
    bool duck_running;
    bool hold_gun_up;
    int score;
    int bullets;
    std::vector<std::unique_ptr<duck>> ducks;
    sf::Sprite SFML_crosshair;
    sf::Texture asset_gun_crosshair;
    sf::RectangleShape fixed_line_shoot;                      //most explained in game.cpp
    std::vector<sf::Texture> scoreTextures;
    std::vector<sf::Sprite> scoreSprites;
    int currentScore;
    void updateScoreDisplay();

    bool use_fixed_line;
    std::unique_ptr<class_handle_user_input> input_handler;
    ControlScheme current_control_settings;

    void duck_spawn_r();
    void duck_update(float deltaTime);
    void duck_collision_check();
    void ui_display();

public:
    hunt_game_class();
    ~hunt_game_class();

    void initialize(int width, int height, const std::string& title);
    void handleEvents();
    void update(float deltaTime);
    void render();
    void shutdown();
    bool running() const { return duck_running; }
    void set_controls(ControlScheme scheme);
    void toggleFixedLineMode();
    void handleMovableCrosshair(float deltaTime);
    void handleFixedLineShooting(float deltaTime);
};
#endif // GAME_H
