#include "api.hpp"
#include "common.hpp"
#include "parser.hpp"

int main(int argc, char *argv[]) {
  rt::RunningOptions run_opt;

  rt::Parser::validate_arguments(argc, argv, run_opt);

  rt::API::init_engine(run_opt);
  rt::API::run();

  return EXIT_SUCCESS;
}
