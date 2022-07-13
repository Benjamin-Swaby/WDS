{ pkgs ? import <nixpkgs> {} }:


  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = [ pkgs.cmake pkgs.gcc pkgs.xorg.libXcursor pkgs.xorg.libXi pkgs.xorg.libXinerama pkgs.xorg.libXrandr pkgs.cudaPackages.cudatoolkit pkgs.libGL pkgs.xorg.libXext ];
    LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";

}
