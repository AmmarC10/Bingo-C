

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

int main(int argc, char *argv[])
{

  // FILES
  // Checking for file errors

  FILE *f1;

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s seed file\n", argv[0]);
    exit(1);
  }
  //

  if (((f1 = fopen(argv[2], "r")) == NULL))
  {
    fprintf(stderr, "%s is nonexistent or unreadable\n", argv[2]);
    exit(3);
  }

  //SEED
  //Initalizing seed and checking seed format
  char *seedinput = argv[1];
  int seed = atoi(seedinput);

  srand(seed);

  //Checking to see if seed is not digit
  if (!isdigit(*seedinput))
  {
    printf("Error");
    fprintf(stderr, "Expected integer seed, but got %s\n", argv[1]);
    exit(2);
  }

  // CALLIST
  // Using List ADT for callList
  int number;
  int min = 1, max = 75;

  List callList;
  init(&callList);

  void generateCallList(int count)
  {

    for (int i = 0; i < count; i++)
    {

      number = (rand() % (max - min + 1)) + min;

      if (!check(callList, number)) //check if the number doesn't already exist in callList
      {
        add(&callList, number);
        count = 0;
      }
    }
  }

  // MATRIX
  // Generating the matrix, checking for matrix errors, printing matrix

  int mat[5][5], i, j;
  int row = 5;
  int col = 5;
  int lineCount = 0;
  char c;

  void generateMatrix()
  {
    while (!feof(f1))
    {

      for (i = 0; i < row; i++)
      {
        for (j = 0; j < col; j++)
        {
          fscanf(f1, "%02d", &mat[i][j]);
        }
      }

      rewind(f1);

      // CARD FORMATTING ERRORS
      // checking for alpha
      for (c = getc(f1); c != EOF; c = getc(f1))
      {
        if (c == '\n')
        {
          lineCount++;
        }
        if (isalpha(c))
        {
          fprintf(stderr, "%s has bad format\n", argv[2]);
          exit(4);
        }
      }
      // check linecount
      if (lineCount > 5)
      {
        fprintf(stderr, "%s has bad format\n", argv[2]);
        exit(4);
      }

      // check num ranges
      for (int i = 0; i < 5; i++)
      {
        for (int j = 0; j < 5; j++)
        {
          if (mat[i][j] < 0)
          {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
          }
          if (j == 0 && mat[i][j] > 15)
          {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
          }
          if (j == 1 && mat[i][j] > 30)
          {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
          }
          if (j == 2 && mat[i][j] > 45)
          {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
          }
          if (j == 3 && mat[i][j] > 60)
          {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
          }
          if (j == 4 && mat[i][j] > 75)
          {
            fprintf(stderr, "%s has bad format\n", argv[2]);
            exit(4);
          }
        }
      }
    }

    fclose(f1);
  }

  // Checking duplicates in matrix
  void checkDupes()
  {
    int mat2[25];
    int ctr = 0;
    for (int c = 0; c < 5; c++)
    {
      for (int i = 0; i < 5; i++)
      {
        mat2[ctr] = mat[c][i];
        ctr++;
      }
    }

    for (int c = 0; c < 25; c++)
    {
      int check = mat2[c];
      for (int i = c + 1; i < 25; i++)
      {
        if (check == mat2[i])
        {
          fprintf(stderr, "%s has bad format\n", argv[2]);
          exit(4);
        }
      }
    }
  }

  void printMatrix(int mat[row][col])
  {
    printf("\n");
    printf("L   I   N   U   X");
    for (i = 0; i < row; i++)
    {
      printf("\n");
      for (j = 0; j < col; j++)
      {
        if (check(callList, mat[i][j]) && mat[i][j] < 10)
        {
          printf("%02dm ", mat[i][j]);
        }
        else if (check(callList, mat[i][j]))
        {
          printf("%02dm ", mat[i][j]);
        }
        else if (i == 2 && j == 2)
        {
          printf("00m ");
        }
        else if (mat[i][j] < 10)
        {
          printf("%02d  ", mat[i][j]);
        }
        else
        {
          printf("%2d  ", mat[i][j]);
        }
      }
    }
    printf("\n");
  }

  // Checking to see if winner
  void checkRow(int mat[][5])
  {
    for (int i = 0; i < 5; i++)
    {
      if (check(callList, mat[i][0]) && check(callList, mat[i][1]) && (check(callList, mat[i][2])) && check(callList, mat[i][3]) && check(callList, mat[i][4]))
      {
        printf("WINNER\n");
        exit(0);
      }
    }
  }

  void checkCol(int mat[][5])
  {
    for (int j = 0; j < 5; j++)
    {
      if (check(callList, mat[0][j]) && check(callList, mat[1][j]) && (check(callList, mat[2][j])) && check(callList, mat[3][j]) && check(callList, mat[4][j]))
      {
        printf("WINNER\n");
        exit(0);
      }
    }
  }

  void checkCorners(int mat[5][5])
  {
    if (check(callList, mat[0][0]) && check(callList, mat[0][4]) && check(callList, mat[4][0]) && check(callList, mat[4][4]))
    {
      printf("WINNER\n");
      exit(0);
    }
  }

  system("clear");

  // MAIN LOOP
  char userInput;
  generateMatrix();
  checkDupes();
  int count = 0;
  while (userInput != 'q')
  {

    // Call List
    printf("CallList: ");

    if (userInput == '\n')
    {
      system("clear");
      print(callList.head);
    }
    else if (userInput == 'q')
    {
      exit(0);
    }
    else
    {
      generateCallList(count);
      system("clear");
      print(callList.head);
    }

    // Matrix
    printf("\n");
    printMatrix(mat);

    // Checking
    checkCorners(mat);
    checkRow(mat);
    checkCol(mat);

    // Input
    printf("enter any non-enter key for Call (q to quit): ");
    fflush(stdout); //prevent repeat printf
    userInput = getchar();

    count++;
    system("clear");
  }

  return (0);
}
