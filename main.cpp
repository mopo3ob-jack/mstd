#include <mstd/geometry>
#include <iostream>

using namespace mstd;

int main() {
	Vector3f start = Vector3f(1.0f, 0.0f, 0.0f);
	Vector3f end = Vector3f(0.0f, 1.0f, 0.0f);
	Rotorf rotor(start, end);

	std::cout << rotor.s << ", <" << rotor.yz << ", " << rotor.zx << ", " << rotor.xy << ">\n";

	Vector3f v = Vector3f(1.0f, 0.0f, 0.0f);

	v = Matrix3f(rotor) * v;

	std::cout << std::string(v) << std::endl;
}
