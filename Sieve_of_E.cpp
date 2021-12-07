// Author: 'Michael Raebiger' aka 'bformless'
// Location: Munich, Germany
// (c) 2019
// 
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
// Date: 07-31-2019
// changed on: 12-07-2021
// Todo: Code cleanup

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <thread>
typedef unsigned long long ULL;
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void wait() {

	cout << "\n\nPress <ENTER> to end program.\a" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void Info() {
	    cout << "=================================================\n" \
		    "||                                             ||\n" \
		    "||           'SIEVE OF ERATOSTHENES'           ||\n" \
		    "||                                             ||\n" \
		    "||                (x64_Windows)                ||\n" \
		    "||                                             ||\n" \
		    "||       Very fast (but not the fastest)       ||\n" \
		    "||                                             ||\n" \
		    "||   'Multithreaded Prime Numbers Algorithm'   ||\n" \
		    "||                                             ||\n" \
		    "=================================================\n" \
		    "|| written in C++  by Michael Raebiger (c)2019 ||\n" \
		    "=================================================\n" \
		    "                                                 \n" \
		    "*************************************************\n" \
		    "**                                             **\n" \
		    "**  ***  Warning!  Use at your own risk!  ***  **\n" \
		    "**                                             **\n" \
		    "**                                             **\n" \
		    "**   >+ 64 billion numbers to search require   **\n" \
		    "**    >+ 64 Gibibyte of free memory (RAM)!     **\n" \
		    "**                                             **\n" \
		    "**       Example: 1 billion = 1 Gibibyte       **\n" \
		    "**                                             **\n" \
		    "**                                             **\n" \
		    "**  ***  Warning!  Use at your own risk!  ***  **\n" \
		    "**                                             **\n" \
		    "*************************************************\n" \
		    "*************************************************\n" << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
auto UserInput() -> ULL {
	ULL reader;
	bool inPut = true;
	do {
		cout << "How many numbers do you want to check for Primes?\n";
		cout << "(2 to 18.446.744.069.414.584.318)\n\n" \
			"-> \a";

		if (cin >> reader) {

			// input worked
			// possible max. 18.446.744.073.709.551.616 = 2^64
			// restricted to 2^64 minus (2^32 + 2)
			// To handle such a big number you need at least 16 Exbibyte of RAM

			if (reader < 2 || reader > 18446744069414584318Ui64) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inPut = true;
			}
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inPut = false;
			}
		}
		else {
			// wrong input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (inPut);
	return reader;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
auto askThreads(ULL numbers) -> ULL {

	ULL numberOfThreads = 1;
	
	bool inPut = true;
	do {
		unsigned int reader;

		ULL numThreadsMax = (ULL) ceil(floor(numbers / 1572864LL)*2);

		if (numThreadsMax == 0 || numbers <= 1572864LL) {
			numThreadsMax = 1;
		}

		if (numThreadsMax >= thread::hardware_concurrency())
		{
			numThreadsMax = thread::hardware_concurrency();
		}

		cout << "How many Threads do you want to use?\n";
		cout << "(1 to " << numThreadsMax << ") " \
			"-> \a";

		if (cin >> reader) {

			// wrong input
			if (reader < 1 || reader > numThreadsMax) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inPut = true;
			}
			else { // input worked
				numberOfThreads = reader;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inPut = false;
			}
		}
		else {
			// wrong input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (inPut);
	return numberOfThreads;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void DisplayElapsedTime(double elapsedTime) {

	cout << "\nIt took " << (elapsedTime) << " seconds for the optimized Sieve of Eratosthenes Algorithm." << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
auto PrimeCounter(ULL sieveSize, bool *primeSieveArray) -> ULL {

	ULL counter = 0;

	if (sieveSize < 2) {
	}
	else if (sieveSize < 3) {
		counter = 1;
	}
	else {
		counter = 1;

		for (ULL i = 3; i <= sieveSize; i += 2) {
			if (!primeSieveArray[i]) {
				counter++;
			}
		}
	}
	return counter;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void DisplayNumberOfPrimes(ULL count) {

	ULL primesCount = count;
	cout << "found: " << primesCount << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void LastPrime(ULL sieveSize, bool *primeSieveArray) {

	cout << "\nThe last Prime number is ";

	#pragma omp parallel for
	for (ULL i = (sieveSize - 1); i >= 2; i -= 2) {

		if ((i - 1) < 2 && i >= 0) {
			cout << "2" << endl;
			break;
		}
		if (i % 2 == 0) {
			--i;
		}
		if (!primeSieveArray[i]) {
			cout << i << endl;
			break;
		}
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void PrintIt(ULL sieveSize, bool *primeSieveArray) {

	ULL counter = 1;
	char reader;
	bool inPut = true;

	do {
		cout << "\nDo you want to print all Prime numbers to the console? (y/n)\n" \
			"-> \a";
		if (cin >> reader) {
			// input worked
			switch (reader) {
			case 'y':
				if (sieveSize < 3) {
					cout << "\n2\n" << endl;
				}
				else {
					cout << "\n\t2";

					for (ULL i = 3; i <= sieveSize; i += 2)
					{
						if (!primeSieveArray[i]) {
							cout << "\t" << i;
							counter++;
							if (counter % 10 == 0) {
								cout << endl;
							}
						}
					}
					cout << endl;
				}
				inPut = false;
				break;

			case 'n':
				inPut = false;
				break;

			default:
				// wrong input
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else {
			// wrong input
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (inPut);
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void Sieve1(const ULL sieveSize, bool* primeSieveArray)
{	
	ULL sqrtSieveSize = ULL(sqrt(sieveSize));
	ULL x = 3LL;
	ULL y = 2LL;
	ULL step = y;
	
	while (x <= sqrtSieveSize)
	{
		y = x;

		while ((x * y) <= sieveSize)
		{

			primeSieveArray[(x * y)] = 1;

			(y += step);
		}

		(x += step);

		ULL test = x;

		while (test <= sqrtSieveSize) {
			if (!primeSieveArray[(test)])
			{
				break;
			}

			x += step;
			test = x;
		}
	}
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void Sieve2(ULL x, ULL y, const ULL sieveSize, bool *primeSieveArray)
{
	ULL sqrtSieveSize = (ULL)sqrt(sieveSize);
	ULL step = y;
	
	while (x <= sqrtSieveSize)
	{
		y = x;

		while ((x * y) <= sieveSize)
		{

			primeSieveArray[(x * y)] = 1;
			y += 2;

		}
		x += step;

		ULL test = x;

		while (test <= sqrtSieveSize) {
			if (!primeSieveArray[(test)])
			{
				break;
			}

			x += step;
			test = x;
		}
	}
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void FindPrimesWithThreads(ULL numThreads, ULL sieveSize, bool* primesSieveArray) {
	
	vector<thread> threadVect;
	//threadVect.reserve(numThreads);
	ULL startNum = 1;

	for (ULL x = 0; x < numThreads; ++x) {
		threadVect.emplace_back(Sieve2, (startNum + 2), (numThreads * 2), sieveSize, primesSieveArray);
		startNum += 2;
	}

	for (auto& t : threadVect) {
		t.join();
	}
	for (auto& t : threadVect) {
		t.~thread();
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
int main() {
	ios_base::sync_with_stdio(false);
	Info();

	double elapsedTime;
	ULL sieveSize = UserInput();
	ULL primeSieveArraySize = (sieveSize+1);
	ULL numOfThreads = 0;
	ULL count = 0;

	cout << "\nBuilding array... ";
	bool *primeSieveArray = new bool[primeSieveArraySize+1] { false };
	cout << "Ready.\n" << endl;

	numOfThreads = askThreads(sieveSize);

	if (numOfThreads < 2) {
		auto start = high_resolution_clock::now();
		Sieve1(sieveSize, primeSieveArray);
		auto end = high_resolution_clock::now();
		duration<double, std::milli> ms_double = end - start;
		elapsedTime = (ms_double.count() / 1000);
	}
	else {
		auto start = high_resolution_clock::now();
		FindPrimesWithThreads(numOfThreads, sieveSize, primeSieveArray);
		auto end = high_resolution_clock::now();
		duration<double, std::milli> ms_double = end - start;
		elapsedTime = (ms_double.count() / 1000);
	}

	DisplayElapsedTime(elapsedTime);

	cout << "\nCounting Primes... ";

	count = PrimeCounter(sieveSize, primeSieveArray);

	DisplayNumberOfPrimes(count);

	LastPrime(primeSieveArraySize, primeSieveArray);

	PrintIt(sieveSize, primeSieveArray);

	cout << "\nDeleting the array and cleaning up... ";

	delete[] primeSieveArray;

	cout << "Ready.";

	wait();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
