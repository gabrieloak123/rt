#ifndef APP_HPP
#define APP_HPP

#include "film.hpp"
#include "background.hpp"
#include "camera.hpp"
#include "utils.hpp"

namespace rt {

class App{
	Film m_film;
	BackgroundColor m_bkg;
	Camera m_camera;

  	void init_engine(RunningOptions run_opt);
  	void run();
  	void clean_up();
};


} //namespace rt

#endif //APP_HPP
