#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "PongConfig.hpp"

namespace PongEngine {

    class Paddle {
    private:
        int x, y;
        int originalX, originalY;
        eControler joyStick;

    public:
        Paddle(int posX, int posY);
        void Reset();
        
        inline int GetX() const { return x; }
        inline int GetY() const { return y; }
        
        void ChangeDirection(eControler dir) { joyStick = dir; }
        void Move();
    };

} // namespace PongEngine

#endif // PADDLE_HPP