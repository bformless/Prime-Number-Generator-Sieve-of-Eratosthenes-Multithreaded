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

	ULL reader;
	bool inPut = true;
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
auto askThreads(const ULL &numbers) -> ULL{

	ULL numberOfThreads = 1;
	bool inPut = true;
	do {
		unsigned int reader;
		ULL numThreadsMax = thread::hardware_concurrency();
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
void DisplayElapsedTime(const double &elapsedTime) {

	cout << "\nIt took " << (elapsedTime / double(CLOCKS_PER_SEC)) << " seconds for the Sieve of Eratosthenes Algorithm" << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
auto PrimeCounter(const ULL &UPPER_BOUND,bool* primesList) -> ULL {
	
	ULL counter = 0;

	if (UPPER_BOUND < 2) {}

	else if (UPPER_BOUND < 3) {
		counter = 1;
	}
	else {
		counter = 1;
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

	ULL primesCount = count;
	cout << "\nPrime numbers found: " << primesCount << endl;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void LastPrime(ULL &arraySize,bool* primes) {

	cout << "\nLast Prime number: ";

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
void PrintIt(ULL &UPPER_BOUND,bool* primes) {

	ULL counter = 1;
	char reader;
	bool inPut = true;

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

	cout << "\n\nPress <ENTER> to end program.\a" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
}
/*----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static void Sieve(ULL &x,ULL &y,const ULL &UPPER_BOUND,const ULL &sqrtUpperBound, bool* primes) {

	for (ULL i = x; i <= (sqrtUpperBound); i += y) {
		for (ULL j = i; (i * j) <= UPPER_BOUND; j += 2) {
			primes[(i * j)] = 1;
		}
	}
}
----------------------------------------------------------------------------*/
static void Sieve2(ULL x,ULL y,const ULL &UPPER_BOUND,const ULL &sqrtUpperBound, bool* primes)
{
	static ULL step = y;

	while (x <= sqrtUpperBound)
	{	y = x;
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
void FindPrimesWithThreads(const ULL &numThreads,const ULL &userInput,const ULL &sqrtUserInput,bool* primes) {

	vector<thread> threadVect;
	ULL startNum = 1;

	for (ULL x = 0; x < numThreads; x++) {
		threadVect.emplace_back(Sieve2, (startNum + 2), (numThreads * 2), userInput, sqrtUserInput, primes);
		startNum += 2;
	}
	for (auto& t : threadVect) {
		t.join();
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
int main() {

	Info();
	double start, end, elapsedTime;

	ULL userInput = UserInput();
	ULL arraySize = (userInput + 1);
	ULL sqrtUserInput = (ULL)sqrt(userInput);

	cout << "\nBuilding array... ";
	static bool* primes = new bool[arraySize] { false };
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

