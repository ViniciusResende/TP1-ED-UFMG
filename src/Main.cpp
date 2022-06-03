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

#define DEFAULT_INPUT_FILE "../assets/entrada.txt"
#define DEFAULT_OUTPUT_FILE "../assets/saida.txt"

struct ConfigStruct {
  bool regmem;
  char logname[100];
};

ConfigStruct config;

void menu() {
  fprintf(stderr,"Poker Game\n");
  fprintf(stderr,"-p filename \t\t(output file to register memory access)\n");
  fprintf(stderr,"-l \t\t(register memory access)\n");
}


void parse_args(int argc,char ** argv) {
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

Vector<Card>* handOfCardsFactory(std::ifstream &inputFile, std::string buffer) {
  Vector<Card> *playerHand = new Vector<Card>(HAND_DEFAULT_SIZE);

  for (int k = 0; k < HAND_DEFAULT_SIZE; k++) {
    std::string cardSpecification;
    inputFile >> cardSpecification;
    
    char cardSuit = toupper(cardSpecification.back());
    cardSpecification.pop_back();

    int cardNumber = stoi(cardSpecification);

    Card currentCard = Card(cardNumber, cardSuit);
    playerHand->setElement(k, currentCard);
  }
  
  playerHand->sortVector();

  return playerHand;
}

Player* playerFactory(std::ifstream &inputFile, Game* masterGame, int initialPlayerMoneyAmount, std::string buffer) {
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

  Vector<Card> *playerHand = handOfCardsFactory(inputFile, buffer);

  Player *currentPlayer = masterGame->retrievePlayerInstance(name, initialPlayerMoneyAmount, betValue, playerHand);

  return currentPlayer;
}

Match matchFactory(std::ifstream &inputFile, std::ofstream &outFile, Game* masterGame, int initialPlayerMoneyAmount, std::string buffer) {
  int numberOfPlayers, minimumAmountToPlay;

  inputFile >> buffer;
  numberOfPlayers = stoi(buffer);
  inputFile >> buffer;
  minimumAmountToPlay = stoi(buffer);

  Match currentMatch = Match(numberOfPlayers, minimumAmountToPlay);

  for (int j = 0; j < numberOfPlayers; j++) {
    Player *currentPlayer = playerFactory(inputFile, masterGame, initialPlayerMoneyAmount, buffer);
    currentMatch.addPlayerToMatch(currentPlayer);
  }

  masterGame->chargeTheMinimunAmountToPlay(minimumAmountToPlay);
  currentMatch.getGameResult(masterGame->inGamePlayers->length(), outFile);    
  currentMatch.printMatch();

  return currentMatch;
}

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