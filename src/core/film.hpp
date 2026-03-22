#ifndef FILM_HPP
#define FILM_HPP

#include <vector>
#include <unordered_map>

#include "common.hpp"

using std::vector;
using std::unordered_map;

using Matrix = vector<vector<RGBColor>>;

enum ImageType_e {
	PNG = 0,
	PPM,
};

enum FilmType_e {
	IMAGE = 0,
};

class Film {
private:
	Matrix m_img;
	FilmType_e m_film_type;
	string m_filename;
	ImageType_e m_img_type;
	uint16_t m_x_res;
	uint16_t m_y_res;
};

#endif //FILM_HPP
