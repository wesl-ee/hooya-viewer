let
  nixpkgs = import <nixpkgs> {};
in
with nixpkgs;
stdenv.mkDerivation {
  name = "hooya-viewer";
  src = ./.;
  nativeBuildInputs = [
    cmake
    clang_14
    pcre
    pkgconfig
    gflags
    cairomm
    gtkmm3
    git
  ];

  buildInputs = [
    gtk3
    cairo
  ];

  configurePhase = ''
    mkdir build
    cd build
    CXX=clang++ cmake ..
  '';

  buildPhase = ''
    make
  '';

  installPhase = ''
    mkdir -p $out/bin
    mv hooya-viewer $out/bin
  '';
}
