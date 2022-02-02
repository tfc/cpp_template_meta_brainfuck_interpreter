let
  sources = import ./sources.nix {};
  pkgs = import sources.nixpkgs {};

  pkg = pkgs.callPackage ./build.nix {};
in

{
  with-gcc = pkg;
  with-clang = pkg.override { stdenv = pkgs.clangStdenv; };
}
