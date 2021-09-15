#ifndef PARTICLE_H
#define PARTICLE_H

#include "SFML/Graphics/CircleShape.hpp"
#include "rectangle.hpp"
#include "vec2.hpp"

class Particle {
public:
	Vec2<float> pos;
	float radius;
	float mass;

	sf::CircleShape shape;

	Particle(Vec2<float> pos, float radius, Vec2<float> vel, const Rectangle<float>& bounds, float mass = 1.0f);

	void update(float dt);

	bool intersects(const Particle& p) const;

	void collide(Particle& p);
	
private:
	Vec2<float> vel;
	Rectangle<float> bounds;

	bool hitLeftBound(float x) const;
	bool hitRightBound(float x) const;
	bool hitTopBound(float y) const;
	bool hitBottomBound(float y) const;
};

#endif