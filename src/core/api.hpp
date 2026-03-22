#ifndef API_HPP
#define API_HPP

#include "film.hpp"
#include "background.hpp"
#include "utils.hpp"
#include "camera.hpp"

class API {
private:
	Film m_film;
	BackgroundColor m_bkg;
	Camera m_camera;

public:
	// stores the running options and initialize the API's internal states (graphics state)
	void init_engine(const RunningOptions &opt);
	// calls the static function parse(opt.file_name)
	void run();
	// ray tracing loop
	void render();
	// frees all the resources previously allocated
	void clean_up();
};

#endif //API_HPP
