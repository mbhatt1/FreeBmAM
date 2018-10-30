# FreeBmAM
Memory acquisition tool for FreeBSD (alpha).

## Getting Started
Make sure you have the sources in the operating system available. Otherwise use svnlite to checkout. 

After, to compile the kernel module, go to the folder and make. 
```
$make
$cp FreeBmAM.ko /boot/kernel
$kldload FreeBmAM.ko

#To Unload:
$kldunload FreeBmAM.ko
```

This is an alpha software. Please expect bad bad bugs. Let me know in the issues of this repo.

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

This project is licensed under the GNU License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* LiME
* Joe Sylve, Irfan Ahmed, Vassil Roussev
* Author of subr_kernio.c and kernio.h for providing the base code.
