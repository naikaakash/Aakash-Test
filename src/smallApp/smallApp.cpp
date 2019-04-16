#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

#define SDSIM_USAGE "Usage: %s [OPTION]\n"                                          \
                    "sdsim application (v%s)\n"                                     \
                    "\n"                                                            \
                    "  -h                 Display this help and exit\n"             \
                    "  -f [FEATURE SET]   The feature set to simulate\n"            \
                    "  <no option>        Start sdsim with device major version 5\n"\

#define SDSIM_INVALID_OPTION "Try '%s -h' for more information\n"
enum
{
    TEST_CHANGE_DFW0,
    TEST_CHANGE_DFW1,
    TEST_CHANGE_DFW2,
    TEST_CHANGE_TFW0,
};

static std::string _version = "0.0";
static unsigned int _featureSet = 9;


//static int _parseCommandLine(int argc, char *argv[]);
int _parseCommandLine(int argc, char *argv[])
{
    int c;
    int rc = 0;

    while ((c = getopt(argc, argv, "f:h")) != -1)
    {
        switch (c)
        {
        case 'h':
            fprintf(stderr, SDSIM_USAGE, argv[0], _version.c_str());
            exit(EXIT_SUCCESS);
            break;

        case 'f':
            {
                if (2 < strlen(optarg))
                {
                    fprintf(stderr, "Invalid agument '%s' to '-s' option\n", optarg);
                    rc = -1;
                }
                else
                {
                    _featureSet = atoi(optarg);

                    if (_featureSet > TEST_CHANGE_TFW0)
                    {
                        fprintf(stderr, "Invalid feature set \n"
                                        "'%s' to '-s' option Invalid\n "
                                        "feature set range (%d - %d)\n", optarg,
                                        TEST_CHANGE_DFW0, TEST_CHANGE_TFW0);
                        rc = -1;
                    }
                    else
                    {
                        std::cerr << "feature set=" << _featureSet << std::endl;
                    }
                }
            }
            break;

        case '?':
            fprintf(stderr, SDSIM_INVALID_OPTION, argv[0]);
            exit(EXIT_FAILURE);

        default:
            break;
        }
    }

    return rc;
}


int main(int argc, char *argv[])
{
   if (-1 == _parseCommandLine(argc, argv))
   {
       std::cerr << "Unable to parse command line options\n";
       exit(EXIT_FAILURE);
   }

   std::cerr << "Exiting this small App\n";
   return EXIT_SUCCESS;
}

