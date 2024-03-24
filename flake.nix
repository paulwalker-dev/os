{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs?ref=nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        pkgsCross = import nixpkgs {
          inherit system;
          crossSystem = { config = "i686-elf"; };
        };
      in {
        devShells.default = pkgsCross.mkShell {
          nativeBuildInputs = with pkgs; [
            nixfmt qemu bear nasm
            (callPackage (import ./misc/mk.nix) { })
          ];
        };
      });
}
