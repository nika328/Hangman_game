#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int ischarinarray(char c, char arr[], int limit)
{
    for (int i=0; i<limit; i++)
    {
        if(arr[i]==c)
        {
            return 1;
        }
    }
    return 0;
}

void hangman (int mistakes)
{
    if(mistakes==0)
    {
        printf("_________\n|\n|\n|\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==-1)
    {
      printf("_________\n|       |\n|\n|\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==1)
    {
      printf("_________\n| /      |\n|/\n|\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==2)
    {
       printf("_________\n| /      |\n|/      (_)\n|\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==3)
    {
       printf("_________\n| /      |\n|/      (_)\n|        |\t\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==4)
    {
       printf("_________\n| /      |\n|/      (_)\n|       \\|\t\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==5)
    {
       printf("_________\n| /      |\n|/      (_)\n|       \\|/\t\n|\n|\n|\n|_____\n");
    }
    else if(mistakes==6)
    {
       printf("_________\n| /      |\n|/      (_)\n|       \\|/\t\n|        |\n|\n|\n|_____\n");
    }
    else if(mistakes==7)
    {
       printf("_________\n| /      |\n|/      (_)\n|       \\|/\t\n|        |\n|       /\n|\n|_____\n");
    }
    else{
       printf("_________\n| /      |\n|/      (_)\n|       \\|/\t\n|        |\n|       / \\\n|\n|_____\n");
    }
}

int main()
{
    FILE *fp = fopen("wordlist.txt", "r");
    if(fp==NULL)
    {

        printf("File cannot be opened");
        return -1;
    }
    char c=fgetc(fp);
    int lines=0;
    while((c=fgetc(fp))!= EOF)
    {
        if(c=='\n')
        {
            lines++;
        }
    }
    lines ++;
    //in case of 10 lines, it goes from 0 to 9

    srand(time(NULL)*time(NULL));
    int num=rand()%lines;
    //printf("%d lines, random line: %d", lines, num);
    //0 to 9 can be chosen

    fclose(fp);
    FILE*pf =fopen("wordlist.txt", "r");
    char words[lines][15];
    int letters[20]={[0]=0};
    for (int i=0; i<lines; i++)
    {
        int j=0;
        while ((c=fgetc(pf))!= '\n' && c!= EOF)
        {
            if(c=='\r')
            {
                c=fgetc(fp);
                break;
            }
            words[i][j]=c;
            letters[i]++;
            j++;

        }
    }

    /*for (int i=0; i<lines; i++)
    {
        printf("\nThe %d word is: ", i);
        for(int j=0; j<letters[i]; j++)
        {
            printf("%c", words[i][j]);
        }
    }*/

    c='v';
    while(c!='x' && c!='X')
    {
        int random=rand()%lines;
        printf("\n===============================\n");
        printf("\nWELCOME TO THE HANGMAN GAME");
        printf("\nX=EXIT\tR=RULES\tP=PLAY: ");
        scanf("%c", &c);
        if(c=='r'|| c=='R'){
            printf("\nTHE RULES:\n");
            printf("There is a word of x letters, each '_' stands for 1 letter\n");
            printf("If you type letter that is not of the word, a new piece of hangman will appear.\nYou got 8 shots\nYou can miss 7 times, with 8th you lose.\nIf the hangman is completed (8 mistakes) before you find the whole word, you loose.\nIf you type a letter that IS of the word, it will appear on all correct positions and you can guess again.\nGood Luck!\n");
        }
        printf("\n=================================\n");
        //This will probably be a function
        /*printf("YOUR WORD: ");
        for (int i=0; i<letters[random]; i++)
        {
            fputc('_', stdout);
        }*/
        int cur_state[letters[random]];
        for (int x=0; x<letters[random]; x++)
        {
          cur_state[x]=0;
        }
        //cur state will be array of 0s and 1s
        //1=the letter will be shown which is at the related positon in words[random][x]
        //0=stands for '_'
        int count=0, mistakes=0;
        char a=' ';
        //count is the number of letters, which are already disclosed
        //found is the state of the CURRENT found, if he did a mistake or not
        //we cannot put them into one bcs founds is sometimes 0 although count can be alredy some bigger number
        char fails[8];
        while(count<letters[random] && mistakes<8)
        {

            printf("\nYOUR WORD: ");
            for(int x=0; x<letters[random]; x++)
            {
              if(cur_state[x]==0)
              {
                fputc('_', stdout);
              }
              else
              {
                fputc(toupper(words[random][x]), stdout);
              }
            }
            int found=0;
            printf("\nYour guess: ");
            scanf(" %c", &a);
            for (int j=0; j<letters[random];j++)
            {
                if(words[random][j]==a)
                {
                  if(cur_state[j]==0)
                  {

                    cur_state[j]=1;
                    count++;
                  }
                  found++;

                }
            }
            if(found==0)
            {
                if(ischarinarray(a, fails, mistakes))
                {
                    printf("WRONG LETTER! (You have tried this one already!) \n");
                }
                else{
                    mistakes++;
                    printf("WRONG LETTER!\n");
                    hangman(mistakes);
                    fails[mistakes-1]=a;
                }

            }
            else
            {
                printf("CORRECT LETTER!\n");
            }

        }
        if(count<=letters[random] && mistakes<8)
        {
          printf("\nGOOD JOB! YOUR WORD WAS: ");
            for(int x=0; x<letters[random]; x++)
            {
                fputc(toupper(words[random][x]), stdout);

            }
            fputc('\n', stdout);
        }
        if(mistakes==8)
        {
            printf("\nYOU LOST! THE WORD WAS: ");
            for(int x=0; x<letters[random]; x++)
            {
                fputc(toupper(words[random][x]), stdout);

            }
            fputc('\n', stdout);
        }

        printf("\nDo you want to continue? (C=CONTINUE X=END): ");
        scanf(" %c", &c);
    }
    fclose(pf);
    return 0;
}
