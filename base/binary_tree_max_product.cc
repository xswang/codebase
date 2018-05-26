/*
 * binary_tree_max_product.cc
 * Copyright (C) 2018 XiaoshuWang <2012wxs@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */
#include <iostream>
#include <vector>

struct TreeNode {
  TreeNode() : value(1), left(nullptr), right(nullptr) {}
  int value;
  TreeNode* left;
  TreeNode* right;
};

int res = INT_MIN;
std::vector<int> max_product_tree(TreeNode* root) {
  std::vector<int> l_return, r_return;
  // if this node has no child, the min ans max is the node value
  if (!root->left && !root->right){
    return {root->value,  root->value};
  }
  if (root->left) {
    // left: the node left child`s min and max
    // left[0]: min of left child
    // left[1]: max of left child
    std::vector<int> left = max_product_tree(root->left);
    // l_return[0]: min value consider root value
    l_return[0] = std::min(left[0] * root->value, left[1] * root->value);
    // l_return[1]: max value consider root value
    l_return[1] = std::max(left[0] * root->value, left[1] * root->value);
  }
  if (root->right) {
    // right[0]: min of right child
    // right[1]: max of right child
    std::vector<int> right = max_product_tree(root->right);
    r_return[0] = std::min(right[0] * root->value, right[1] * root->value);
    r_return[1] = std::max(right[0] * root->value, right[1] * root->value);
  }
  std::vector<int> res;
  // res[0]: min of this path include root
  res[0] = std::min(l_return[0], r_return[0]);
  // res[1]: max of this path include root
  res[1] = std::max(r_return[1], r_return[1]);
  return res;
}

int main(){
  //TreeNode* root = build_tree();
  // if root has no child renturn it`s value
  if (!root->left && !root->right) return root->value;
  std::vector<int> left, right;
  // get left child`s min and max
  if (root->left)
    left = max_product_tree(root->left);
  // get right child`s min product and max product
  if (root->right)
    right = max_product_tree(root->right);
  // calculate the result
  int res1 = std::max(left[0] * right[0] * root->val, left[1] * right[1] * root->value);
  int res2 = std::max(root->value * left[0], root->value * left[1]);
  int res3 = std::max(root->value * right[0], root->value * right[1]);
  return std::max(left[0] * right[0] * root->value, std::max(left[1] * right[1] * root->value);
}
