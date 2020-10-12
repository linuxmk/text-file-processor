#include <iostream>
#include "parseargs.h"
#include "parsetext.h"
//#include "include/parseargs.h"
//#include "include/parsetext.h"

int main(int argc, char **argv)
{

    ParseArgs args(argc, argv);
    args.parseArgs();

    if(!args())
    {
        std::cerr << argv[0] << " --in <filename> --mode <all|words|paragraphs|sentance|punctions> [--out <filename>]\n";
        return -1;
    }

    try {
        TextParser data(args);
        data.parseText(args.getModes());

    }  catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
