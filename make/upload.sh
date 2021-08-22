#!/bin/fish

# A little script that takes a device path. It'll upload the firmware, sync
# to clear the buffer and actually write to the watch, and then unmount.
# You'll likely need sudo for this script

set dev $argv[1]

if test -z $argv[1]
	echo "Which device is the watch?"
	exit
end

mount $dev /mnt/watch
cp build/watch.uf2 /mnt/watch/
sync
umount /mnt/watch
