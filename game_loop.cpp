#include "game_loop.h"

Game_Loop::Game_Loop() : deltaTime(0.0f) {      //initializes with zero values
}

Game_Loop::~Game_Loop() {
}

void Game_Loop::initialize() {  //800x600 res. with title "Duck Hunt" on window. 
    //if needed add the scoring and other input handlers
    game = std::make_unique<hunt_game_class>();
    game->initialize(1920, 1080, "Duck Hunt");
}

/*
main game loop:"

1. Calculates frame time (deltaTime)
2. Processes input events
3. Updates game state
4. Renders the framee
*/




void Game_Loop::run() {
   
    while (game->running()) { //main loop
        deltaTime = clock.restart().asSeconds(); //delta time to prevent extreme values
        if (deltaTime > 0.25f) deltaTime = 0.25f; // max fram time is 250ms


        
        game->handleEvents();
        game->update(deltaTime);         //core game loop sequence
        game->render();
    }
}

void Game_Loop::shutdown() {
    game->shutdown();
}
