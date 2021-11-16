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
3. A boolean is 8 bit in memory, because of a standard array
   maybe using vector<bool> or write own packed array -> 1 bit per boolean
   (but this slows down the algo a little bit.)

<br>
<hr>
<br>

Processor: Intel i9-9940X - 3.3 Ghz - Turbo-Mode: off - 128 GB RAM (2400 Mhz Quadchannel)

10 billion numbers in about 15 seconds

![Console](https://github.com/bformless/Prime-Number-Generator-Win64/blob/main/Sieve_of_E.jpg)



