#include "parsetext.h"


TextParser::TextParser(const ParseArgs & args) : mInFile{args.inFilename()}, mOutFile{args.outFilename()}, mModes{args.getModes()}, mParagraphs{0}, mSentances{0}
{
    mIn.open(mInFile);

    if(!mIn)
    {
        throw std::invalid_argument("File can not be opened");
    }

    if(!mOutFile.empty())
    {
        mOut.open(mOutFile,ios_base::out);
        if(!mOut)
        {
            throw std::invalid_argument("File can not be opened for writing");
        }
    }
}

void TextParser::parseText(std::bitset<4> modes)
{
    char ch, prev;
    char word[128];
    uint32_t cnt = 0;

    while(mIn.read(&ch,1))
    {
//        std::cerr<< ch << " ";
        if(modes.test(ParseArgs::mWords))
        {
            if(isalnum(ch))
            {
                word[cnt++] = ch;
                continue;
            }

            if( isspace(ch) || ispunct(ch))
            {
                if( word[0] != '\0')  //optimise not to call a func //if(strlen(word) > 0)
                {
                    word[0] = tolower(word[0]);
                    word[cnt] = '\0';
                    ++mWords[word];
                    cnt = 0;
                    word[cnt] = '\0';

//                    memset(word,0,128);
                }

            }
        }

        if(modes.test(ParseArgs::mPunctuation) && ispunct(ch))
        {
            ++mPunctuation[ch];
        }

        if( modes.test(ParseArgs::mSentances) && ch == '.')
        {
            ++mSentances;
        }

        if( modes.test(ParseArgs::mPara) && prev == '.' && ch == '\n')
        {
            ++mParagraphs;
        }
        prev = ch;
    }
}

auto TextParser::invert_map(map<string, int> &mymap)
{
    multimap<int, string, greater<int>> multiMap;

    map<string, int> :: iterator it;
    for (it=mymap.begin(); it!=mymap.end(); it++)
    {
        multiMap.insert(make_pair(it->second, it->first));
    }

    return multiMap;
}

ostream& operator<< (ostream &out, TextParser & data)
{

    auto convWord = data.invert_map(data.mWords);

    if(!data.mOutFile.empty())
    {
       streambuf* stream_buffer_file = data.mOut.rdbuf();
            // Redirect cout to file
       cout.rdbuf(stream_buffer_file);
    }

    if(data.mModes.test(ParseArgs::mWords))
    {
        out << "Word count statistics:\n";
        for( auto word = convWord.begin() ; word != convWord.end() ; ++word)
        {
            out<< word->second << " -> " << word->first << "\n";
        }
    }

    if(data.mModes.test(ParseArgs::mPara))
        out << "\nParagraph count: " << data.mParagraphs << "\n";

    if(data.mModes.test(ParseArgs::mSentances))
        out << "\nSentence count: " << data.mSentances << "\n";

    if(data.mModes.test(ParseArgs::mPunctuation))
    {
        out << "\nPunctuation mark statistics:\n";
        for( auto punc = data.mPunctuation.begin() ; punc != data.mPunctuation.end() ; ++punc)
        {
            out<< punc->first << " -> " << punc->second << "\n";
        }
    }

    return out;
}

