# Sieve Of Eratosthenes Multithreaded
Very fast 64 bit Multithreaded Sieve of Eratosthenes Prime Number Generator, written in C++. <br>
(You can calculate Primes up to 18.446.744.069.414.584.318, if you have enough RAM installed -> ~ 16 Exbibytes)

Source code with a compiled Windows x64 EXE included.

Have fun!

!;)

<br>
<hr>
<br>

Todo:
1. Code cleanup

2. Use of AVX2 registers (Agner Fog's Vector Class Library) - 
   I have tested it, but it is slightly slower.

3. A boolean is 8 bit in memory (standard array).
   A 1 bit array to save memory. (vector boolean or boost bitset)
   
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
Benchmark on:
<br>
Intel 9940X, 128 GB RAM, Windows 10 Professional
<br>

Dave's optimized Algorithm (Single Thread):
<br>
Passes: 7145, Time: 5.000022, Avg: 0.000700, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

davepl_pol;7145;5.000022;1;algorithm=base,faithful=yes,bits=1
<br>
<br>
My current Algorithm (12/07/2021) (Single Thread):
<br>
Passes: 11302, Time: 5.000130, Avg: 0.000442, Limit: 1000000, Count1: 78498, Count2: 78498, Valid: 1

mraebiger_cpp_single_uint64_8bit;11302;5.000130;1;algorithm=base,faithful=yes,bits=8
