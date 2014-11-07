#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME  "candylist.txt"
#define NUM_OF_TYPES 20

struct candy {
   char name[20];
   int quantity;
};

struct candy candies[NUM_OF_TYPES];


main() {

   char* buffer = 0;
   long length;
   FILE* fp = fopen(FILE_NAME, "rb");

   int numOfCandies = 0;


   /* Read file into buffer */
   if(fp) {
      fseek(fp, 0, SEEK_END);
      length = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      buffer = malloc (length);
      if(buffer) {
         fread(buffer, 1, length, fp);
      }
      fclose(fp);
   }



   if(buffer) {
      /* Print contents */
      //printf("%s", buffer);

      int x;int z=0;
      char currentWord[20] = "";      
      for(x = 0; x < length; x++) {
	 if(buffer[x] != '\n') {
            currentWord[z] = buffer[x];
	    z++;
         } else {
            //printf("%s\n", currentWord);
            z = 0;   
            int y;
            int contains = 0;
            for(y = 0; y < NUM_OF_TYPES; y++) {
               if(strcmp(candies[y].name, currentWord) == 0) {
                  candies[y].quantity++;
                  contains = 1;
                  break;
               } else {
                  contains = 0;
               }
            }
            if(contains == 0) {
               strcpy(candies[numOfCandies].name, currentWord);
               candies[numOfCandies].quantity++;
               numOfCandies++;                                    
            }


            int i;
            for(i = 0; i < 20; i++) {
               currentWord[i] = '\0';
            }
         }
      }
      int i;
      for(i = 0; i < NUM_OF_TYPES; i++) {
         double percent = ((double)candies[i].quantity / 1000);
         printf("Type: %20s -- Quantity: %d -- %%%.3f\n", candies[i].name, candies[i].quantity, percent);
      }
   }

   return (0);
}
