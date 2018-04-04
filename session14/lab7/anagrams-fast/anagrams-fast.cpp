// anagrams-fast.cpp

#include "stdafx.h"

using namespace std;

class Anagram
{
public:
    Anagram(string word);
    string word;
    string letters;
};

Anagram::Anagram(string word)
{
    boost::to_lower(word);
    this->word = word;
    sort(word.begin(), word.end());
    this->letters = word;
}

auto compare_lambda = []
(const Anagram& a, const Anagram& b) -> bool {
    return a.letters < b.letters;
};

vector<string> phrases {
    "Stop", "Least", "Traces", "Players", "Restrain",
    "Mastering", "Supersonic"
};

vector<Anagram> anagrams;

int main()
{
    // Load dictionary into the anagrams vector
    string line;
    ifstream inputFile("english_dictionary.txt");
    while (getline(inputFile, line)) {
        boost::trim(line);
        if (line.length() > 0 )
            anagrams.push_back(Anagram(line));
    }

    // Sort the anagrams by their sorted letters
    sort(anagrams.begin(), anagrams.end(),compare_lambda);

    // Start a timer
    boost::timer timer;

    for (const auto& phrase : phrases) {
        Anagram input{ phrase };

        // Find *first* word in dictionary that has sorted letters
        // matching the current phrase also sorted by letters
        auto lower = lower_bound(anagrams.begin(),
                                 anagrams.end(), input, compare_lambda);

        // Find *last* word in dictionary that has sorted letters
        // matching the current phrase also sorted by letters
        auto upper = upper_bound(lower, anagrams.end(),
                                 input,compare_lambda);

        // Display all dictionary words matching the phrase's anagram
        for(auto& a{lower}; a < upper; ++a)
            cout << a->word << endl;

        cout << endl;
    }

    cout << "Total search time = "
         << fixed << setprecision(4)
         << timer.elapsed() << " s" << endl;

    return 0;
}




