# Running the RADos ISO image
The following steps can be followed on an Ubuntu to run make and run the ISO image present in the repository:

1. We must have the following packages installed
	- build-essential
	- gcc-multilib
	- nasm
	- qemu-system-x86
	- grub-pc-bin
	- xorriso
2. The following are executed in order:
	- `make`
	- `qemu-system-i386 -cdrom kernel.iso` OR simply `qemu-system-i386 kernel.iso` 

Note: Any warnings during _make_ may be ignored.


# Setting up a Cross Compiler
The use of `gcc` from the host Operating System along with some of its related flags may lead to multiple inconsistencies like, but not limited to, conflict with 32-bit and 64-bit division, string mismatches etc. To solve this we use a Cross-Compiler(CC) that will specifically target the i386 system, i.e., our target system.

The following are the steps used to install a cross compiler in Ubuntu 22.04

1. The following dependencies must be installed
	- bison
	- flex
	- libgmp3-dev
	- ibmpc-dev
	- libmpfr-dev
	- texinfo
2. The following paths are to be exported:
```
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH" 
```

Here, `PREFIX` is the location where we store our CC. It is highly recommend to NOT set the prefix to any `/usr` directory. `TARGET` is the target architecture.

3. After the paths are successfully set up, we download `binutils` and `gcc`:
	- For `gcc`, `git clone https://gcc.gnu.org/git/gcc.git`
	- For `binutils`, `git clone git://sourceware.org/git/binutils-gdb.git`

4. We then create a directory _build-binutils_ and run the following inside that dir:
	- `../binutils-gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror`
	- `make`
	- `make install`
5. For `gcc`, we make a directory called _build-gcc_ and run the following inside the directory:
	- `../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers`
	- `make all-gcc`
	- `make all-target-libgcc`
	- `make install-gcc`
	- `make install-target-libgcc`
6. `gcc` is then available in `~/opt/cross/bin/i686-elf-gcc`. We can verify the installation by running `--version` at this path.

# Development System
The following tools are their versions were used in the development of this project:

- Host OS: Ubuntu 24.04 LTS (x86_64)
- gcc: 11.4.0
- i686-elf-gcc: 16.0.1 20260327 (experimental)
- NASM: 2.15.05
- qemu-system-x86_64: 6.2.0 (Debian 1:6.2+dfsg-2ubuntu6.30)
- make: 4.3
- GNU gdb: 12.1 (Ubuntu 12.1-0ubuntu1~22.04.2)
- GNU ld: 2.38 (GNU Binutils for Ubuntu)
- GRUB2/multiboot: 2.06-2ubuntu7.2
- grub-mkrescue: 2.06-2ubuntu7.2
- xorriso: 1.5.4
