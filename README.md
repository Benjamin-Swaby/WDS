# Wave Diffraction Simulation

## Dependancies General:
- Opengl
- cuda toolkit
- cmake
- C/++ compiler

## Dependancies Linux:
- libXcursor
- libXi
- libXinerama
- libXrandr
   

## Building Linux:
	mkdir build
	cd build
	cmake ..
	make all
	
## Building With Nix:
   mkdir build
   export NIXPKGS_ALLOW_UNFREE=1
   nix-shell
   cd build
   cmake ..
   make all

## 