#include "hangman.h"
#include <iostream>

int main() {

  /* Regular Hangman */
  // Hangman hm;
  // hm.play();

  /* Evil Hangman with user input */
  int length = 0;
  while (length < 2 || length == 26 || length == 27 || length > 29) {
    std::cout<<"Enter the length of the word you would like to guess: "<<std::endl;
    std::cin>>length;
  }

  int guesses = 0;
  std::cout<<"How many guesses would you like?"<<std::endl;
  std::cin>>guesses;
  if (guesses < 1) {
    std::cout<<"Invalid input. Default of 8 guesses given."<<std::endl;
    guesses = 8;
  }

  char answer = 'n';
  std::cout<<"Would you like to know the number of words remaining in the word list? (y/n)"<<std::endl;
  std::cin>>answer;

  if (answer == 'y') {
    EvilHangman eh(length, guesses, true);
    eh.play();
  }
  else {
    EvilHangman eh(length, guesses, false);
    eh.play();
  }

  /* Defualt Evil Hangman */
  //EvilHangman eh;
  //eh.play();
}
