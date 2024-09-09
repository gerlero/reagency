# reagency

[![CI](https://github.com/gerlero/reagency/actions/workflows/ci.yml/badge.svg)](https://github.com/gerlero/reagency/actions/workflows/ci.yml)
[![OpenFOAM versions](https://img.shields.io/badge/openfoam-v2112%20%7C%20v2206%20%7C%20v2212%20%7C%20v2306%20%7C%20v2312%20%7C%20v2406-informational)](https://www.openfoam.com)
[![Docker](https://github.com/gerlero/reagency/actions/workflows/docker.yml/badge.svg)](https://github.com/gerlero/reagency/actions/workflows/docker.yml)
[![Docker image](https://img.shields.io/badge/docker%20image-microfluidica%2Freagency-0085a0)](https://hub.docker.com/r/microfluidica/reagency/)

A simple, extensible reaction model for OpenFOAM.

## Installation

### Install from source

#### Requirements

**reagency** requires [OpenFOAM](https://www.openfoam.com), as distributed by OpenCFD (openfoam.com). Compatible OpenFOAM versions are v2112, v2206, v2212, v2306, v2312 and v2406.

_Versions produced by the OpenFOAM Foundation (openfoam.org) (e.g. OpenFOAM 11, OpenFOAM 12) are not compatible. macOS users may want to consider [OpenFOAM.app](https://github.com/gerlero/openfoam-app)._


#### Download

[Download the source code](https://github.com/gerlero/porousMicroTransport/archive/refs/heads/main.zip) of **reagency**, or clone this repository with Git:

```sh
git clone https://github.com/gerlero/reagency.git
```

#### Compile

To build and install **reagency**, just invoke the top-level `Allwmake` script:

```sh
cd reagency
./Allwmake -j
```

_If necessary, activate/source the correct OpenFOAM environment before running `Allwmake`._

#### Test

Optionally, you can verify the installation of **reagency** by running the included test suite (requires Python 3.7 or later):

```sh
tests/Alltest
```
