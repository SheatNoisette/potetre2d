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
    stb.url = "github:nothings/stb";
    stb.flake = false;
    fenster.url = "github:zserge/fenster";
    fenster.flake = false;
  };
  outputs = { self, nixpkgs, flake-utils, wren, tigr, stb, fenster, ... }:
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
            buildInputs = [ pkgs.python3 pkgs.libGLU pkgs.xorg.libX11 pkgs.alsa-lib ];

            EXTERNAL_PATH = "./external_deps";

            patchPhase = ''
              # Create the folders for external dependencies
              mkdir -p ${EXTERNAL_PATH}/wren/build/
              mkdir -p ${EXTERNAL_PATH}/wren/src
              mkdir -p ${EXTERNAL_PATH}/tigr/
              mkdir -p ${EXTERNAL_PATH}/pithy
              mkdir -p ${EXTERNAL_PATH}/stb
              mkdir -p ${EXTERNAL_PATH}/fenster
              mkdir -p ${EXTERNAL_PATH}/sts_mixer

              # Copy Wren
              cp ${wrenAmalgamation}/wren.c ${EXTERNAL_PATH}/wren/build/wren.c
              cp -r ${wren}/src/include ${EXTERNAL_PATH}/wren/src/

              # Copy Tigr
              cp -r ${tigr}/tigr.c ${tigr}/tigr.h ${EXTERNAL_PATH}/tigr

              # Copy STB libs
              cp -r ${stb}/stb_vorbis.c ${stb}/stb_perlin.h ${EXTERNAL_PATH}/stb

              # Copy Fenster audio
              cp ${fenster}/fenster_audio.h ${EXTERNAL_PATH}/fenster

              # Copy Pithy
              # Pithy is actually in-repo
              cp -r ./external/pithy/pithy.c ./external/pithy/pithy.h ${EXTERNAL_PATH}/pithy

              # Copy sts_mixer_mono
              # In repo
              cp ./external/sts_mixer/sts_mixer_mono.h ${EXTERNAL_PATH}/sts_mixer
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
