#include "Arena.hpp"
#include <iostream>
#include <time.h>
#include "Vector3.hpp"

int main(int argc, char** argv) {
	using namespace mstd;

	std::string numberA;
	std::string numberB;
	std::string numberC;
	std::string numberD;
	std::cin >> numberA;
	std::cin >> numberB;
	std::cin >> numberC;
	std::cin >> numberD;
	Vector3f a(std::atof(numberA.c_str()), std::atof(numberD.c_str()), std::atof(numberB.c_str()));
	Vector3f b(std::atof(numberA.c_str()), std::atof(numberB.c_str()), std::atof(numberC.c_str()));
	
	std::cout << std::string(a / std::atof(numberA.c_str())) << std::endl;

	return 0;
}
