#include <stdio.h>
#include <string.h>

void ask_yes_or_no() 
{
  char answer[4];
  printf("Answer yes or no: ");
  scanf("%s", answer);
  
  if (strcmp(answer, "yes") == 0) {
    printf("Alright.\n");
  } else if (strcmp(answer, "no") == 0) {
    printf("Sure.\n");
  } else {
    printf("You must answer yes or no.\n");
    ask_yes_or_no();
  }
}

int main()
{
  ask_yes_or_no();
  return 0;
}
