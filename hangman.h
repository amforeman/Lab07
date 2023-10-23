/*
 * File: hangman.h
 *--------------------------
 * This file defines the hangman class and evil hangman subclass.
 */

#ifndef _hangman_h
#define _hangman_h

#include <string>
#include <vector>

/*
 * Class: Hangman
 * ----------------------
 * This class contains variables and functions to play a fair game of hangman.
 * An external dictionary is used to populate the words the computer may choose.
 * The user is given a certain amount of guesses, and must guess individual 
 * letters until the word is correctly guessed or their number of guesses run out.
 */
class Hangman {

  /* Member variables */
  // integer representing the number of guesses the user has used
  int numberOfGuesses;
  // integer representing the number of guesses the user is allotted
  int numberOfAllowedGuesses;
  // string representing the word the user must guess
  std::string targetWord;
  // string representing the correct placement of letters the user has guessed
  std::string displayString;
  // int representing the length of the target word
  int lengthOfWord;
  // vector of all possible words in the dictionary
  std::vector<std::string> dictionary;

  /*
   * Method: chooseWord
   * Usage: string word = chooseWord();
   * -----------------------------------
   * Chooses a random word from the dictionary.
   */
  std::string chooseWord();

  /*
   * Method: displayBoard
   * ---------------------------------------
   * Displays the updated display string.
   */
  void displayBoard();

  /*
   * Method: handleInput
   * ------------------------------------
   * Prompts and handles the user input and calls the updateBoard function.
   */
  void handleInput();

  /*
   * Method: updateBoard
   * ------------------------------
   * Calls the revealWord function to check guess correctness and updates
   * the guess count and display string accordingly.
   */
  void updateBoard(char c);

  /*
   * Method: checkState
   * -----------------------------------------
   * Returns an integer representing the status of the game: in play, player win,
   * or player lose.
   */
  int checkState();

  /*
   * Method: turn 
   * ------------------
   * Goes through the game until the player wins or loses.
   */
  void turn();

  /*
   * Method: revealWord 
   * -----------------------
   * Hangman implementation simply checks if the word contains the guessed
   * letter. It returns true if the letter is in the target word does and 
   * false if it isn't.
   */
  virtual bool revealWord(char c);
  

 public:

  /*
   * Constructor
   * ---------------------------------
   * Initializes a hangman object, reading the dictionary and calling 
   * chooseWord to initialize the target word.  No input is taken.
   */
  Hangman();

  /*
   * Deconstructor
   * --------------------
   * Empty
   */
  ~Hangman(){};
  
  /*
   * Methods: Setters and getters for private variables
   * -----------------------------------------------------
   * Setters set the variables to specified input.
   * Getters return the values stored in the variables.
   */
  std::string getDisplayString();
  void setTargetWord(std::string s);
  std::string getTargetWord();
  void setDisplayString(std::string s);
  int getWordLength();
  void setWordLength(int i);
  void setNumberOfGuesses(int i);
  int getNumberOfGuesses();
  void setNumberOfAllowedGuesses(int i);
  int getNumberOfAllowedGuesses();

  /*
   * Method: play()
   * -----------------
   * Displays a welcome and instructions for hangman. The turn method is called
   * to begin gameplay
   */
  void play(); 
};

/*
 * Subclass: EvilHangman
 * ---------------------------
 * The evil hangman subclass plays an unfair game of hangman. As the user 
 * guesses, evil hangman separates the possible words into word families and
 * chooses the word family with the most possibilities as the new "target word".
 */
class EvilHangman : public Hangman {

  /* vector of possible words that the computer can choose based on the length
  of the word and the guesses the user has made  */
  std::vector<std::string> possibleWords;
  // bool representing whether the user wants to see the list of possible words
  bool wordListOn;

public:

  /*
   * Method: revealWord
   * ----------------------------
   * Overrides the Hangman implementation, checking the list of possible words
   * against the user's guess. From this, a map of word families are created.
   * The largest word family is then set at the vector of possible words. If
   * If the largest family does not include the user's guess, the function 
   * returns false. If it does, the function returns true.
   */
  bool revealWord(char c) override;

  /*
   * Constructor: EvilHangman
   * -----------------------------
   * Initializes an evil hangman object, setting the length of the word, number
   * of guesses, and display of possible word list to the user's input if 
   * specififed. If not, the length initializes to 4, number of guesses to 8, 
   * and the possible word list will not be displayed.
   */
  EvilHangman();
  EvilHangman(int length, int guesses, bool list);
  ~EvilHangman(){};

  /*
   * Method: setPossibleWords
   * ------------------------------
   * Sets the vector of possible words to the given input
   */
  void setPossibleWords(std::vector<std::string>);
};

#endif
