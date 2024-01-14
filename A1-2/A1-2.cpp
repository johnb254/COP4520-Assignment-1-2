
#include <iostream>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <vector>
#include <thread>
#include <cmath>
#include <fstream>
#include <mutex>

using namespace std;
mutex mtx;

/**
 * Given a number, returns whether it is prime or not
 * @param num Number to check
 * @return bool representing whether the given number is prime
 */
static bool isPrime(int num)
{
	// base cases
	if (num <= 1) return false;
	if (num == 2) return true;
	if (num % 2 == 0) return false;

	// checks all odd numbers up to the square root of the number
	for (int i = 3; i <= sqrt(num); i += 2)
	{
		// if the number is divisible by any number up to its square root, it is not prime
		if (num % i == 0)
		{
			return false;
		}
	}
	// if the number is not divisible by any number up to its square root, it is prime
	return true;
}

/** Given a range, finds all the prime numbers in that range and stores them in the given vector
 * @param start Start of the range
 * @param end Inclusive end of the range
 * @param primes Vector to store the prime numbers in
 */
static void findPrimesInRange(int start, int end, vector<int64_t>& primes)
{
	// there are no primes less than 2, so start at 2
	if (start < 2) start = 2;
	if (start == 2) {
		mtx.lock();
		primes.push_back(2);
		mtx.unlock();
	}
	// if the start is even, increment it by 1
	if (start % 2 == 0) start++;

	for (int num = start; num <= end; num += 2)
	{
		if (isPrime(num))
		{
			mtx.lock();
			primes.push_back(num);
			mtx.unlock();
		}
	}
}

int main()
{
	const int START = 1;
	const int END = (int)pow(10, 8);
	const int NUM_THREADS = 8;

	vector<int64_t> primes;
	vector<thread> threads;

	const int RANGE = END - START + 1;
	const int CHUNK_SIZE = RANGE / NUM_THREADS;

	int64_t total;

	ofstream output;

	// starts timer
	auto start = chrono::high_resolution_clock::now();

	// creates threads to find primes in each chunk of the range
	for (int i = 0; i < NUM_THREADS; i++)
	{
		int threadStart = START + i * CHUNK_SIZE;
		int threadEnd = (i == NUM_THREADS - 1) ? END : threadStart + CHUNK_SIZE - 1;
		threads.emplace_back(findPrimesInRange, threadStart, threadEnd, ref(primes));
	}

	// waits for all threads to finish
	for (auto &thread : threads)
	{
		thread.join();
	}

	// end timer and calculate duration
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

	// sort in ascending order and calculate total
	sort(primes.begin(), primes.end());
	total = accumulate(primes.begin(), primes.end(), (int64_t) 0);

	// delete file if it exists
	if (remove("primes.txt"))
	{
		cout << "Deleted file" << endl;
	}

	// write results to file
	output.open("primes.txt");
	cout << "File opened" << endl;

	output << "Program executed in " << duration << "ms." << endl;
	output << "Primes found in range " << START << " to " << END << ": " << primes.size() << endl;
	output << "Sum of primes: " << total << endl;
	output << "Top 10 primes: ";
	for (int i = primes.size() - 10; i < primes.size(); i++)
	{
		output << primes[i] << " ";
	}

	// print results of file operations to console
	output << endl;
	cout << "File written" << endl;

	output.close();
	cout << "File closed" << endl;

	return 0;
}
