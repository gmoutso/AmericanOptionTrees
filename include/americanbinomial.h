#ifndef BINOMIAL_H
#define BINOMIAL_H
#include<vector>
#include<string>
using namespace std;
#include<payoffs.h>
#include<simplebinomial.h>

/// A Binomial Stock Tree is a Binomial Tree
/// with information about a stock, its volatility, etc,
/// facilities to push an american put option into the tree
class BinomialStockTree : public BinomialTree
{
public:
  BinomialStockTree(double S0min, double volatility, double interest_rate, unsigned int days, unsigned int steps_per_day =1, unsigned int basefactor = 0);
  void PushAmericanOption(Put& option);
  /// GetStock gets the stored stock in terms of up/down moves
  /// if the tree has base, offset=0 corresponds to the lowest initial stock
  const double& GetStock(unsigned int up, unsigned int down, unsigned int offset=0) const;
  void saveas(string filename);
private:
  double S0min_;
  // double S0max_;
  unsigned int basefactor_;
  unsigned int spd_;
  // unsigned int basedepth_;
  double discount_;
  double up_;
  double riskp_;
  /// stocks in the tree are in a single vector precomputed,
  /// with index = depth+up-down in [0,2depth)
  vector<double > stocks_;
  void BuildStockData();
  TreeNodeItem IncrementalPrice(unsigned int up, unsigned int down, Put&, unsigned int offset=0);
};

#endif
