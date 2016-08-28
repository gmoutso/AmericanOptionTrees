#include<iostream>
//#include<sstream>
#include<string>
using namespace std;
#include<americanbinomial.h>
#include<payoffs.h>
//#include<ctime>

int main() {

  // cout << "tree level: ";
  // int N;
  // cin >> N;
  // cout << "\n";

  double S0;
  cout << "enter spot rate: ";
  cin >> S0;
  cout << "\n";

  double interest;
  cout << "enter interest rate: ";
  cin >> interest;
  cout << "\n";

  double vol;
  cout << "enter annual volatility: ";
  while(cin >> vol && vol==0) { cout << "\nWarning volatility cannot be zero. Try again: "; }
  cout << "\n";

  double days,spd,basefactor;
  cout << "enter days, steps per day and basefactor (separated by space): ";
  cin >> days >> spd >> basefactor;
  cout << "\n";

  cout << "Making binomial tree..." << "\n";
  BinomialStockTree tree(S0,vol,interest,days,spd,basefactor);

  double strike;
  cout << "\nenter an American put strike: ";
  cin >> strike;
  cout << "\n";
  Put put(strike);

  cout << "Calculating put price..." << "\n";

  tree.PushAmericanOption(put);

  double price = tree.GetNode(0,0).GetItem(0).GetValue();
  cout << "put price is " << price << "\n";

  // write to file section
  cout << "file name to write tree (enter: don't write) ";
  string filename;
  cin.ignore();
  getline(cin,filename);
  if (!filename.empty()) tree.saveas(filename);

}
