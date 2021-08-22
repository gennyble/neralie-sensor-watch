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
Assuming your watch is plugged in to the computer and in the UF2 bootloader mode...

be sure you're still in the `make` directory. Run `make install`, which might error with `No such file or directory: '/media'`. If that's the case, run `sudo ./upload.sh`. I recommend you look at the script, as you're running it with `sudo`. It expects `/mnt/watch` to exist. If all went well your watch's red light should flash with incoming data and then reset into your program.