#!/bin/sh
# copy needed files to floppy image.

sudo  mount -o loop boot.img /mnt/

sudo  cp mymain.bin /mnt/loader.bin
#sudo  cp -v ~/git/simple_scheme/x86_16/mymain.bin /mnt/loader.bin

#sudo  cp /tmp/simple_scheme/x86_16/mymain.bin /mnt/loader.bin
sudo  ls -l /mnt 
sudo  umount /mnt 

