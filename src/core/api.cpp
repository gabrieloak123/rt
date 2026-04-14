#include <memory>

#include "api.hpp"
#include "common.hpp"
#include "error.hpp"
#include "parser.hpp"

namespace rt {

// @author = Selan Santos
// ===
std::unique_ptr<RenderOptions> API::m_render_options;
API::APIState API::m_api_state = API::Uninitialized;
RunningOptions API::m_run_options;

void API::init_engine(const RunningOptions &opt) {
  m_run_options = opt;

  if (m_api_state != API::Uninitialized) {
    ERROR("App::init_engine() has already been called! ");
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
// [3] Enter the ray tracing main loop, because parser has found the `world_end` tag
};
void API::render() {
// 	// Perform objects initialization here.
// 	// The Film object holds the memory for the image.
// 	// ...
// 	auto w = m_camera.film().width(); // Retrieve the image dimensions in
// pixels. 	auto h = m_camera.film().height();
// 	// Traverse all pixels to shoot rays from.
// 	for (uint16_t  j = 0 ; j < h ; j++ ) {
// 		for(uint16_t i = 0 ; i < w ; i++ ) {
// 			// Not shooting rays just yet; so let us sample the
// background. 			auto color = m_bkg.sample( float(i)/float(w), float(j)/float(h)
// ); // get background color. 			m_camera.film().add( Pixel{i,j}, color ); // set
// image buffer at position (i,j), accordingly.
// 		}
// 	}
// 	// send image color buffer to the output file.
// 	m_camera.film().write_image();
}
// frees all the resources previously allocated
void clean_up();
// ===

} // namespace rt
