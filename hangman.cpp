#include "hangman.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

std::string Hangman::chooseWord() {
  std::srand(time(NULL));
  int randomIndex = std::rand() % dictionary.size();
  // randomly choose word in dictionary
  std::string word = dictionary[randomIndex];
  return word;
}

void Hangman::displayBoard() {
  std::cout<<"The word now looks like this: "<<getDisplayString()<<std::endl;
}

void Hangman::handleInput() {
  char guess;
  std::cout<<"Guess a letter: "<<std::endl;
  std::cin>>guess;
  
  updateBoard(guess);
}

void Hangman::updateBoard(char c) {
  bool correctGuess = revealWord(c);

  if (!correctGuess) {
    //increase number of guesses used
    numberOfGuesses++;
    std::cout<<"Sorry, that guess was incorrect."<<std::endl;
  }
  else {
    std::cout<<"That guess was correct!"<<std::endl;
    for (int i = 0; i < lengthOfWord; i++) {
      if (targetWord[i] == c) {
	// update display string with correct placement of letter guess
	displayString[i] = c;
      }
    }
  }
  //display updated string
  displayBoard();
  //display updated guess count
  std::cout<<"Number of guesses: "<<numberOfGuesses<<"/"<<numberOfAllowedGuesses<<std::endl;
}

int Hangman::checkState() {
  if (numberOfGuesses == numberOfAllowedGuesses) {
    std::cout<<"You lost. The word was: "<<targetWord<<std::endl;
    //game over
    return 0;
  }
  if (displayString == targetWord) {
    std::cout<<"You won. You guessed the word: "<<targetWord<<std::endl;
    //game over
    return 0;
  }
  // continue playing
  return 1;
}

void Hangman::turn() {
  handleInput();
  int status = checkState();
  if (status == 0) {
    return;
  }
  else {
    turn();
  }
}

bool Hangman::revealWord(char c) {
  for (int i = 0; i < lengthOfWord; i++) {
    if (targetWord[i] == c) {
      // input is in target word
      return true;
    }
    else {
      continue;
    }
  }
  // input not in target word
  return false;
}

Hangman::Hangman() {
  //read dictionary file
  std::ifstream dictionaryFile;
  std::vector<std::string> dict;
  std::string dictWord;
  dictionaryFile.open("dictionary.txt", std::ios::in);
  dictionaryFile>>dictWord;
  while(!dictionaryFile.eof()) {
    dict.push_back(dictWord);
    dictionaryFile>>dictWord;
  }
  dictionaryFile.close();
  this->dictionary = dict;
  this->numberOfGuesses = 0;
  this->numberOfAllowedGuesses = 8;
  this->targetWord = chooseWord();
  for (int i = 0; i < targetWord.length(); i++) {
    this->displayString+="_";
  }
  this->lengthOfWord = targetWord.length();
}

std::string Hangman::getDisplayString() {
  return this->displayString;
}

void Hangman::setTargetWord(std::string s) {
  this->targetWord = s;
}

std::string Hangman::getTargetWord() {
  return this->targetWord;
}

void Hangman::setDisplayString(std::string s) {
  this->displayString = s;
}

int Hangman::getWordLength() {
  return this->lengthOfWord;
}

void Hangman::setWordLength(int i) {
  this->lengthOfWord = i;
}

void Hangman::setNumberOfGuesses(int i) {
  this->numberOfGuesses = i;
}

int Hangman::getNumberOfGuesses() {
  return this->numberOfGuesses;
}

void Hangman::setNumberOfAllowedGuesses(int i) {
  this->numberOfAllowedGuesses = i;
}

int Hangman::getNumberOfAllowedGuesses() {
  return this->numberOfAllowedGuesses;
}

void Hangman::play() {
  std::cout<<"Welcome to hangman!"<<std::endl;
  std::cout<<"I have a word in mind. On each turn you will guess a letter. If the letter is correct, I will show you where it appears in the word. If your letter is incorrect, you lose a guess and a part of your body gets strung to the scaffold. The object is to guess the word before you are hung."<<std::endl;
  std::cout<<"You have "<<getNumberOfAllowedGuesses()<<" guesses."<<std::endl;
  displayBoard();
  turn();
}

// Default constructor
EvilHangman::EvilHangman() {
  setWordLength(4);
  std::ifstream dictionaryFile;
  std::vector<std::string> dict;
  std::string dictWord;
  dictionaryFile.open("dictionary.txt", std::ios::in);
  dictionaryFile>>dictWord;
  while(!dictionaryFile.eof()) {
    dict.push_back(dictWord);
    dictionaryFile>>dictWord;
  }
  dictionaryFile.close();
  
  for (int i = 0; i < dict.size(); i++) {
    if (dict[i].length() == getWordLength()) {
      this->possibleWords.push_back(dict[i]);
    }
  }
  setTargetWord(possibleWords[0]);
  setDisplayString("");
  for (int i = 0; i < getWordLength(); i++) {
    setDisplayString(getDisplayString()+="_");
  }
  setNumberOfAllowedGuesses(8);
  this->wordListOn = false;
}

// Constructor with input for word length, number of guesses, and display of word list
EvilHangman::EvilHangman(int length, int guesses, bool list) {
  std::ifstream dictionaryFile;
  std::vector<std::string> dict;
  std::string dictWord;
  dictionaryFile.open("dictionary.txt", std::ios::in);
  dictionaryFile>>dictWord;
  while(!dictionaryFile.eof()) {
    dict.push_back(dictWord);
    dictionaryFile>>dictWord;
  }
  dictionaryFile.close();
  
  for (int i = 0; i < dict.size(); i++) {
    if (dict[i].length() == length) {
      this->possibleWords.push_back(dict[i]);
    }
  }
  
  setTargetWord(possibleWords[0]);
  setDisplayString("");
  for (int i = 0; i < length; i++) {
    setDisplayString(getDisplayString()+="_");
  }
  setNumberOfAllowedGuesses(guesses);
  this->wordListOn = list;
}

bool EvilHangman::revealWord(char c) {
  /*
   * Map of word families. The key is a string that represents where the user's
   * guess appears in the word. The value is a vector of all words in the 
   * possible word list that match the frequency and placement of the letter.
   */
  std::unordered_map<std::string, std::vector<std::string>> wordFamilies;

  //empty string to build keys from
  std::string emptyString = "";
  for (int i = 0; i < getWordLength(); i++){
    emptyString+="_";
  }

  //finding the index of the letter in each word, if it exists
  for (int j = 0; j < possibleWords.size(); j++) {
    std::vector<int> letterIndex = {};
    std::string word = possibleWords[j];
    for (int k = 0; k < word.length(); k++) {
      if (word[k] == c) {
	letterIndex.push_back(k);
      }
    }

    //adding the word to the correct word family
    if (letterIndex.size() == 1) {
      std::string singleLetter = emptyString;
      singleLetter[letterIndex[0]] = c;
      wordFamilies[singleLetter].push_back(word);
    }
    else if (letterIndex.size() > 1) {
      std::string multipleLetter = emptyString;
      for (int l = 0; l < letterIndex.size(); l++) {
	multipleLetter[letterIndex[l]] = c;
      }
      wordFamilies[multipleLetter].push_back(word);
    }
    else {
      wordFamilies[emptyString].push_back(word);
    }
  }
  
  // finding the largest word family
  std::vector<std::string> largestFamily = {};
  int i = 1;
  for (auto family : wordFamilies) {
    std::vector<std::string> current = family.second;
    if (current.size() > largestFamily.size()) {
      largestFamily = current;
    }
    i++;
  }
  // set possible words vector to the larget word family, throwing out the words that don't match the family
  setPossibleWords(largestFamily);
  // set a new target word
  setTargetWord(possibleWords[0]);
  //display list if user requested
  if (wordListOn == true) {
    std::cout<<"Words left in list: "<<possibleWords.size()<<std::endl;
    for (int i = 0; i < possibleWords.size(); i++) {
      std::cout<<possibleWords[i]<<std::endl;
    }
  }
  
  //if the user's guess is in the new target word, return true
  std::string newTarget = getTargetWord();
  for (int n = 0; n < getWordLength(); n++) {
    if (newTarget[n] == c) {
      return true;
    }
  }
  // return false otherwise
  return false;
}

void EvilHangman::setPossibleWords(std::vector<std::string> vec) {
  this->possibleWords = vec;
}

