#ifndef API_HPP
#define API_HPP

#include <memory>
#include <unordered_map>

#include "background.hpp"
#include "film.hpp"
#include "paramset.hpp"

namespace rt {

struct RenderOptions {
  std::unique_ptr<Background> bkg;
  std::unordered_map<string, ParamSet> objects;
};

class API {
public:
  enum APIState {
    Uninitialized,
    Initializing,
    Setup,
    World,
  };

  /// The infrastructure to render a scene (camera, integrator, etc.).
  static std::unique_ptr<RenderOptions> m_render_options;
  /// Current API state
  static APIState m_api_state;
  // Stores the CLI options that the 
  static RunningOptions m_run_options;

  // setup the ray tracer
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
