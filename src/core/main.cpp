#include "background.hpp"

int main(int argc, char *argv[]) {
  BackgroundColor *b = new BackgroundColor({
      RGBColor{0, 255, 51},
      RGBColor{255, 255, 51},
      RGBColor{0, 0, 51},
      RGBColor{255, 0, 51},
  });

  b->dummy();

  return 0;
}

int main(int argc, char *argv[]) {
  BackgroundColor *b = new BackgroundColor({
      RGBColor{0, 255, 51},
      RGBColor{255, 255, 51},
      RGBColor{0, 0, 51},
      RGBColor{255, 0, 51},
  });

  b->dummy();

  return 0;
}

int main(int argc, char* argv[]) {
  rt::RunningOptions run_options;  // Stores incoming arguments.

  // ================================================
  // (1) Validate command line arguments.
  // ================================================
  validate_arguments(argc, argv, run_options);
  if (run_options.verbose) {  // Show options set by user if in "verbose" mode.
    constexpr short line_length{ 80 };
    std::cout << std::setw(line_length) << std::setfill('-') << "\n";
    std::cout << ">>> Running options are:\n" << to_string(run_options) << '\n';
    std::cout << std::setw(line_length) << std::setfill('-') << "\n\n";
  }
  // ================================================
  // (2) Welcome message
  // ================================================
  MESSAGE("Ray Tracer Teaching Tool -- rt3, v1.0\ncopyright DIMAp/UFRN 2025-2026.\n");

  // ================================================
  // (3) Initialize the renderer engine and load a scene.
  // ================================================
  rt::App::init_engine(run_options);
  rt::App::run();
  // rt::App::clean_up();

  MESSAGE("\n  --> Thanks for using rt3! <--\n");

  return EXIT_SUCCESS;
}
