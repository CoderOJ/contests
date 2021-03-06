#include "./main.h"

int main() {
  
  HamiltonianConstruction s;
  auto res = s.construct(
#include "./in.csh"
  );
  logArray(res.begin(), res.end(), "\n");
  return 0;
}
