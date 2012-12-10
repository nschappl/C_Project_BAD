//John Giunco
//Project 4: Memory Simulation
//Project Info: This is the product of a couple attempts.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
/*
Function: print_array

Parameters: 
Param 1 - 64 element array

*/
void print_array(int mem[64][2])
{
        int a;
        for(a = 0; a <= 63; a++)
        {
                printf("%d, ", mem[a][0]);
                printf("%d\n", mem[a][1]);
        }
}

/*
Function: main

Parameters: 
Param 1 - Int field

*/
void main(int argv, char* argc[])
{
        /* Intialize */
        int MemStack[64][2];
        int proc[2];
        char procbuff[25];
        char buffer[25];
        int a,b,c,d,e;
        int fsize, fst;

        while(true)
        {
                /* To prevent reset */
                int timeloaded=1;
                /* File Request */
                printf("Please enter a valid simulation file or exit to quit:\n");
                scanf("%s", &buffer);

                if((strcmp(buffer, "exit"))==0)
                {
                        exit(0);
                }

                /* Determine File Size */
                FILE* fp;
                fp = fopen(buffer, "r");

                if(fp != NULL)
                {
                        fsize=0;

                        while(!feof(fp))
                        {
                                fscanf(fp, "%d", &procbuff);
                                fsize++;
                        }

                        fst = (fsize-1)/2;
                } else {
                        printf("File does not exist or is corrupt!\n");
                        continue;
                }
                fclose(fp);

                /* Re-Open for Use */
                fp = fopen(buffer, "r");
                int fileContents[fst][2];
                if(fp != NULL)
                {
                        for(a=0; a < fst; a++)
                        {
                                for(b=0; b <= 1; b++)
                                {
                                        fscanf(fp, "%d", &fileContents[a][b]);
                                }
                        }
                } else {
                        printf("File does not exist or is corrupt!\n");
                        continue;
                }
                fclose(fp);

                /* Begin Simulation */
                /* Clear Memory & Load OS (8M of 64M) */
                for (a=0; a <= 63; a++)
                {
                        if( a <= 7)
                        {
                                MemStack[a][0] = -1;
                                MemStack[a][1] = -1;
                        } else {
                                MemStack[a][0] = 0;
                                MemStack[a][1] = 0;
                        }
                }
                /* Load Processes */
                for (a=0; a < fst; a++)
                {
                        /* Check if alread in mem */
                        int does_exist =0;
                        for (b=0; b <= 63; b++)
                        {
                                if( fileContents[a][0] == MemStack[b][0])
                                {
                                        does_exist =1;
                                        break;
                                }

                        }

                        if (does_exist == 1)
                        {
                                continue;
                        }

                        /* Check Size  */
                        int count=0;
                        int index=0;
                        for(b=0; b <= 63; b++)
                        {
                                if(count ==0 && MemStack[b][0] == 0)
                                {
                                        index = b;
                                } else if (MemStack[b][0] > 0){
                                        index =0;
                                        count =0;
                                }
                                if(MemStack[b][0] == 0)
                                {
                                        count++;
                                }
                                if(count == fileContents[a][1])
                                {
                                        break;
                                }

                        }

                        int control=0;
                        int lowest;
                        int tempi;
                        int tempc;
                        /* Load else remove */
                        if(count >= fileContents[a][1])
                        {
                                for(b = index; b <= ((index + fileContents[a][1])-1); b++)
                                {
                                        MemStack[b][0] = fileContents[a][0];
                                        MemStack[b][1] = timeloaded;
                                }
                                timeloaded++;
                        } else {
                                while(control !=1)
                                {
                                        /* Find Lowest */
                                        lowest = timeloaded;
                                        for(b=0; b <= 63; b++)
                                        {
                                                if(MemStack[b][1] > 0 && lowest >  MemStack[b][1])
                                                {
                                                        lowest = MemStack[b][1];
                                                }
                                        }


                                        /* Remove Lowest */
                                        for(b=0; b <= 63; b++)
                                        {
                                                if(MemStack[b][1] == lowest)
                                                {
                                                        MemStack[b][0]=0;
                                                        MemStack[b][1]=0;
                                                }
                                        }

                                        /* Check for space */
                                        tempi =0;
                                        tempc =0;
                                        for(b=0; b <= 63; b++)
                                        {
                                                if(tempc ==0 && MemStack[b][0] == 0)
                                                {
                                                        tempi = b;
                                                } else if (MemStack[b][0] > 0) {
                                                        tempi =0;
                                                        tempc =0;
                                                }
                                                if(MemStack[b][0] == 0)
                                                {
                                                        tempc++;
                                                }
                                                if(tempc == fileContents[a][1])
                                                {
                                                        break;
                                                }
                                        }

                                        /* Terminate or Remove again? */
                                        if(tempc >= fileContents[a][1])
                                        { 
                                                control =1;
                                        }

                                }//While End

                                for(b=tempi; b <= ((tempc + tempi)-1); b++)
                                {
                                        MemStack[b][0] = fileContents[a][0];
                                        MemStack[b][1] = timeloaded;
                                }
                                timeloaded++;

                        }//Else end



                }// End Load
        print_array(MemStack);

        }// End While

}
