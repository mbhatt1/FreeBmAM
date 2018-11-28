# FreeBmAM ~ Free B-sd m-emory A-cquisition M-odule
Memory acquisition tool for FreeBSD (alpha). Took me a couple of months so please be nice :) Just creates a DD now. 

## Getting Started
Make sure you have the sources in the operating system available. Otherwise use svnlite to checkout. 

After, to compile the kernel module, go to the folder and make. 
```
$ awk -f <location of vnode.awk> <location of vnode.src> -h
$ make
$ cp FreeBmAM.ko /boot/kernel
$ kldload FreeBmAM.ko

#To Unload:
$ kldunload FreeBmAM.ko
```

This is an alpha software. 

### Prerequisites
Kernel source tree

Main Source Files:

```
module.c (Most of the logic)
subr_kernio.c (File IO from the kernel). 

```
Suggestions are welcome under Issues

## Contributing

Please create an issue before a PR.

## License

This project is licensed under the GNU License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* LiME
* Linus Trovalds for inventing git
* Joe Sylve, Irfan Ahmed, Vassil Roussev
* Author of subr_kernio.c and kernio.h for providing the base code.

# Please post any issues.
TEST
