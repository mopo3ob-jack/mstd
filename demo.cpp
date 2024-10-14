#include <iostream>
#include <time.h>
#include <mstd/geometry>

int main(int argc, char** argv) {
	using namespace mstd;

	Vector4f vector(1.0f, 2.0f, 3.0f, 0.0f);
	Rotorf rotorA({1.0f, 0.0f, 0.0f}, {sqrtf(0.5f), sqrtf(0.5f), 0.0f});
	Rotorf rotorB({1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f});

	Matrix4f matrix = Matrix4f::perspective(1, M_PI / 2, 0.125, 4096.0);

	for (U32 y = 0; y < 4; ++y) {
		for (U32 x = 0; x < 4; ++x) {
			std::cout << matrix[y][x] << "\t";
		}
		std::cout << "\n";
	}

	//std::cout << std::string(matrix * vector) << "\n";
	
	return 0;
}
