#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <extfat.h>
#include <processArgs.h>
#include <fileMapping.h>
#include <printDirectory.h>
#include <stdint.h>


#define DATA_LENGTH_EXPECTED 4096

//TODO:  coding standard for this file
//       do after we actually have it working

void printFileName(char * name, uint8_t * nameLen)
{
    for(int i = 0; i < 30; i+=2)
    {
      printf("%c", name[i]);
      *nameLen -=1;
      if(*nameLen == 0)
      {
         return;
      }
        
    }
}

void printAllDirectories(fileInfo * disk)
{
   getSelectedCluster(disk,0,0);
}


int cluster(Main_Boot * MB, int n)
{
   uint32_t bytesPerSector = 2 << (MB->BytesPerSectorShift - 1);
   uint32_t sectorsPerCluster = 2 << (MB->SectorsPerClusterShift - 1);
   //band aid solution
   if(sectorsPerCluster == 0)
   {
      sectorsPerCluster = 1;
   }
   if(n==0)
      n = ((MB->ClusterHeapOffset * bytesPerSector) + ((MB->FirstClusterOfRootDirectory - 2) * bytesPerSector * sectorsPerCluster));
   else
      n = ((MB->ClusterHeapOffset * bytesPerSector) + ((n - 2) * bytesPerSector * sectorsPerCluster));
   
   return n;
}
//n is the number cluster we are selecting, nesting is how nested that cluster is in the directory (0 for root)
int getSelectedCluster(fileInfo* disk,int n, int nesting)
{  
   n = cluster(disk->M_Boot,n);
   GenericDirectoryStruct *x = n + disk->Data;


   int i = 0;
   while (x[i].EntryType){i++;}
   i--;
   int num_entries = i;
   i=0;

   FileDirectoryEntry * F;

   while (i<num_entries)
   {
      if(x[i].EntryType == 0x85)
      {
         F=(FileDirectoryEntry *) x+i;
         printDirectoryEntry(F,disk,nesting);
         printf("\n");
      }

      i++;
   }

   return i+1;
}


//takes a FileDirectoryEntry *, pointer to disk struct, and number indicating how far nested the file is in directory structure
void printDirectoryEntry(FileDirectoryEntry * F, fileInfo* disk, int nesting)
{
   //immediately following every FileDirectoryEntry is 1 streamextension and at least 1 filename extension
   StreamExtensionEntry * StreamEx = (StreamExtensionEntry *) F+1;
   FilenameExtensionEntry * Fname =(FilenameExtensionEntry *) F+2;
   uint8_t numChars = StreamEx->NameLength;//we need this so we know when to stop printing
   for(int i = 0; i < nesting; i++)//we use tabs to indicate how far nested in the directory structure a file is
   {
      printf("\t");
   }
   while(numChars > 0)
   {
      printFileName(Fname->FileName,&numChars);
      Fname++;
   }
   if((uint8_t)F->FileAttributes[0] & 0b00010000)//we are just testing the bit that shows whether it is a directory
   {
      //if this runs a directory was detected
      printf(">>>\n");
      nesting++;
      //going to the cluster specified in the stream extension entry and repeating this process with 1 more indent
      getSelectedCluster(disk,StreamEx->FirstCluster,nesting);
   }





}





