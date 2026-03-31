#ifndef FILM_HPP
#define FILM_HPP

#include <vector>
#include <unordered_map>

#include "common.hpp"

using std::vector;
using std::unordered_map;

using Image = vector<vector<rt::RGBColor>>;
using Resolution = uint16_t; 

enum ImageType_e {
	PNG = 0,
	PPM3,
	PPM6,
};

enum FilmType_e {
	IMAGE = 0,
};

namespace rt {

class Film {
public:
	Film();
	~Film() = default;

	Resolution width(){ return m_x_res; };
	Resolution height(){ return m_y_res; };

	void add(Pixel p, RGBColor c);
	void write_image();
private:
	// The matrix of pixels itself, starting from TL until BR
	Image m_img;
	ImageType_e m_img_type;
	FilmType_e m_film_type;

	// The dimentions of the final image
	Resolution m_x_res;
	Resolution m_y_res;

	string m_filename;
};

} // namespace rt

#endif //FILM_HPP
