#include "particle.h"
#include <numeric>
#include <algorithm>

Particle::Particle(Vec2<float> pos, float radius, Vec2<float> vel, const Rectangle<float>& bounds, float mass) 
	: pos(pos), radius(radius), vel(vel), bounds(bounds), mass(mass) {
	shape = sf::CircleShape(radius);
	shape.setPosition(pos.x, pos.y);
	shape.setOrigin(radius, radius);
	int r = std::min(mass, 255.0f);
	int b = std::max(255-mass, 0.0f);
	shape.setFillColor(sf::Color(r, b, 0, 255));
}

void Particle::update(float dt) {
	float newX = pos.x + vel.x * dt;
	float newY = pos.y + vel.y * dt;

	if (hitLeftBound(newX)) {
		vel.x = -vel.x;
		pos.x = bounds.left + radius;
	}
	else if (hitRightBound(newX)) {
		vel.x = -vel.x;
		pos.x = bounds.getRight() - radius;
	}
	if (hitTopBound(newY)) {
		vel.y = -vel.y;
		pos.y = bounds.top + radius;
	}
	else if (hitBottomBound(newY)) {
		vel.y = -vel.y;
		pos.y = bounds.getBottom() - radius;
	}

	pos.x += vel.x * dt;
	pos.y += vel.y * dt;

	shape.setPosition(pos.x, pos.y);
}

bool Particle::intersects(const Particle& p) const{
	return (pos.x - p.pos.x)*(pos.x - p.pos.x)		  // a^2
		 + (pos.y - p.pos.y)*(pos.y - p.pos.y)		  // b^2
		 < (radius + p.radius) * (radius + p.radius); // r^2
}

void Particle::collide(Particle& p) {
	Vec2<float> collision = pos - p.pos;

	float dist = collision.getLength();
	
	Vec2<float> mtd(1.0f, 1.0f);
	if (radius + p.radius != dist)
		mtd = collision * (((radius + p.radius) - dist) / dist);

	float im1 = 1 / mass;
	float im2 = 1 / p.mass;

	pos += (mtd * (im1 / (im1 + im2)));
	p.pos -= (mtd * (im2 / (im1 + im2)));

	Vec2<float> v = vel - p.vel;
	float vn = (vel - p.vel).dot(mtd.unitVector());

	if (vn > 0.0f) return;

	float i = (-(1.0f + 0.85f) * vn) / (im1 + im2);
	Vec2<float> impulse = mtd.unitVector() * i;

	Vec2<float> imp1 = impulse * im1;
	
	vel += impulse * im1;
	p.vel -= impulse * im2;
}

bool Particle::hitLeftBound(float x) const {
	return x - bounds.left <= radius;
}

bool Particle::hitRightBound(float x) const {
	return bounds.getRight() - x <= radius;
}

bool Particle::hitTopBound(float y) const {
	return y - bounds.top <= radius;
}

bool Particle::hitBottomBound(float y) const {
	return bounds.getBottom() - y <= radius;
}