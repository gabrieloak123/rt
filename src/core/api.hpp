#ifndef API_HPP
#define API_HPP

#include <memory>
#include <unordered_map>

#include "background.hpp"
#include "camera.hpp"
#include "paramset.hpp"


namespace rt {

struct RenderOptions {
	std::unique_ptr<Film> film;
	std::unique_ptr<Background> bkg;
	std::unordered_map<string, ParamSet> objects;
};

class API {
	enum APIState {
		Initializing,
		Setup,
		World,
	};

private:
	Background m_bkg;
	Camera m_camera;
	RenderOptions m_render_opts;


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

} //namespace rt

#endif //API_HPP
