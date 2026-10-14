#include <cstring>

#include "int_vector.h"

void IntVector::push_back(int val) {
  if (n + 1 > allowed) {
    allowed = allowed * 2;

    int *new_buf = new int[allowed];
    memcpy(new_buf, buf, 4*n);

    delete[] buf;
    buf = new_buf;
  }

  *(buf + n) = val;
  n++;
}

int IntVector::at(int i) { return *(buf + i); }

int IntVector::size() { return n; }
