#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include "memlog.h" 
#include "msgassert.h" 
#include "Vector.hpp"
#include "List.hpp"
#include "Card.hpp"
#include "Player.hpp"
#include "Match.hpp"
#include "Game.hpp"

#define DEFAULT_INPUT_FILE "./entrada.txt"
#define DEFAULT_OUTPUT_FILE "./saida.txt"

struct ConfigStruct {
  bool regmem;
  char logname[100];
};

ConfigStruct config;

/**
 * @brief Function responsible to print to user a informative menu.
 */
void menu() {
  fprintf(stderr,"Poker Game\n");
  fprintf(stderr,"-p filename \t\t(output file to register memory access)\n");
  fprintf(stderr,"-l \t\t(register memory access)\n");
}

/**
 * @brief Function responsible to read run time parameters and set config values.
 * 
 * @param argc Number of run time parameters.
 * @param argv Array with run time parameters.
 */
void parse_args(int argc, char ** argv) {
  extern char * optarg;

  int c;

  config.regmem = false;
  config.logname[0] = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "p:lh")) != EOF)
    switch(c) {
      case 'p': 
        strcpy(config.logname, optarg);
        break;
      case 'l': 
        config.regmem = true;
        break;
      default:
        menu();
        exit(1);
        break;
    }
}

/**
 * @brief Factory: Responsible for creating a Vector of Cards with the size of 5, 
 * reading the values from an input file. By the end, a pointer to this Vector is returned.
 * 
 * @param inputFile A reference to an input file of ifstream type, to read the cards info.
 * @param buffer String used to store the value being currently read from the input file.
 * @param id Id of the Card being created, it is only used for memory usage analysis purpose.
 * 
 * @return Returns a pointer to a Vector of Cards with the size of 5, with the read values from the input file.
 */
Vector<Card>* handOfCardsFactory(std::ifstream &inputFile, std::string buffer, int id) {
  Vector<Card> *playerHand = new Vector<Card>(HAND_DEFAULT_SIZE);

  for (int k = 0; k < HAND_DEFAULT_SIZE; k++) {
    std::string cardSpecification;
    inputFile >> cardSpecification;
    
    char cardSuit = toupper(cardSpecification.back());
    cardSpecification.pop_back();

    int cardNumber = stoi(cardSpecification);
    //Necessary to assure that the Ace Card is the biggest one
    if(cardNumber == 1)
      cardNumber = 14;

    Card currentCard = Card(cardNumber, cardSuit, id);
    playerHand->setElement(k, currentCard);
  }
  
  playerHand->sortVector();

  return playerHand;
}

/**
 * @brief Factory: Responsible for acquiring a Player instance, reading the needed values from an input file. 
 * By the end, a pointer to this instance is returned.
 * 
 * @param inputFile A reference to an input file of ifstream type, to read the cards info.
 * @param masterGame A pointer to the game where the player is in.
 * @param initialPlayerMoneyAmount The initial money amount for the created player.
 * @param buffer String used to store the value being currently read from the input file.
 * @param id Id of the Player and Cards being created, it is only used for memory usage analysis purpose.
 * 
 * @return Returns a pointer to the acquired Player instance.
 */
Player* playerFactory(std::ifstream &inputFile, Game* masterGame, int initialPlayerMoneyAmount, std::string buffer, int id) {
  std::string name;
  int betValue;

  inputFile >> buffer;
  while (!std::isdigit(buffer[0])) {
    name.append(buffer);
    name.append(" ");
    inputFile >> buffer;
  }
  name.pop_back();

  betValue = stoi(buffer);

  Vector<Card> *playerHand = handOfCardsFactory(inputFile, buffer, id);

  Player *currentPlayer = masterGame->retrievePlayerInstance(name, initialPlayerMoneyAmount, betValue, playerHand, id);

  return currentPlayer;
}

/**
 * @brief Factory: Responsible for creating a Match instance, reading the needed values from an input file. 
 * By the end, a pointer to this instance is returned.
 * 
 * @param inputFile A reference to an input file of ifstream type, to read the cards info.
 * @param masterGame A pointer to the game where the match is in.
 * @param initialPlayerMoneyAmount The initial money amount for the match players.
 * @param buffer String used to store the value being currently read from the input file.
 * 
 * @return Returns a pointer to the created Match instance.
 */
Match matchFactory(std::ifstream &inputFile, std::ofstream &outFile, Game* masterGame, int initialPlayerMoneyAmount, std::string buffer) {
  int numberOfPlayers, minimumAmountToPlay;

  inputFile >> buffer;
  numberOfPlayers = stoi(buffer);
  inputFile >> buffer;
  minimumAmountToPlay = stoi(buffer);

  Match currentMatch = Match(numberOfPlayers, minimumAmountToPlay);

  for (int j = 0; j < numberOfPlayers; j++) {
    Player *currentPlayer = playerFactory(inputFile, masterGame, initialPlayerMoneyAmount, buffer, currentMatch.id);
    currentMatch.addPlayerToMatch(currentPlayer);
  }

  bool isChargeOperationValid;
  masterGame->chargeTheMinimunAmountToPlay(minimumAmountToPlay, isChargeOperationValid);
  if(isChargeOperationValid) {
    bool isGetMatchRestultValid;
    currentMatch.getMatchResult(masterGame->inGamePlayers->length(), isGetMatchRestultValid, outFile);  

    if(isGetMatchRestultValid) {
      if(config.regmem) currentMatch.printMatch();
    } else {
      masterGame->giveBackTheMinimunAmountToPlay(minimumAmountToPlay);
      outFile << "0 0 I" << std::endl;
    }
  } else
    outFile << "0 0 I" << std::endl;
  

  return currentMatch;
}

/**
 * @brief Function responsible for iterating over the players in the game and printing 
 * their names followed by the accumulated money amount on the output file.
 *
 * @param outFile A reference to an output file of ofstream type, to print the game result.
 * @param masterGame A pointer to the game (global context).
 */
void printGameResult(std::ofstream &outFile, Game* masterGame) {
  outFile << "####" << std::endl;

  Match firstMatch = masterGame->inGameMatches->getElement(0);
  errorAssert(firstMatch.inMatchPlayers->length() == masterGame->inGamePlayers->length(), "Not all game players have participated in first match");
  firstMatch.inMatchPlayers->sortVectorDesc();

  Player* it;
  for (int i = 0; i < firstMatch.inMatchPlayers->length(); i++) {
    it = firstMatch.inMatchPlayers->getElement(i);
    outFile << it->getName() << " " << it->getMoney() << std::endl;
  }  
}

/**
 * @brief Orchestrator: Function responsible for orchestrating the Poker game process, 
 * calling the pertinent methods, and opening the input and output files.
 */
void runGameOrchestrator() {
  std::ifstream inputFile(DEFAULT_INPUT_FILE);
  errorAssert(inputFile.is_open(), "\nFailed to open input file");
  std::ofstream outFile(DEFAULT_OUTPUT_FILE);
  errorAssert(outFile.is_open(), "\nFailed to open output file");

  std::string buffer;

  int numberOfMatches, initialPlayerMoneyAmount;
  inputFile >> buffer;
  numberOfMatches = stoi(buffer);
  inputFile >> buffer;
  initialPlayerMoneyAmount = stoi(buffer);

  Game *masterGame = new Game(numberOfMatches);

  for (int i = 0; i < numberOfMatches; i++) {
    Match currentMatch = matchFactory(inputFile, outFile, masterGame, initialPlayerMoneyAmount, buffer);
    masterGame->addMatchToGame(currentMatch);
  }

  printGameResult(outFile, masterGame);

  outFile.close();
  inputFile.close();

  warnAssert(!inputFile.is_open(), "\nFailed to close input file");
  warnAssert(!outFile.is_open(), "\nFailed to close output file");
}

/**
 * @brief Main Function: Responsible for initializing the MemLog lib depending on the run-time 
 * parameters and calling the game orchestrator function.
 * @param argc Number of run time parameters.
 * @param argv Array with run time parameters.
 */
int main(int argc, char ** argv) {
  parse_args(argc,argv);

  startMemLog(config.logname);

  if (config.regmem) 
    activateMemLog();
  else 
    deactivateMemLog();

  runGameOrchestrator();

  return endUpMemLog();
}