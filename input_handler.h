#define _CRT_SECURE_NO_WARNINGS
#ifndef INPUT_HANDLER_H

#define INPUT_HANDLER_H

#include <SFML/Graphics.hpp>
#include <iostream>

/*

uses lm and rm buttons for input
and r for reload


planned implimentation:
1. finger = shoot (replaces right mouse button)
2. fingers = hold gun up (replaces left mouse button)   (not fully implimented yet)
3.fingers = reload (replaces r key)
*/

class class_handle_user_input {
private:
    bool LMpress;
    bool RMpress;
    bool Rpress;
    sf::Vector2f curr_mouse_pos;

    bool past_tense_LMpress;
    bool past_tense_RMpress;             //past tense states
    bool past_tense_Rpress;

public:
    class_handle_user_input();    
    ~class_handle_user_input();

    void update(sf::RenderWindow& window);

    bool shot_detect() const;
    bool shoot_being_held() const;
    bool reload_triggered() const;                //these are explained in th .cpp file with comments
    sf::Vector2f getAimPosition() const;

    bool onefinger_shootCheck() const;
    bool threefinger_reload_check() const;
    sf::Vector2f get_handAIM_position() const;
};
#endif // INPUT_HANDLER_H
