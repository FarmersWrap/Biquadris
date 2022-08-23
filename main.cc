#include <string>
#include <cstdlib>
#include "gameplay.h"

using namespace std;

int main(int argc, const char *argv[]) {
	int seed = 1; // default seed
	string file1 = "biquadris_sequence1.txt"; // default sequence file 1
	string file2 = "biquadris_sequence2.txt"; // default sequence file 2
	int startLevel = 0; // default level
	int hiScore = 0; // default highest score
	bool textOnly = false; // default is to show both text and graphics

	for (int i = 1; i < argc; ++i) {
		string s = argv[i];
		if (s == "-text") {
			textOnly = true;
		} else if (s == "-seed") {
		    seed = stoi(argv[i + 1]);
		} else if (s == "-scriptfile1") {
			file1 = argv[i + 1];
		} else if (s == "-scriptfile2") {
			file2 = argv[i + 1];
		} else if (s == "-startlevel") {
			startLevel = stoi(argv[i + 1]);
		}
	}
	bool isRandom = startLevel == 0 ? false : true;
	bool isBasicGame = true;
	srand(seed);
	GamePlay gp{textOnly, seed, file1, file2, startLevel, hiScore, isRandom, isBasicGame};
	gp.start();
    return 0;
}

