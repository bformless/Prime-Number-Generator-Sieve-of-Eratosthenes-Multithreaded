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

2. Use of AVX2 registers
   I have tested it, but it is slightly slower.

3. A boolean is 8 bit in memory (standard array).
   Maybe using a 1 bit array. (vector boolean or boost bitset)
   
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

