/**
* Pair Programming Simple Particle Effect Exercise
*
* Authors: Adam Carter, Ian Richardson
*
* Started:  October 13th, 2022
* Finished: October 17th, 2022
*
* Description: This program is a simple Particle and ParticleEffect class to
*   create a particle effect on left mouse clicks. Specifically, the particle,
*   particle effect, and game classes should have the following
*   requirements/constraints:
*    - A particle class that maintains a shape, velocity, and lifespan. Your
*       particles should all be one shape, such as a circle (do NOT worry
*       about inheritance or polymorphism yet).
*   - A particle effect class that creates and maintains an array of particles.
*       These particles should be stored on and removed from the heap. The
        array should not be dynamically allocated (i.e., you can make an
        assumption that it will be the same number of particles
        created/destroyed every time for the particle effect).
*   - Your game class should be modified so that it maintains a particle effect
*       pointer and creates a new particle effect whenever there is a left
*       mouse click.
*
* Controls:
*  LMB - generate particle effect
*  RMB - swap (permanently) to textured sprites
* 
*/

#include "ParticleEffect.h"
#include "Game.h"

#include <iostream>

using namespace sf;

//*****************************************************************************
// Constants
//*****************************************************************************
#define WINDOW_W 800
#define WINDOW_H 600

int main()
{
    Game G;
    ParticleEffect PE;

    RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "Particle Program");

    Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            G.handleInput(window, event, PE);
        }
        G.update(PE);
        G.render(window, PE);
    }

    return 0;
}