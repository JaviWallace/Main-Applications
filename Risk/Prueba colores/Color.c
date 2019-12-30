#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <direct.h>
#include <io.h>

int main(void)
{
    int i, j;


  for (i = 0; i < 15; i++){
    SetColor(i);
    for(j = 0; j < 40; j++)printf("%c", 219);
    puts("");
  }
  getch();
  return 0;
}

void SetColor(int ForgC)
 {
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}
