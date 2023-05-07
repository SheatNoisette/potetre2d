{
  description = " A really tiny engine for small games";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    flake-compat.url = "github:edolstra/flake-compat";
    flake-compat.flake = false;
    wren.url = "github:wren-lang/wren";
    wren.flake = false;
    tigr.url = "github:erkkah/tigr";
    tigr.flake = false;
  };
  outputs = { self, nixpkgs, flake-utils, wren, tigr, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        extension = if nixpkgs.lib.hasSuffix "Darwin" system then "mach" else "elf";
      in
      {
        packages = rec {
          wrenAmalgamation = pkgs.stdenvNoCC.mkDerivation {
            name = "wren-amalgamation";
            nativeBuildInputs = [ pkgs.python3 ];
            src = wren;
            buildPhase = ''
              mkdir -p $out
              python util/generate_amalgamation.py > $out/wren.c
              cp -r src/include $out
            '';
          };
          default = pkgs.clangStdenv.mkDerivation rec {
            name = "potetre2d";
            src = ./.;
            buildInputs = [ pkgs.python3 pkgs.libGLU pkgs.xorg.libX11 ];

            EXTERNAL_PATH = "./external_deps";

            patchPhase = ''
              # Create the folders for external dependencies
              mkdir -p ${EXTERNAL_PATH}/wren/build/ ${EXTERNAL_PATH}/wren/src ${EXTERNAL_PATH}/tigr/ ${EXTERNAL_PATH}/pithy

              # Copy Wren
              cp ${wrenAmalgamation}/wren.c ${EXTERNAL_PATH}/wren/build/wren.c
              cp -r ${wren}/src/include ${EXTERNAL_PATH}/wren/src/

              # Copy Tigr
              cp -r ${tigr}/tigr.c ${tigr}/tigr.h ${EXTERNAL_PATH}/tigr

              # Copy Pithy
              # Pithy is actually in-repo
              cp -r ./external/pithy/pithy.c ./external/pithy/pithy.h ${EXTERNAL_PATH}/pithy
            '';

            installPhase = ''
              mkdir -p $out/bin $out/include $out/share
              cp -r src/generated/engine_std.wren $out/share
              cp -r src/generated/engine_std.h $out/include
              cp build/potetre2d.${extension} $out/bin/potetre2d
            '';
          };
        };
      }
    );
}
