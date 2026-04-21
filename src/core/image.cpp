#include <cstdint>

#include <fstream>

#include "image.hpp"

namespace rt {

/// Saves an image as a **binary** PPM file.
bool save_ppm6(const std::vector<RGBColor> data,
               Resolution w,
               Resolution h,
               const std::string& file_name_,
               Resolution d
                ) {
  std::ofstream ofs(file_name_, std::ios::out | std::ios::binary);

  if(!ofs.is_open()){
    std::cerr << "Error on create the file" + file_name_ << '\n';
    return false;
  }

  ofs << "P6\n" << w << ' ' << h << '\n';
  ofs << "255\n";

  std::vector<char> buffer;
  buffer.reserve(w * h * 3);

  for(const auto& color : data){
    buffer.push_back(static_cast<char>(color.red));
    buffer.push_back(static_cast<char>(color.green));
    buffer.push_back(static_cast<char>(color.blue));
  }

  ofs.write(buffer.data(), buffer.size());
  ofs.close();

  return true;  // STUB
}

/// Saves an image as a **ascii** PPM file.
bool save_ppm3(const std::vector<RGBColor> data,
               Resolution w,
               Resolution h,
               const std::string& file_name_,
               Resolution d) {

  std::ofstream ofs(file_name_);

  if(!ofs.is_open()){
    std::cerr << "Error on create the file " + file_name_ << '\n';
    return false;
  }
  ofs << "P3\n" << w << ' ' << h << "\n255\n";

  for(auto& color : data){
    ofs << (int) color.red << ' ' << (int) color.green << ' ' << (int) color.blue << '\n';
  }
  
  ofs.close();
  return true;  // STUB
}

bool save_png(const std::vector<RGBColor> data,
              Resolution w,
              Resolution h,
              const std::string& file_name_,
              Resolution d) {
  
  std::vector<std::uint8_t> img;
  img.reserve(w * h * 4);

  for(auto& color : data){
    img.push_back(color.red);
    img.push_back(color.green);
    img.push_back(color.blue);
    img.push_back(255); // blk = 255.
  }

  unsigned error = lodepng::encode(file_name_, img, w, h);
  if(error){std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << "\n";return false;}
  else     {std::cout << "image generated in: " << file_name_ << "\n";}
  return true;  // STUB
}

}  // namespace rt
