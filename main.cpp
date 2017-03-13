#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

static const float pi = 3.1415926535897932384626433832795f;

float gaussianFunction(float x, float sigma) {
	float first_part = 1.0f / sqrt(2.0f * pi * pow(sigma, 2.0f));
	float second_part = pow(x, 2.0f) / (2.0f * pow(sigma, 2.0f));
	float result = first_part * exp(-second_part);

	return result;
}

int main(int argc, char *argv[]) {
	int samples = 0;
	bool output_to_file = false;
	
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "-f") == 0) {
			output_to_file = true;
		}
		else {
			stringstream ss(argv[i]);
			ss >> samples;
		}
	}
	
	if (samples == 0) {
		cout << "Usage: gauss [options] samples\n"
			 << "Options:\n"
			 << "  -f     Save output to a file called \"gauss.txt\"\n";
		return 1;
	}

	ofstream out_file;
	if (output_to_file) {
		out_file = ofstream("gauss.txt");
		cout.rdbuf(out_file.rdbuf());
	}

	float gauss_weight = 0.0f;
	float accum = 0.0f;
	
	cout << fixed << setprecision(5);
	for (int i = -samples; i <= samples; ++i) {
		gauss_weight = gaussianFunction(i, samples / 2);
		accum += gauss_weight;
		cout << gauss_weight;
		cout << (i < samples ? ", " : "");
	}
	cout << "\n\n";
	cout << "Kernel Size: " << (samples * 2 + 1) << '\n';
	cout << "Accum: " << (1.0 / accum) << '\n';
	cout << "^(reciprocal of the sum of all kernel components)\n";
	
	if (output_to_file)
		out_file.close();

	return 0;
}
