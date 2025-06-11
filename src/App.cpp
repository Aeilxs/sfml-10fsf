#include "App.hpp"

#include <iostream>

App::App() {}
App::~App() {}

State App::getState() const { return this->state; }
void App::setState(State s) { state = s; }
