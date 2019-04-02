// anagrams-fast.cpp

#include "stdafx.h"

using namespace std;

class Anagram2
{
public:
	Anagram2(string word);
	Anagram2(string word1, string word2);
	string word1;
	string word2;
	string letters;
};

Anagram2::Anagram2(string word)
{
	sort(word.begin(), word.end());
	this->letters = word;
}

Anagram2::Anagram2(string word1, string word2)
{
	this->word1 = word1;
	this->word2 = word2;
	string word = word1 + word2;
	sort(word.begin(), word.end());
	this->letters = word;
}

auto compare_lambda = [](const Anagram2& a, const Anagram2& b) ->bool {
	return a.letters < b.letters; };

bool contained(string a, string b)
{
	// Is a fully & uniquely contined in b?
	if (a.length() > b.length())
		return false;

	for (size_t i{}; i < a.length(); i++)
	{
		auto pos = b.find(a[i], i);
		if (pos == string::npos)
			return false;
		b[pos] = ' ';
	}

	return true;
}

vector<string> dictionary;
vector<Anagram2> anagrams;

int main()
{
	string phrase{ "Dormitory" };
	//string phrase{ "Software" };
	//string phrase{ "Mother-In-Law" };

	cout << phrase << endl;
	boost::remove_erase_if(phrase, boost::is_any_of(" _-.,()\\%\t"));
	boost::to_lower(phrase);
	Anagram2 input(phrase);

	// Read in the dictionary file
	ifstream inputFile("english_dictionary.txt");
	string line;
	while (getline(inputFile, line)) {
		boost::trim(line);
		if (line.length() > 0) {
			Anagram2 word(line);
			// Only add words from dictionary that could
			// possibly be in the anagram of the given phrase
			if (contained(word.letters, input.letters))
				dictionary.push_back(line);
		}
	}

	// Create compound anagram from every
	// successive two words in the dictionary
	for (size_t i{}; i < dictionary.size() - 1; i++)
		for (size_t j{ i + 1 }; j < dictionary.size(); j++)
			anagrams.push_back(
				Anagram2(dictionary.at(i),
					dictionary.at(j)));

	// Sort the anagrams by their sorted letters
	sort(anagrams.begin(), anagrams.end(), compare_lambda);

	// Find *first* word in dictionary that has sorted letters
	// matching the current phrase also sorted by letters
	auto lower = lower_bound(anagrams.begin(), anagrams.end(),
		input, compare_lambda);

	// Find *last* word in dictionary that has sorted letters
	// matching the current phrase also sorted by letters
	auto upper = upper_bound(lower, anagrams.end(),
		input, compare_lambda);

	// Create a vector concatenating both words of each anagram
	vector<string> phrases;
	for (auto& a = lower; a < upper; a++)
		phrases.push_back(a->word1 + " " + a->word2);

	// Sort & display the vector of the compound anagrams
	sort(phrases.begin(), phrases.end());
	for (auto& s : phrases)
		cout << s << endl;

	//return 0;
}
