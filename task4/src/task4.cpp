#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <boost/lexical_cast.hpp>

using namespace std;

vector<int> max_indices(vector<int> &in, int max) {
	vector<int> out;
	for (size_t i = 0; i < in.size(); i++)
	{
		if (in[i] == max)
		{
			out.push_back(i);
		}
	}
	return out;
}

int main (int argc, char** argv) {
	ifstream file4(argv[1]);
	vector<array<int,2>> intervals;
	string temp_string;
	int enter, exit, hours, minutes;
	while ( getline(file4, temp_string, ' ') ) {
		hours = boost::lexical_cast<int> (temp_string.substr(0, temp_string.find(':')));
		minutes = boost::lexical_cast<int> (temp_string.substr(temp_string.find(':') + 1));
		enter = (hours-8)*60 + minutes;
		getline(file4, temp_string);
		hours = boost::lexical_cast<int> (temp_string.substr(0, temp_string.find(':')));
		minutes = boost::lexical_cast<int> (temp_string.substr(temp_string.find(':') + 1));
		exit = (hours-8)*60 + minutes;
		intervals.push_back({enter,exit});
	}
	file4.close();

	vector<int> cust_at_min;
	int cust;
	for (int i = 0; i < 720; i++) {
		cust=0;
		for (size_t j = 0; j < intervals.size(); j++) {
			if (i >= intervals[j][0] && intervals[j][1] > i) {
				cust++;
			}
		}
		cust_at_min.push_back(cust);
	}
	int max =  *max_element(cust_at_min.begin(), cust_at_min.end());
	vector<int> maxranges = max_indices(cust_at_min, max);
	int start_max_range = 0;
	size_t it;
	for (it = 1; it < maxranges.size(); it++) {
		if (maxranges[it]-maxranges[it-1]==1){
			continue;
		}
		else {
			cout << (maxranges[start_max_range]+480)/60 << ':' << setw(2) << setfill('0') << (maxranges[start_max_range]+480)%60 << ' ' << (maxranges[it-1]+480+1)/60 << ':' << setw(2) << setfill('0') << (maxranges[it-1]+480 +1)%60 << endl;
			start_max_range = it;
		}
	}
	cout << (maxranges[start_max_range]+480)/60 << ':' << setw(2) << setfill('0') << (maxranges[start_max_range]+480)%60 << ' ' << (maxranges[it-1]+480+1)/60 << ':' << setw(2) << setfill('0') << (maxranges[it-1]+480 +1)%60 << endl;
	return 0;
}
