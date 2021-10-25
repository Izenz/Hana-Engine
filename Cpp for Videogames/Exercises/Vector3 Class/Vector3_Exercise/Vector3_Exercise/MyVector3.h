#ifndef MYVECTOR3_H
#define MYVECTOR3_H

#include <cmath>
#include <numbers>

template <class T>
class MyVector3 {
public:
	T x, y, z;
public:
	MyVector3() : x(T(0)), y(T(0)), z(T(0)) {};							// In the industry  this kind of class is usually no initialized.
																		// Although that doesnt mean we should have non initialized variables
	// const not needed when you pass by values because if you change them nobody cares
	MyVector3(T value) : x(value), y(value), z(value) {};
	MyVector3(T x_value, T y_value, T z_value) : x(x_value), y(y_value), z(z_value) {};
	MyVector3(const MyVector3<T>& vec) : x(vec.x), y(vec.y), z(vec.z) {};

	MyVector3<T>& Normalize();
	T Magnitude() const;

	T distance_to(const MyVector3<T>& point) const;
	T dot_product(const MyVector3<T>& vec) const;
	// If you return by value makes no sense to return const it makes no difference
	MyVector3<T> cross_product(const MyVector3<T>& vec) const;
	T angle_between(const MyVector3<T>& vec) const;

	MyVector3<T>& operator+=(const T value);
	MyVector3<T>& operator-=(const T value);
	MyVector3<T>& operator*=(const T value);
	MyVector3<T>& operator/=(const T value);

	MyVector3<T>& operator+=(const MyVector3<T>& vec);
	MyVector3<T>& operator-=(const MyVector3<T>& vec);
	MyVector3<T>& operator*=(const MyVector3<T>& vec);
	MyVector3<T>& operator/=(const MyVector3<T>& vec);
private:
		T square(T value) const;
};

template <class T>
MyVector3<T>& MyVector3<T>::Normalize() {
	T temp = this->Magnitude();
	x /= temp;
	y /= temp;
	z /= temp;
	return *this;
}

template <class T>
inline T MyVector3<T>::Magnitude() const{
	return (T)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

template <class T>
inline T MyVector3<T>::distance_to(const MyVector3<T>& point) const {
	return (T) sqrt(square(point.x - x) + square(point.y - y) + square(point.z - z));
}

template <class T>
inline T MyVector3<T>::dot_product(const MyVector3<T>& vec) const {
	// Refactorize using minus operator.
	return (T)(x * vec.x + y * vec.y + z * vec.z);
}

template <class T>
MyVector3<T> MyVector3<T>::cross_product(const MyVector3<T>& vec) const {
	return MyVector3(
		(y * vec.z) - (z * vec.y),
		(z * vec.x) - (x * vec.z),
		(x * vec.y) - (y * vec.x)
	);
}

template <class T>
T MyVector3<T>::angle_between(const MyVector3<T>& vec) const {
	T dot_prod = this->dot_product(vec);
	T temp = (this->Magnitude() * vec.Magnitude());
	// Move rads outside to main since its only used to show values. Engine uses radians.
	return (T)acos(dot_prod / temp);
}

template <class T>
MyVector3<T>& MyVector3<T>::operator+=(const T value) {
	x += value;
	y += value;
	z += value;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator-=(const T value) {
	x -= value;
	y -= value;
	z -= value;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator*=(const T value) {
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator/=(const T value) {
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator+=(const MyVector3<T>& vec) {
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator-=(const MyVector3<T>& vec) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator*=(const MyVector3<T>& vec) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;

	return *this;
}

template <class T>
MyVector3<T>& MyVector3<T>::operator/=(const MyVector3<T>& vec) {
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;

	return *this;
}

template <class T>
inline T MyVector3<T>::square(T value) const {
	return value * value;
}

template class MyVector3<int>;
template class MyVector3<short>;
template class MyVector3<double>;
template class MyVector3<float>;

#endif

// Its better to have an inline function that squares a number instead of calling pow
/*

inline auto square (const auto a) {
	return a*a;
} // Has to be inline to not be an overhead.

normalize{
	T n = sqrt(square(x)....)
	assert(n > T(EPSILON));
	// #define EPSILON 1e-5
	T invN = T(1)/n;
	return...;
}

pow > expensive than writing your own square func.


*/