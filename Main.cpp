#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <time.h>
#include <cmath>
#include <vector>
#include <thread>
typedef unsigned long long ULL;
using namespace std;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void Info() {
	ios_base::sync_with_stdio(false);
	cout << "=================================================\n" \
		"||     SIEVE OF ERATOSTHENES (x64_Windows)     ||\n" \
		"||    Multithreaded Prime Numbers Algorithm    ||\n" \
		"=================================================\n" \
		"||     written by Michael Raebiger (c)2019     ||\n" \
		"=================================================\n" \
		"=================================================\n" \
		"||        Warning! Use at your own risk!       ||\n" \
		"||                                             ||\n" \
		"||     1 billion numbers to search require     ||\n" \
		"||       1 Gigabyte of free memory (RAM)!      ||\n" \
		"=================================================\n" << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

auto UserInput() -> ULL {
	ios_base::sync_with_stdio(false);
	static ULL reader;
	static bool inPut = true;
	do {
		cout << "How many numbers do you want to check for Primes?\n";
		cout << "(2 to 254.999.999.998)\n\n" \
			"-> \a";

		if (cin >> reader) {

			// input worked // possible max. 18.446.744.073.709.551.614
			if (reader < 2 || reader > 2549999999998Ui64) {
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

auto askThreads(const ULL &numbers) -> ULL {

	ios_base::sync_with_stdio(false);

	static ULL numberOfThreads = 1;
	static bool inPut = true;
	do {
		unsigned int reader;
		static ULL numThreadsMax = thread::hardware_concurrency();
		if (numThreadsMax == 0) {
			numThreadsMax = 1;
		}

		if (numbers < 500000)
		{
			numThreadsMax = (numThreadsMax / numThreadsMax);
		}

		cout << "How many Threads do you want to use?\n";
		cout << "(1 to " << numThreadsMax << ") " \
			"-> \a";

		if (cin >> reader) {

			// input worked
			if (reader < 1 || reader > numThreadsMax) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				inPut = true;
			}
			else {
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

void DisplayElapsedTime(const double& elapsedTime) {
	ios_base::sync_with_stdio(false);

	cout << "\nIt took " << (elapsedTime / double(CLOCKS_PER_SEC)) << " seconds for the Sieve of Eratosthenes Algorithm" << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

auto __forceinline PrimeCounter(const ULL &UPPER_BOUND, bool *primesList) -> ULL {
	ios_base::sync_with_stdio(false);
	static ULL counter = 0;

	if (UPPER_BOUND < 2) {}

	else if (UPPER_BOUND < 3) {
		counter = 1;
	}
	else {
		counter = 1;

		#pragma omp parallel for
		for (ULL i = 3; i <= UPPER_BOUND; i += 2) {
			if (!primesList[i]) {
				counter++;
			}
		}
	}
	return counter;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void DisplayNumberOfPrimes(ULL &count) {
	ios_base::sync_with_stdio(false);

	static ULL primesCount = count;
	cout << "\nPrime numbers found: " << primesCount << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void __forceinline LastPrime(ULL &arraySize, bool *primes) {

	ios_base::sync_with_stdio(false);
	cout << "\nLast Prime number: ";

	#pragma omp parallel for
	for (ULL i = (arraySize - 1); i >= 2; i -= 2) {

		if ((i - 1) < 2 && i >= 0) {
			cout << "2" << endl;
			break;
		}
		if (i % 2 == 0) {
			--i;
		}
		if (!primes[i]) {
			cout << i << endl;
			break;
		}
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void __forceinline PrintIt(ULL& UPPER_BOUND, bool *primes) {
	ios_base::sync_with_stdio(false);
	static ULL counter = 1;
	static char reader;
	static bool inPut = true;

	do {
		cout << "\nDo you want to print all Prime numbers? (y/n)\n" \
			"-> \a";
		if (cin >> reader) {
			// input worked
			switch (reader) {
			case 'y':
				if (UPPER_BOUND < 3) {
					cout << "\n2\n" << endl;
				}
				else {
					cout << "\n\t2";

					#pragma omp parallel for
					for (ULL i = 3; i <= UPPER_BOUND; i += 2)
					{
						if (!primes[i]) {
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
void wait() {
	ios_base::sync_with_stdio(false);

	cout << "\n\nPress <ENTER> to end program.\a" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void __forceinline Sieve(ULL x,ULL y,const ULL &UPPER_BOUND,const ULL &sqrtUpperBound, bool* primes) {

	#pragma omp parallel for
	for (ULL i = x; i <= (sqrtUpperBound); i += y) {
		#pragma omp parallel for
		for (ULL test = i; test <= sqrtUpperBound; test += y)
		{
			if (primes[(test * test)]) {
				i += y;
			}
			else {
				break;
			}
		}

		#pragma omp parallel for
		for (ULL j = i; (i * j) <= UPPER_BOUND; j += 2) {
			primes[(i * j)] = 1;
		}
	}
}
//----------------------------------------------------------------------------

static void __forceinline Sieve2(ULL x, ULL y, const ULL &UPPER_BOUND, const ULL &sqrtUpperBound, bool *primes)
{

	static const ULL step = y;

	while (x <= sqrtUpperBound)
	{
		
                #pragma omp parallel for
		for (ULL test = x; test <= sqrtUpperBound; test += step)
		{
			if (primes[(test * test)]) {
				x += step;
			}
			else {
				break;
			}
		}
		y = x;

		while ((x * y) <= UPPER_BOUND)
		{
			primes[(x * y)] = 1;
			y += 2;
		}
		x += step;
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

void __forceinline FindPrimesWithThreads(const ULL &numThreads, const ULL &userInput, const ULL &sqrtUserInput, bool* primes) {
	
	ios_base::sync_with_stdio(false);
	
	static vector<thread> threadVect;
	static ULL startNum = 1;
	#pragma omp parallel for
	for (ULL x = 0; x < numThreads; x++) {
		threadVect.emplace_back(Sieve2, (startNum + 2), (numThreads * 2), userInput, sqrtUserInput, primes);
		startNum += 2;
	}
	#pragma omp parallel for
	for (auto& t : threadVect) {
		t.join();
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

int main() {
	ios_base::sync_with_stdio(false);
	Info();
	double start, end, elapsedTime;

	ULL userInput = UserInput();
	ULL arraySize = (userInput + 1);
	ULL sqrtUserInput = (ULL)sqrt(userInput);

	cout << "\nBuilding array... ";
	__declspec (align (64)) static bool *primes = new bool[arraySize] { false };
	cout << "Ready.\n" << endl;

	ULL numOfThreads = askThreads(userInput);

	start = clock();
	FindPrimesWithThreads(numOfThreads, userInput, sqrtUserInput, primes);
	end = clock();

	ULL count = PrimeCounter(userInput, primes);

	DisplayNumberOfPrimes(count);

	LastPrime(arraySize, primes);

	elapsedTime = (end - start);
	DisplayElapsedTime(elapsedTime);

	PrintIt(userInput, primes);

	delete[] primes;
	wait();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
