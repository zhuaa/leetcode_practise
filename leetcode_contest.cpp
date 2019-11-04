/*
1.
Given a circular array C of integers represented by A, find the maximum possible sum of a non-empty subarray of C.

Here, a circular array means the end of the array connects to the beginning of the array.  (Formally, C[i] = A[i] when 0 <= i < A.length, and C[i+A.length] = C[i] when i >= 0.)

Also, a subarray may only include each element of the fixed buffer A at most once.  (Formally, for a subarray C[i], C[i+1], ..., C[j], there does not exist i <= k1, k2 <= j with k1 % A.length = k2 % A.length.)
*/
class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        //maximum possible sum of C
        /*
        int n = A.size();
        vector<int> B=A;
        for(auto a:B){
            A.push_back(a);
        }
        //cout<<A.size()<<endl;
        int max_sum = INT_MIN;
        for(int i=0; i<n; i++){
            vector<int> t(A.begin()+i, A.begin()+i+n);
            //cout<<find_max_subsum(t)<<endl;
            max_sum = max(max_sum, find_max_subsum(t));
        }
        return max_sum;
        */
        int res1 = find_max_subsum(A);
        int sum = 0;
        for(int i=0;i<A.size(); i++){
            sum += A[i];
            A[i] = -A[i];
        }
        
        if(find_max_subsum(A) == -sum) return res1;
        
        sum = sum + find_max_subsum(A);
        return (sum>res1)?sum:res1;
    }
    
    int find_max_subsum(vector<int> nums){
        if(nums.empty()) return 0;
        int res = INT_MIN;
        int cur = 0;
        for(int i=0; i<nums.size(); i++){
            cur = max(cur+nums[i], nums[i]);
            res = max(res, cur);
        }
        return res;
    }
    
    
};



/*
2.
A complete binary tree is a binary tree in which every level, except possibly the last, is completely filled, and all nodes are as far left as possible.

Write a data structure CBTInserter that is initialized with a complete binary tree and supports the following operations:

CBTInserter(TreeNode root) initializes the data structure on a given tree with head node root;
CBTInserter.insert(int v) will insert a TreeNode into the tree with value node.val = v so that the tree remains complete, and returns the value of the parent of the inserted TreeNode;
CBTInserter.get_root() will return the head node of the tree.
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class CBTInserter {
private:
    
    vector<vector<TreeNode*>> levels;
    
public:
    CBTInserter(TreeNode* root) {
        
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int t = q.size();
            vector<TreeNode*> out;
            for(int i=0; i<t; i++){
                TreeNode* node = q.front();
                q.pop();
                out.push_back(node);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            levels.push_back(out);
        }
    }
    
    int insert(int v) {
        //returns the value of the parent of the inserted TreeNode
        int n = levels.size();
        TreeNode* newNode = new TreeNode(v);
        if(levels[n-1].size() < pow(2, n-1)) {
            levels[n-1].push_back(newNode);
            int idx = levels[n-1].size()-1;
            if(idx%2==1) levels[n-2][idx/2]->right = newNode;
            else levels[n-2][idx/2]->left = newNode;
            return levels[n-2][idx/2]->val;
        }
        else{
            vector<TreeNode*> out;
            out.push_back(newNode);
            levels.push_back(out);
            levels[levels.size()-2][0]->left = newNode;
            return levels[levels.size()-2][0]->val;
        }
        
    }
    
    TreeNode* get_root() {
        return levels[0][0];
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter obj = new CBTInserter(root);
 * int param_1 = obj.insert(v);
 * TreeNode* param_2 = obj.get_root();
 */





 /*
 3.
 Given a string S, return the "reversed" string where all characters that are not a letter stay in the same place, and all letters reverse their positions.
 */
class Solution {
public:
    string reverseOnlyLetters(string S) {
        int left = 0, right = S.size()-1;
        while(left<=right){
            if(isalpha(S[left]) && isalpha(S[right])){
                swap(S[left++], S[right--]);
            }
            while(!isalpha(S[left])) left++;
            while(!isalpha(S[right])) right--;
        }
        return S;
    }
};


/*
4.
Your music player contains N different songs and she wants to listen to L (not necessarily different) songs during your trip.  You create a playlist so that:

Every song is played at least once
A song can only be played again only if K other songs have been played
Return the number of possible playlists.  As the answer can be very large, return it modulo 10^9 + 7.
*/






