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
public:
  enum APIState {
    Initializing,
    Setup,
    World,
  };

  Background m_bkg;
  Camera m_camera;
  RenderOptions m_render_opts;
  static RunningOptions m_run_options;

  // stores the running options and initialize the API's internal states
  // (graphics state)
  static void init_engine(const RunningOptions &opt);
  // calls the static function parse(opt.file_name)
  static void run();
  // ray tracing loop
  static void render();
  // frees all the resources previously allocated
  static void clean_up();

  static void camera(const ParamSet &ps);
  static void look_at(const ParamSet &ps);
  static void background(const ParamSet &ps);
  static void material(const ParamSet &ps);
  static void world_begin(const ParamSet &ps);
  static void world_end(const ParamSet &ps);
  static void film(const ParamSet &ps);
  static Film *make_film(const ParamSet &);
};

} // namespace rt

#endif // API_HPP
