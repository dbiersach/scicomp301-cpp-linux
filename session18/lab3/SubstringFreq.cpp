// SubstringFreq.cpp

#include "stdafx.h"

using namespace std;

ifstream* infile = nullptr;
ofstream* outfile = nullptr;
string filename;
string* seq;
unordered_map<string, string> codons;

void OpenDataFiles(int argc, char *argv[])
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

	// Append file name suffix to root of filename
	filename += ".ssfreq.csv";

	outfile = new ofstream(filename, ofstream::trunc);

	// Ensure the output file can be written
	if (!outfile->is_open()) {
		cout << "Error: Unable to write to file "
			"\"" << filename << "\"" << endl;
		exit(-1);
	}
}

void CloseDataFiles()
{
	if (infile != nullptr) {
		infile->close();
		delete infile;
	}

	if (outfile != nullptr) {
		outfile->flush();
		outfile->close();
		delete outfile;
	}
}

void AddCodon(string label, vector<string> seqs)
{
	for (auto& s : seqs)
		codons.insert(pair<string, string>(s, label));
}

void InitCodons()
{
	AddCodon("Ala", { "GCT","GCA","GCC","GCG" });				// Alanine (Ala/A)
	AddCodon("Arg", { "CGT","CGC","CGA","CGG","AGA","AGG" });	// Arginine (Arg/R)
	AddCodon("Asn", { "AAT", "AAC" });							// Asparagine (Asn/N)
	AddCodon("Asp", { "GAT", "GAC" });							// Aspartic Acid (Asp/D)
	AddCodon("Cys", { "TGT", "TGC" });							// Cysteine (Cys/C)
	AddCodon("Gln", { "CAA", "CAG" });							// Glutamine (Gln/Q)
	AddCodon("Glu", { "GAA", "GAG" });							// Glutamic Acid (Glu/E)
	AddCodon("Gly", { "GGT", "GGC","GGA","GGG" });				// Glycine (Gly/G)
	AddCodon("His", { "CAT", "CAC" });							// Histidine (His/H)
	AddCodon("Ile", { "ATT", "ATC","ATA" });					// Isoleucine (Ile/I)
	AddCodon("Leu", { "TTA","TTG","CTT","CTC","CTA","CTG" });	// Leucine (Leu/L)
	AddCodon("Lys", { "AAA", "AAG" });							// Lysine (Lys/K)
	AddCodon("Met/Start", { "ATG" });							// Methionine (Met / M) & Start
	AddCodon("Phe", { "TTT", "TTC" });							// Phenylalanine (Phe/F)
	AddCodon("Pro", { "CCT","CCC","CCA","CCG" });				// Proline (Pro/P)
	AddCodon("Ser", { "TCT","TCC","TCA","TCG","AGT","AGC" });	// Serine (Ser/S)
	AddCodon("Thr", { "ACT","ACC","ACA","ACG" });				// Threonine (Thr / T)
	AddCodon("Trp", { "TGG" });									// Tryptophan (Trp/W)
	AddCodon("Tyr", { "TAT", "TAC" });							// Tyrosine (Tyr/Y)
	AddCodon("Val", { "GTT", "GTC","GTA","GTG" });				// Valine (Val/V)
	AddCodon("Stop", { "TAA", "TGA","TAG" });					// Stop
}

string GetCodons(string subseq)
{
	string proteins;
	while (subseq.length() > 2) {
		string triplet{ subseq.substr(0,3) };
		if (codons.count(triplet) > 0)
			proteins += (codons.find(triplet)->second + ", ");
		subseq.erase(0, 3);
	}
	if (proteins.length() > 0)
		proteins.erase(proteins.length() - 2, 2);

	return proteins;
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

void WriteFreq(vector<pair<string, int>>& list, int len,
	bool topmost, size_t limit)
{
	string freqLabel;
	if (topmost) {
		freqLabel = "Most";
		// Sort list by decreasing substring frequency
		sort(list.begin(), list.end(),
			[](const pair<string, int> &a,
				const pair<string, int>& b)
		{
			return a.second > b.second;
		});
	}
	else
	{
		freqLabel = "Least";
		// Sort list by increasing substring frequency
		sort(list.begin(), list.end(),
			[](const pair<string, int> &a,
				const pair<string, int>& b)
		{
			return a.second < b.second;
		});
	}

	//size_t range = list.size() > limit ? limit : list.size();
	list.size() > limit ? limit : list.size();
	for (size_t row{};row < limit;++row) {
		*outfile << len << "," << list.at(row).second
			<< "," << freqLabel << "," << list.at(row).first
			<< "," << GetCodons(list.at(row).first) << endl;
	}
}

void WriteSubstrings()
{
	cout << "Creating file \""
		<< filename << "\" ...";

	*outfile << "length,count,freq,seq,proteins"
		<< endl;

	map<string, int> table;

	for (int len{ 3 };len < 19;++len)
	{
		table.clear();
		for (size_t pos{};pos <= seq->length() - len;++pos)
		{
			string key = seq->substr(pos, len);
			auto p = table.find(key);
			if (p == table.end())
				table.insert(pair<string, int>(key, 1));
			else
				p->second++;
		}

		// Copy sorted map to an unsorted list
		vector<pair<string, int>> list;
		for (auto& p : table)
			list.push_back(p);

		WriteFreq(list, len, true, 5);
		WriteFreq(list, len, false, 5);
	}

	cout << " done!" << endl;
}

int main(int argc, char *argv[])
{
	InitCodons();

	OpenDataFiles(argc, argv);

	LoadSequence();

	WriteSubstrings();

	CloseDataFiles();

	return 0;
}

