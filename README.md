# Sensor Watch Neralie
A face for the sensor watch that will allow you to display time in Neralie. 

## Required packages
In order to compile this face, you'll need the correct compiler and a libc that'll be happy about being on the watch.

On Arch, the package names are `arm-none-eabi-gcc` and `arm-none-eabi-newlib` for the compiler and lib, respectively.

## Compilation
It's still a little clunky, but here's how I do it.

Clone this repository within the Sensor Watch's. It'll look something like this

```
git clone https://github.com/joeycastillo/Sensor-Watch
cd Sensor-Watch
git clone https://github.com/gennyble/neralie-sensor-watch
```

Now navigate into `neralie-sensor-watch/make` and run `make`.

## Getting it on the watch
Get the Sensor Watch board free from it's white plastic prison. Be sure the watch is not still powered; don't plug it into the MicroB without removing the battery. Now plug it in to a MicroB cable. Be sure that the beveled side of the Micro-B connector is on the same side as the processor of the Sensor Watch board. Flip the board over- gently! the connector is delicate- and find the small reset button. Tap it twice, rapidly, to put the watch into the required UF2 bootloader mode. It usually takes me a few attempts, so don't worry if it takes a few tries.

If you're on a sensible system- mainly Windows, Mac, or Ubuntu in this case- `make install` should work for you. If, however, you are on a system that doesn't mount for you, you can use the script found at `/make/upload.sh` to get the firmware to the watch. You need to run it as root, to mount/unmount the watch, so I recommend you give it a glance before you do so.

If all went well your watch's red light should flash with incoming data and then reset into your program. You're now safe to remove it from the MicroB and reassemble the watch.

# Licensing
The file at `/make/Makefile` is Copyright (c) 2021 Joey Castillo under the MIT License. See [LICENSE_MIT](LICENSE_MIT)

The rest of the code here is cast into the public domain under the CC0 license as seen in [LICENSE](LICENSE). You are free to do with it what you want, go crazy. No attribution required, but always appreciated.