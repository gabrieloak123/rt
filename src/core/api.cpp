#include <chrono>
#include <iomanip>
#include <memory>
#include <sstream>
#include <utility>

#include "api.hpp"
#include "common.hpp"
#include "error.hpp"
#include "parser.hpp"

namespace rt {

// @author = Selan Santos
// ===
std::unique_ptr<RenderOptions> API::m_render_options;
API::APIState API::m_api_state = API::Uninitialized;
// @author = Selan Santos
// ===
RunningOptions API::m_run_options;

void API::init_engine(const RunningOptions &opt) {
  m_run_options = opt;

  if (m_api_state != API::Uninitialized) {
    ERROR("API::init_engine() has already been called! ");
  }

  m_api_state = API::Setup;
  m_render_options = std::make_unique<RenderOptions>();
  // m_current_gs = GraphicsState();
  MESSAGE("[1] Rendering engine initiated.\n");
}

// calls the static function parse(opt.file_name)
void API::run() {
  Parser::parse_scene(m_run_options.scene);
  // [1] Parser and load scene file
  // [2] Instantiate the Camera, Film, and Background objects.
  // [3] Enter the ray tracing main loop, because parser has found the
  // `world_end` tag
};

// frees all the resources previously allocated
void API::clean_up() {}

/// Check whether the current state has been intialized.
bool API::check_in_initialized_state(std::string_view func_name) {
  if (m_api_state == API::Uninitialized) {
    std::ostringstream oss;
    oss << "API::init() must be called before " << func_name << ". Ignoring...";
    ERROR(oss.str());
    return false;
  }
  return true;
}

/// Check whether the current state corresponds to setup section.
bool API::check_in_setup_block_state(std::string_view func_name) {
  check_in_initialized_state(func_name);
  if (m_api_state == API::World) {
    std::ostringstream oss;
    oss << "Rendering setup cannot happen inside World Definition block; ";
    oss << func_name << " not allowed. Ignoring...";
    ERROR(oss.str());
    return false;
  }
  return true;
}

/// Check whether the current state corresponds to the world section.
bool API::check_in_world_block_state(std::string_view func_name) {
  check_in_initialized_state(func_name);
  if (m_api_state == API::Setup) {
    std::ostringstream oss;
    oss << "Scene description must happen inside World Definition block; ";
    oss << func_name << " not allowed. Ignoring...";
    ERROR(oss.str());
    return false;
  }
  return true;
}

void API::world_begin(const ParamSet &ps) {
  check_in_setup_block_state("API::world_begin()");
  m_api_state = API::World; // correct machine state.
  hard_engine_reset();
}

/// Erase temporary engine states so that we may render another scene with the
/// same configuration.
void API::hard_engine_reset() {
  // Render options reset
  // TODO: in the future.
}

void API::world_end(const ParamSet &ps) {
  MESSAGE(
      "====================================================================");
  MESSAGE("   Parsing Phase has ended. Rendering process starts now...");
  MESSAGE(
      "====================================================================");

  check_in_world_block_state("API::world_end()");

  // ===============================================================
  // 1) Create the integrator.
  // 2) Create the scene (requires the list of objects and background)
  // ===============================================================
  // For now, we create the film here but in the future it will be
  // instantiated somewhere else.
  std::unique_ptr<Film> film = make_film(m_render_options->objects["film"]);
  if (film == nullptr) {
    ERROR("API::setup_camera(): Unable to create film.");
  } else {
    m_render_options->film = std::move(film);
  }

  // The scene has already been parsed and properly set up. It's time to render
  // the scene. [1] Create the integrator. [2] Create the scene. [3] Run
  // integrator if previous instantiations went ok
  bool scene_and_integrator_ok{true}; // THIS is a STUB.
  if (scene_and_integrator_ok) {
    MESSAGE("    Parsing scene successfuly done!\n");
    MESSAGE("[2] Starting ray tracing progress.\n");
    MESSAGE("    Ray tracing is usually a slow process, please be patient: \n");
    //================================================================================
    auto start = std::chrono::steady_clock::now();
    // m_integrator->render(*m_scene);
    render();
    auto end = std::chrono::steady_clock::now();
    //================================================================================
    auto diff = end - start; // Store the time difference between start and end
    // Seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    MESSAGE("    Time elapsed: " + std::to_string(diff_sec.count()) +
            " seconds (" +
            std::to_string(
                std::chrono::duration<double, std::milli>(diff).count()) +
            " ms) \n");
  }
  // [4] Basic clean up, preparing for new rendering, in case we have
  // several scene setup + world in a single input scene file.
  m_api_state = API::Setup; // correct machine state.
}

void API::film(const ParamSet &ps) {
  if (not check_in_setup_block_state("API::film()")) {
    return;
  }
  // Store the ps associated with camera for later retrieval.
  m_render_options->objects["film"] = ps;
  if (m_run_options.verbose) {
    auto type = ps.retrieve<std::string>("type", "unknown");
    std::cout << ">>> film type: " << std::quoted(type) << '\n';
  }
}

void API::background(const ParamSet &ps) {
  check_in_world_block_state("API::background");

  auto type = ps.retrieve<std::string>("type", "unknown");
  if (type == "unknown") {
    ERROR(
        "API::background(): Missing \"type\" specificaton for the background.");
  }
  Background *bkg{nullptr};
  if (type == "single_color" or type == "4_colors") {
    bkg = create_color_background(type, ps);
  } else {
    WARNING(std::string{"API::background(): unknown background type \""} +
            type + std::string{"\" provided; assuming colored background."});
    bkg = create_color_background(type, ps);
  }
  // Store current background objec.
  m_render_options->background.reset(bkg);
}

void API::render() {
  // Perform objects initialization here.
  // -------------------------------------------------------------
  // The Film object holds the memory for the image.

  auto &film = m_render_options->film;
  auto w = film->width();
  auto h = film->height();
  // -------------------------------------------------------------
  // Traverse all pixels to shoot rays from.
  for (byte j = 0; j < h; j++) {
    for (byte i = 0; i < w; i++) {
      // Not shooting rays just yet; so let us sample the background.
      auto color = m_render_options->background->sample(
          float(i) / float(w), float(j) / float(h)); // get background color.
      m_render_options->film->add(
          Pixel{i, j},
          color); // set image buffer at position (i,j), accordingly.
    }
  }
  // send image color buffer to the output file.
  m_render_options->film->write_image();
}

std::unique_ptr<Film> API::make_film(const ParamSet &ps) {
  std::unique_ptr<Film> film{nullptr};
  auto film_type = ps.retrieve<string>("type", "unknown");
  if (film_type == "image") {
    film = create_film(ps);
  } else {
    WARNING(string{"Film \""} + film_type + string{"\" unknown."});
  }
  return film;
}
// ===

} // namespace rt
