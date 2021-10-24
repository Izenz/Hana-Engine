#ifndef MYVECTOR3_H
#define MYVECTOR3_H
#include <cmath>

#define _RADSTODEG 57.2958f;

template <class T>
class MyVector3 {
public:
	T x, y, z;
public:
	MyVector3() : x(T(0)), y(T(0)), z(T(0)) {};
	MyVector3(const T value) : x(value), y(value), z(value) {};
	MyVector3(const T x_value, const T y_value, const T z_value) : x(x_value), y(y_value), z(z_value) {};
	MyVector3(const MyVector3<T>& vec) : x(vec.x), y(vec.y), z(vec.z) {};

	MyVector3<T>& Normalize();
	const T Magnitude() const;

	const T distance_to(const MyVector3<T>& point) const;
	const T dot_product(const MyVector3<T>& vec) const;
	MyVector3<T> cross_product(const MyVector3<T>& vec) const;
	const T angle_between(const MyVector3<T>& vec) const;

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
inline const T MyVector3<T>::Magnitude() const{
	return (T)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

template <class T>
inline const T MyVector3<T>::distance_to(const MyVector3<T>& point) const {
	return (T) sqrt(pow(point.x - x,2) + pow(point.y - y, 2) + pow(point.z - z, 2));
}

template <class T>
inline const T MyVector3<T>::dot_product(const MyVector3<T>& vec) const {
	return (T)x * vec.x + y * vec.y + z * vec.z;
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
const T MyVector3<T>::angle_between(const MyVector3<T>& vec) const {
	T dot_prod = this->dot_product(vec);
	T temp = (this->Magnitude() * vec.Magnitude());
	return (T)acos(dot_prod / temp) * _RADSTODEG;
}

template class MyVector3<int>;
template class MyVector3<short>;
template class MyVector3<double>;
template class MyVector3<float>;

#endif