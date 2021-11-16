# Sieve Of Eratosthenes Multithreaded
Very fast Multithreaded Sieve of Eratosthenes Prime Number Generator, written in C++.

Source code with a compiled Windows x64 (AVX2) EXE included.

Have fun!

!;)

<br>
<hr>
<br>

Todo:
1. Code cleanup
2. Adding calculation in AVX2 registers (maybe integrate Agner Fog's Vector Class Library)
3. A boolean is 8 bit in memory (standard array). Vector with booleans could be used or writing an alternative array with 1 bit per boolean
   (but this could slow down the algo a little bit.)

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

