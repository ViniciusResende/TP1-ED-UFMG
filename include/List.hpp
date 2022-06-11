#ifndef LISTH
#define LISTH

#include <string>

#include "memlog.h"
#include "ListCell.hpp"
#include "Player.hpp"

class ListCell;
class List {
  public:  
    /**
     * @brief Default constructor for List class instance. Responsible for initialize
     * the List attributes.
     */
    List();

    /**
     * @brief Returns the current lenght of the List.
     *
     * @return Returns the value of the class attribute "size".
     */
    int length();
    /**
     * @brief Getter function responsible for returning the element stored in a certain Index of the List. 
     *
     * @param idx Index of the element that will be returned.
     * 
     * @return Returns the element stored in the List at idx position.
     */
		Player* getElement (int idx);
    /**
     * @brief Method responsible for changing the value of a certain element in the List. 
     *
     * @param idx Index of the element that will have the value changed.
     * @param value Value to change the element for.
     */
		void setElement(int idx, Player* value);
    /**
     * @brief Method responsible for append a new element in the first position of the List. 
     *
     * @param value Value of the element to be appended.
     */
    void pushFront(Player* value);
    /**
     * @brief Method responsible for append a new element in the last position of the List. 
     *
     * @param value Value of the element to be appended.
     */
    void pushBack(Player* value);
    /**
     * @brief Method responsible for append a new element in the specified position of the List. 
     *
     * @param idx Index of the position where the element will be appended.
     * @param value Value of the element to be appended.
     */
    void pushPosition(int idx, Player* value);
    /**
     * @brief Method responsible for delete the element in the first position of the List. 
     *
     * @return Returns the value stored at the deleted element.
     */
    Player* popFront();
    /**
     * @brief Method responsible for delete the element in the last position of the List. 
     *
     * @return Returns the value stored at the deleted element.
     */
    Player* popEnd();
    /**
     * @brief Method responsible for delete the element in a specified position of the List. 
     *
     * @param idx Index of the position where the element will be deleted.
     * 
     * @return Returns the value stored at the deleted element.
     */
    Player* popPosition(int idx);
    /**
     * @brief Method responsible for search and return a Player stored in the list by its name. 
     *
     * @param playerName Name of the player being searched (key value).
     * 
     * @return Returns a pointer to the player instance found in the list
     * or nullptr in case of the player hasn't been found.
     */
    Player* searchByName(std::string playerName);
    /**
     * @brief This method is responsible for ordering the chained list of players by their names, it is, in alphabetical order.
     */
    void bubbleSort();
    /**
     * @brief Method responsible for reducing, from each player in the list, a specified amount of money. 
     *
     * @param amount Amount of money to be reduced from each player.
     * @param isOperationValid This is a reference to a boolean variable that will have 
     * its value changed according to the validity of the operation.
     */
    int forEachPlayerReduceMoney(int amount, bool &isOperationValid);
     /**
     * @brief Method responsible for raising, from each player in the list, 
     * until a certain value, a specified amount of money. 
     *
     * @param amount Amount of money to be raised from each player.
     * @param limitIdx This is the limit Player index to be included in the raise.
     */
    void forEachPlayerRaiseMoney(int amount, int limitIdx);

    /**
     * @brief Default destructor of the class, that will clean it up when called and free the allocated memory.
     */
    ~List();

  private:
    static int _id;
    int id;
    int size;
    ListCell* head;
    ListCell* tail;

    /**
     * @brief Method responsible for returning a pointer to a cell in a certain list position. 
     *
     * @param idx Index of the position which is desirable to place a pointer to.
     * @param before Boolean condition that indicates if the returned pointer refers to idx - 1.
     * 
     * @return Returns a pointer to the list cell in the specified position.
     */
    ListCell* setPosition(int idx, bool before);
     /**
     * @brief This method is responsible for switching two consecutive elements of 
     * the list, really helpful when working with Bubble Sort algorithms.
     *
     * @param fistCell Pointer to the first cell of the two consecutive to be switched.
     * @param secondCell Pointer to the second cell of the two consecutive to be switched.
     * @param cellBeforeFirst Pointer to the cell before the first cell of the two consecutive to be switched.
     */
    void swapConsecutiveListCells(ListCell *fistCell, ListCell *secondCell, ListCell *cellBeforeFirst);
};

#endif
