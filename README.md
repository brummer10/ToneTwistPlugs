# ToneTwist Plugs

## MetalTone

![MetalTone](https://github.com/brummer10/ToneTwistPlugs/blob/main/MetalTone.png?raw=true)

MetalTone is modeled after the renowned BOSS MT-2 Metal Zone(*), a high gain distortion pedal with an advanced EQ section. 

It has standard active EQ controls with a massive 15dB of cut/boost range for the lows and highs. 
It also sports a parametric active EQ for the mids with two controls: the frequency, and the boost/cut amount. 

The midfreq parameter has a very wide range, going from 200Hz all the way to 5kHz. As a result, it's better to think of it simply as a single highly flexible active EQ, 
and disregard the idea that it's only for shaping the mids. 

Features: 
Modeled by Brummer 
Based on the BOSS MT-2 Metal Zone(*) 

(*) 'Other product names modeled in this software are trademarks of their respective companies that do not endorse and are not associated or affiliated with this software. 
BOSS MT-2 Metal Zone is a trademark or trade name of another manufacturer and was used merely to identify the product whose sound was reviewed in the creation of this 
product. All other trademarks are the property of their respective holders.

## CollisionDrive

![CollisionDrive](https://github.com/brummer10/ToneTwistPlugs/blob/main/CollisionDrive.png?raw=true)

CollisionDrive is modeled after the Horizon Devices Precision Drive(*), a modern overdrive pedal with a built-in noise gate.

Besides the usual Volume and Drive controls, the CollisionDrive features Attack and Bright controls.

The Attack control manipulates the response of the pedal, turning it down simultaneously softens the overdrive attack and increases the sustain.

The Bright control gives you even more flexibility. It can add presence to darker sounding amps, or remove buzzing when needed.

The Gate control sets the noise gate threshold. In the plugin interface, this control lights up to indicate that the noise gate is active.

Features:
Modeled by Brummer
Based on the Horizon Devices Precision Drive(*)

(*) 'Other product names modeled in this software are trademarks of their respective companies that do not endorse and are not associated or affiliated with MOD.
Horizon Devices Precision Drive is a trademark or trade name of another manufacturer and was used merely to identify the product whose sound was reviewed in the creation of this 
product. All other trademarks are the property of their respective holders.

## Formats

Neural Record come in the following plug-in formats:

* [LV2]
* [VST3]

## Compiling

Make sure you have installed the required build tools and libraries (see
section "Prerequisites" below) and then clone this repository (including
sub-modules) and simply run `make` in the project's root directory:

```con
git clone --recursive https://github.com:brummer10/ToneTwistPlugs
cd neuralrecord
make
```

## Installation

To install all plugin formats to their appropriate system-wide location, run
the following command (root priviledges may be required):

```con
make install
```

The makefiles support the usual `PREFIX` and `DESTDIR` variables to change the
installation prefix and set an installation root directory (defaulty: empty).
`PREFIX` defaults to `/usr/local`, but on macOS and Windows it is not used,
since the system-wide installation directories for plugins are fixed.

Use make's `-n` option to see where the plugins would be installed without
actually installing them.

You can also set the installation directory for each plugin format with a
dedicated makefile variable.

* LV2: `LV2_DIR` (`<prefix>/lib/lv2`)
* VST3: `VST3_DIR` (`<prefix>/lib/vst3`)

Example:

```con
make DESTDIR=/tmp/build-root PREFIX=/usr VST2_DIR=/usr/lib/lxvst install
```

To install the plugins only for your current user account, run:

```con
make install-user
```

Again, you can also set the installation directory for each plugin format with
a dedicated makefile variable.

* LV2: `USER_LV2_DIR` (`$HOME/.lv2`)
* VST2: `USER_VST2_DIR` (`$HOME/.vst2`)
* VST3: `USER_VST3_DIR` (`$HOME/.vst3`)
* CLAP: `USER_CLAP_DIR` (`$HOME/.clap`)

*Note: The given default values for all of the above listed environment
variables differ depending on the target OS.*


## Prerequisites

* The GCC C++ compiler, library and the usual associated software build tools
  (GNU `make`, etc.).

  Debian / Ubuntu users should install the `build-essential` package
  to get these, Arch users the `base-devel` package group.

* [pkgconf]

The [LV2] and [VST2] (vestige) headers are included in the
[DPF] framework, which is integrated as a Git sub-module. These need not be
installed separately to build the software in the respective plug-in formats.


## Author

This software was created by *brummer*.


## Acknowledgements

This project is built using the DISTRHO Plugin Framework ([DPF])

[DPF]: https://github.com/DISTRHO/DPF
[LV2]: http://lv2plug.in/
[pkgconf]: https://github.com/pkgconf/pkgconf
[VST3]: https://en.wikipedia.org/wiki/Virtual_Studio_Technology
