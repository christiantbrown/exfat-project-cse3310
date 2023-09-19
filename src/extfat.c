#include <assert.h>
#include <verify.h>
#include <extfat.h>
#include <processArgs.h>
#include <fileMapping.h>
#include <stdlib.h>
#include <string.h>
#include<sys/mman.h>
#include<unistd.h>
#include <printDirectory.h>

//Group 12, Iteration 2

/*
this is the main function for our extfat executable
it accepts command line arguments in the form of
    ./extfat -"x" "argument_if_necessary" -"y"
currently it accepts
    -i xxxx:    name of the input file (necessary)
    -o xxxx:    name of the output file
    -c: copy input file to output file
    -v: check if main and backup boot sectors in input file are the same
    -h: display a help menu with all this information (implemented in processCommandInput in processArgs.c)




*/



//Important global variable: storedInput
//we use storedInput to store important data from the command line arguments
//defined in processArgs.c

int main(int argc, char * argv[])
{
    fileInfo disk = {0};
    inputParamaters storedInput = processCommandInput(argc, argv);                //this reads values into the global variable storedInput (see processArgs.c)
    disk.fileName = storedInput.fileIn;
    disk.Data = map_entire_file(&disk);
    //----------------------------------------------//intializing boot sector structs
    disk.M_Boot = disk.Data;
    disk.SectorSize = 2 << (disk.M_Boot->BytesPerSectorShift-1);
    
    disk.B_Boot = (void*) disk.M_Boot + 12 * disk.SectorSize;


    //-------------------------------------------------------------------------------


   // assert(storedInput.fileIn != NULL); // Here I used the assert function to check the value of storedInput is not NULL






    fileInfo disk_copy = {0};
    if(storedInput.hasC)                            //+if copy option is selected
    {
        disk_copy.fileName = storedInput.fileOut;
        copy_file(&disk, &disk_copy);               //copy our input file to the output file

        disk_copy.Data = map_entire_file(&disk);    //this is our whole big file mapped in memory.
    }

    if(storedInput.hasV)                            //+if verify option is selected
    {
        verify(disk.M_Boot, disk.B_Boot);
    }

    if(storedInput.hasC){
        munmap(disk_copy.Data, disk.FileLength);
        close(disk_copy.fd);
    }
    if(storedInput.hasD)                        //+if print directories option is selected
    {
        printAllDirectories(&disk);             //this prints directories using recursion 
    }
    munmap(disk.Data, disk.FileLength);             //clean up memory

}

    // The assert sections:
    // This check the value of the return value 
    // Meet requirement for coding standard 2


    // int returnValue = some_function(); 
    // assert(returnValue >= 0 && returnValue <= 100);
    
