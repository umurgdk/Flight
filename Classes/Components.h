//
//  Components.h
//  Flight
//
//  Created by Umur Gedik on 17/08/15.
//
//

namespace Flight {
    namespace Components {
        typedef struct Health {
            Health(float healthPoints = 100.0f) : healthPoints(healthPoints) {}

            float healthPoints;
        } Health;

        typedef struct Position {
            Position(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

            float x, y;
        } Position;
    }
}
