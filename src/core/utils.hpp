#ifndef UTILS_HPP
#define UTILS_HPP

#include <array>
#include <string>
#include <iostream>

using std::array;
using std::string;

using std::cout;
using std::endl;

namespace rt {
struct Point {
	u_int16_t x;
	u_int16_t y;
};

struct RunningOptions {
	array<Point,2> crop_region;
	bool quick;
	string outfile;
};

void print(RunningOptions run_opt) {
	cout << "RunningOptions:" << endl;
	cout << "	- Region:" << endl;
	cout << "		- (" << run_opt.crop_region[0].x << ", " << run_opt.crop_region[0].y << ")" << endl;
	cout << "		- (" << run_opt.crop_region[1].x << ", " << run_opt.crop_region[1].y << ")" << endl;
	cout << "	- Quick: " << run_opt.quick << endl;
	cout << "	- Filename: " << run_opt.outfile << endl;
}
} // namespace rt

#endif //UTILS_HPP
