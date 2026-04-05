#include "common.hpp"

namespace rt {
class Parser {
public:
  ~Parser() = default;

  static void validate_arguments(int argc, char **argv, RunningOptions &run_opt);
  void parse_scene(char* filename);

};

} // namespace rt

void print(rt::RunningOptions run_opt);
