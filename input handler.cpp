#include "input_handler.h"

class_handle_user_input::class_handle_user_input() : //constructor intizilizing all input states to false 
    LMpress(false),
    RMpress(false),                   //current states
    Rpress(false),
    past_tense_LMpress(false),
    past_tense_RMpress(false),                 //past states
    past_tense_Rpress(false) {
}

class_handle_user_input::~class_handle_user_input() {//simple destructor

}

void class_handle_user_input::update(sf::RenderWindow& window) {      //every fram the input status will be updated
    past_tense_LMpress = LMpress;
    past_tense_RMpress = RMpress;
    //previous states are stored
    past_tense_Rpress = Rpress;

    curr_mouse_pos = sf::Vector2f(sf::Mouse::getPosition(window));          //screen ccoordinates of mouse/cursor/handcrosshair

    LMpress = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    RMpress = sf::Mouse::isButtonPressed(sf::Mouse::Right);
    Rpress = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
}

bool class_handle_user_input::shot_detect() const {         //true for rm detect

    return RMpress && !past_tense_RMpress;
}

bool class_handle_user_input::shoot_being_held() const {        //true if right moush button is being held down
    return RMpress;
}

bool class_handle_user_input::reload_triggered() const { //true is r is pressed

    return Rpress && !past_tense_Rpress;
}

sf::Vector2f class_handle_user_input::getAimPosition() const { //gets mouse coordinates
    return curr_mouse_pos;
}

bool class_handle_user_input::onefinger_shootCheck() const {  //return true when one finger is detected
    return false;
}

bool class_handle_user_input::threefinger_reload_check() const {     //returns true when three fingers are detected
    return false;
}

sf::Vector2f class_handle_user_input::get_handAIM_position() const {//detects hand position coordinates
    return sf::Vector2f(0, 0);
}
