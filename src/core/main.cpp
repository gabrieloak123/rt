#include "common.hpp"
#include "parser.hpp"

void print(rt::RunningOptions run_opt) {
	cout << "RunningOptions:" << endl;
	cout << "	- Input File:" << endl;
	cout << "		- " << run_opt.scene << endl;
	cout << "	- Region:" << endl;

	if(run_opt.crop_region.has_value()) {
		const auto &region = *run_opt.crop_region;

		cout << "		- (" << region[0].x << ", " << region[0].y << ")" << endl;
		cout << "		- (" << region[1].x << ", " << region[1].y << ")" << endl;
	} else {
		cout << "		not set" << endl;
	}
	cout << "	- Quick: " << run_opt.quick << endl;
	cout << "	- Filename: " << run_opt.outfile << endl;
}

int main(int argc, char* argv[]) {
  rt::RunningOptions run_opt;
  rt::Parser p(argc,argv);

  p.validate_arguments(run_opt);

  // rt::App::init_engine(run_options);
  // rt::App::run();
  // rt::App::clean_up();

  // MESSAGE("\n  --> Thanks for using rt3! <--\n");
  // p.parse_scene(run_opt.scene);
  delete run_opt.scene;

  return EXIT_SUCCESS;
}
