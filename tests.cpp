#include "src/parseargs.cpp"
#include "src/parsetext.cpp"
#include <gtest/gtest.h>
//#include <fstream>

enum
{
	mWords = 0,
        mParagraphs = 1,
        mSentances = 2,
        mPunctuation = 3
};

TEST(ParsingArgs, parseArgs) { 
    
	char *argv[] = { "runTEst", "--in", "input.txt", "--mode", "all", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
	args.parseArgs();
	
    	ASSERT_EQ( true, args());
    	ASSERT_EQ( true, args.getModes().test(mWords));
    	ASSERT_EQ( true, args.getModes().test(mParagraphs));
    	ASSERT_EQ( true, args.getModes().test(mSentances));
    	ASSERT_EQ( true, args.getModes().test(mPunctuation));
}
 
TEST(ParsingText, parseAll) {

        char 	cwd[1024] = "/home/rb/devel/projects/c++/companiesTests/testLab/text-file-processor";

        //getcwd(cwd, sizeof(cwd));

	strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "all", "--out", "output.txt"};

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());
	
        ASSERT_EQ(33 , data.getNumWords());
        ASSERT_EQ(2 , data.getNumParagraphs());
        ASSERT_EQ(4 , data.getNumSentances());
        ASSERT_EQ(2 , data.getNumPunctuation());
}

TEST(ParsingText, parseSetOneByOne) {

        char    cwd[1024] = "/home/rb/devel/projects/c++/companiesTests/testLab/text-file-processor";

      //  getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "words", "--mode", "paragraphs","--mode", "sentances","--mode", "punctuations", "--out", "output.txt"};

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

        ASSERT_EQ(33 , data.getNumWords());
        ASSERT_EQ(2 , data.getNumParagraphs());
        ASSERT_EQ(4 , data.getNumSentances());
        ASSERT_EQ(2 , data.getNumPunctuation());
}


TEST(ParsingText, CheckOutFile) {

        char    cwd[1024];
	char	outFile[32] = "output.txt";

        getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "all", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

	std::ifstream out(outFile);

        ASSERT_EQ(true, out.is_open());

	out.close();
}


TEST(ParsingText, parseWords) {

        char    cwd[1024] ;

        getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "words", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

        ASSERT_EQ(33 , data.getNumWords());
        ASSERT_EQ(0 , data.getNumParagraphs());
        ASSERT_EQ(0 , data.getNumSentances());
        ASSERT_EQ(0 , data.getNumPunctuation());
}

TEST(ParsingText, parseParagraphs) {

        char    cwd[1024];

        getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "paragraphs", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

        ASSERT_EQ(0 , data.getNumWords());
        ASSERT_EQ(2 , data.getNumParagraphs());
        ASSERT_EQ(0 , data.getNumSentances());
        ASSERT_EQ(0 , data.getNumPunctuation());
}

TEST(ParsingText, parseSentances) {

        char    cwd[1024];

       getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "sentances", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

        ASSERT_EQ(0 , data.getNumWords());
        ASSERT_EQ(0 , data.getNumParagraphs());
        ASSERT_EQ(4 , data.getNumSentances());
        ASSERT_EQ(0 , data.getNumPunctuation());
}

TEST(ParsingText, parsePunctuations) {

        char    cwd[1024];

        getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "punctuations", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

        ASSERT_EQ(0 , data.getNumWords());
        ASSERT_EQ(0 , data.getNumParagraphs());
        ASSERT_EQ(0 , data.getNumSentances());
        ASSERT_EQ(2 , data.getNumPunctuation());
}

TEST(ParsingText, parsaeWordsAndPunctuations) {

        char    cwd[1024];

        getcwd(cwd, sizeof(cwd));

        strcat(cwd, "/input.txt");

        char *argv[] = { "runTests", "--in", cwd , "--mode", "punctuations", "--mode", "words", "--out", "output.txt" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        TextParser data(args);
        data.parseText(args.getModes());

        ASSERT_EQ(33 , data.getNumWords());
        ASSERT_EQ(0 , data.getNumParagraphs());
        ASSERT_EQ(0 , data.getNumSentances());
        ASSERT_EQ(2 , data.getNumPunctuation());
}


TEST(ParsingArgs, MissingModes) {
    
	char	outFile[13] = "output.txt";

        char *argv[] = { "runTests", "--in", outFile };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
	args.parseArgs();

	ASSERT_EQ(false , args());

}
 
TEST(ParsingArgs, MissingInputFile) {

        char *argv[] = { "runTests", "--mode", "all" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        ASSERT_EQ(false , args());
}


TEST(ParsingArgs, MissingWrongMode) {

        char *argv[] = { "runTests", "--in", "input.txt", "--mode", "alll" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        ASSERT_EQ(false , args());
}

TEST(ParsingArgs, MissingMisspeldSentance) {

        char *argv[] = { "runTests", "--in", "input.txt", "--mode", "sentancs" };

        ParseArgs args(sizeof(argv)/sizeof(char *) , argv);
        args.parseArgs();

        ASSERT_EQ(false , args());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
