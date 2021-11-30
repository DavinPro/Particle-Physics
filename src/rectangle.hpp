#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "vec2.hpp"

template <typename T>
class Rectangle {
public:
	T left;
	T top;
	T width;
	T height;

	constexpr Rectangle<T>(T left, T top, T width, T height) noexcept
		: left(left), top(top), width(width), height(height) {}

	constexpr Rectangle<T>(Vec2<T>& position, Vec2<T>& size) noexcept
		: left(position.x), top(position.y), width(size.x), height(size.y) {}

	constexpr T getRight() const noexcept {
		return left + width;
	}

	constexpr T getBottom() const noexcept {
		return top + height;
	}

	constexpr bool contains(const Rectangle<T>& r) const noexcept {
		return left <= r.left && getRight() >= r.getRight() &&
			   top <= r.top && getBottom() >= r.getBottom();
	}

	constexpr bool contains(const Vec2<T>& v) const noexcept {
		return v.x >= left && v.x <= getRight() &&
			   v.y >= top && v.y <= getBottom();
	}

	constexpr bool intersects(const Rectangle<T>& r) const noexcept {
		return left < r.getRight() && getRight() > r.left &&
			   top < r.getBottom() && getBottom() > r.top;
	}
};

#endif 
