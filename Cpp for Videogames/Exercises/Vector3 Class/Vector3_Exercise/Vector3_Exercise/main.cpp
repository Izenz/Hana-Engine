#include "MyVector3.h"
#include <iostream>
#include <cassert>

template <typename T>
std::ostream& operator << (std::ostream& out, MyVector3<T> vec) {
	out << "<" << vec.x << "," << vec.y << "," << vec.z << ">" << std::endl;
	return out;
}

int main()
{
	MyVector3<int> example_1;
	MyVector3<float> example_2(1,0,1);
	MyVector3<float> example_3(5,2,6);

	MyVector3<float> norm_e3(example_3);
	norm_e3.Normalize();

	std::cout << "V1: " << example_1;
	std::cout << "V2: " << example_2;
	std::cout << "V3: " << example_3;
	std::cout << "Normalized V3: " << norm_e3;

	std::cout << "Distance between V2 and V3: " << example_2.distance_to(example_3) << std::endl;
	std::cout << "Angle between V2 and V3: " << example_2.angle_between(example_3) << std::endl;
	std::cout << "DotP between V2 and V3: " << example_2.dot_product(example_3) << std::endl;
	std::cout << "CrossP between V2 and V3: " << example_2.cross_product(example_3) << std::endl;
}
