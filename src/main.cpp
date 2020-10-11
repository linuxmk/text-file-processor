#include <iostream>
#include "include/parseargs.h"
#include "include/parsetext.h"

int main(int argc, char **argv)
{

    ParseArgs args(argc, argv);

    if(args.parseArgs())
    {
        std::cerr << argv[0] << " --in <filename> --mode <all|words|paragraphs|sentance|punctions> [--out <filename>]\n";
        return -1;
    }

    TextParser data(args);

    data.parseText(args.getModes());


    std::cout << data << std::endl;
    return 0;
}
