/*
* Author: Riccardo Bean
* Assignment: Simple 2D Scene
* Date due: 10/05/2026
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.

*/

#include "CS3113/cs3113.h"
#include <cmath>

// Global Constants
constexpr int SCREEN_WIDTH = 1700,
              SCREEN_HEIGHT = 950,
              FPS = 60;

constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
constexpr Vector2 BASE_SIZE = {1000.0f, 1000.0f};
constexpr Vector2 SUN_SIZE = {200.0f, 200.0f};
constexpr Vector2 PLANET1_SIZE = {300.0f, 300.0f};
constexpr Vector2 PLANET2_SIZE = {280.0f, 280.0f};
constexpr Vector2 PLANET3_SIZE = {380.0f, 380.0f};
constexpr Vector2 MOON_SIZE = {100.0f, 100.0f};
constexpr char BACKGROUND[] = "assets/game/skybox-space-nebula.png";
constexpr char SUN[] = "assets/game/sphere0.png";
constexpr char SUN_NOISE[] = "assets/game/noise01.png";
constexpr char PLANET1[] = "assets/game/planet01.png";
constexpr char PLANET2[] = "assets/game/planet05.png";
constexpr char PLANET3[] = "assets/game/planet09.png";
constexpr char MOON[] = "assets/game/light7.png";
constexpr char MOON_NOISE[] = "assets/game/noise04.png";

// Global Variables
AppStatus gAppStatus = RUNNING;
float gPulseTime = 0.0f;
float gPreviousTicks = 0.0f;

// Global Variables - Background
Texture2D gBackground;
Vector2 gBackgroundPosition = ORIGIN;
Vector2 gBackgroundScale = BASE_SIZE;
Color gBackgroundColor;

// Global Variables - Sun
Texture2D gSun, gSunNoise;
Vector2 gSunPosition = {300, 600};
Vector2 gSunScale = SUN_SIZE;
float gSunRotation = 0.0f;

// Global Variables - Planet1
Texture2D gPlanet1;
Vector2 gPlanet1Position = {500,500};
Vector2 gPlanet1Scale = PLANET1_SIZE;
float gPlanet1Orbit = 0.0f;
float gPlanet1Rotation = 0.0f;

// Global Variables - Planet2
Texture2D gPlanet2;
Vector2 gPlanet2Position = {800, 800};
Vector2 gPlanet2Scale = PLANET2_SIZE;
float gPlanet2Orbit = 0.0f;
float gPlanet2Rotation = 0.0f;

// Global Variables - Planet3
Texture2D gPlanet3;
Vector2 gPlanet3Position = {400, 400};
Vector2 gPlanet3Scale = PLANET3_SIZE;
float gPlanet3Orbit = 0.0f;
float gPlanet3Rotation = 0.0f;

// Global Variables - Moon
Texture2D gMoon, gMoonNoise;
Vector2 gMoonPosition = {400, 400};
Vector2 gMoonScale = MOON_SIZE;
float gMoonOrbit = 0.0f;
float gMoonRotation = 0.0f;

// Function Declarations
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
void initialise() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple 2D Scene");

    gBackground = LoadTexture(BACKGROUND);
    gSun = LoadTexture(SUN);
    gSunNoise = LoadTexture(SUN_NOISE);
    gPlanet1 = LoadTexture(PLANET1);
    gPlanet2 = LoadTexture(PLANET2);
    gPlanet3 = LoadTexture(PLANET3);
    gMoon = LoadTexture(MOON);
    gMoonNoise = LoadTexture(MOON_NOISE);

    SetTargetFPS(FPS);
}

void processInput() {
    if (WindowShouldClose())
        gAppStatus = TERMINATED;
}

void update() {
    float ticks = GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;
    // Delta time to make the pulse look exactly the same on every computer
    gPulseTime += 1.0f * deltaTime;
    gBackgroundScale = {
        BASE_SIZE.x + 30.0f * cos(gPulseTime),
        BASE_SIZE.y + 30.0f * cos(gPulseTime)};

    gBackgroundColor = {
        static_cast<unsigned char>(128 + 127 * cos(0.5 * gPulseTime)),
        static_cast<unsigned char>(128 + 127 * cos(0.5 * gPulseTime)),
        255,
        255
    };

    gSunScale = {
        SUN_SIZE.x + 6.0f * cos(gPulseTime),
        SUN_SIZE.y + 6.0f * cos(gPulseTime)
    };

    gSunPosition = {
        gSunPosition.x + 0.05f * cos(gPulseTime),
        gSunPosition.y + 0.05f * cos(gPulseTime)
    };

    // Rotations
    gSunRotation += 2.0f * deltaTime;
    gPlanet1Rotation += 2.2f * deltaTime;
    gPlanet2Rotation += 2.5f * deltaTime;
    gPlanet3Rotation += 3.0f * deltaTime;
    gMoonRotation += 3.0f * deltaTime;

    // Orbits
    gPlanet1Orbit -= 0.5f * deltaTime;
    gPlanet2Orbit -= 0.4f * deltaTime;
    gPlanet3Orbit -= 0.2f * deltaTime;
    gMoonOrbit -= 1.2f * deltaTime;

    // Update positions based on orbits
    gPlanet1Position = {
        gSunPosition.x - 900.0f * cos(gPlanet1Orbit),
        gSunPosition.y - 700.0f * sin(gPlanet1Orbit)
    };

    gPlanet2Position = {
        gSunPosition.x - 600.0f * cos(gPlanet2Orbit),
        gSunPosition.y - 500.0f * sin(gPlanet2Orbit)
    };

    gPlanet3Position = {
        gSunPosition.x - 1200.0f * cos(gPlanet3Orbit),
        gSunPosition.y - 1200.0f * sin(gPlanet3Orbit)
    };

    gMoonPosition = {
        gPlanet1Position.x - 200.0f * cos(gMoonOrbit),
        gPlanet1Position.y - 200.0f * sin(gMoonOrbit)
    };


}

void render() {
    BeginDrawing();

    // Texture Area
    Rectangle backgroundTextureArea = {
        // Top left corner
        0.0f,
        0.0f,

        // How large of a rectangle, starting from 0,0 do we want to slice
        static_cast<float>(gBackground.width),
        static_cast<float>(gBackground.height),

    };

    Rectangle sunTextureArea = {
        // Top left corner
        0.0f,
        0.0f,

        // How large of a rectangle, starting from 0,0 do we want to slice
        static_cast<float>(gSun.width),
        static_cast<float>(gSun.height),

    };

    Rectangle planet1TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gPlanet1.width),
        static_cast<float>(gPlanet1.height),
    };

    Rectangle planet2TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gPlanet2.width),
        static_cast<float>(gPlanet2.height),
    };

    Rectangle planet3TextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gPlanet3.width),
        static_cast<float>(gPlanet3.height),
    };

    Rectangle moonTextureArea = {
        0.0f,
        0.0f,

        static_cast<float>(gMoon.width),
        static_cast<float>(gMoon.height),
    };

    // Destination Area
    Rectangle backgroundDestinationArea = {
        // where we want our rectangle to start being drawn
        gBackgroundPosition.x, gBackgroundPosition.y,

        // how big do we want it to be on our screen / scale
        gBackgroundScale.x * 2, gBackgroundScale.y * 2
    };
    Rectangle sunDestinationArea = {
        // where we want our rectangle to start being drawn
        gSunPosition.x, gSunPosition.y,

        // how big do we want it to be on our screen / scale
        gSunScale.x * 2, gSunScale.y * 2
    };
    Rectangle planet1DestinationArea = {
        gPlanet1Position.x, gPlanet1Position.y,

        gPlanet1Scale.x / 2, gPlanet1Scale.y / 2
    };
    Rectangle planet2DestinationArea = {
        gPlanet2Position.x, gPlanet2Position.y,

        gPlanet2Scale.x / 2, gPlanet2Scale.y / 2
    };
    Rectangle planet3DestinationArea = {
        gPlanet3Position.x, gPlanet3Position.y,

        gPlanet3Scale.x / 2, gPlanet3Scale.y / 2
    };

    Rectangle moonDestinationArea = {
        gMoonPosition.x, gMoonPosition.y,

        gMoonScale.x / 2, gMoonScale.y / 2
    };

    // Origin Offset
    Vector2 backgroundOriginOffset = {
        gBackgroundScale.x, gBackgroundScale.y
    };
    Vector2 sunOriginOffset = {
        gSunScale.x , gSunScale.y 
    };
    Vector2 planet1OriginOffset = {
        gPlanet1Scale.x / 4, gPlanet1Scale.y / 4
    };
    Vector2 planet2OriginOffset = {
        gPlanet2Scale.x / 4, gPlanet2Scale.y / 4
    };
    Vector2 planet3OriginOffset = {
        gPlanet3Scale.x / 4, gPlanet3Scale.y / 4
    };
    Vector2 moonOriginOffset = {
        gMoonScale.x / 4, gMoonScale.y / 4
    };

    // Draw the textures
    DrawTexturePro(gBackground, backgroundTextureArea, backgroundDestinationArea, backgroundOriginOffset, 0.0f, gBackgroundColor);
    DrawTexturePro(gSun, sunTextureArea, sunDestinationArea, sunOriginOffset, gSunRotation, ColorFromHex("#FFD21F"));
    DrawTexturePro(gSunNoise, sunTextureArea, sunDestinationArea, sunOriginOffset, gSunRotation, ColorFromHex("#FF8C00"));
    DrawTexturePro(gPlanet1, planet1TextureArea, planet1DestinationArea, planet1OriginOffset, gPlanet1Rotation, WHITE);
    DrawTexturePro(gPlanet2, planet2TextureArea, planet2DestinationArea, planet2OriginOffset, gPlanet2Rotation, WHITE);
    DrawTexturePro(gPlanet3, planet3TextureArea, planet3DestinationArea, planet3OriginOffset, gPlanet3Rotation, WHITE);
    DrawTexturePro(gMoon, moonTextureArea, moonDestinationArea, moonOriginOffset, gMoonRotation, WHITE);
    DrawTexturePro(gMoonNoise, moonTextureArea, moonDestinationArea, moonOriginOffset, gMoonRotation, ColorFromHex("#FFFFFF"));

    ClearBackground(gBackgroundColor);

    EndDrawing();
}

void shutdown() {
    CloseWindow();
    UnloadTexture(gBackground);
    UnloadTexture(gSun);
    UnloadTexture(gSunNoise);
    UnloadTexture(gPlanet1);
    UnloadTexture(gPlanet2);
    UnloadTexture(gPlanet3);
    UnloadTexture(gMoon);
    UnloadTexture(gMoonNoise);

}

int main(void) {
    initialise();

    while (gAppStatus == RUNNING) {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
