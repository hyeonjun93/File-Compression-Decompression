#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void compression(FILE *inputFile, FILE *outputFile);
void decompression(FILE *inputFile, FILE *outputFile);

int main(int argc, char *argv[])
{
  if (argc == 4)
  {
    
    //initialize other variables
    char *z = "z";
    char *d = "d";

    FILE *inputFile, *outputFile;
    int ch;
    
    //Error check
    if ((strcmp(argv[1], z) != 0) && (strcmp(argv[1], d) != 0))
    {
      printf("The inputted value is not z or d\n");
      exit(0);
    }
    //if inputted value is z or d
    else
    {
      //open file
      inputFile = fopen(argv[2], "remainder");
      
      //Error check
      if (inputFile == NULL)
      {
        printf("Cannot open the inputted file %s\n", argv[1]);
        exit(0);
      }
      //if file exist
      else
      {
        //write output file
        outputFile = fopen(argv[3], "w");
        
        //Error check
        if (outputFile == NULL)
        {
          printf("Cannot open the outputted file %s\n", argv[2]);
          exit(0);
        }
        
        //compression or decompression function
        if ((strcmp(argv[1], z)) == 0)
        {
          compression(inputFile, outputFile);
        }
        else if (strcmp(argv[1], d) == 0)
        {
          decompression(inputFile, outputFile);
        }
      }
    }
    
    //close files
    fclose(inputFile);
    fclose(outputFile);
  }
  //Error check
  else
  {
    printf("Not the correct number of command line arguments\n");
    exit(0);
  }
}

//compression function
void compression(FILE *inputFile, FILE *outputFile)
{
  //initialize variables
  int remainder, counter = 1;
  char ch, ch2;
 
  //read first character
  ch = fgetc(inputFile);
  
  while (ch != EOF)
  {
    //read 2nd character
    ch2 = fgetc(inputFile);
    
    if (ch2 == ch)
    {
      counter++;
    }
    else
    {
      if (counter == 1)
      {
        fprintf(outputFile, "%c", ch);     //print character
        counter = 1;
      }
      else if (counter == 2)
      {
        //print values
        fprintf(outputFile, "%c%c", ch, ch);
        fprintf(outputFile, "%c", 0);
        counter = 1;
      }
      else if (counter > 2 && counter < 256)
      {
        //print values
        fprintf(outputFile, "%c%c", ch, ch);
        char counter2 = counter-2;
        fprintf(outputFile, "%c", counter2);
        counter = 1;
      }
      else if (counter > 255)
      {
        //print values
        fprintf(outputFile, "%c%c", ch, ch);
        char number2 = 255;
        fprintf(outputFile, "%c", number2);
        remainder = counter - 255;       //get remainder
        
        //loop
        while (remainder > 255)
        {
          //print values
          fprintf(outputFile, "%c", number2);
          remainder -= 255;
        }
        
        if (remainder < 255)
        {
          //print values
          char remain = remainder;
          fprintf(outputFile, "%c", remain);
        }
        counter = 1; 
      }
    }
    ch = ch2;
  }

  //close files
  fclose(inputFile);
  fclose(outputFile);
}

//decompresssion function
void decompression(FILE *inputFile, FILE *outputFile)
{
  //initialize variables
  int i, counter2;
  char ch, ch2, ch3, ch4;
  
  //read first character
  ch = fgetc(inputFile);
  
  while (ch != EOF)
  {
    //read 2nd character
    ch2 = fgetc(inputFile);

    //if repeat
    if (ch2 == ch)
    {
      //read third character
      ch3 = fgetc(inputFile);
      int counter = ch3;      //convert to decimal value
      
      while (counter == 255)
      {
        for (i = 0; i < 255; i++)
        {
          fprintf(outputFile, "%c", ch2);
        }
        ch4 = fgetc(inputFile);
        counter = ch4;
      }
      
      if (counter < 255)
      {
        for (i = 0; i <= counter; i++)
        {
          fprintf(outputFile, "%c", ch2);
        }
      }
    }
    //if no repeat
    else if (ch2 != ch)
    {
      //print values
      fprintf(outputFile, "%c", ch);
    }
    ch = ch2;
  }

  //close files
  fclose(inputFile);
  fclose(outputFile);
}
