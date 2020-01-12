#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace std;
using namespace boost::geometry;

int main (int argc, char** argv) {
	ifstream file21(argv[1]);
	vector <string> temp_vect21;
	string temp_string21;
	while ( getline(file21, temp_string21) ) {
		temp_vect21.push_back(temp_string21);
	}
	file21.close();
	ifstream file22(argv[2]);
	vector <string> temp_vect22;
	string temp_string22;
	while ( getline(file22, temp_string22) ) {
		temp_vect22.push_back(temp_string22);
	}
	file22.close();
	double vert_coord[8];
	double test_coord[temp_vect22.size()*2];
	string::size_type space_pos;
	string vertices_strs[4];
	string edges_strs[4];
	string poly_str = "POLYGON((";
	string test_points_strs[temp_vect22.size()];
	typedef model::d2::point_xy<double> point_type;
	point_type vertices[4];
	point_type test_points[temp_vect22.size()];
	model::segment<point_type> edges[4];
	model::polygon<point_type> poly;
	for (int i=0; i < 4; i++) {
		vert_coord[2*i]   = stod (temp_vect21[i],&space_pos);
		vert_coord[2*i+1] = stod (temp_vect21[i].substr(space_pos));
		vertices_strs[i] = "POINT(" + to_string(vert_coord[2*i]) + ' ' + to_string(vert_coord[2*i+1]) + ')';
		read_wkt(vertices_strs[i], vertices[i]);
	}
	for (int i=0; i < 4; i++) {
		if (i<3) {
			edges_strs[i] = "SEGMENT(" + to_string(vert_coord[2*i]) + ' ' + to_string(vert_coord[2*i+1]) + ',' + to_string(vert_coord[2*i+2]) + ' ' + to_string(vert_coord[2*i+3]) + ')';
			read_wkt(edges_strs[i], edges[i]);
			poly_str += to_string(vert_coord[2*i]) + ' ' + to_string(vert_coord[2*i+1]) + ',';
		}
		else {
			edges_strs[i] = "SEGMENT(" + to_string(vert_coord[2*i]) + ' ' + to_string(vert_coord[2*i+1]) + ',' + to_string(vert_coord[0]) + ' ' + to_string(vert_coord[1]) + ')';
			read_wkt(edges_strs[i], edges[i]);
			poly_str += to_string(vert_coord[2*i]) + ' ' + to_string(vert_coord[2*i+1]) + ',' + to_string(vert_coord[0]) + ' ' + to_string(vert_coord[1]) + "))";
			read_wkt(poly_str, poly);
		}
	}
	for (size_t i=0; i < temp_vect22.size(); i++) {
		test_coord[2*i]   = stod (temp_vect22[i],&space_pos);
		test_coord[2*i+1] = stod (temp_vect22[i].substr(space_pos));
		test_points_strs[i] = "POINT(" + to_string(test_coord[2*i]) + ' ' + to_string(test_coord[2*i+1]) + ')';
		read_wkt(test_points_strs[i], test_points[i]);
		if ( within(test_points[i], vertices[0]) || within(test_points[i], vertices[1]) || within(test_points[i], vertices[2]) || within(test_points[i], vertices[3]) ) {
			cout << "0" << endl;
		}
		else if ( within(test_points[i], edges[0]) || within(test_points[i], edges[1]) || within(test_points[i], edges[2]) || within(test_points[i], edges[3]) ) {
			cout << "1" << endl;
		}
		else if ( within(test_points[i], poly) ) {
			cout << "2" << endl;
		}
		else {
			cout << "3" << endl;
		}
	}
	return 0;
}
