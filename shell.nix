let
  nixpkgs = import <nixpkgs> {};
in
with nixpkgs;
stdenv.mkDerivation {
  name = "hooya-viewer";
  nativeBuildInputs = [
    cmake
    clang_14
    pcre
    gtkmm3
    pkgconfig
    gflags
    cairomm
  ];

  buildInputs = [
    git
    cmake-language-server
    ccls
  ];

  configurePhase = ''
    mkdir build
    cd build
    CXX=clang++ cmake .
  '';

  buildPhase = ''
    make
  '';
}
