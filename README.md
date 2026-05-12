# Title
A minimal 32-bit x86 bare-metal unikernel operating system with basic hardware driver support

# The Philosophy
Operating Systems are arguably one of, if not the most instrumental pieces of software in the current era of computing. As of April 2026, Windows holds the [majority of the market share](https://gs.statcounter.com/os-market-share/desktop/worldwide/) in desktop OS. However, as a side note, it is interesting to note that a majority of Microsoft's profits are derived from it's [cloud services](https://www.investopedia.com/how-microsoft-makes-money-4798809) which run some form of Linux as their OS.

Frankly speaking, the current scenario in the field of Operating Systems leaves much to be desired. Even more so when many current OSes, previously considered to be highly optimized and performance critical systems, now come prevalent with a bundle of AI features as a, what I consider to be, an "additional layer of abstraction on OS functionalities".

This project attempts to try a different approach which is, essentially, a trade-off between performance and computing-proficiency, if that is considered to be a trade-off in the first place. We attempt to address issues like [hardware degradation related to Operating Systems](https://www.sciencedirect.com/science/article/abs/pii/S0164121206001750) and try a new approach in low-end computing. For this, we have decided to try a [Unikernel](https://en.wikipedia.org/wiki/Unikernel) approach. RADos is , to us, a small but still significant step in that direction.

# About RADos
The following are some features of RADos, supported as of now:
- 32-bit x86 kernel
- Bare-metal environment
- Monolithic architecture
- Single address space
- GRUB2/Multiboot-compliant
- VGA text-mode interface
- Programmable Interrupt Timers
- The Global Descriptor Table
- Minimal Keyboard drivers
- Dynamic memory allocation through `kmalloc`
- Barebones terminal-like set of minimal commands
# Contributors

[Rajdeep Gogoi](https://github.com/rajdeepgogoi), 
[Abhimanyu Saikia](https://github.com/escursio675), 
[Debraj Roy](https://github.com/roydebraj2003)

# References
- [OSDev Wiki](https://wiki.osdev.org/)
- [x86 Assembly with NASM by OliveStem](https://www.youtube.com/playlist?list=PL2EF13wm-hWCoj6tUBGUmrkJmH1972dBB)
- [Preliminary Work](https://github.com/escursio675/osdev-by-OliveStem)

