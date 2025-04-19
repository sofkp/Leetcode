//1939. Merge BSTs to create Single BST
class Solution {
public:
    TreeNode* search(TreeNode* node, int key) {
        if (!node || node->val == key) return node;
        if (key < node->val)
            return search(node->left, key);
        return search(node->right, key);
    }

    void inorder(TreeNode* node, vector<int>& v) {
        if (!node) return;
        inorder(node->left, v);
        v.push_back(node->val);
        inorder(node->right, v);    
    }

    bool isValidBST(TreeNode* root) {
        vector<int> v;
        inorder(root, v);
        for(int i = 1; i < v.size(); i++) {
            if(v[i] <= v[i-1]) {
                return false;
            }
        }
        return true;
    }

    TreeNode* canMerge(vector<TreeNode*>& trees) {
        if (trees.empty()) return nullptr;

        unordered_map<int, TreeNode*> roots;
        unordered_map<int, int> contador; 
        
        for (auto tree : trees) {
            roots[tree->val] = tree;
            contador[tree->val]++;
            if (tree->left) contador[tree->left->val]++;
            if (tree->right) contador[tree->right->val]++;
        }
        
        TreeNode* root = nullptr;
        for (auto tree : trees) {
            if (contador[tree->val] == 1) {
                if (root) return nullptr;
                root = tree;
            }
        }
        if (!root) return nullptr; 
        
        roots.erase(root->val);
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (curr->left && !curr->left->left && !curr->left->right) {
                int val = curr->left->val;
                if (roots.count(val)) {
                    curr->left = roots[val];
                    roots.erase(val);
                    q.push(curr->left);
                }
            }
            
            if (curr->right && !curr->right->left && !curr->right->right) {
                int val = curr->right->val;
                if (roots.count(val)) {
                    curr->right = roots[val];
                    roots.erase(val);
                    q.push(curr->right);
                }
            }
        }
        
        if (!roots.empty()) return nullptr;
        
        if (!isValidBST(root)) return nullptr;
        
        return root;
    }
};
