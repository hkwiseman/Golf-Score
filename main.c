#include <stdio.h>

// A function to determine the difficulty of each hole based off the avergae over/under par
void difficulty(int par[18], int strokes[4][18], float Diff[18][2])
  {
      int x, y;
      float avg[18] = {0}, subAvg[18] = {0}, temp[1][2];

     // Calculating the difficulty
      for (x = 0; x < 18; x++){
         for (y = 0; y < 4; y++)
            subAvg[x] += strokes[y][x];
         avg[x] = (subAvg[x] / 4);
         Diff[x][0] = x + 1;
         Diff[x][1] = (avg[x] - par[x]);
}
     // Sorting the holes by difficulty for output
     for (x = 0; x < 18; x++){
         for (y = 0; y < 18 - x; y++) {
             if (Diff[y][1] < Diff[y+1][1])
               {
                   temp[1][0] = Diff[y][0];
                   temp[1][1] = Diff[y][1];
                   Diff[y][0] = Diff[y+1][0];
                   Diff[y][1] = Diff[y+1][1];
                   Diff[y+1][0] = temp[1][0];
                   Diff[y+1][1] = temp[1][1];
              }
         }
     }
}

// A function to determine the subtotal score from the front and back nine 
int subTotal(int a, int strokes[4][18])
 {
    int frontScore[4][1] = {0}, x;
    //for (y = 0; y < 4; y++) {

       for (x = 0; x < 9; x++)
          frontScore[a][0] += strokes[a][x];
       return frontScore[a][0];


    return 0;
}


int main (void)

{
   // Declaring and initializing variables
   int par[18], lowest, subtotal[4], backtotal[4], strokes[4][18], totalPar = 0;
   int winner = 0, totalScore[4] = {0};
   float Diff[18][2];
   char names[4][16];
   int a, b, c;

   // Reading in values for par score, player names, and player scores
   for (a = 0; a < 18; a++)
      scanf("%i", &par[a]);

   for (a = 0; a < 4; a++)
      scanf("%s", names[a]);

   for (a = 0; a < 18; a++){
      for (b = 0; b < 4; b++)
         scanf("%i", &strokes[b][a]);
   }

   // Calculating total par score and total score of players for output later
   for (a = 0; a < 18; a++)
       totalPar += par[a];

   for (a = 0; a < 18; a++){
      for (b = 0; b < 4; b++)
         totalScore[b] += strokes[b][a];
   }

   // Determining winner
   lowest = totalScore[0];
   for (a = 0; a < 3; a++)
      if (lowest > totalScore[a]){
         lowest = totalScore[a];
         winner = a;
      }

   // Outputting names/scores & calling function to output subtotal scores from front and back nine
   printf("\n");
   for (a = 0; a < 4; a++) {
      printf("%-16s %i", names[a], totalScore[a]);
      subtotal[a] = subTotal(a, strokes);
      backtotal[a] = totalScore[a] - subtotal[a];
      printf(" (%i - %i)\n", subtotal[a], backtotal[a]);

   }

   // Outputting winner with score
   if (lowest - totalPar > 0)
      printf("\n%s is the winner with a score of +%i\n\n", names[winner], lowest - totalPar);
   else
      printf("\n%s is the winner with a score of %i\n\n", names[winner], lowest - totalPar);

   // Formatting and outputting a full scorecard   
   printf("\n");
   for (a = 0; a < 95; a++)
      printf("-");

   printf("\nHole #");

   for (a = 0; a < 10; a++)
      printf(" ");

   for (a = 0; a < 18; a++)
      printf("%4i", a+1);

   printf(" Score\n");

   for (a = 0; a < 95; a++)
      printf("-");

   printf("\nPar");

   for (a = 0; a < 13; a++)
      printf(" ");

   for (a = 0; a < 18; a++)
      printf("%4i", par[a]);

   printf("%4i\n", totalPar);
   for (a = 0; a < 95; a++)
      printf("-");

   // Output of names and scores for scorecard
   for (a = 0; a < 4; a++){
      printf("\n%-16s", names[a]);
      for (b = 0; b < 18; b++) {
            printf("%4i", strokes[a][b]);
      }
      printf("%4i", totalScore[a]);
   }

   // Final formatting for scorecard
   printf("\n");
   for (a = 0; a < 95; a++)
      printf("-");

   printf("\n\n\n");


   // Calling function to output a list of the hole difficulty from hardest to easiest
   difficulty(par, strokes, Diff);
   printf("Hole   Average strokes under/over par\n");
   for (a = 0; a < 18; a++) {
       printf("%2.0f", Diff[a][0]);
       printf("%18.2f\n", Diff[a][1]);
   }

   printf("\n");

   return 0;
}
