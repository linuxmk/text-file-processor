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

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
auto flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;

    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                   flip_pair<A,B>);
    return dst;
}


class TextParser
{
public:
    TextParser(const ParseArgs &args);
    void parseText(std::bitset<4> modes);
    auto invert_map(map<string, int> & mymap);

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
