#include <stdio.h>
#include <getopt.h>
#include <processArgs.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//this code being seperated will likely be usefull when merging, so ill keep it here!



/*
----------------------------------------------------------
storedInput holds the paramaters input by a
user through the command line
----------------------------------------------------------
char *fileIn: String with name of input file (-i filenamehere)
char *fileOut: String with name of output file (-o filenamehere)
int hasV: Verify was selected (-v)
int hasC: Copy was selected (-c)
*/


/*
----------------------------------------------------------
function that fills struct named "storedInput" containing
Strings and ints (ints are only used as booleans):
----------------------------------------------------------
Help (-h)
-char *fileIn: String with name of input file (-i filenamehere)
-char *fileOut: String with name of output file (-o filenamehere)
-int *hasV: Verify option selected (-v)
-int *hasC: Copy option selected(-c)
*/
inputParamaters processCommandInput(int argc, char *argv[])
{
    assert(argc >= 1 && "argc provided is 0 or lower");
    assert(argv != NULL && "argv provided is null");
    inputParamaters storedInput = {0};
    

    const char fileExtension[6] = {'.', 'i','m','a','g','e'};//we use this to check if our file is a .image
    int opts;
    while((opts = getopt(argc, argv, "i:hcvdo:")) != -1)
    {
        switch(opts)
        {
            case 'h':
                printf("here are the commands extfat can be run with!\n");
                printf("extfat can be run by typing ./extfat in the bash console\n");
                printf("-h this help menu :D\n");
                printf("-i \"input\" input being a filename\n");
                printf("-o \"output\" output being a filename and is optional (if not specified, the output file is the same as the input file)\n");
                printf("-c copies the \"input\" file to the \"output\" file.\n");
                printf("-v verifies the main and backup boot sectors of the \"input\" file are the same.\n");
                break;
            case 'c':
                printf("recognized the \"-c\" option\n");
                storedInput.hasC=1;
                break;
            case 'd':
                printf("recognized the \"-d\" option\n");
                storedInput.hasD=1;
                break;
            case 'v':
                printf("recognized the \"-v\" option\n");
                storedInput.hasV = 1;
                break;
            case 'i':
                printf("recognized the \"-i\" option\n");
                storedInput.fileIn=optarg;
                printf("file input: %s\n", storedInput.fileIn);
                assert(storedInput.fileIn[strlen(storedInput.fileIn) - 1] != '\0' && "Input file was not null-terminated");
                break;
            case 'o':
                printf("recognized the \"-o\" option\n");
                storedInput.fileOut=optarg;
                printf("file output: %s\n", storedInput.fileOut);
                if (storedInput.fileOut == NULL) {
                    perror("Error: output file name is NULL");
                    
                }
                assert(storedInput.fileOut[strlen(storedInput.fileOut) - 1] != '\0' && "Output file was not null-terminated");
                break;

        }
    }



    //making sure we have an input file
    if(storedInput.fileIn == 0)
    {
        perror("Specify an input file with the -i option\n");
        exit(1);
    }




    //checking to see if the input and output files are .image
    for(int i = 0; i < 6; i++)
    {
        if(storedInput.fileIn[i + strlen(storedInput.fileIn) - 6] != fileExtension[i])
        {
            //assert(i + strlen(storedInput.fileIn) - 6 >= 0u && "Out of Range");
            perror("\nEnter a .image file for input\n");
            exit(1);
        }
    }
    if(storedInput.fileOut != 0)
    {
        for(int i = 0; i < 6; i++)
        {
            //assert((i + strlen(storedInput.fileOut) - 6) >= 0u && "Out of Range!");
            if(storedInput.fileOut[i + strlen(storedInput.fileOut) - 6] != fileExtension[i])
            {
                perror("\nEnter a .image file for output\n");
                exit(1);
            }
        }
    }
    
    return storedInput;
}