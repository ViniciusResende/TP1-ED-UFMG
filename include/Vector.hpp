#ifndef CHAINEDLISTH
#define CHAINEDLISTH

#include "memlog.h"

template<typename T>
class Vector {
  public:  
    Vector(int size);

		T warmUpVector();
		void setElement(int idx, T value);
		T getElement (int idx);

    ~Vector();

  private:
    T* value;
    int size;
    static int _id;
    int id;
};

#endif
