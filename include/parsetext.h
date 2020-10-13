#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <vector>
using namespace std;

#include "parseargs.h"

class TextParser
{
public:
    TextParser(const ParseArgs &args);
    void parseText(std::bitset<4> modes);
    auto invert_map(map<string, int> & mymap);
    auto getNumWords() { return mWords.size(); }
    auto getNumParagraphs() { return mParagraphs; }
    auto getNumSentances() { return mSentances; }
    auto getNumPunctuation() { return mPunctuation.size(); }
    ~TextParser();


    friend ostream& operator<< (ostream &out, TextParser & data);

private:
    std::string                         mInFile;
    std::string                         mOutFile;
    std::fstream                        mIn;
    std::fstream                        mOut;

    std::bitset<4>                      mModes;
    std::map<std::string, int>          mWords;
    uint32_t                            mParagraphs;
    uint32_t                            mSentances;
    std::map<char, int>                 mPunctuation; // struct of period, commas, question marks, , eclipses
};

#endif // PARSETEXT_H
