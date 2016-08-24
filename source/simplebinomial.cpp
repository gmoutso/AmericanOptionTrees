#include<simplebinomial.h>
#include<ctime>
#include<iostream>
#include<sstream>

//
// Tree Node Items
//

const TreeNodeItem& TreeNode::GetLastItem() const {
  return nodedata_.back();
}


const TreeNodeItem& TreeNode::GetItem(int n) const {
  return nodedata_[n];
}

/// format a TreeNodeItem in an output stream
ostream & operator<<(ostream &os, const TreeNodeItem& node) {
  os << "(" << node.GetValue() << ", " << node.GetBool() << ")";
  return os;
}

//
// Tree nodes
//

unsigned int TreeNode::Size() const {
  int size = nodedata_.size();
  return size; // returning const ref to temporary!
}

void TreeNode::PushItem(const TreeNodeItem& item)
{ nodedata_.push_back(item); }


/// format a TreeNode in an output stream
ostream & operator<<(ostream &os, const TreeNode& node) {
  stringstream streamnode;
  streamnode << "[";
  vector<TreeNodeItem >::const_iterator iter;
  const vector< TreeNodeItem > & data = node.nodedata_;
  for (iter = data.begin(); iter < data.end()-1; ++iter) {
      streamnode << *iter  << ",";
  }
  streamnode << data.back() << "]";
  os << streamnode.str();
  return os;
}


//
// Binomial Trees
//

BinomialTree::BinomialTree(unsigned int depth, int basedepth):
  depth_(depth), basedepth_(basedepth)
{
  // resize the depth
  treedata_.resize(depth+1);
  // resize each layer i
  for (unsigned int i=0; i < depth+1; i++)
    {
       treedata_[i].resize(i+basedepth_+1);
    }
}



void BinomialTree::PushName(const string& s)
{ nodedatanames_.push_back(s); }

const TreeNode& BinomialTree::GetNode(unsigned int ups, unsigned int downs, unsigned int offset) const
{ return treedata_[ups+downs][downs+offset]; }

void BinomialTree::PushItem(unsigned int ups, unsigned int downs,const TreeNodeItem& item, unsigned int offset){
  TreeNode& node = treedata_[ups+downs][downs+offset];
  node.PushItem(item);
}

/// format a Binomial Tree in an output stream
ostream& operator<<(ostream& ost,const BinomialTree& tree) {
  stringstream line;
  int depth = tree.GetDepth();
  for (int i=0; i<depth+1; i++) {
    for (int j=0; j<i; j++) { //not include the downmost 
      const TreeNode& thisnode = tree.GetNode(i-j,j);
      line << thisnode << ", ";
    }
    const TreeNode& thisnode = tree.GetNode(0,i); //include the downmost
    line << thisnode << endl;
    ost << line.str();
    line.str(string());
  }
  return ost;
}
