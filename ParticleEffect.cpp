/**
* ParticleEffect.cpp
* 
* Authors: Adam Carter, Ian Richardson
* 
* The particle effect source file.
*/

#include "ParticleEffect.h"
#include "Random.h"

#include <iostream>

using namespace sf;

//*****************************************************************************
// Particle 
//*****************************************************************************
// Constructors & Deconstructors
ParticleEffect::Particle::Particle(const std::string& str_shape,
	const Vector2f& initialPosition, const float lifespan,
	const Vector2f& initialVelocity) {

	// Initialize if shape
	if (str_shape == "Circle") {
		shape = new sf::CircleShape();
		shape->setPosition(initialPosition);

		// Randomize size
		shape->setRadius(Random::Range(20.f, 5.f));

		// NOT optimized color randomization
		int rand_val = Random::Range(5, 0);
		Color rand_color;
		switch (rand_val) {
		case (0): rand_color = Color::Red;
			break;
		case (1): rand_color = Color::Blue;
			break;
		case(2): rand_color = Color::Green;
			break;
		case(3): rand_color = Color::Magenta;
			break;
		case(4): rand_color = Color(128, 0, 128);
			break;
		case(5): rand_color = Color(255, 165, 0);
		}
		shape->setFillColor(rand_color);
	}

	// Initialize if sprite
	if (str_shape == "Sprite") {
		Texture texture;
		if (!texture.loadFromFile("Assets/asteroid_lava.png")) {
			// std::cout << "texture not loading" << std::endl;
		}
		// sprite = new Sprite();
		sprite.setTexture(texture);
		sprite.setPosition(initialPosition);
		sprite.setScale(0.5f, 0.5f);

		// If sprite, set shape to nullptr
		shape = nullptr;
	}

	this->lifespan = lifespan;
	this->velocity = initialVelocity;
}

ParticleEffect::Particle::~Particle() {
	delete shape;
	shape = nullptr;
}

// Game Loop Functions
void ParticleEffect::Particle::update() {

	if (shape != nullptr) {
		shape->setPosition(shape->getPosition() + (velocity * SHAPE_SPEED_RATE));
	}
	else {
		sprite.setPosition(sprite.getPosition() + (velocity * SPRITE_SPEED_RATE));
	}

	// Test speed relative to framerate
	lifespan -= 0.001f;
}

void ParticleEffect::Particle::render(RenderWindow& window) {

	if (shape != nullptr) {
		window.draw(*shape);
	}
	else {
		Texture texture;
		if (!texture.loadFromFile("Assets/asteroid_lava.png")) {
			// std::cout << "texture not loading" << std::endl;
		}
		sprite.setTexture(texture);
		window.draw(sprite);
		// std::cout << "drawing sprite" << std::endl;
	}
}

// Helper Functions
Vector2f ParticleEffect::Particle::getPosition() const {
	if (shape != nullptr)
		return shape->getPosition();
	else return sprite.getPosition();
}

bool ParticleEffect::Particle::isAlive() const {
	if (lifespan <= 0)
		return false;
	return true;
}

//*****************************************************************************
// ParticleEffect
//*****************************************************************************
ParticleEffect::ParticleEffect() {
	for (short i = 0; i < NUM_OF_PARTICLES; ++i) {
		particles[i] = nullptr;
	}
}

ParticleEffect::~ParticleEffect() {
	for (short i = 0; i < NUM_OF_PARTICLES; ++i) {
		delete particles[i];
		particles[i] = nullptr;
	}
}

void ParticleEffect::update() {
	for (short i = 0; i < NUM_OF_PARTICLES; ++i) {
		if (particles[i] != nullptr) {
			particles[i]->update();
			if (!(particles[i]->isAlive())) {
				delete particles[i];
				particles[i] = nullptr;
			}
		}
	}
}

void ParticleEffect::render(RenderWindow& window) {
	for (short i = 0; i < NUM_OF_PARTICLES; ++i) {
		if (particles[i] != nullptr)
			particles[i]->render(window);
	}
}

void ParticleEffect::Emit(const float x, const float y) {
	// Applies force to particles (start moving here)
	Vector2f temp, position;
	position.x = x;
	position.y = y;

	for (short i = 0; i < NUM_OF_PARTICLES; ++i) {
		// Random velocity
		temp.x = Random::Range(HI, LO, RAND_MAX);
		temp.y = Random::Range(HI, LO, RAND_MAX);

		// Random lifespan
		float rand_lifespan = Random::Range(10.f, 1.f);

		// Replace "Sprite" with "Circle" for basic circle shape
		this->AddParticle(i, particleType, position, rand_lifespan, temp);
	}
}

void ParticleEffect::AddParticle(short i, const std::string& str_shape,
	Vector2f& initialPosition, const float lifespan, Vector2f& initialVector) {

	particles[i] = new Particle(str_shape, initialPosition, lifespan,
		initialVector);
}

void ParticleEffect::ChangeParticle() {
	if (particleType == "Circle")
		particleType = "Sprite";
	else particleType == "Circle";
}
