#ifndef SIMPLEBINOMIAL_H
#define SIMPLEBINOMIAL_H
#include<vector>
#include<string>
using namespace std;

/// A Tree Node Item will be an item of a Tree Node
/// contains a double and a boolean only
class TreeNodeItem {
public:
  // create a node item
  explicit TreeNodeItem(double v): itemvalue_(v), itembool_(0) {};
  explicit TreeNodeItem(double v, bool p): itemvalue_(v), itembool_(p) {};
  // set/get
  void SetBool(bool b) {itembool_=b;}
  const bool& GetBool() const {return itembool_;}
  void SetValue(double v) {itemvalue_=v;}
  const double& GetValue() const {return itemvalue_;}
  // stream output a data node item
  friend ostream& operator<<(ostream&,const TreeNodeItem&);
protected:
  double itemvalue_;
  bool itembool_;
};

/// A TreeNode contains Tree Node Items as vector elements
class TreeNode {
public:
  TreeNode(): nodedata_(){};
  /// PushItem a TreeNodeItem into the Node
  void PushItem(const TreeNodeItem&);
  // get the first element (usually the spot value)
  // const double& GetSpot() const;
  /// get the n-th element
  const TreeNodeItem& GetItem(int) const;
  /// get the size
  unsigned int Size() const;
  /// get last item
  const TreeNodeItem& GetLastItem() const;
  /// stream output a node
  friend ostream& operator<<(ostream&,const TreeNode&); 
private:
  vector< TreeNodeItem > nodedata_;
};

/// A binomial tree contains treedata, i.e. nested Tree Nodes
class BinomialTree
{
public:
  //  explicit BinomialTree(unsigned int depth);
  explicit BinomialTree(unsigned int depth, int basedepth);
  /// GetNode uses up and down, eg use GetDepth(i-j,j)
  const TreeNode& GetNode(unsigned int ups, unsigned int downs, unsigned int offset=0) const;
  /// push the name of the n'th Tree Node Item (stored separately to the tree)
  void PushName(const string&);
  /// Get the depth of the tree
  const unsigned int& GetDepth() const {return depth_;}
  const unsigned int& GetBaseDepth() const {return basedepth_;}
  friend ostream& operator<<(ostream&,const BinomialTree&);
protected:
  void PushItem(unsigned int ups, unsigned int downs, const TreeNodeItem&, unsigned int offset=0);
private:  
  unsigned int basedepth_;
  unsigned int depth_;
  vector<vector <TreeNode > > treedata_;
  vector<string> nodedatanames_;
};

#endif
