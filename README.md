# Project 1: Simple 2D Space Scene
## CS-UY 3113

This project is an animated space scene built in C++ by *Riccardo Bean* as part of CS-UY 3113 coursework.

## Objects
 - Soft nebula background
 - Spherical object used as the Sun
 - Noise mesh applied on top of the Sun to simulate dark spots
 - Three orbiting planets of different colors
 - Moon object
 - Noise mesh applied on top of the moon to simulate craters

## Animations
 - The background gently pulses and gradually changes color, 
 - The sun rotates and pulses, 
 - The planets rotate and move around the sun in ellictic orbits 
 - The moon rotates and moves around the Earth in a circular orbit


## Project structure

- `main.cpp` — the full scene setup, animation logic, and render loop
- `assets/game/` — textures used for the background, sun, planets, and moon
- `CS3113/` — the project’s graphics/game support code
- `makefile` — builds the application

## How to run it

From the project directory, build and run the program with:

```bash
make
make run
```

If the build succeeds, the application window should open and display the animated scene.

## Credits

This project uses graphics from [Kenney](www.kenney.nl), distributed under CC0 license. In particular, the background is taken from Kenney Skyboxes, while all the other objects are taken from Kenney Planets. 

Before downloading, using, our distributing, check out the [LICENSE](LICENSE).