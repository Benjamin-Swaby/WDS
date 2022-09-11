{ pkgs ? import <nixpkgs> {} }:


  pkgs.mkShell {
    # nativeBuildInputs is usually what you want -- tools you need to run
    nativeBuildInputs = [ pkgs.cmake pkgs.clang pkgs.xorg.libXcursor pkgs.xorg.libXi pkgs.xorg.libXinerama pkgs.xorg.libXrandr pkgs.cudaPackages.cudatoolkit pkgs.libGL pkgs.xorg.libXext pkgs.imgui pkgs.glfw pkgs.mesa pkgs.libGLU];
    LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";
    #LD_LIBRARY_PATH=with pkgs; "${libGL}/lib";

}
