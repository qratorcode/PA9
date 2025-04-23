#include "game.h"
#include "duck.h"
#include "input_handler.h"
#include <iostream>




hunt_game_class::hunt_game_class() :
    window(nullptr),
    duck_running(false),
    score(0),
    hold_gun_up(false),                           //initializing with default values
    bullets(3),
    use_fixed_line(false),
    current_control_settings(ControlScheme::MOUSE_KEYBOARD) {
}

hunt_game_class::~hunt_game_class() { //destructor
    if (window != nullptr) {
        delete window;
        window = nullptr;
    }
}

void hunt_game_class::initialize(int width, int height, const std::string& title) {
	window = new sf::RenderWindow(sf::VideoMode(width, height), title);          //creates the game window

	if (!landscape_texture_asset.loadFromFile("add the path to background here, should be png")) {          //load the background texture
        std::cout << "error failed to load the background textures :( " << std::endl;
    }
    else {
        backgroundSprite.setTexture(landscape_texture_asset);
    }

	if (!asset_gun_crosshair.loadFromFile("add the png path here")) {                       //load the crosshair texture
        std::cout << "error failed to load the crosshair texture/sprite" << std::endl;
    }
    else {
        SFML_crosshair.setTexture(asset_gun_crosshair);               //
    }

    input_handler = std::make_unique<class_handle_user_input>();
    fixed_line_shoot.set_linesize(sf::Vector2f(5.0f, static_cast<float>(height)));
    fixed_line_shoot.set_colorfill(sf::Color::Red);                                   //this is the fixed shooting line on the side of screen. can ignore for now. just a backup incase we cant get hand aiming to work
    fixed_line_shoot.set_line_position(width / 2.0f, 0.0f);

    ducks.clear();
    duck_running = true;
}

void hunt_game_class::duck_spawn_r() {
    auto newDuck = std::make_unique<duck>();
    newDuck->initialize("place texture path here", 100.0f);
    newDuck->spawn(window->getSize().x, window->getSize().y);   
    ducks.push_back(std::move(newDuck));
}

void hunt_game_class::duck_collision_check() {
    for (auto& duck : ducks) {
		if (duck->duck_flying_current()) {      //check if duck is flying
            if (!use_fixed_line && input_handler->shot_detect() && bullets > 0) {// check if user shot with bullets left
                if (duck->hit_detect_true(SFML_crosshair.getter_areabounds())) {
                    duck->kill();
                    score++;
                    bullets--;                  //inrimenting score and bullets and breaking loop
                    break;
                }
            }
        }
    }
}

