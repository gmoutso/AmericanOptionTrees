#include<algorithm>
using namespace std;
#include<payoffs.h>

double Put::operator()(double spot) {
  double result = max(0.,GetStrike() - spot);
  return result;
}

double Call::operator()(double spot) {
  double result = max(0.,-GetStrike() + spot);
  return result;
}
