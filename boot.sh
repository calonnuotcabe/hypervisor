#!/bin/sh

qemu-system-i386 \
  -kernel linux-2.6.32/arch/x86/boot/bzImage \
  -initrd initramfs.cpio.gz \
  -append "console=ttyS0" \
  -nographic \
  -s -S
  -virtfs local,path=/home/huhu/hypervisor,mount_tag=hostshare,security_model=none,id=hostshare
