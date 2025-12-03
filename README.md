# Texture Packer

master      | development
:---------: | :-----------:
[![Build status: master](https://ci.appveyor.com/api/projects/status/lqfgod1e1pncowc2/branch/master?svg=true)](https://ci.appveyor.com/project/reybits/texture-packer/branch/master "Branch: master") ![GitHub last commit (master)](https://img.shields.io/github/last-commit/reybits/texture-packer/master) | [![Build status: development](https://ci.appveyor.com/api/projects/status/lqfgod1e1pncowc2/branch/development?svg=true)](https://ci.appveyor.com/project/reybits/texture-packer/branch/development "Branch: development") ![GitHub last commit (development)](https://img.shields.io/github/last-commit/reybits/texture-packer/development)

The Texture Packer tool efficiently combines multiple images into a single optimized texture atlas, minimizing memory usage and boosting rendering performance. By leveraging advanced packing algorithms, it maximizes space utilization and streamlines asset management for game development and UI design, enabling faster load times and simplified workflow.

## Key features

- Automatically add images from a folder or via the command line.
- Supports input formats: JPEG, PNG, TGA, BMP, PSD, GIF, HDR, PIC, PNM.
- Exports to PNG (default), TGA, and BMP.
- Ability to trim input images to remove transparent areas.
- Option to set a border around images for better separation.

## Usage

```sh
texpacker INPUT_IMAGE [INPUT_IMAGE] <OPTIONS> --atlas=PATH
  INPUT_IMAGE        Input image file or directory (space-separated)
  --border=SIZE      Add border around sprites (default: 0 px)
  --padding=SIZE     Add padding between sprites (default: 1 px)
  --atlas=PATH       Output atlas file name (default: PNG)
  --xml=PATH         The output file path for the atlas description in XML format
  --prefix=PREFIX    Add prefix to texture path
  --algorithm=NAME   Packing algorithm (kdtree or classic, default: kdtree)
  --drop-ext         Remove file extension from sprite ID (default: false)
  --allow-dupes      Allow duplicate sprites (default: false)
  --keep-float       Preserve float hotspot coordinates (default: false)
  --atlas-size=SIZE  Maximum atlas size (default: 2048 px)
  --no-recurse       Do not search subdirectories
  --overlay          Overlay sprites (default: false)
  --pot              Make atlas dimensions power of two (default: false)
  --trim-sprite      Trim transparent borders from sprites (default: false)
  --trim-id=COUNT    Remove COUNT characters from the start of sprite IDs (default: 0)
```

## Download and build

You can browse the source code repository on GitHub or get a copy using git with the following command:
```sh
git clone https://github.com/reybits/texture-packer.git
make release
```

## Install with homebrew

```sh
brew tap reybits/homebrew-tap
brew install reybits/texture-packer
```

## Input files notes

- **JPEG** baseline & progressive (12 bpc/arithmetic not supported, same as stock IJG lib).
- **PNG** 1/2/4/8-bit-per-channel (16 bpc not supported).
- **TGA** (not sure what subset, if a subset).
- **BMP** non-1bpp, non-RLE.
- **PSD** (composited view only, no extra channels, 8/16 bit-per-channel).
- **GIF** (*comp always reports as 4-channel).
- **HDR** (radiance rgbE format).
- **PIC** (Softimage PIC).
- **PNM** (PPM and PGM binary only).

***

```
Copyright © 2017-2025 Andrey A. Ugolnik. All Rights Reserved.
https://github.com/reybits
and@reybits.dev
```
