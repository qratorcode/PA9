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
    // Seed the random number generator once
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    window = new sf::RenderWindow(sf::VideoMode(width, height), title);          //creates the game window

    if (!landscape_texture_asset.loadFromFile("C:\\Users\\Nicholas\\Downloads\\duckhunt background.png")) {          //load the background texture
        std::cout << "error failed to load the background textures :( " << std::endl;
    }
    else {
        backgroundSprite.setTexture(landscape_texture_asset);
    }

    if (!asset_gun_crosshair.loadFromFile("C:\\Users\\Nicholas\\Downloads\\crosshair.png")) {                       //load the crosshair texture
        std::cout << "error failed to load the crosshair texture/sprite" << std::endl;
    }
    else {
        SFML_crosshair.setTexture(asset_gun_crosshair);
        SFML_crosshair.setScale(0.1f, 0.1f);
        SFML_crosshair.setOrigin(SFML_crosshair.getGlobalBounds().width / 2, SFML_crosshair.getGlobalBounds().height / 2);
    }

    input_handler = std::make_unique<class_handle_user_input>();

    fixed_line_shoot.setSize(sf::Vector2f(5.0f, static_cast<float>(height)));
    fixed_line_shoot.setFillColor(sf::Color::Red);                                   //this is the fixed shooting line on the side of screen. can ignore for now. just a backup incase we cant get hand aiming to work
    fixed_line_shoot.setPosition(width / 2.0f, 0.0f);

    ducks.clear();
    duck_running = true;
    duck_spawn_r();
}

void hunt_game_class::duck_spawn_r() {
    auto newDuck = std::make_unique<duck>();
    newDuck->initialize("C:\\Users\\Nicholas\\Downloads\\duck.png", 200.0f);
    newDuck->spawn(window->getSize().x, window->getSize().y);
    ducks.push_back(std::move(newDuck));
}

void hunt_game_class::duck_collision_check() {
    for (auto& duck : ducks) {
        if (duck->duck_flying_current()) {      //check if duck is flying
            if (!use_fixed_line && input_handler->shot_detect() && bullets > 0) {// check if user shot with bullets left
                if (duck->hit_detect_true(SFML_crosshair.getGlobalBounds())) {
                    duck->kill();
                    score++;
                    bullets--;                  //inrimenting score and bullets and breaking loop
                    break;
                }
            }
        }
    }
}

void hunt_game_class::handleEvents() {}

void hunt_game_class::update(float deltaTime) {
    // Remove dead ducks
    ducks.erase(
        std::remove_if(ducks.begin(), ducks.end(),
            [](const std::unique_ptr<duck>& d) { return !d->isAlive(); }),
        ducks.end()
    );

    // If no ducks exist, spawn one
    if (ducks.empty()) {
        duck_spawn_r();
    }

    // Temporary vector to track ducks that have left the screen
    std::vector<size_t> ducksToRemove;

    // Update all existing ducks
    for (size_t i = 0; i < ducks.size(); i++) {
        auto& duck = ducks[i];
        duck->update(deltaTime, window->getSize().x, window->getSize().y);

        // Only mark ducks that are COMPLETELY off screen or dead
        if (!duck->isAlive() || (duck->getPosition().x > window->getSize().x && !duck->duck_flying_current())) {
            ducksToRemove.push_back(i);
        }
    }

    // If any ducks were marked for removal, spawn ONE new duck
    if (!ducksToRemove.empty()) {
        // Remove all ducks that left the screen or are dead
        for (int i = ducksToRemove.size() - 1; i >= 0; i--) {
            size_t index = ducksToRemove[i];
            if (index < ducks.size()) {
                ducks.erase(ducks.begin() + index);
            }
        }

        // Spawn just ONE new duck
        duck_spawn_r();
    }

    // Update input handler for crosshair
    if (input_handler) {
        input_handler->update(*window);
        SFML_crosshair.setPosition(input_handler->getAimPosition());
    }

    // Check for duck collisions with crosshair
    duck_collision_check();
}

void hunt_game_class::render() {
    if (window && window->isOpen()) {
        window->clear(); // clear the window

        // drawing background
        window->draw(backgroundSprite);

        // draw all ducks
        for (const auto& duck : ducks) {
            if (duck->isAlive()) { // render alive ducks only
                duck->render(*window);
            }
        }

        // draw crosshair
        window->draw(SFML_crosshair);

        // display all assets
        window->display();
    }
}
void hunt_game_class::shutdown() {}
