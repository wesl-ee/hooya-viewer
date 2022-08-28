HooYa! Viewer
=============

A standalone and simple GTK3 image viewer ported from the native file browser of
my HooYa! image tagger. The viewer is notable for its use of a masonry layout
to minimize the amount of blank space within the viewer itself.

Here is the viewer rendering some of <a href="https://twitter.com/chaesuart">Chaesu's</a> art.

<p align="center">
    <img src="https://raw.githubusercontent.com/wesl-ee/hooya-viewer/trunk/doc/img/two-window.jpeg" />
    <img src="https://raw.githubusercontent.com/wesl-ee/hooya-viewer/trunk/doc/img/directory-view.jpeg" />
</p>

Loosely inspired by [JPEGView](https://sourceforge.net/projects/jpegview/) and
[sxiv](https://github.com/muennich/sxiv).

Dependencies
------------

- cairo
- gtk3

If you plan on building from source you will need these also:

- cmake
- gflags
- C++ compiler like clang++ / g++
- pkgconfig
- gtkmm3
- cairomm

Building
--------

The HooYa! viewer is built and installed like this:

```
mkdir build
cd build
cmake ..
# or, CXX=clang++ cmake ..
make
make install
```

Nix users can simply run `nix-env -if ./default.nix` in the repo directory to
download the correct packages, build and install `hooya-viewer`.

Usage
-----

The HooYa! viewer can both view single images and also browse a directory of
images.

```
# Browse a directory of images
#
# > Double-click an image to open it in an extra window
hooya-viewer </path/to/directory>

# View a single image
#
# > Scroll on an image to zoom in or out
# > + / - to zoom in and out
hooya-viewer </path/to/image>
```

License
-------

All code in this repository is licensed under the MIT License (see `/LICENSE` file)
