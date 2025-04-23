#ifndef GAME_LOOP_H
#define GAME_LOOP_H
#include "game.h"
#include <SFML/System/Clock.hpp>
#include <memory>
#include <iostream>

class Game_Loop {
private:

    std::unique_ptr<hunt_game_class> game;
    sf::Clock clock;
    float deltaTime;

public:                            //comments explain game loop in game_loop.cpp
    Game_Loop();
    ~Game_Loop();

    void initialize();
    void run();
    void shutdown();
};
#endif // GAME_LOOP_H
