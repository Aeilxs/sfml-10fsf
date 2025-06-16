#pragma once

#include "Context.hpp"

class Screen {
   public:
    explicit Screen(Context& ctx) : ctx(ctx) {}
    virtual ~Screen() = default;

    virtual void handleEvent(const sf::Event& event) = 0;

    virtual void update(f32 dt) = 0;
    virtual void draw() = 0;

   protected:
    Context& ctx;
};
