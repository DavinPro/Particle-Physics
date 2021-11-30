#ifndef VEC2_HPP
#define VEC2_HPP

#include <math.h>

template <typename T>
class Vec2 {
public:
	T x;
	T y;

	constexpr Vec2<T>(T x, T y) noexcept
		: x(x), y(y) {}

	constexpr Vec2<T> operator+ (const Vec2<T>& right) const {
		return Vec2<T>(x + right.x, y + right.y);
	}

	constexpr Vec2<T> operator- (const Vec2<T>& right) const {
		return Vec2<T>(x - right.x, y - right.y);
	}

	constexpr Vec2<T> operator* (const Vec2<T>& right) const {
		return Vec2<T>(x * right.x, y * right.y);
	}

	constexpr Vec2<T> operator* (T t) const {
		return Vec2<T>(x * t, y * t);
	}

	constexpr Vec2<T> operator/ (const Vec2<T>& right) const {
		return Vec2<T>(x / right.x, y / right.y);
	}

	constexpr Vec2<T> operator/ (float right) const {
		return Vec2<T>(x / right, y / right);
	}

	constexpr Vec2<T>& operator+= (const Vec2<T>& other) noexcept {
		x += other.x;
		y += other.y;
		return *this;
	}

	constexpr Vec2<T>& operator-= (const Vec2<T>& other) noexcept {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	constexpr Vec2<T>& operator*= (const Vec2<T>& other) noexcept {
		x *= other.x;
		y *= other.y;
		return *this;
	}

	constexpr Vec2<T>& operator/= (const Vec2<T>& other) noexcept {
		x /= other.x;
		y /= other.y;
		return *this;
	}

	constexpr T dot(const Vec2<T>& right) const {
		return x * right.x + y * right.y;
	}

	constexpr Vec2<T> unitVector() {
		float mag = sqrt(x * x + y * y);
		return Vec2<T>(x / mag, y / mag);
	}

	constexpr T getLength() const {
		return sqrt(x * x + y * y);
	}
};

template <typename T>
constexpr Vec2<T> operator* (T t, const Vec2<T>& v) {
	return Vec2<T>(v.x * t, v.y * t);
}

#endif