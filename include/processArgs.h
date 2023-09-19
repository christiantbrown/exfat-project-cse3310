#pragma once


typedef struct
{
    char *fileIn;
    char *fileOut;
    int hasC;
    int hasV;
    int hasD;
} inputParamaters;
//struct contains crucial data from command line arguments read with processCommandInput

inputParamaters processCommandInput(int argc, char *argv[]);
//reads values into global variable storedInput
//takes argc and argv from main
