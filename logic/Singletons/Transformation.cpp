//
// Created by nick on 28.12.20.
//

#include "Transformation.h"

namespace turbohiker {
    std::shared_ptr<Transformation> Transformation::instance = nullptr;

    Coordinates Transformation::logic_to_pixles(double x, double y) const {
        x += 4;
        y += 3;
        x /= 8.0;
        y /= 6.0;
        x *= window_x;
        y *= window_y;
        if (y > 0) {
            y += 0.5;
        }
        if (y < 0) {
            y -= 0.5;
        }
        Coordinates toreturn{x + 0.5, y};
        return toreturn;
    }

    int Transformation::logic_to_pixle_y(double y) const {
        y += 3;
        y /= 6.0;
        y *= window_y;
        if (y > 0) {
            y += 0.5;
        }
        if (y < 0) {
            y -= 0.5;
        }
        return static_cast<int>(y);
    }

    double Transformation::pixle_to_logic_y(double y) const {
        y /= window_y;
        y *= 6;
        y -= 3;
        return y;
    }
}
