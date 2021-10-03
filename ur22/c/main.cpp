#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int main()
{
  std::string s;
  std::cin >> s;
  if (s.find('0') == std::string::npos)
    puts("0");
  else
    puts("-1");
  return 0;
}

