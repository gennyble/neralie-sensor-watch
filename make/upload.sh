#!/bin/sh

# This script mounts the watch in a temporary location, copies the firmware
# to the watch, runs `sync` to be sure buffers are flushed, and the unmounts.

WATCHDEVICE=/dev/disk/by-label/WATCHBOOT

if [ ! -e "$WATCHDEVICE" ]; then
	echo "Cannot find watch device!"
	exit
fi

mkdir -p /tmp/neralie-sensor-watch-mount && \
mount $WATCHDEVICE /tmp/neralie-sensor-watch-mount && \
cp build/watch.uf2 /tmp/neralie-sensor-watch-mount && \
sync && \
umount /tmp/neralie-sensor-watch-mount
