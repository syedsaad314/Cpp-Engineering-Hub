#ifndef BALL_HPP
#define BALL_HPP

#include "PongConfig.hpp"

namespace PongEngine {

    class Ball {
    private:
        int x, y;
        int originalX, originalY;
        eDirection dir;

    public:
        Ball(int posX, int posY);
        void Reset();
        void ChangeDirection(eDirection direction);
        void SetRandomDirection();
        
        inline int GetX() const { return x; }
        inline int GetY() const { return y; }
        inline eDirection GetDir() const { return dir; }
        
        void Move();
    };

} // namespace PongEngine

#endif // BALL_HPP