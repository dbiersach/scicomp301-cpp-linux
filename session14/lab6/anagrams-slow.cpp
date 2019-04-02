// anagrams-slow.cpp

#include "stdafx.h"

using namespace std;

vector<string> phrases {
    "Stop", "Least","Traces", "Players", "Restrain"
};

vector<string> dictionary;
vector<string> words;

template <typename T>
string Concat(vector<T>* set)
{
    string c{};
    for (const auto& item : *set)
        c += item;
    return c;
}

template <typename T>
void Swap(vector<T>* set, int a, int b)
{
    T tmp = set->at(a);
    set->at(a) = set->at(b);
    set->at(b) = tmp;
}

template <typename T>
void Permute(vector<T>* set, int level)
{
    // Heap's Algorithm
    if (level == 0) {
        // At this point, set contains a new permutation
        words.push_back(Concat(set));
    } else {
        for (int i{ 0 }; i < level; ++i) {
            Permute(set, level - 1);
            Swap(set, level % 2 == 1 ? 0 : i, level - 1);
        }
    }
}

int main()
{
    // Read in the dictionary file
    ifstream inputFile("english_dictionary.txt");
    string line;
    while (getline(inputFile, line)) {
        boost::trim(line);
        if (line.length() > 0)
            dictionary.push_back(line);
    }

    // Start a timer
    boost::timer timer;

    // Find any anagrams for every requested phrase
    for (auto& phrase : phrases) {

        // Convert phrase to all lowercase
        boost::to_lower(phrase);

        // Create vector of individual characters
        vector<char> letters;
        for (auto s : phrase)
            letters.push_back(s);

        // Add all permutations of letters to words vector
        words.clear();
        Permute<char>(&letters, letters.size());

        // Remove redundant permutations caused
        // by a phrase having duplicated letters
        sort(words.begin(), words.end());
        auto last = unique(words.begin(), words.end());
        words.erase(last, words.end());

        // Display only words that are found in the dictionary
        for (const auto& word : words)
            if (binary_search(dictionary.begin(),
                              dictionary.end(), word))
                cout << word << endl;

        cout << endl;
    }

    cout << "Total search time = "
         << fixed << setprecision(3)
         << timer.elapsed() << " s" << endl;

    return 0;
}

