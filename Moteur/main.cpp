#include "transform.h"


int main()
{
	Transform obj1;
	obj1.identity();
	obj1.rotate(0.f, 90.f, 0.f);
	std::cout << "Position: " << obj1.fPos.x << ", " << obj1.fPos.y << ", " << obj1.fPos.z << std::endl;
	std::cout << "Direction: " << obj1.fDir.x << ", " << obj1.fDir.y << ", " << obj1.fDir.z << std::endl;
	std::cout << "Right: " << obj1.fRight.x << ", " << obj1.fRight.y << ", " << obj1.fRight.z << std::endl;
	std::cout << "Up: " << obj1.fUp.x << ", " << obj1.fUp.y << ", " << obj1.fUp.z << std::endl;

	return 0;
}