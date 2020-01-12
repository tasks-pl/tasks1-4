#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <boost/lexical_cast.hpp>

using namespace std;

int main (int argc, char** argv) {
	ifstream files[5];
	string temp_string;
	float sixteenx5[16][5];
	for (int i=0; i < 5; i++) {
		files[i].open(argv[i+1]);
		for (int j=0; j < 16; j++) {
			getline(files[i], temp_string);
			sixteenx5[j][i] = boost::lexical_cast<float> (temp_string);
		}
		files[i].close();
	}
	float sixteen[16];
	for (int i=0; i<16; i++) {
		sixteen[i] = accumulate(sixteenx5[i], sixteenx5[i]+5, 0., std::plus<float>());
	}
	cout << 1 + distance(sixteen, max_element(sixteen, sixteen + 16)) << endl;
	return 0;
}
