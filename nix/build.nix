{ stdenv, lib }:

stdenv.mkDerivation {
  name = "cpp_template_meta_brainfuck_interpreter";

  src = lib.sourceByRegex ./.. [
    "^.*\.cpp$"
    "^.*\.hpp$"
    "^Makefile$"
  ];

  doCheck = true;
  checkPhase = ''
    output=$(./main)
    [[ "$output" =~ "Hello World!" ]] || echo "expected Hello World output"
  '';

  installPhase = ''
    mkdir -p $out/bin
    install -m755 main $out/bin
  '';
}
