#include <iostream>
#include "parseargs.h"
#include "parsetext.h"

int main(int argc, char **argv)
{

    std::map<std::string, int> words;

    ParseArgs args(argc, argv);

    if(args())
    {
        std::cerr << argv[0] << " --in <filename> --mode <all|words|paragraphs|sentance|punctions> [--out <filename>]\n";
        return -1;
    }

    TextParser data(args);

    data.parseText(args.getModes());


    std::cout << data << std::endl;
    return 0;
}
