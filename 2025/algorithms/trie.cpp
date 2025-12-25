#include <iostream>
#include <vector>

class TreeNode {
public:
  bool isEnd;
  std::vector<TreeNode*> child;
  TreeNode() {
    this->isEnd = false;
    child.resize(26, nullptr);
  }
};

class Trie {
private:
  TreeNode* root;
public:
  Trie() {
    root = new TreeNode();
  }

  void insert(const std::string &word) {
    TreeNode* temp = root;
    for (const auto ch : word) {
      if (temp->child[ch - 'a'] == nullptr) {
        temp->child[ch - 'a'] = new TreeNode();
      }
      temp = temp->child[ch - 'a'];
    }
    temp->isEnd = true;
  }

  bool search(const std::string &word) {
    const TreeNode* temp = root;
    for (const auto ch : word) {
      if (temp->child[ch - 'a'] == nullptr) {
        return false;
      }
      temp = temp->child[ch - 'a'];
    }
    return temp->isEnd;
  }

  bool startsWith(const std::string &word) {
    const TreeNode* temp = root;
    for (const auto ch : word) {
      if (temp->child[ch - 'a'] == nullptr) {
        return false;
      }
      temp = temp->child[ch - 'a'];
    }
    return true;
  }
};