#include "ScreenIntro.h"

#include <iostream>

void ScreenIntro::init() {
    std::cout << "screen init";
}

void ScreenIntro::update() {
    std::cout << "screen intro";
}

void ScreenIntro::handleInput() {
    std::cout << "screen intro handle input";
}

void ScreenIntro::render() {
    std::cout << "screen intro render";
}
