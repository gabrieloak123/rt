#ifndef API_HPP
#define API_HPP

#include <memory>
#include <stack>
#include <vector>
#include <unordered_map>
#include <string>


#include "paramset.hpp"
#include "parser.hpp"
#include "common.hpp"

using Resolution = uint16_t;

namespace rt {
  class Background;
  class Camera;
  class Integrator;
  class Scene;
  class Light;
  class Primitive;
  class Material;
  class Film;
  class Transform;

  enum AggregateType { LIST = 0, BVH };


  using DictOfMat = std::unordered_map< string, std::shared_ptr<Material> >;

struct GraphicsState{
  std::shared_ptr<Material> curr_material;  //!< Current material that globally affects all objects.
	std::shared_ptr<DictOfMat> mats_lib;      //!< Library of materials.
  bool flip_normals{false};                 //!< When true, we flip the normals
	bool mats_lib_cloned{false};

};

struct RenderOptions {
  
  std::shared_ptr<Background> background;
  std::shared_ptr<Camera> camera;
  std::unique_ptr<Integrator> integrator;
  std::unique_ptr<Scene> scene;
  AggregateType aggregator;
  int num_prims = 4;
  std::vector<std::shared_ptr<Light>> light_sources;
  std::vector<std::shared_ptr<Primitive>> elements;
  std::unordered_map<std::string, ParamSet> setup_params;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Primitive>>> obj_instances;
  std::unordered_map<std::string, std::shared_ptr<Material>> material_memory;

  std::vector<std::shared_ptr<Primitive>>* curr_instance{nullptr};
  std::shared_ptr<Material> current_material;

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

  static Transform curr_TM;

  static std::unordered_map<std::string, Transform> named_coord_sys;
  static GraphicsState curr_GS;
  static std::stack<GraphicsState> saved_GS;
  static std::stack<Transform> saved_TM;
  static std::unordered_map<std::string, std::shared_ptr<const Transform>> transformation_cache;

  // setup the ray tracer
  static void init_engine(const RunningOptions &opt);
  // calls the static function parse(opt.file_name)
  static void run();
  // ray tracing loop
  static void render();
  // frees all the resources previously allocated
  static void clean_up();

  // ParamSet methods to use on objects
  static void camera(const ParamSet &ps);
  static void look_at(const ParamSet &ps);
  static void background(const ParamSet &ps);
  static void material(const ParamSet &ps);
  static void world_begin(const ParamSet &ps);
  static void world_end(const ParamSet &ps);
  static void film(const ParamSet &ps);
  static void object(const ParamSet &ps);
  static void integrator(const ParamSet &ps);
  static void make_named_material(const ParamSet &ps);
  static void named_material(const ParamSet &ps);
  static void light_source(const ParamSet& ps);
  static void aggregator(const ParamSet& ps);

  static void identity(const ParamSet &ps);
  static void translate(const ParamSet &ps);
  static void scale(const ParamSet &ps);
  static void rotate(const ParamSet &ps);
  static void push_CTM(const ParamSet &ps);
  static void pop_CTM(const ParamSet &ps);
  static void push_GS(const ParamSet &ps);
  static void pop_GS(const ParamSet &ps);

  static void obj_instance_begin(const ParamSet& ps);
  static void obj_instance_call(const ParamSet& ps);
  static void obj_instance_end(const ParamSet& ps);
  

  // Methods that create the objects based on paramset's data
  static std::unique_ptr<Camera> make_camera(const ParamSet &camera,
                                             const ParamSet &look_at,
                                             const Resolution width,
                                             const Resolution height);
  static std::unique_ptr<Film> make_film(const ParamSet &ps);
  static std::unique_ptr<Integrator> make_integrator(const ParamSet& ps);
private:
  static bool check_in_initialized_state(std::string_view func_name);
  static bool check_in_setup_block_state(std::string_view func_name);
  static bool check_in_world_block_state(std::string_view func_name);

  static void soft_engine_reset();
  static void hard_engine_reset();
};

} // namespace rt

#endif // API_HPP
