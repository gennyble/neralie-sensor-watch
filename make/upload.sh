#!/bin/fish

# A little script that takes a device path. It'll upload the firmware, sync
# to clear the buffer and actually write to the watch, and then unmount.
# You'll likely need sudo for this script

set watchdevice "/dev/disk/by-label/WATCHBOOT"

if test ! -e $watchdevice
	echo "Cannot find watch device!"
	exit
end

mkdir -p /tmp/neralie-sensor-watch-mount && \
mount $watchdevice /tmp/neralie-sensor-watch-mount && \
cp build/watch.uf2 /tmp/neralie-sensor-watch-mount && \
sync && \
umount /tmp/neralie-sensor-watch-mount
