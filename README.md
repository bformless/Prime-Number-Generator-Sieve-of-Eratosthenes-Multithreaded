# Sieve Of Eratosthenes Multithreaded
Very fast 64 bit (real! not simulated!) Multithreaded Sieve of Eratosthenes Prime Number Generator, written in C++. <br>
(You can calculate Primes up to 18.446.744.069.414.584.318, if you have enough RAM installed -> ~ 16 Exbibytes)

Source code with a compiled Windows x64 EXE included.

Have fun!

!;)

<br>
<hr>
<br>

Todo:
1. Code cleanup
2. Reducing memory footprint
3. Different code for multithreaded Sieve
<br>
The multithreaded implementation was done quickly and fits very good.
But i think there's much more performance possible, because with a small number range (e.g. < 50,000,000) the multithreaded solution is slower in average due to the threads overhead. I have to consider an other formula for multi threads. Maybe a range for every thread might be a solution.
<br>
<hr>
<br>

Processor: Intel i9-9940X - 3.3 Ghz - Turbo-Mode: off - 128 GB RAM (2400 Mhz Quadchannel)

Multithreaded (14 Threads) - 10 billion numbers searched for Primes in about 13 seconds

![Console](https://github.com/bformless/Prime-Number-Generator-Win64/blob/main/Picture_2021-11-16.jpg)

<br>
<hr>
<br>

Singlethreaded (1 Thread) - 10 billion numbers searched for Primes in about 67 seconds

![Console](https://github.com/bformless/Prime-Number-Generator-Win64/blob/main/Picture_2021-11-16_ST.jpg)

<br>
<hr>
<br>

Dave's Garage Speed Contest (Drag Race):
<br>
https://www.youtube.com/watch?v=yYcHWGxtRQo
<br>
<br>
Benchmarks on:
<br>
Intel 9940X (standard BIOS settings), 128 GB RAM
<br>
<h3>Dave's optimized Algorithm:</h3>
<h4>Single Thread, Windows 10 Pro, Visual Studio 2019, LLVM + MSVC compile:</h4>
Passes: 7145, Time: 5.000022, Avg: 0.000700, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

davepl_pol;7145;5.000022;1;algorithm=base,faithful=yes,bits=1
<br>
<h4>Single Thread, VM Linux Debian64 Bullseye, clang-11_compile:</h4>
Passes: 4902, Time: 5.000871, Avg: 0.001020, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

davepl_pol;4902;5.000871;1;algorithm=base,faithful=yes,bits=1
<br>
<h4>Single Thread, VM Linux Debian64 Bullseye, g++_compile:</h4>
Passes: 7550, Time: 5.000559, Avg: 0.000662, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

davepl_pol;7550;5.000559;1;algorithm=base,faithful=yes,bits=1
<br>
<br>
<h3>My current Algorithm<h3>
<h4>Single Thread, Windows 10 Pro, Visual Studio 2019, LLVM + MSVC compile:</h4>
Passes: 11302, Time: 5.000130, Avg: 0.000442, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

mraebiger_cpp_single_uint64_8bit;11302;5.000130;1;algorithm=base,faithful=yes,bits=8
<br>
<h4>Single Thread, VM Linux Debian64 Bullseye, clang-11_compile:</h4>
Passes: 8520, Time: 5.000188, Avg: 0.000587, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

mraebiger_cpp_single_uint64_8bit;8520;5.000188;1;algorithm=base,faithful=yes,bits=8
<br>
<h4>Single Thread, VM Linux Debian64 Bullseye, g++_compile:</h4>
Passes: 8230, Time: 5.000580, Avg: 0.000608, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

mraebiger_cpp_single_uint64_8bit;8230;5.000580;1;algorithm=base,faithful=yes,bits=8
