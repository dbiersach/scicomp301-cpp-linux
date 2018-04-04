// freq-bigram-win.cpp

#include "stdafx.h"

using namespace std;

vector<uint8_t> ReadFile(string fileName)
{
    // Open file at the end so the "get" position will be file size
    ifstream ifs(fileName, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    // Allocate a vector big enough to hold all the file bytes
    vector<uint8_t> fileBytes(pos);

    // Read in the file from the beginning straight into the vector
    ifs.seekg(0, ios::beg);
    ifs.read((char*)(fileBytes.data()), pos);

    return fileBytes;
}

vector<uint8_t> CleanBuffer(vector<uint8_t> buff)
{
    vector<uint8_t> cleanBuff;
    for (auto c : buff) {
        bool isClean = true;
        // Only true letter characters are "clean"
        if (c < 65) isClean = false;
        if ((c > 90) && (c < 97)) isClean = false;
        if ((c > 123) && (c < 126)) isClean = false;
        if ((c == 146) || (c == 150)) isClean = false;
        if (isClean) {
            // Convert lowercase letters to UPPERCASE letters
            if ((c > 96) && (c < 123)) c -= 32;
            cleanBuff.push_back(c);
        }
    }
    return cleanBuff;
}

vector<int> CountBigrams(vector<uint8_t> buff)
{
    vector<int> bigrams(65536, 0);

    // Count each bigram occurance in the buffer
    // Each bigram index =
    //      (ASCII value of first char * 256) +
    //           ASCII value of second char
    for (size_t i{}; i < buff.size() - 1; ++i) {
        auto c1 = buff.at(i);
        auto c2 = buff.at(i + 1);
        auto c3 = c1 * 256 + c2;
        bigrams.at(c3)++;
    }

    return bigrams;
}

void DisplayBigrams(vector<int> bigrams,
                    size_t buffSize,
                    double threshold)
{
    int countNonZeroBigrams = count_if(
                                  bigrams.begin(), bigrams.end(),
    [](int c) {
        return c > 0;
    });

    cout << "ASCII\t\tCHARS\t FREQ" << endl;

    for (size_t i{}; i < bigrams.size(); ++i) {
        // Only show bigrams having recurrance freq > threshold
        double freq = (double)bigrams.at(i) / countNonZeroBigrams;
        if (freq > threshold) {
            auto c1 = i / 256;
            auto c2 = i % 256;
            auto ch1 = (char)c1;
            auto ch2 = (char)c2;
            cout << "(" << c1 << ", " << c2 << ")\t"
                 << ch1 << ch2 << "\t"
                 << setw(5) << fixed << setprecision(2)
                 << (double)bigrams.at(i) / buffSize * 100
                 << endl;
        }
    }
}

int main()
{
    bool usePlaintextFile = false;

    string fileName;
    double bigramDisplayThreshold;

    if (usePlaintextFile) {
        fileName = "Kennedy Moon English.txt";
        bigramDisplayThreshold = .05;
    } else {
        fileName = "Encrypted.txt";
        bigramDisplayThreshold = .50;

    }

    cout << "Most recurring bigrams in file:"
         << endl << "  " << fileName
         << endl << endl;

    vector<uint8_t> buff = CleanBuffer(
                               ReadFile(fileName));

    vector<int> bigrams = CountBigrams(buff);

    DisplayBigrams(bigrams, buff.size(),
                   bigramDisplayThreshold);

    return 0;
}
