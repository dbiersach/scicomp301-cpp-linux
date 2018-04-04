// LRSS.cpp

#include "stdafx.h"

using namespace std;

ifstream* infile = nullptr;
string filename;
string* seq;

void OpenDataFile(int argc, char *argv[])
{
	// Ensure user has provided a filename
	if (argc < 2) {
		cout << "Error: Missing sequence filename";
		exit(-1);
	}

	filename = argv[1];
	infile = new ifstream(filename);

	// Ensure the input file can be read
	if (!infile->is_open()) {
		cout << "Error: Unable to open file "
			"\"" << filename << "\"" << endl;
		exit(-1);
	}
}

void CloseDataFile()
{
	if (infile != nullptr) {
		infile->close();
		delete infile;
	}
}

void LoadSequence()
{
	// Read the entire text file into the string
	seq = new string(
		istreambuf_iterator<char>(*infile),
		istreambuf_iterator<char>());

	// Remove any embedded special characters
	seq->erase(remove_if(seq->begin(), seq->end(),
		[](char c) {return isspace(c);}), seq->end());
}

string match(string s1, string s2)
{
	if (s1.size() > s2.size())
		s1.swap(s2);
	string match{};
	for (size_t i{}; i < s1.size()
		&& s1.at(i) == s2.at(i);++i)
		match += s1.at(i);
	return match;
}

string lrss(string s)
{
	// Create the suffix array
	vector<string> suffixes(s.size());
	for (size_t i{}; i < suffixes.size(); ++i)
		suffixes.at(i) = s.substr(i, s.size() - i);

	// Bubble sort the suffix array
	while (true) {
		bool swapped = false;
		for (size_t i{}; i < suffixes.size() - 1;++i)
			if (suffixes.at(i) > suffixes.at(i + 1)) {
				string temp = suffixes.at(i);
				suffixes.at(i) = suffixes.at(i + 1);
				suffixes.at(i + 1) = temp;
				swapped = true;
			}
		if (!swapped)
			break;
	}

	// Find the longest repeated substring (lrss)
	string longest{};
	for (size_t i{}; i < suffixes.size() - 1;++i) {
		string candidate = match(suffixes.at(i),
			suffixes.at(i + 1));
		if (candidate.size() > longest.size())
			longest = candidate;
	}
	return longest;
}


int main(int argc, char *argv[])
{
	OpenDataFile(argc, argv);

	LoadSequence();

	clock_t startTime{ clock() };

	string longest = lrss(*seq);

	clock_t stopTime{ clock() };

	cout << "The longest repeated substring in "
		<< "\"" << filename << "\" is: "
		<< longest << endl << endl;

	double totalTime{ ((double)(stopTime - startTime)
		/ CLOCKS_PER_SEC) * 1000 };

	cout.imbue(std::locale(""));
	cout << "Total run time (ms): "
		<< totalTime << endl;

	CloseDataFile();

	return 0;
}