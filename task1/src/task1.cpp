#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <gsl/gsl_statistics_double.h>
#include <gsl/gsl_sort.h>
#include <boost/lexical_cast.hpp>

using namespace std;

int main (int argc, char** argv) {
	ifstream file1(argv[1]);
	vector <string> temp_vect;
	string temp_string;
	while ( getline(file1, temp_string) ) {
		temp_vect.push_back(temp_string);
	}
	file1.close();
	int size = temp_vect.size();
	double data[size];
	for (int i=0; i < size; i++) {
		data[i] = boost::lexical_cast<double> (temp_vect[i]);
	}
	cout.precision(2);
	cout << fixed;
	gsl_sort(data, 1, size);
	cout << gsl_stats_quantile_from_sorted_data(data, 1, size, 0.9) << endl;
	cout << gsl_stats_median_from_sorted_data(data, 1, size) << endl;
	cout << gsl_stats_max(data, 1, size) << endl;
	cout << gsl_stats_min(data, 1, size) << endl;
	cout << gsl_stats_mean(data, 1, size) << endl;
	return 0;
}
