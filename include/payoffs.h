#ifndef CALLPUTS_H
#define CALLPUTS_H
//#include<string>
#include<algorithm>
using namespace std;

class StrikeOption {
public:
  explicit StrikeOption(double K): strike_(K) {}
  virtual double operator()(double spot_)=0;
  const double& GetStrike() const {return strike_;}
private:
  double  strike_;
};

class Put : public StrikeOption {
public:
  Put(double K): StrikeOption(K) {}
  double operator()(double spot);
};

class Call :  public StrikeOption {
public:
  Call(double K): StrikeOption(K) {}
  double operator()(double spot);
};

#endif

