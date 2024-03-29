{ pkgs ? import <nixpkgs> {} }:

  pkgs.mkShell {
    nativeBuildInputs = [
        pkgs.cmake pkgs.clang
        pkgs.xorg.libXcursor pkgs.xorg.libXi pkgs.xorg.libXinerama pkgs.xorg.libXrandr pkgs.xorg.libXext
        pkgs.libGL pkgs.imgui pkgs.glfw pkgs.mesa pkgs.libGLU
    ];
    
    LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";
}
