{
  description = "A really tiny engine for small games";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    flake-compat.url = "github:edolstra/flake-compat";
    flake-compat.flake = false;
  };
  outputs = { self, nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        extension = if nixpkgs.lib.hasSuffix "Darwin" system then "mach" else "elf";
      in
      {
        packages = rec {
          default = pkgs.clangStdenv.mkDerivation rec {
            name = "potetre2d";
            src = ./.;
            buildInputs = [ pkgs.python3 pkgs.libGLU pkgs.xorg.libX11 pkgs.alsa-lib ];

            EXTERNAL_PATH = "./libs";
            AUDIO_BACKEND = "fenster";

            installPhase = ''
              mkdir -p $out/bin $out/include $out/shared $out/tools
              cp build/potetre2d.${extension} $out/bin/potetre2d
              cp build/tools/* $out/tools
            '';
          };
        };
      }
    );
}
