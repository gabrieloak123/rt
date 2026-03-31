#include "common.hpp"

namespace rt {
class Parser {
public:
  Parser(int argc, char **argv) : m_argc(argc), m_argv(argv) {};
  ~Parser() = default;

  void validate_arguments(RunningOptions &run_opt);
  void parse_scene(char* filename);

private:
  int m_argc;
  char **m_argv;
};
} // namespace rt
