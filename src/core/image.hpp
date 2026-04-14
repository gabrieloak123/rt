#ifndef IMAGE_HPP
# define IMAGE_HPP

// @author = Sam Altman's child
// ===
# include <cstdint>
# include <string>
# include <vector>

# include "common.hpp"
# include "lodepng/lodepng.h"


namespace rt {
/// Routines to write images to a file.
bool save_ppm6(const std::vector<RGBColor>, size_t, size_t, const std::string& = "image.ppm", size_t = 1);

/// Saves an image as a **ascii** PPM file.
bool save_ppm3(const std::vector<RGBColor>, size_t, size_t, const std::string& = "image.ppm", size_t = 1);

/// Saves an image as a PNG file.
bool save_png(const std::vector<RGBColor>, size_t, size_t, const std::string& = "image.png", size_t = 1);
}  // namespace rt
// ===
#endif
