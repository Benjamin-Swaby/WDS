{ pkgs ? import <nixpkgs> {} }:


  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = [ pkgs.cmake pkgs.gcc pkgs.cudaPackages.cudatoolkit pkgs.libGL pkgs.gtk4 pkgs.pkg-config];
    LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";

}
