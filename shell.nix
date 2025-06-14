let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-24.11";
  pkgs = import nixpkgs { config = {}; overlays = []; };
in

pkgs.mkShell {
  packages = with pkgs; [
    cmake
    git
    curl
    pkg-config
    patchelf
    boost
    icu
    glm
    libarchive
    tinyxml-2
    libpng
    sdl3
    glew-egl
  ];

  BUILD_USE_NIX = "ON";

  shellHook = ''
    echo "Run ./build.sh to build the application with Nix."
  '';
}
