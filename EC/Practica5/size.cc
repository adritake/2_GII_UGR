// size.cc

#include <array>        // array
#include <chrono>       // high_resolution_clock
#include <iomanip>      // setw
#include <iostream>     // cout

using namespace std::chrono;

const unsigned LINE = 16;                // line size
const unsigned MAXSIZE = 1024;           // maximun cache size to test
const unsigned GAP = 12;                 // gap for cout columns
const unsigned REP = 10;                 // number of repetitions of every test
const unsigned STEPS = 32 * 1024 * 1024; // 32M steps

std::array<char, 1 << 24> bytes;         // 16MB

int main()
{
	std::cout << "#"
	          << std::setw(GAP - 1) << "size (B)"
	          << std::setw(GAP    ) << "time (ms)"
	          << std::endl;

	bytes.fill(0);

	for (unsigned size = MAXSIZE; size <= STEPS; size <<= 1)
	{
		std::array<duration<float, std::milli>, REP> score;

		for (auto &s: score)
		{
			auto start = high_resolution_clock::now();

			for (unsigned i = 0; i < STEPS; ++i)
				bytes[(i*64) & (bytes.size() - 1) & (size -1)] ^= 1;

			auto stop = high_resolution_clock::now();

			s = stop - start;
		}

		std::cout << std::setw(GAP) << size
		          << std::setw(GAP) << std::fixed << std::setprecision(1)
		          << std::setw(GAP) << std::min(score.begin(), score.end())->count()
		          << std::endl;
	}

	return bytes.front() + bytes.back();
}
