#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <getopt.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <bitset>


class ParseArgs
{
public:

    enum
    {
        mWords = 0,
        mParagraphs = 1,
        mSentances = 2,
        mPunctuation = 3
    };

    ParseArgs(int argc, char** argv);
    bool            operator()() const {
//        std::cerr << mSucc << std::endl;
        return mSucc;}
    std::string     inFilename() const { return mInputFilename;}
    std::string     outFilename() const { return mOutputFilename;}
    bool            parseArgs( );
    std::bitset<4>  getModes() const { return mModes;}
private:
    int         mArgc;
    char**      mArgv;
    bool        mSucc;
    std::string mInputFilename;
    std::string mOutputFilename;

    std::bitset<4> mModes;

};
#endif // PARSEARGS_H
