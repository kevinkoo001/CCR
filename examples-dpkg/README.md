# Self Randomizing Debian Packages using the CCR Toolchain

This document describes a sample build process of a debian package 
integration with the CCR toolchain.

## Building Debian Packages Quickstart

A quick and concise guide on creating functional debian packages 
can be found [here](https://ubuntuforums.org/showthread.php?t=910717).

The guide does not cover the use of a debian maintainer script, 
which contains required behaviors as pre/post installation/uninstallation and so on. 
It should be located in the `DEBIAN` directory of your package source.

## Typical Use of the CCR

The executables produced by the CCR can be transformed into various instances using a randomizer. 
These variants are identifiable by the "\_shuffled" suffix added on to the name of 
the master executable by default.

### The Randomizer

We have packaged the randomizer (dubbed `prander`) into the debian package named `prander.deb` 
so that end users can invoke. Other packages relying on `prander` can list it as a dependency. 

## Achieving Self Randomization using Maintainer Scripts

To transform a master binary,
we designed a debian package maintainer script that can be triggered during installation process. 
Using a specific maintainer script for post-install operations (`postinst`), 
we invoke code transformation for each program to be installed. 
Keeping a `manifest` file allows for containing complete paths to all the executables in your package. 
Then, writing a `postinst` script allows for reading each file from `manifest` to call `prander`.
It ensures an automatic randomization process for every executable without user's intervention.

## Building the Self Randomizing Package

#### Compiling and Packaging

1. Compile your program written C/C++ with the CCR. It will generate the metadata for randomization 
(i.e., in the `.rand` section).
2. Create the debian package source directory.

#### Handling Randomization

3. Make a text file called `manifest`, containing full paths to all the exectuables seperated by new-line characters.
4. Write the `postinst` script in the `DEBIAN` directory to invoke `prander` listed in the `manifest` file. 
Our example has a `shuffle.sh`. 

#### Package Building and Installing

5. Build the package using the command `dpkg-deb --build <directory>`, which generates a `<directory>.deb` 
file being written to the present working directory.
6. Install the package with the command `sudo apt install ./<deb_file>`.

## Example

### Self-Randomizing Putty Package

The below illustrates the source directories of the `putty` package as an example. 
```
putty_0.70
├── DEBIAN
│   ├── control
│   ├── postinst
│   └── prerm
└── usr
    ├── bin
    │   ├── plink -> /usr/lib/putty/plink_shuffled
    │   ├── pscp -> /usr/lib/putty/pscp_shuffled
    │   ├── psftp -> /usr/lib/putty/psftp_shuffled
    │   ├── pterm -> /usr/lib/putty/pterm_shuffled
    │   ├── putty -> /usr/lib/putty/putty_shuffled
    │   ├── puttygen -> /usr/lib/putty/puttgen_shuffled
    │   ├── puttytel -> /usr/lib/putty/puttytel_shuffled
    │   └── shuffleputty -> /usr/lib/putty/shuffle.sh
    └── lib
        └── putty
            ├── manifest
            ├── plink
            ├── pscp
            ├── psftp
            ├── pterm
            ├── putty
            ├── puttygen
            ├── puttytel
            └── shuffle.sh
```

Specifically, this implementation takes advantage of `postinst` to trigger randomization. 
Here, `postinst` calls the script `shuffle.sh` by reading `manifest`, followed by invoking `prander`.

#### shuffle.sh
```
#!/bin/bash

set -e

MANIF="/usr/lib/putty/manifest"
while read line
do
    prander $line
done < "$MANIF"

exit 0
```

Lastly, we have added another command `shuffleputty` so that the user could re-randomize the executables on demand. 