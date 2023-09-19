#pragma once
#include <stdint.h>


/*
------------------------------
vvvvv entryType (byte 0) vvvvv

> typeCode(5 bits) defines the type of a given directory
> TypeImportance 0 means critical, 1 means benign
> TypeCategory 0 means primary, 1 means secondary
> isInUse 0 means directory is not used, 1 means it is in use


vvvvv customDefined (byte 1 to byte 19) vvvvv

***while mandatory, it does not store information we need to print directories (that I know of)
it may come up later, wouldnt surprise me :b


vvvvv firstCluster (byte 20 to byte 23) vvvvv

contains the index of the first cluster of an allocation in the Cluster Heap


vvvvv dataLength (byte 24 to byte 31) vvvvv

DataLength field describes the size, in bytes, of the data the associated cluster allocation contains
Max Value = ClusterCount * 2^(SectorsPerClusterShift) * 2^(BytesPerSectorShift)


------------------------------

*/
   typedef struct
   {
      union
      {
         uint8_t EntryType;
         struct
         {
            uint8_t TypeCode : 5;
            uint8_t TypeImportance : 1;
            uint8_t TypeCategory : 1;
            uint8_t InUse : 1;
         };
      };
      uint8_t CustomDefined[19];
      uint32_t FirstCluster;
      uint64_t DataLength;
   } GenericDirectoryStruct;

    //note the filename only takes up around 16 bytes
    //so the mentioned array size is NOT ACCURATE
    //I just dont have the time to code in the rest of the parameters
   struct secondaryEntry
         {
            union
            {
               uint8_t EntryType;
               struct
               {
                  uint8_t TypeCode : 5;
                  uint8_t TypeImportance : 1;
                  uint8_t TypeCategory : 1;
                  uint8_t InUse : 1;
               };
            };
            uint8_t GeneralSecondaryFlags : 8;
            char FileName[30];                  //this should be redefined to size 18 imo, but its 4am and I want to sleep :)
         };


typedef struct StreamExtensionEntry
{
    char EntryType;
    char GeneralSecondaryFlags;
    char Reserved;
    uint8_t NameLength;
    char NameHash[2];
    char Reserved2[2];
    uint64_t ValidDataLength;
    char Reserved3[4];
    uint32_t FirstCluster;
    uint64_t DataLength;





}StreamExtensionEntry;


typedef struct FilenameExtensionEntry
{
    uint8_t EntryType;
    char GeneralSecondaryFlags;
    char FileName[30];
} FilenameExtensionEntry;

typedef struct DirectoryEntry
{
    uint8_t EntryType;
    char contents[31];
} DirectoryEntry;


typedef struct FileDirectoryEntry
{
    char EntryType;
    char SecondaryCount;//number of secondary entries, min 2 (streamextension and filenames)
    uint16_t SetChecksum;
    char FileAttributes[2];//the 5th bit (bit 4) says whether it is a file (0) or directory(1), use bitwise AND
    char Reserved[2];
    char CreationTime[4];
    char LastModified[4];
    char LastAccessed[4];
    char Create10msIncrement;
    char LastModified10msIncrement;
    char LastAccessed10msIncrement;
    char Reserved2[9];





}FileDirectoryEntry;




void printAllDirectories(fileInfo * disk);


//prints the selected entry
void printDirectoryEntry(FileDirectoryEntry * F, fileInfo* disk, int nesting);

/*
prints directories associated with the image file. the first cluster is calculated using the following:
MB->ClusterHeapOffset * bytesPerSector + (bytesPerSector * sectorsPerCluster * (MB->FirstClusterOfRootDirectory-2));
*/
int cluster(Main_Boot * MB, int n);

/*
prints directories associated with the image file.
using "directoryEntries" (a generic directory) as an array of entries to go through
each entry and print it
*/
int getSelectedCluster(fileInfo * disk, int n, int nesting);


         
