#include<vector>
#include<string>
#include <fstream>
#include <sstream>
using namespace std;
#include<simplebinomial.h>
#include<americanbinomial.h>
#include<payoffs.h>
#include<cmath>
#include<iostream>

BinomialStockTree::BinomialStockTree(double S0min, double volatility, double interest_rate, unsigned int days, unsigned int steps_per_day, unsigned int basefactor):
  BinomialTree(days * steps_per_day, basefactor * steps_per_day), // FIX!
  S0min_(S0min), spd_(steps_per_day), 
  basefactor_(basefactor) {
  // calculate the discount per step
  // compounding will happen steps_per_day times per day!
  double dt = static_cast<double>(steps_per_day)/360;
  double r = interest_rate;
  discount_ = exp(-r * dt);
  // calculate the risk free up/down probability
  // the volatility is measured in annual units
  up_ = exp( volatility * sqrt(dt) );
  double down = 1/up_;
  double p = (1/discount_ - down)/(up_-down);
  riskp_=p;
  // fix S0max to fit in mesh
  // we record basedepth and depth (in BinomialTree),
  // basefactor and we also have steps_per_day. They are related
  // basedepth = basefactor * steps_per_day;
  // depth = days * steps_per_day
  // S0max_ = S0min * pow(up_, basedepth_ );
  // build the stock data
  BuildStockData();
}

void BinomialStockTree::BuildStockData() {
  // ups from S0_min = -depth, ... , basedepth+depth
  stocks_.resize(2 * GetDepth()  + GetBaseDepth() + 1);
  // lowermost stock
  double stock = S0min_/ pow(up_ , GetDepth());
  for (auto&& i : stocks_) {	// C++11, access by reference
    i = stock;			// the type of i is double&
    stock *= up_;
  }
}

const double& BinomialStockTree::GetStock(unsigned int up,unsigned int down, unsigned int offset) const {
  //must have offset in [0,basedepth]
  const unsigned int & depth = GetDepth();
  return stocks_[depth + up -down +offset];
}

/// An auxiliary private function
/// that calculates and pushes an american option price
/// to be used by PushAmericanOption
TreeNodeItem BinomialStockTree::IncrementalPrice(unsigned int up, unsigned int down, Put& option, unsigned int offset) {
  double spot = GetStock(up,down,offset);
  double payoff = option(spot); 
  double upprice = GetNode(up+1,down,offset).GetLastItem().GetValue();
  double downprice = GetNode(up,down+1,offset).GetLastItem().GetValue();
  double Eprice = discount_*( riskp_ * upprice  + (1-riskp_) * downprice);
  bool b = (payoff>Eprice);
  double price = b? payoff : Eprice;
  return TreeNodeItem(price,b);
}


void BinomialStockTree::PushAmericanOption(Put& option) {
  const unsigned int& depth=GetDepth();
  const unsigned int& basedepth=GetBaseDepth();
  PushName("American Put");
  // first calculate the payoff at maturity
  for (unsigned int down = 0; down < depth+1; down++) { 
    unsigned int up = depth - down;
    double spot = GetStock(up, down, 0);
    double payoff = option(spot);
    PushItem(up,down, TreeNodeItem(payoff,payoff>0), 0);
  }
  for (unsigned int offset=1; offset<basedepth+1; ++offset) {
    unsigned int up = depth;
    double spot = GetStock(up, 0, offset);
    double payoff = option(spot);
    PushItem(up,0,TreeNodeItem(payoff,payoff>0), offset);    
  }
  // calculate american prices
  for (int i=depth-1; i>-1 ; i--) { // go backwards start from second-to-last
    for (int j=0; j<i+1; j++) {
      unsigned int up = i -j , down = j, offset = 0;
      TreeNodeItem PriceItem = IncrementalPrice(up,down,option,offset);
      PushItem(up,down, PriceItem, offset);
    }
    for (int offset=1; offset < basedepth+1; offset++) {
      unsigned int up = i, down = 0;
      TreeNodeItem PriceItem = IncrementalPrice(up,down,option,offset);
      PushItem(up,down, PriceItem, offset);
    }
  }
}

void BinomialStockTree::saveas(string filename){
  ofstream file (filename);
    if (file.is_open())
      {
	// json data in one line
	file << "{ \"S0min\": " << S0min_
	     << ", \"depth\": " << GetDepth()
	     << ", \"basedepth\": " << GetBaseDepth()
	     << ", \"basefactor\": " << basefactor_
	     << ", \"spd\": " << spd_
	     << ", \"up\": " << up_
	     << ", \"options\": " << GetNames().size()
	     << " }" << "\n";
	// the next streamer is that of BinomialTree
	file << *this;
	file.close();
      }
    else cout << "Unable to open file"; 
}
