# Ray Tracer

Project developed to a university class. Basically it renders a image given a scene description.

## Build

To build execute the following:
```
cmake -S . -B build
cmake --build build
```

Or, make it more convenient:
```bash
alias build_rt="cmake -S . -B build; cmake --build build"
```

## Run

The executable `rt` will be generate inside the `/build` directory, so is highly recommended to:
```bash
alias rt="./build/rt"
```

Use one of the scenes available in `/scenes` or create your based on the same syntax.

```bash
❯ rt -h

rt [OPTIONS] <input_scene_file>


POSITIONALS:
  <input_scene_file> TEXT:FILE REQUIRED

OPTIONS:
  -h,     --help              Print this help text.
  -w,     --window UINT:INT in [0 - 65535] x 4
                              Specify an image crop window.
  -o,     --outfile TEXT      Write the rendered image to <filename>.
  -q,     --quick             Reduces quality parameters to render image quickly.
          --verbose           Prints some internal info.
```

