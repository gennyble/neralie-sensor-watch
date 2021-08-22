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

In the make directory, run the `upload.sh` script (probably as root as it needs to mount and unmount the watch). If all went well your watch's red light should flash with incoming data and then reset into your program. You're now safe to remove it from the MicroB and reassemble the watch.