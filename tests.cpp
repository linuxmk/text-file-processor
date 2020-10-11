#include "src/parseargs.cpp"
#include "src/parsetext.cpp"
#include <gtest/gtest.h>
 

enum
{
	mWords = 0,
        mParagraphs = 1,
        mSentances = 2,
        mPunctuation = 3
};

TEST(Parsing, PositiveNos) { 
    
	char *argv[] = { "--in", "input.txt", "--mode", "all", "--out", "output.txt" };
			

	ParseArgs args(6 , argv);

	
    ASSERT_EQ(true, args.parseArgs());
    ASSERT_EQ(false, args());
    ASSERT_EQ( true, args.getModes().test(mWords));
    ASSERT_EQ( true, args.getModes().test(mParagraphs));
    ASSERT_EQ( true, args.getModes().test(mSentances));
    ASSERT_EQ( true, args.getModes().test(mPunctuation));



}
 
TEST(SquareRootTest, NegativeNos) {
/*    ASSERT_EQ(-1.0, squareRoot(-15.0));
    ASSERT_EQ(-1.0, squareRoot(-0.2));
    */
}
 

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
