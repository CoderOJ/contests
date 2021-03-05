#include "./main.h"

int main() {
  
  ConversionMachine s;
  const auto res = s.countAll(
#include "./in.csh"
  );

  see(res);

  return 0;
}
