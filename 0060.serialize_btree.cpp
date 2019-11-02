#include "common.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

struct STreeNode {
  int val;
  int left, right;
  STreeNode() {
  }
  STreeNode(int x) : val(x), left(-1), right(-1) {
  }
};

#define TEST 1
class Solution {
public:
  char* Serialize(TreeNode *root) {    
    if (!root) return nullptr;
    vector<STreeNode> vs;
    stack<TreeNode*> st;
    map<TreeNode*, int> ma;
    st.push(root);
    while (!st.empty()) {
      TreeNode* r = st.top(); st.pop();
      int si = get_snode(vs, ma, r);
      if (r->left) {
#if TEST == 0
        int p = get_snode(vs, ma, r->left);
        vs[si].left = p;
#else
        vs[si].left = get_snode(vs, ma, r->left);
#endif
        // cout << "SI" << si << ", " << vs.size() << endl;
        cout << "LEFT " << vs[si].left << endl;
        st.push(r->left);
      }
      if (r->right) {
        vs[si].right = get_snode(vs, ma, r->right);
        st.push(r->right);
      }
      cout << r->val << " " << vs[si].left << endl;
    }
    char *buf = new char[4 + vs.size() * sizeof(STreeNode)];
    *reinterpret_cast<int*>(buf) = vs.size();
    memcpy(buf + 4, vs.data(), vs.size() * sizeof(STreeNode));
    return buf;
  }
  TreeNode* Deserialize(char *str) {
    if (!str) return nullptr;
    int len = *reinterpret_cast<int*>(str);
    STreeNode *sr = reinterpret_cast<STreeNode*>(str + 4);
    vector<TreeNode*> vs;
    for (int i = 0; i < len; ++i) {
      vs.push_back(new TreeNode{sr[i].val});
    }
    for (int i = 0; i < len; ++i) {
      if (sr[i].left != -1)
        vs[i]->left = vs[sr[i].left];
      if (sr[i].right != -1)
        vs[i]->right = vs[sr[i].right];
    }
    return vs[0];
  }
private:
  int get_snode(vector<STreeNode> &vs, map<TreeNode*, int> &ma, TreeNode* r) {
    if (!ma.count(r)) {
      ma[r] = vs.size();
      vs.push_back(r->val);
    }
    cout << "RETN" << ma[r] << "|" << vs.size() << endl;
    return ma[r];
  } 
};

int main() {
  Solution so;
  TreeNode* root = INPUT_BTREE_VLR<TreeNode>();
  char* str = so.Serialize(root);
  PRINT_BTREE_VLR(so.Deserialize(str));
  return 0;
}
