#include "../include/Ball.hpp"
#include <cstdlib>
#include <ctime>

namespace PongEngine {

    Ball::Ball(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        dir = STOP;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    void Ball::Reset() {
        x = originalX;
        y = originalY;
        dir = STOP;
    }

    void Ball::ChangeDirection(eDirection direction) {
        dir = direction;
    }

    void Ball::SetRandomDirection() {
        // Keeps user's exact baseline 1-6 randomized startup distribution
        dir = static_cast<eDirection>((std::rand() % 6) + 1);
    }

    void Ball::Move() {
        switch (dir) {
            case STOP:
                break;
            case RIGHT:
                x++;
                break;
            case UPRIGHT:
                x++; y--;
                break;
            case DOWNRIGHT:
                x++; y++;
                break;
            case LEFT:
                x--;
                break;
            case UPLEFT:
                x--; y--;
                break;
            case DOWNLEFT:
                x--; y++;
                break;
        }
    }

} // namespace PongEngine