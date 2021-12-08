// Author: 'Michael Raebiger' aka 'bformless'
// Location: Munich, Germany
// The 'prime_Sieve' function is (c) 2019
// taken from my 64 bit 'Multithreaded Sieve of Eratosthenes' program
// ------------------------------------------------------------------------------------------------------------------------------------------------------------ 
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// ------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// This Software was rewritten for "Dave's Garage Speed Contest"
// with some of his Drag Race code (c) by Dave Plummer
// Date: 12/08/2021
//------------------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <cmath>
#include <map>
#include <chrono>

typedef unsigned long long ULL;			// 64 bit unsigned integer - uint64_t
using namespace std;
using std::chrono::steady_clock;
using std::chrono::duration;
using std::chrono::microseconds;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

bool validateResults(ULL const sieveSize, ULL const validatedcount)
{
	static const std::map<ULL, ULL> resultsDictionary =
	{
			{            10LL, 4           },
			{            11LL, 5           },					// Historical data for validating our results - the number of primes
			{           100LL, 25          },					// to be found under some limit, such as 168 primes under 1000
			{           101LL, 26          },					// added for optimal checks of an array!
			{          1000LL, 168         },
			{          1009LL, 169         },
			{         10000LL, 1229        },
			{         10007LL, 1230        },
			{        100000LL, 9592        },
			{        100003LL, 9593        },
			{       1000000LL, 78498       },
			{       1000003LL, 78499       },
			{      10000000LL, 664579      },
			{      10000019LL, 664580      },
			{     100000000LL, 5761455     },
			{     100000007LL, 5761456     },
			{     982451653LL, 50000000    },
			{    1000000000LL, 50847534    },
			{    1000000007LL, 50847535    },
			{   10000000000LL, 455052511   },					// added for 64 bit Sieves comparison
			{   10000000019LL, 455052512   },
			{  100000000000LL, 4118054813  },
			{  100000000003LL, 4118054814  },
			{ 1000000000000LL, 37607912018 },
	};

	auto result = resultsDictionary.find(sieveSize);
	
	if (resultsDictionary.end() == result)
	{
		return false;
	}
	else {
		return result->second == (validatedcount);
	}
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

auto countPrimes(ULL sieveSize, bool *primeSieveArray) -> ULL {

	ULL counter = 1;

	for (ULL i = 3; i <= sieveSize; i += 2)
	{
			if (!primeSieveArray[i])
			{
				counter++;
			}
	}

	return counter;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void printResults(bool showResults, double elapsedTime, ULL passes, ULL sieveSize, bool *primeSieveArray)
{
	if (showResults)
	{
		printf("2, ");
	}
	
	ULL count = (sieveSize >= 2);                             // Starting count (2 is prime)

	for (ULL num = 3; num <= sieveSize; num += 2)
	{
		if (!primeSieveArray[num])
		{
			if (showResults)
			{
				printf("%llu, ", num);
			}
			count++;
		}
	}

	if (showResults)
	{
		printf("\n");
	}

	printf("Passes: %llu, Time: %lf, Avg: %lf, Limit: %llu, Count1: %llu, Count2: %llu, Valid: %d\n",
		passes,
		elapsedTime,
		elapsedTime / passes,
		sieveSize,
		count,
		countPrimes(sieveSize, primeSieveArray),
		validateResults(sieveSize, (countPrimes(sieveSize, primeSieveArray))));

	// Following 2 lines added by rbergen to conform to drag race output format
	printf("\n");
	printf("mraebiger_cpp_single_uint64_8bit;%llu;%f;1;algorithm=base,faithful=yes,bits=8\n", passes, elapsedTime);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Standard algorithm for single thread
// taken from my multithreaded Sieve of Eratosthenes program

void prime_Sieve(ULL const sieveSize, bool *primeSieveArray)
{
	ULL x = 3LL;
	ULL y = 2LL;
	ULL step = y;
	ULL sqrtSieveSize = ULL(sqrt(sieveSize));
	
	while (x <= sqrtSieveSize)

	{
		y = x;

		while ( (x * y) <= sieveSize)

		{
			primeSieveArray[(x * y)] = 1;
			(y += step);
		}

		(x += step);

		ULL test = x;

		while (test <= sqrtSieveSize) {

			if (!(primeSieveArray[(test)]))
			{
				break;
			}
			x += step;
			test = x;
		}

		//for (ULL test = x; test <= sqrtSieveSize; (test += step))
		//{
		//	if (primeSieveArray[(test)]) {
		//		(x += step);
		//	}
		//	else {
		//		break;
		//	}
		//}
	}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

int main()
{
	// disable synchronizing with console
	ios_base::sync_with_stdio(false);

	// initializing variables
	ULL sieveSize = 1000000LL;
	double elapsedTime;
	ULL passes = 0;
	duration<double, std::milli> milliseconds_timer = microseconds(0);
	duration<double, std::milli> milliseconds_sum = microseconds(0);
	auto start = std::chrono::steady_clock::time_point();
	auto end = std::chrono::steady_clock::time_point();

	// initializing standard array - a boolean is 8 bit in memory
	static bool* primeSieveArray = new bool[(sieveSize+1)]{ 0 };

	// start of benchmark loop
	while (milliseconds_sum.count() < 5000) {

			// clearing the array
			for (ULL index = 0; index <= sieveSize; ++index)

			{
				primeSieveArray[(index)] = 0;
			}

			// start timing the algorithm
			start = std::chrono::steady_clock::now();

				prime_Sieve(sieveSize, primeSieveArray);

			// stop timing the algorithm
			end = std::chrono::steady_clock::now();

		++passes;

		// adding up benchmark time
		milliseconds_timer = (end - start);							
		milliseconds_sum += (milliseconds_timer);
	}// end of benchmark loop
	
	elapsedTime = (milliseconds_sum.count() / 1000);
	ios_base::sync_with_stdio(true);
	printResults(false, elapsedTime, passes, sieveSize, primeSieveArray);
	delete[] primeSieveArray;
}
