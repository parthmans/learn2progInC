#include "input.h"
#include <string.h>


// this function will take in two characters and check if the first is a valid value and the second a valid suit.
// if they are both valid it will return 10, if the first is the charcter '?' then the function will check if the second
// is a valid number( between 0 and 9) and will return it. if anything else, the function will return -1 
int checkEntry(char v, char s){
  int val=0, su=0;
  for(int i=2; i<=9; i++){
    if(v=='0'+i){ val++;}
  }
  if(v=='0'){
    val++;
  }
  if(v=='J'){ val++;}
  if(v=='Q'){ val++;}
  if(v=='K'){ val++;}
  if(v=='A'){ val++;}
  if(v=='?'){ val = 5;}
  if(s=='s'){ su++;}
  if(s=='h'){ su++;}
  if(s=='d'){ su++;}
  if(s=='c'){ su++;}

  if((val==1)&&(su==1)){ return 10;}
  else if((val==5)&&(su==0)){
    for(int j=0; j<10; j++){
      if(s=='0'+j){ return j;}
    }
  }
  return -1;
}


deck_t * hand_from_string(const char * str, future_cards_t * fc){
  if((str ==NULL)||(strlen(str)==0)){
    perror("ther is no character in this line\n");
    exit(EXIT_FAILURE);
  }
  deck_t *deck = calloc(1, sizeof(*deck));
  deck->n_cards = 0;
  deck->cards = NULL;
  int i=0, count=0; // count will help us count the number of cards we have in the hand
  while((str[i]!='\n')&&(str[i]!='\0')){
    while(str[i]==' '){
      i++;
    }
    if(i+1>=strlen(str)){
	goto label;
      }
    if(checkEntry(str[i], str[i+1])==10){
       card_t c = card_from_letters(str[i], str[i+1]);
       add_card_to(deck, c);
       count++;
    }
    else if(checkEntry(str[i], str[i+1])>=0){
      card_t *card = add_empty_card(deck);
      add_future_card(fc, checkEntry(str[i], str[i+1]), card);
      printf("%s, the current character is %c\n", str, str[i]);
    }
    else{ perror(" wrong cards\n"); exit(EXIT_FAILURE);}
    if(i>=strlen(str)){
      goto label;
    }
    i+=2;
  }
 label: if(count<5){
    perror("This line has less than 5 cards\n");
    exit(EXIT_FAILURE);
  }
  return deck;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){
  if(f==NULL){
    perror("The file is not open\n");
  }
  deck_t **deckArray = NULL;
  deckArray = realloc(deckArray, sizeof(*deckArray));
  *n_hands = 0;
  char *line=NULL;
  size_t x=0;
  while(getline(&line, &x, f)>0){
    deckArray = realloc(deckArray, (*n_hands + 1)*sizeof(*deckArray));
    size_t t = *(n_hands);
    deckArray[t] = hand_from_string(line, fc);
    *n_hands +=1;
  }
  free(line);
  return deckArray;
}
