#include <vector>

void InitA(
    int N, int A, std::vector<int> U, std::vector<int> V, std::vector<int> C);
void InitB(
    int N, int B, std::vector<int> S, std::vector<int> T, std::vector<int> D);

void ReceiveA(bool x);
void ReceiveB(bool y);

void SendA(bool y);
void SendB(bool x);

std::vector<int> Answer();
