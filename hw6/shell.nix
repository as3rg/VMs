{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.gnumake
    pkgs.gdb
    pkgs.valgrind
    pkgs.cppcheck
    pkgs.clang-tools
  ];
}
