#include <cstdint>
#include <cstdio>
#include <stdexcept>
#include <string>

#include "tinyxml2/tinyxml2.h"
#include <CLI11/CLI11.hpp>

#include "common.hpp"
#include "parser.hpp"

void print(vector<string> v) {
  for (auto s : v) {
    cout << s << endl;
  }
}

struct WindowValidator : public CLI::Validator {
  WindowValidator() {
    name_ = "WINDOW";
    func_ = [](const string &str) {
      vector<string> parts = CLI::detail::split(str, ' ');
      if (parts.size() != 4) {
        cout << str << endl;
        print(parts);
        return string("Crop window must have 4 values (x1,y1,x2,y2)");
      }

      try {
        uint16_t x1 = std::stoul(parts[0]);
        uint16_t y1 = std::stoul(parts[1]);
        uint16_t x2 = std::stoul(parts[2]);
        uint16_t y2 = std::stoul(parts[3]);

        uint16_t max = 65535;

        // stoul converts to unsigned long, just checking early so the error
        // doesnt propagate
        if (x1 > max || x2 > max || y1 > max || y2 > max) {
          throw std::out_of_range("");
        }

        if (x2 < x1 || y2 < y1)
          return string("Invalid window: x2 < x1 or y2 < y1");

      } catch (const std::out_of_range &oor) {
        return string("Integer overflow on type uint16_t.");
      } catch (...) {
        return string("Invalid numeric values");
      }

      return string{};
    };
  }
};

struct ImageFormatValidator : public CLI::Validator {
  ImageFormatValidator() {
    name_ = "IMAGE";
    func_ = [](const string &str) {
      string lower = CLI::detail::to_lower(str);

      // if ends with .png or .ppm
      if (lower.size() < 4 || (lower.substr(lower.size() - 4) != ".png" &&
                               lower.substr(lower.size() - 4) != ".ppm")) {
        return string("File must have .png or .ppm extension");
      }

      return string{};
    };
  }
};

struct XMLValidator : public CLI::Validator {
  XMLValidator() {
    name_ = "XML";
    func_ = [](const string &str) {
      string lower = CLI::detail::to_lower(str);

      // if ends with .xml
      if (lower.size() < 4 || (lower.substr(lower.size() - 4) != ".xml")) {
        return string("File must have .xml extension");
      }

      return string{};
    };
  }
};

const static WindowValidator WindowValidator;
const static ImageFormatValidator ImageFormatValidator;
const static XMLValidator XMLValidator;

namespace rt {

void Parser::validate_arguments(int argc, char **argv,
                                rt::RunningOptions &run_opt) {
  CLI::App opts;
  opts.set_help_flag("--help,-h", "Print this help text.");

  string input_scene;
  vector<u_int16_t> crop_window;
  bool quick = false;
  string outfile;

  opts.add_option("<input_scene_file>", input_scene, "")
      ->required()
      ->check(CLI::ExistingFile)
      ->check(XMLValidator);

  auto crop_opt = opts.add_option("--window,-w", crop_window,
                                  "Specify an image crop window.")
                      ->check(CLI::Range(0, 65535))
                      ->expected(4);
  if (*crop_opt) {
    if (crop_window.size() != 4) {
      throw std::runtime_error("Crop window must have 4 values");
    }

    auto x1 = crop_window[0];
    auto y1 = crop_window[1];
    auto x2 = crop_window[2];
    auto y2 = crop_window[3];

    if (x2 < x1 || y2 < y1) {
      throw std::runtime_error("Invalid window");
    }

    run_opt.crop_region = {Pixel{x1, y1}, Pixel{x2, y2}};
  }
  opts.add_option("--outfile,-o", outfile,
                  "Write the rendered image to <filename>.")
      ->check(ImageFormatValidator);

  opts.add_flag("--quick,-q", quick,
                "Reduces quality parameters to render image quickly.");

  try {
    opts.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    std::exit(opts.exit(e));
  }

  run_opt.scene = input_scene;
  run_opt.quick = quick;
  run_opt.outfile = outfile;

  if (*crop_opt) {
    run_opt.crop_region = {Pixel{crop_window[0], crop_window[1]},
                           Pixel{crop_window[2], crop_window[3]}};
  } else {
    run_opt.crop_region.reset();
  }
}

void Parser::parse_scene(char *filename) {
  tinyxml2::XMLDocument scene;

  if (scene.LoadFile(filename) != tinyxml2::XML_SUCCESS) {
    cout << "Error loading scene." << endl;
    return;
  }

  tinyxml2::XMLElement *root = scene.RootElement(); // tag RT3

  if (root == nullptr) {
    cout << "Elementless" << endl;
    return;
  }

  for (tinyxml2::XMLElement *tag = root; tag->FirstChildElement() != nullptr;
       tag->NextSiblingElement()) {
    string tag_name = tag->Name();
    cout << tag_name << endl;
  }
}

} // namespace rt

void print(rt::RunningOptions run_opt) {
  cout << "RunningOptions:" << endl;
  cout << "	- Input File:" << endl;
  cout << "		- " << run_opt.scene << endl;
  cout << "	- Region:" << endl;

  if (run_opt.crop_region.has_value()) {
    const auto &region = *run_opt.crop_region;

    cout << "		- (" << region[0].x << ", " << region[0].y << ")"
         << endl;
    cout << "		- (" << region[1].x << ", " << region[1].y << ")"
         << endl;
  } else {
    cout << "		not set" << endl;
  }
  cout << "	- Quick: " << run_opt.quick << endl;
  cout << "	- Filename: " << run_opt.outfile << endl;
}
