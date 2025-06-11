#pragma once
enum class State { Idle, Pending, Finished };

class App {
   public:
    App();
    ~App();

    State getState() const;
    void setState(State s);

   private:
    State state = State::Idle;
};