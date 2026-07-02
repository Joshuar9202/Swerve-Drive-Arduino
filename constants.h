#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    // Physical constants in cm
    constexpr float length = 19.579191;
    constexpr float width = 19.579191;
    constexpr float wheelRadius = 5.08;

    constexpr float FLangleOffset = 80;
    constexpr float FRangleOffset = -100;    
    constexpr float BLangleOffset = -94;
    constexpr float BRangleOffset = 110;

    constexpr int maxSpeed = 40 * wheelRadius;

    constexpr int maxDriverVoltage = 6;
    constexpr int maxMotorVoltage = 6;

    constexpr int deadzone = 5;
}

#endif