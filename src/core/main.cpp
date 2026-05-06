#include "api.hpp"


int main(int argc, char *argv[]) {
  rt::RunningOptions run_opt;

  rt::Parser::validate_arguments(argc, argv, run_opt);

  rt::API::init_engine(run_opt);
  rt::Parser::parse_scene(run_opt.scene);
  rt::API::clean_up();

  return EXIT_SUCCESS;
}
