#include <iostream>
#include <time.h>
#include <mstd/geometry>

int main(int argc, char** argv) {
	using namespace mstd;

	Vector3f vector(1.0f, 2.0f, 3.0f);
	Rotorf rotorA({1.0f, 0.0f, 0.0f}, {0.0f, sqrtf(0.5f), sqrtf(0.5f)});
	Rotorf rotorB({1.0f, 0.0f, 0.0f}, {0.0f, sqrtf(0.5f), sqrtf(0.5f)});

	std::cout << std::string((rotorA + rotorB).rotate(vector)) << "\n";
	
	return 0;
}
