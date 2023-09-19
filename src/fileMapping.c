#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include <assert.h>
#include <stdint.h>



//see fileMapping.h
#include<extfat.h>//<---------Isaac Medrano 3/27/2023 (3.1)
char *map_entire_file(fileInfo *disk) {//<---------Isaac Medrano 3/27/2023 (3.1)
     struct stat sb;//this will contain file size

      disk->fd = open(disk->fileName, O_RDONLY);//getting a file descriptor with the open() function //<---------Isaac Medrano 3/27/2023 (3.1)

    if (disk->fd == -1) {//<---------Isaac Medrano 3/27/2023 (3.1)
        perror("Error opening input file");
         exit(1);
    }



    if (fstat(disk->fd, &sb) == -1) {//fstat reads values into sb, including file size //<---------Isaac Medrano 3/27/2023 (3.1)
        perror("fstat failed");
        return NULL;
    }
    disk->FileLength = sb.st_size; //<---------Isaac Medrano 3/27/2023 (3.1)
    char *file_data = mmap(NULL, //reading our file contents into a big block of memory with mmap
                            sb.st_size, 
                            PROT_READ, 
                            MAP_PRIVATE, 
                            disk->fd, //<---------Isaac Medrano 3/27/2023 (3.1)
                            0);

    if(file_data == MAP_FAILED)
    {
        perror("mmap failed");
    }

    return file_data;
}




void copy_file(fileInfo *disk, fileInfo *disk_copy) {//<---Isaac Medrano 4/2/2023 (4.2)
    

   //----------------------------------------------------------------
    assert(disk != NULL && "Null pointer passed to copy file");

    // Creating the output file
    disk_copy->fd = open(disk_copy->fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);//<---Isaac Medrano 4/2/2023 (4.4)
    if (disk_copy->fd == -1) {//<---Isaac Medrano 4/2/2023 (4.4)
        perror("Unable to create output file");
        return;
    }

    // Increase the size of the output file to match the input file
    if (lseek(disk_copy->fd, disk->FileLength - 1, SEEK_SET) == -1) {//<---Isaac Medrano 4/2/2023 (4.4)
        perror("FAILed, unable to read output file size");
        return;
    }

    if (write(disk_copy->fd, "", 1) == -1) {//<---Isaac Medrano 4/2/2023 (4.4)
        perror("Error writing to output file");
        return;
    }

    // Map the output file to memory
    disk_copy->Data = mmap(0, 
                        disk->FileLength, //<---Isaac Medrano 4/2/2023 (4.4)
                        PROT_READ | PROT_WRITE, 
                        MAP_SHARED, 
                        disk_copy->fd, 0);//<---Isaac Medrano 4/2/2023 (4.4)
    assert((disk_copy->Data != MAP_FAILED) && "Unable to map outfile to memory" );

    disk_copy->FileLength = disk->FileLength;//<---Isaac Medrano 4/2/2023 (4.4)
    disk_copy->SectorSize = disk->SectorSize; //<---------Isaac Medrano 4/2/2023 (4.4)
    // Copy the data from the input file to the output file
    memcpy(disk_copy->Data, disk->Data, disk->FileLength);//<---Isaac Medrano 4/2/2023 (4.4)
    //munmap(disk->Data, disk->FileLength);//<---Isaac Medrano 4/2/2023 (4.5)
    //munmap(disk_copy->Data, disk->FileLength);//<---Isaac Medrano 4/2/2023 (4.5)
    
    // Close the files
    //close(inputFile);//<---Isaac Medrano 4/2/2023 (4.5)
    //close(disk_copy->fd);//<---Isaac Medrano 4/2/2023 (4.5)
}

