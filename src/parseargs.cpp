#include "parseargs.h"

void PrintHelp()
{
    std::cerr <<
            "-i,  --in <fileName>:                                       File input to the program\n"
            "-m,  --mode <all|words|paragraphs|sentance|punctions>:      Mode to operate on\n"
            "-o,  –-out [<fileName>]:                                    File to write to\n"
            "-h,  –-help:                                                Show help\n";
    exit(1);
}

ParseArgs::ParseArgs(int argc, char** argv) : mArgc{argc}, mArgv{argv}
{
    mSucc = parseArgs();
}

bool ParseArgs::parseArgs()
{
    char *subopts, *value;
    int  args = 0;
    const char* const short_opts = "i:m:o:h";
    const option long_opts[] = {
            {"in", required_argument, nullptr, 'i'},
            {"mode", required_argument, nullptr, 'm'},
            {"out", required_argument, nullptr, 'o'},

            {"help", no_argument, nullptr, 'h'},
            {nullptr, no_argument, nullptr, 0}
    };

    enum
    {
      ALL = 0,
      WORDS,
      PARAGRAPHS,
      SENTANCES,
      PUNCTUATIONS,
      THE_END
    };

     const char *mount_opts[] =
    {
      [ALL] = "all",
      [WORDS] = "words",
      [PARAGRAPHS] = "paragraphs",
      [SENTANCES] = "sentances",
      [PUNCTUATIONS] = "punctuations",
      [THE_END] = NULL
    };

    while (true)
    {
        const auto opt = getopt_long(mArgc, mArgv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
            case 'i':
                ++args;
                mInputFilename = optarg;
//                std::cout << "filename is " << inFilename() << std::endl;
                break;

            case 'm':
                args++;
                subopts = optarg;
                while (*subopts != '\0')
                {
                    int xxx = getsubopt (&subopts,(char *const *) mount_opts, &value);
                    switch (xxx)
                    {
                        case ALL:
                          mModes.set(mWords);
                          mModes.set(mParagraphs) ;
                          mModes.set(mSentances);
                          mModes.set(mPunctuation);

                          std::cerr << "all is set\n";
                          break;

                        case WORDS:
                            mModes.set(mWords);
                            std::cerr << "WORDS is set\n";
                          break;

                        case PARAGRAPHS:
                            mModes.set(mParagraphs );
                            std::cerr << "PARAGRAPHS is set\n";
                          break;

                        case SENTANCES:
                            mModes.set(mSentances);
                            std::cerr << "SENTANCES is set\n";
                          break;

                        case PUNCTUATIONS:
                            mModes.set(mPunctuation);
                            std::cerr << "PUNCTUATIONS is set\n";

                          break;
                        default:
                          /* Unknown suboption. */
                            std::cerr << "Unknown suboption " << value << "\n";
                            mSucc = false;
                          break;
                    }
                }
                break;

            case 'o':
                mOutputFilename = optarg;
                std::cout << "Write file set to: " << mOutputFilename << std::endl;
                break;

            case 'h': // -h or –help
            case '?': // Unrecognized option
            default:
                mSucc = false;
                PrintHelp();
                break;
        }
    }
    return args < 2;
}
