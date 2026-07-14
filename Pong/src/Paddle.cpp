#include "../include/Paddle.hpp"

namespace PongEngine {

    Paddle::Paddle(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        joyStick = PAUSE;
    }

    void Paddle::Reset() {
        x = originalX;
        y = originalY;
        joyStick = PAUSE;
    }

    void Paddle::Move() {
        switch (joyStick) {
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            case PAUSE:
                break;
        }
    }

} // namespace PongEngine