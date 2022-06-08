#include <iostream>
#include "matrix.hpp"

using mt::math::Vec21d;
using mt::math::Vec31d;
using mt::math::Vec13d;
using mt::math::Vec12d;

using mt::math::Mat22d;
using mt::math::Mat33d;
using mt::math::Mat44d;

using mt::math::Mat23d;
using mt::math::Mat34d;
using mt::math::Mat45d;
using mt::math::Mat56d;
using mt::math::Mat67d;
using mt::math::Mat78d;
using mt::math::Mat89d;
using mt::math::Mat910d;
using mt::math::Mat1011d;

int main()
{
	Mat23d A({ {
		{66,512,61},
		{3,8,7}
		
} });

	Mat34d B({ {
		{3,9,15,32},
		{4,7,10,56},
		{18,2,30,9}
} });

	Mat44d C({ {
		{1,2,3.4},
		{5,6,7,8},
		{9,10,11,12},
		{13,14,15,16}
	} });

	Mat56d D({ {
		{9,1,18,6,3,7},
		{1,43,8,11,3,26},
		{3,1,5,7,23,86},
		{98,2,67,12,21,34},
		{1,7,6,5,43,22}
} });

	std::cout << B.Gauss();
	std::cout << A + B;
	std::cout << A.Transp();
	std::cout << A - B;
	std::cout << A.Reverse();
	std::cout << A.Det();

	return 0;
}