#ifndef VECTORH
#define VECTORH

#include "memlog.h"

template<typename T>
class Vector {
  public:  
    Vector(int size);

    int length();
		T warmUpVector();
		void setElement(int idx, T value);
		T getElement (int idx);
    void pushBack(T value);
    void sortVector();
    void sortVectorDesc();

    ~Vector();

  private:
    T* value;
    int size;
    int lastInputedIndex;
    static int _id;
    int id;
};

#endif
