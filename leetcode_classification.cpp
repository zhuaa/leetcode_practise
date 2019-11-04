****************************************************************************************************************************************
Parentheses
****************************************************************************************************************************************
20. Valid Parentheses
🌼🌼🌼//solution 1: using stack, time complecity O(N), space complecity O(N)
class Solution {
public:
    bool isValid(string s) {
        //Note that an empty string is also considered valid.
        if(s.empty()) return true;
        
        stack<char> st;
        for(int i=0; i<s.size(); i++){
            char c = s[i];
            
            if(c=='{' || c=='[' || c=='(') {
              //cout<<"here"<<endl;
              st.push(c);
            }
            
            else{
              switch(c){
                case '}': if(!st.empty() && st.top()=='{') st.pop(); else return false; break;
                case ']': if(!st.empty() && st.top()=='[') st.pop(); else return false; break;
                case ')': if(!st.empty() && st.top()=='(') st.pop(); else return false; break;
              }
            }
        }
        if(st.empty()) return true;  //!!!最后判断是否stack为空
        else return false;
               
    }
};


class Solution {
public:
    bool isValid(string s) {
        //Note that an empty string is also considered valid.
        if(s.empty()) return true;
        stack<char> st;
        for(char c:s){
            if(c=='(' || c=='[' || c=='{') st.push(c);
            else{
                switch(c){
                    case ')': if(st.empty()||st.top()!='(') return false; else st.pop(); break;
                    case ']': if(st.empty()||st.top()!='[') return false; else st.pop(); break;
                    case '}': if(st.empty()||st.top()!='{') return false; else st.pop(); break;
                }
            }
        }
        return st.empty();
    }
};



32. Longest Valid Parentheses  
// solution 1: also using stack
//将index压入栈
class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        
        stack<int> st;
        int max_len = 0;
        int start = 0;
        //push index of '(' into stack
        for(int i=0; i<s.size(); i++){
            if(s[i]=='(') st.push(i);
            else if(s[i]==')'){ 
                if(st.empty()) start = i+1; //!!!
                else{
                    st.pop();
                    max_len = st.empty()? max(max_len, i-start+1):max(max_len, i-st.top()); //!!!i-start+1
                }
            }
        }
           
        return max_len;
    }
}; 


301. Remove Invalid Parentheses      hard
🌼🌼🌼//BFS
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        //bfs
        vector<string> res;
        set<string> visited({s}); // !!!visited string
        queue<string> q({s});
        bool found = false;  //!!!
        
        while(!q.empty()){
            string t = q.front();
            q.pop();
            
            if(isvalid(t)){
                res.push_back(t);
                found = true;
            }
            
            if(found == true) continue;  //if is found then we do no need to delete char
            
            
            //delete char
            for(int i=0; i<t.size(); i++){
                if(t[i] != '(' && t[i] != ')') continue;
                string str = t.substr(0, i) + t.substr(i+1);
                if(!visited.count(str)){
                    q.push(str);
                    visited.insert(str);
                }
            }
        }
        
        return res;
    }
    
    bool isvalid(string s){
        int count = 0;
        for(int i=0; i<s.size(); i++){
            if(s[i] == '(') count++;
            if(s[i] == ')') count--;
            if(count < 0) return false;
        }
        return count == 0;   //！！！判断count==0
    }
};


678. Valid Parenthesis String
🌼🌼🌼//dfs
class Solution {
public:
    bool checkValidString(string s) {
        //stack left star;
        //recursion
        return checkValid(s, 0, 0);
    }
    bool checkValid(string s, int start, int count){
        if(count<0) return false;
        for(int i=start; i<s.size(); i++){
            if(s[i]=='(') count++;
            else if(s[i]==')'){count--; if(count<0) return false;}
            else{
                return checkValid(s, i+1, count) || checkValid(s, i+1, count-1) || checkValid(s, i+1, count+1);
            }
        }
        return count==0;
    }
};

//solution 2: stack
class Solution {
public:
    bool checkValidString(string s) {
        //stack left star;
        //recursion
        stack<int> left, star;
        for(int i=0; i<s.size(); i++){
            if(s[i]=='(') left.push(i);
            else if(s[i]=='*') star.push(i);
            else{
                if(left.empty()&&star.empty()) return false;
                else if(!left.empty()) left.pop();
                else star.pop();
            }
        }
        while(!left.empty() && !star.empty()){
            if(left.top() > star.top()) return false;
            left.pop();
            star.pop();
        }
        return left.empty();
    }

};
//
class Solution {
public:
    bool checkValidString(string s) {
        //two stacks
        stack<int> left, star;
        for(int i=0; i<s.size(); i++){
            if(s[i]=='(') left.push(i);
            if(s[i]=='*') star.push(i);
            
            if(s[i]==')'){
                if(!left.empty()) left.pop();
                else if(!star.empty()) star.pop();
                else return false;
            }
        }
        
        while(!left.empty()){
            if(star.empty() || star.top() < left.top()) return false;
            star.pop();
            left.pop();
        }
        return left.empty();
    }

};


//another solution
class Solution {
public:
    bool checkValidString(string s) {
        //lower upper of unpaired '('
        int lower = 0, upper = 0;
        for(char c:s){
            if(c=='('){
                lower++;
                upper++;
            }
            else if(c==')'){
                if(lower>0) lower--;
                upper--;
            }
            else{
                if(lower>0) lower--;
                upper++;
            }     //'*'
            if(upper<0) return false;
        }
        
        return lower == 0;
    }

};



22. Generate Parentheses
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        //backtracking
        vector<string> res;
        string out = "";
        backtrack(res, out, n, 0, 0);
        return res;
    }
    void backtrack(vector<string>& res, string out, int n, int left, int right){
        if(left < right || left>n || right>n) return;
        if(left==n && right == n){
            res.push_back(out);
            return;
        }
        backtrack(res, out+"(", n, left+1, right);
        backtrack(res, out+")", n, left, right+1);
    }
    
};



****************************************************************************************************************************************************
two sum; 3 sum; 4 sum
****************************************************************************************************************************************************
1. Two Sum

//hash map. time complexity: O(N), space complexity:O(N)
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        vector<int> res;
        for(int i=0; i<nums.size(); i++){
            int t = target-nums[i];
            if(m.count(t)){
                res.push_back(m[t]);
                res.push_back(i);
                break;
            }
            m[nums[i]] = i;
        }
        return res;
    }
};

167. Two Sum II - Input array is sorted
//two pointers. time complexity: O(N)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        //two pointers
        if(numbers.empty()) return {};
        int left = 0, right = numbers.size()-1;
        while(left<right){
            int sum = numbers[left] + numbers[right];
            if(sum<target) left++;
            else if(sum >target) right--;
            else{
                return {left+1, right+1};
            }
        }
        return {};
    }
};


653. Two Sum IV - Input is a BST
//solution1: set + DFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        set<int> s;
        return helper(root, s, k);
    }
    bool helper(TreeNode* root, set<int>& s, int k){
        if(root==NULL) return false;
        if(s.count(k - root->val)) return true;
        s.insert(root->val);
        return helper(root->left, s, k) || helper(root->right, s, k);
    }
   
};
//solution2: set + BFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        //using set
        //inorder + two pointers
        //BFS
        if(!root) return false;
        queue<TreeNode*> q;
        q.push(root);
        unordered_set<int> s;
        while(!q.empty()){
            TreeNode* t = q.front();
            q.pop();
            if(s.count(k-t->val)) return true;
            s.insert(t->val);
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }
        return false;
    }

   
};

15. 3Sum
🌼🌼🌼// time complexity: O(N^2) sapce complexity: O(N)
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        if(nums.empty() || nums.size()<3) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for(int i=0; i<nums.size()-2; i++){
            if(nums[i]>0) break;
            if(i>0 && nums[i]==nums[i-1]) continue;  //!!! i>0
            int target = 0 - nums[i];
            int left=i+1, right = nums.size()-1;
            while(left<right){
                if(nums[left]+nums[right]==target){
                    res.push_back({nums[i], nums[left], nums[right]});
                    while(left<right && nums[left+1] == nums[left]) left++;  //!!!
                    while(left<right && nums[right-1] == nums[right]) right--; //!!!
                    left++;
                    right--;
                }
                else if(nums[left]+nums[right]<target) left++;
                else right--;
            }
        }
      return res;
    }
      
};



259. 3Sum Smaller
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if(nums.empty() || nums.size()<3) return 0;
        sort(nums.begin(), nums.end());
        int res = 0;
        for(int i=0; i<nums.size()-2; i++){
            int left = i+1, right = nums.size()-1;
            while(left<right){
                int sum = nums[i] + nums[left] + nums[right];
                if(sum >= target){right--;}
                else if(sum < target){res += right - left; left++;}  //!!!res += right - left
            }
        }
        return res;
    }
};


18. 4Sum
🌼🌼🌼
//time complexity O(N^3)
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.empty() || nums.size()<4) return {};
        vector<vector<int>> res;
        
        sort(nums.begin(), nums.end());
        for(int i=0; i<nums.size()-3; i++){
            if(i>0 && nums[i]==nums[i-1]) continue;
            for(int j=i+1; j<nums.size()-2; j++){
                if(j>i+1 && nums[j]==nums[j-1]) continue;
                int left = j+1, right = nums.size()-1;
                while(left<right){
                    int sum = nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum==target){
                        res.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while(nums[left+1]==nums[left]) left++;
                        while(nums[right-1]==nums[right]) right--;
                        left++;
                        right--;
                    }
                    else if(sum<target) left++;
                    else right--;
                }
                
            }
        }
        
        return res;
        
    }
};
// time complxity: O(N^2) hash table , 但是不是distinct的结果
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.empty() || nums.size()<4) return {};
        unordered_map<int, vector<pair<int, int>>> m;
        vector<vector<int>> res;
        
        for(int i=0; i<nums.size(); i++){
            for(int j=i+1; j<nums.size(); j++){
                int sum = nums[i] + nums[j];
                if(m.count(target-sum)){
                    vector<pair<int, int>> v = m[target-sum];
                    for(auto a:v){
                        if(a.first != i && a.first!=j && a.second!=i && a.second!=j)
                            res.push_back({nums[a.first], nums[a.second], nums[i], nums[j]});
                    }
                }
                m[sum].push_back({i, j});
            }
        }
        
        return res;
        
    }
};

//用set
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size()<4) return {};
        sort(nums.begin(), nums.end());
        set<vector<int>> res;
        for(int i=0; i<nums.size()-3; i++){
            for(int j=i+1; j<nums.size()-2; j++){
                if(j>i+1 && nums[j]==nums[j-1]) continue;
                int left = j+1, right = nums.size()-1;
                while(left<right){
                    int sum = nums[left] + nums[right] + nums[i] + nums[j] ;
                    if(sum == target) res.insert({nums[i], nums[j], nums[left++], nums[right--]});
                    else if(sum < target) left++;
                    else right--;   
                }
            }
        }
        return vector<vector<int>>(res.begin(), res.end());
    }
};





****************************************************************************************************************************
binary search  !!!确定一种写法
*****************************************************************************************************************************
//when array is very huge, (low+right)/2 may be overflow, so we'd better use left + (right-left)/2
//binary 写法：
class Solution{
public:

    int binarySearch1(int target, vector<int> nums){      /*1 3 4 5 6 7 8 the first one >= target   4->2*/
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        return left;
    }


    int binarySearch2(int target, vector<int> nums){     /*the last one <= target   4->2*/
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] > target) right=mid-1;
            else left = mid+1;
        }
        return right;
    }
    int binarySearch3(int target, vector<int> nums){                 /*the first one > target   4->3*/
        int left = 0, right = nums.size()-1;
        while(left <= right){
            int mid = left + (right-left)/2;
            if(nums[mid] <= target) left = mid+1;
            else right = mid-1;
        }
        return left;

    }
    int binarySearch4(int target, vector<int> nums){        /*the last one < target  4->1*/
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] >= target) right = mid-1;
            else left = mid+1;
        }
        return right;
    }
};


278. First Bad Version
// Forward declaration of isBadVersion API. time complexity: O(logN) space complexity: O(1)
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int left  = 1, right = n;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(isBadVersion(mid)==false) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
};

29. Divide Two Integers








33. Search in Rotated Sorted Array
class Solution {
public:
    int search(vector<int>& nums, int target) {
        //input: target num + array
        //output: index of target
        //my plan: binary search
        int left = 0, right = nums.size()-1;
        while(left <= right){
            int mid = left + (right -left)/2;
            if(nums[mid] == target) return mid;
            if(nums[mid] < nums[right]){   //right half is sorted
                if(target > nums[mid] && target <= nums[right])  //in right half  !!!等号
                    left = mid+1;
                else right = mid-1;
            }
            else{                        //left half is sorted
                if(target >= nums[left] && target < nums[mid])  //in left half   !!!等号
                    right = mid-1;
                else left = mid+1;
            }
        }
        return -1;
    }
};

🌼🌼🌼
//another solution
int find_pivot(vector<int> nums){
  int left = 0, right = nums.size()-1;
  while(left<=right){
    int mid = left + (right-left)/2;
    if(nums[mid] < nums[mid-1]) return mid;
    else if(nums[mid] >= nums[0]) left = mid+1;
    else right = mid-1;
  }
  return 0;
}

int binarySearch(vector<int> nums, int left, int right, int target){
  while(left <= right){
    int mid = left + (right-left)/2;
    if(nums[mid] == target) return mid;
    else if(nums[mid] < target) left = mid+1;
    else right = mid-1;
  }
  return -1;
  
}


int shiftedArrSearch( const vector<int>& shiftArr, int num ) 
{
   // time = log(N)
  int pivot = find_pivot(shiftArr);
  
  //cout << "pivot:"<<pivot <<endl;
  if(pivot == 0 || num < shiftArr[0])
    return binarySearch(shiftArr, pivot, shiftArr.size()-1, num);
  else return binarySearch(shiftArr, 0, pivot-1, num);
  
}




81. Search in Rotated Sorted Array II
//contain duplicates
//return true or false
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid]==target) return true;
            else if(nums[mid]<nums[right]){  //right half is sorted
                if(target>nums[mid] && target<=nums[right]) left = mid+1;   //!!!等号
                else right = mid-1;
            }
            else if(nums[mid]>nums[right]){   //left half is sorted
                if(target<nums[mid] && target>=nums[left]) right = mid-1;  //!!! 等号
                else left = mid+1;
            }
            else right--;    // 1 1 3 1 
                             // ^ ^   ^
        }
        return false;
    }
};


//another solution
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right =  nums.size()-1, mid;
        
        while(left<=right)
        {
            mid = (left + right) >> 1;
            if(nums[mid] == target) return true;

            // the only difference from the first one, trickly case, just updat left and right
            if( (nums[left] == nums[mid]) && (nums[right] == nums[mid]) ) {++left; --right;}

            else if(nums[left] <= nums[mid])
            {
                if( (nums[left]<=target) && (nums[mid] > target) ) right = mid-1;
                else left = mid + 1; 
            }
            else
            {
                if((nums[mid] < target) &&  (nums[right] >= target) ) left = mid+1;
                else right = mid-1;
            }
        }
        return false;
    }
};





153. Find Minimum in Rotated Sorted Array
class Solution {
public:
    int findMin(vector<int>& nums) {
        //binary search
        if(nums[0] <= nums[nums.size()-1]) return nums[0]; //unrotated
        int left = 0, right = nums.size()-1;
        while(left != right-1){ //!!!
            int mid = left + (right-left)/2;
            if(nums[left] < nums[mid]){   
                left = mid;
            }
            else{
                right = mid;
            }
        }
        return min(nums[left], nums[right]);
    }
};




//find pivot
class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty()) return -1;
        
        //binary search
        int left = 0, right = nums.size()-1;
        while(left <= right){
            int mid = left + (right-left)/2;
            if(nums[mid] <nums[mid-1]) return nums[mid];
            else if(nums[mid] >= nums[0]) left = mid+1;
            else right = mid-1;
        }
        return nums[0];
    }
};





34. Find First and Last Position of Element in Sorted Array
//solution 1, in worst case:[8 8 8 8 8], 8, time complexity: O(N)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        //5,7,7,8,8,10
        //      ^    ^
        //find one index of target, then find the left and right boundary
        int index = -1;
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] == target) {
                index = mid;
                break;
            }
            else if(nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        if(index == -1) return {-1, -1};
        vector<int> res;
        //find the left boundary
        left = index, right = index;
        while(left>=0 && nums[left] == target){
            left--;
        }
        //find the right boundary
        res.push_back(left+1);
        while(right<nums.size() && nums[right] == target){
            right++;
        }
        res.push_back(right-1);
        return res;
    }
};

 🌼🌼🌼//solution 2, O(logN)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return {-1, -1};
        //5,7,7,8,8,10
        //      ^    ^
        //find the left boundary, the first one >= target  !!!第一个8
        vector<int> res(2, -1);
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        if(left<nums.size() && nums[left] == target) res[0] = left;
        else return res;
        //find the right boundary, the last one <= target  !!!最后一个8
        left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid]>target) right = mid-1;
            else left = mid+1;
        }
        res[1] = right;
        return res;
    }
};

//
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty()) return {-1, -1};
        //binary search find the first target    =>     the first one >= target
        vector<int> res(2, -1);
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] < target) left = mid+1;
            else right = mid-1;
        }
        if(left>=nums.size() || nums[left]>target) return res;  //!!!!
        else res[0] = left;
        
        //binary search find the last target      =>         the last one <= target
        left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] > target) right = mid-1;
            else left = mid+1;
        }
        res[1] = right;
        
        return res;
    }
};



50. Pow(x, n)




162. Find Peak Element
//find the Peak by binary search
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        //basic solution: traverse the arr, time complexity: O(N)
        //better: binary search, time complexity: O(logN)
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] < nums[mid+1]) left = mid+1;
            else right = mid;
        }
        return left;
    }
};

74. Search a 2D Matrix
//time complexity: O(log(m*n))
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        //see the matrix as a increasing vector
        int row = matrix.size();
        int col = matrix[0].size();
        int left = 0, right = row*col-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            int val = matrix[mid/col][mid%col];
            if(val== target) return true;
            else if(val < target) left = mid+1;
            else right = mid-1;
        }
        return false;
    }
};



240. Search a 2D Matrix II
//time complexity: O(m+n)
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        if(target < matrix[0][0] || target > matrix.back().back()) return false;
        int row = matrix.size()-1, col = 0;
        while(row>=0 && col<matrix[0].size()){
            if(target > matrix[row][col]) col++;
            else if(target < matrix[row][col]) row--;
            else return true;
        }
        return false;
    }
};


378. Kth Smallest Element in a Sorted Matrix
class Solution {
public:
    int kthSmallest(vector<vector<int> >& matrix, int k) {
        //1. using heap-->time complexity:O(n*n*logk)
        /*
        if(matrix.empty() || matrix[0].empty()) return -1;
        priority_queue<int> q;
        for(int i=0; i<matrix.size(); i++){
            for(int j =0; j<matrix[0].size(); j++){
                q.push(matrix[i][j]);
                if(q.size()>k) q.pop();
            }
        }
        return q.top();
        */
        //2. using binary search  --> time complexity: O((m+n)log(max-min))!!!
        int left = matrix[0][0], right=matrix.back().back();
        while(left<=right){
            int mid = left+(right-left)/2;
            if(search_less_or_equal(matrix, mid) < k) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
    
    int search_less_or_equal(vector<vector<int>>& matrix, int target){
        int n = matrix.size();
        int row = n-1, col = 0;
        int count = 0;
        while(row>=0 && col<n){
            if(matrix[row][col]<=target){
                count += row+1;
                col++;
            }
            else{
                row--;
            }
        }
        return count;
    }
};


287. Find the Duplicate Number
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        //read only array ---> no sort
        //space---O(1)
        //time--- < O(n^2)
        
        //1. binary search
        //if k is repeated then the count of nums <= k is bigger then k
        //time----O(NlogN) space----O(1)
        
        int left = 1, right = nums.size();
        while(left<=right){
            int mid = left + (right-left)/2;
            int cnt = 0;
            for(auto num:nums){
                if(num<=mid) cnt++;
            }
            if(cnt <= mid) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
};





209. Minimum Size Subarray Sum
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.empty()) return 0;
        //2,3,1,2,4,3
        int left = 0;
        int sum = 0;
        int res = nums.size()+1;
        for(int right =0; right<nums.size(); right++){
            sum += nums[right];
            while(sum >= s){
                res = min(res, right-left+1);
                sum -= nums[left++];
            }
        }
        return res==nums.size()+1? 0 : res;
    }
};


270. Closest Binary Search Tree Value
//solution 1: recursion , time complexity: O(N)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        if(!root) return -1;
        int res = root->val;
        helper(root, target, res);
        return res;
    }
    void helper(TreeNode* root, double target, int& res){
        if(!root) return;
        helper(root->left, target, res);
        if(abs(root->val - target) < abs(res - target)) res = root->val;
        helper(root->right, target, res);
    }
};
//solution 2: binary search, time complexity: O(logN)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
🌼🌼🌼
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        if(!root) return -1;
        int res = root->val;
        while(root){
            if(abs(root->val - target) < abs(res - target)) res = root->val;  //!!!

            if(root->val > target){  //!!!>  left subtree
                root = root->left;
            }
            else{                  //right subtree
                root = root->right; 
            }   
        }
        return res;
    }
};


//🌼🌼🌼
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        //recursive
        if(target == root->val) return target;
        double diff = abs(root->val - target);
        if(target < root->val){
            if(root->left) {
                int left = closestValue(root->left, target);
                return diff < abs(left-target)?root->val:left;
            }
            else return root->val;
        }
        else{
            if(root->right){
                int right = closestValue(root->right, target);
                return diff < abs(right-target)?root->val:right;
            }
            else return root->val;
        }

    }
};


300
349
350

658. Find K Closest Elements
//solution 2: binary search
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        //binary search
        //the first one >= x
        int left = 0, right = arr.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(arr[mid] < x) left = mid+1;
            else right = mid-1;
        }
        right = left;
        left = left-1;
        while(k>0){
            if(right>=arr.size() || left>=0&&x - arr[left] <= arr[right] - x) left--;
            else right++;
            k--;
        }
        return vector<int>(arr.begin()+left+1, arr.begin()+right);
    }
};

//
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        
        //binary search
        //the first one >= x(binary search)
        int left = 0, right = arr.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(arr[mid] < x) left = mid +1;
            else right = mid -1;
        }
        
        int right_idx = left, left_idx = right_idx-1;  // right_idx: the first one >= x
        
        //then find closest k element
        for(int i=0; i<k; i++){
            if(left_idx<0) right_idx++;    //!!!
            else if(right_idx>=arr.size()) left_idx--;   //!!!
            else{
                if(x - arr[left_idx] <= arr[right_idx] - x) left_idx--;
                else right_idx++;   
            }
        }
        return vector<int>(arr.begin()+left_idx+1, arr.begin()+right_idx);
    }
};


//solution 3: binary search  ！！！
//可以把x看作中心，以mid为左边界k个大小的窗口滑动。如果左边比右边大就右滑，否则就左滑
🌼🌼🌼
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left = 0, right = arr.size() - k;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (x - arr[mid] > arr[mid + k] - x) left = mid + 1;
            else right = mid;
        }
        return vector<int>(arr.begin() + left, arr.begin() + left + k);
    }
};



862



************************************************************************************************************************
dynamic programming (DP)
************************************************************************************************************************
91. Decode Ways
// time complexity: O(N) space complexity: O(N)
class Solution {
public:
    int numDecodings(string s) {
        if(s.empty() || s[0]=='0') return 0;
        
        vector<int> dp(s.size()+1, 0);   //dp = (condition)dp[i-1] + (condition)dp[i-2]
        dp[0] = 1;
        
        for(int i=1; i<dp.size(); i++){
            dp[i] += s[i-1] == '0'? 0: dp[i-1];  // ...X '3' dp[i]+= dp[i-1]   ....X0  
            if(s[i-2] == '1' || s[i-2] == '2' && s[i-1]<='6')   //...X '1' '2'  ...X '2' '4' dp[i] += dp[i-2]  
                dp[i] += dp[i-2];
        }
        return dp[s.size()];
    }
};


//solution 2
// time complexity: O(N) space complexity: O(1)
class Solution {
public:
    int numDecodings(string s) {
        if(s.empty() || s[0]=='0') return 0;
        
        int c1 = 1, c2 = 1;
        for(int i=0; i<s.size(); i++){
            if(s[i]=='0') c1 = 0;
            if(s[i-1]=='1' || s[i-1]=='2'&&s[i]<='6'){
                c1 = c1 + c2;
                c2 = c1 - c2;
            }
            else{
                c2 = c1;
            }
        }
        return c1;
    }
};

//递归
//1. Recursion O(2^n)
int numDecodings(string s) {
    return s.empty() ? 0: numDecodings(0,s);    
}
int numDecodings(int p, string& s) {
    int n = s.size();
    if(p == n) return 1;
    if(s[p] == '0') return 0;
    int res = numDecodings(p+1,s);
    if( p < n-1 && (s[p]=='1'|| (s[p]=='2'&& s[p+1]<'7'))) res += numDecodings(p+2,s);
    return res;
}
//2. recursion Memoization O(n)
int numDecodings(string s) {
    int n = s.size();
    vector<int> mem(n+1,-1);
    mem[n]=1;
    return s.empty()? 0 : num(0,s,mem);   
}
int num(int i, string &s, vector<int> &mem) {
    if(mem[i]>-1) return mem[i];
    if(s[i]=='0') return mem[i] = 0;
    int res = num(i+1,s,mem);
    if(i<s.size()-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) res+=num(i+2,s,mem);
    return mem[i] = res;
}



//3. dp O(n) time and space, this can be converted from #2 with copy and paste.
int numDecodings(string s) {
    int n = s.size();
    vector<int> dp(n+1);
    dp[n] = 1;
    for(int i=n-1;i>=0;i--) {
        if(s[i]=='0') dp[i]=0;
        else {
            dp[i] = dp[i+1];
            if(i<n-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) dp[i]+=dp[i+2];
        }
    }
    return s.empty()? 0 : dp[0];   
}


//4.dp constant space
int numDecodings(string s) {
    int p = 1, pp, n = s.size();
    for(int i=n-1;i>=0;i--) {
        int cur = s[i]=='0' ? 0 : p;
        if(i<n-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) cur+=pp;
        pp = p;
        p = cur;
    }
    return s.empty()? 0 : p;   
}


639. Decode Ways II







🌼🌼🌼//solution 2: time complexity: O(N) spce complexity: O(1)
class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s.front() == '0') return 0;
        int c1 = 1, c2 = 1;
        for (int i = 1; i < s.size(); ++i) {
            if (s[i] == '0') c1 = 0;
            if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6')) {
                c1 = c1 + c2;
                c2 = c1 - c2;
            } else {
                c2 = c1;
            }
        }
        return c1;
    }
};



5
10
32
44

53. Maximum Subarray
//dynamic programming: O(N) 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int curSum = 0;
        int res = INT_MIN;
        for(int i = 0; i<nums.size(); i++){
            curSum = max(curSum+nums[i], nums[i]);
            res = max(res, curSum);
        }
        return res;
    }
};
//
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //maxSubArray(A, i) = maxSubArray(A, i - 1) > 0 ? maxSubArray(A, i - 1) : 0 + nums[i];
        //i is the end element
        int res = INT_MIN;
        int cur = 0;
        for(int i=0; i<nums.size(); i++){
            cur = (cur>0? cur:0) + nums[i];
            res = max(res, cur);
        }
        return res;
    }

};

//divide and conquer: O(NlonN)
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //divied and conquer
        if(nums.empty()) return 0;
        return helper(nums, 0, (int)nums.size()-1); 
    }
    int helper(vector<int>& nums, int left, int right){
        if(left >= right) return nums[left];
        int mid = left + (right - left)/2;
        int lmax = helper(nums, left, mid-1);
        int rmax = helper(nums, mid+1, right);
        int mmax = nums[mid], t = nums[mid];
        for(int i = mid-1; i>=left; i--){
            t += nums[i];
            mmax = max(mmax, t);
        }
        t = mmax;
        for(int i = mid+1; i<=right; i++){
            t += nums[i];
            mmax = max(mmax, t);
        }
        return max(mmax, max(lmax, rmax));
    }
};

//follow up: minimum sum subarray (求相反数opposite num， 求maximum subarray就好了)
int maxSubArray(vector<int>& nums) {
    if(nums.empty()) return 0;
    int curSum = 0;
    int res = INT_MIN;
    for(int i = 0; i<nums.size(); i++){
        curSum = max(curSum+nums[i], nums[i]);
        res = max(res, curSum);
    }
    return res;
}


int minSubArray(vector<int>& nums) {
    for(int &a:nums) a=-a;
    return -1 * maxSubArray(nums);
}

int main(){
    vector<int> nums = {1, 2, 0, -1, -4, 4};
    cout<< minSubArray(nums) <<endl;
    return 0;
}



52. Maximum Product Subarray
/*Besides keeping track of the largest product, we also need to keep track of the smallest product. Why? 
The smallest product, which is the largest in the negative sense could become the maximum when being multiplied by a negative number.*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return -1;
        int mx = nums[0], mn = nums[0], res = nums[0];
        for(int i=1; i<nums.size(); i++){   //!!!
            int tmax = mx, tmin = mn;    //!!!
            mx = max(nums[i], max(tmax*nums[i], tmin*nums[i]));
            mn = min(nums[i], min(tmax*nums[i], tmin*nums[i]));
            res = max(res, mx);
        }
        return res;
    }
};



62. Unique Paths
//time cpmlexity: O(M*N), space comlexity: O(N*M)
class Solution {
public:
    int uniquePaths(int m, int n) {
        //m->col n->row
        vector<vector<int>> dp(n, vector<int>(m, 1));
        /*|1|1|1|
          |1|2|3|
        */
        //dp[i][j] = dp[i][j-1] + dp[i-1][j]
        for(int i=1; i<n; i++){
            for(int j=1; j<m; j++){
                dp[i][j] = dp[i][j-1] + dp[i-1][j];
            }
        }
        return dp[n-1][m-1];
        
    }
};


//solution 2
//time complexity: O(M*N), space complexity: O(N)
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        
        //general case dp[j] = dp[j] + dp[j-1]; 
        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                dp[j] = dp[j] + dp[j-1];
            }
        }
        return dp[n-1];
    }
};

//solution 3
//idea: m-1 from m+n-2, or pick n-1 from m+n-2
//C(m-1) (m+n-2)
//时间复杂度是O(min(m,n))，而空间复杂度是O(1)
class Solution {
public:
    int uniquePaths(int m, int n) {
        //pick m-1 from m+n-2;
        double a = 1, b = 1;
        
        for(int i=1; i<=min(m, n)-1; i++){
            a *= m+n-2 - i + 1;
            b *= i;
        }
        
        return (int)(a/b);
        
    }
};





63. Unique Paths II
//1d-dp
// DP
🌼🌼🌼class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        if (obstacleGrid.empty() || obstacleGrid[0].empty()) return 0;
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] == 1) return 0;
        vector<int> dp(n, 0);
        dp[0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) dp[j] = 0;
                else if (j > 0) dp[j] += dp[j - 1];
            }
        }
        return dp[n - 1];
    }
};

//2d-DP
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //dp[i][j] = dp[i-1][j] + dp[i][j-1]
        //if(obstacleGrid.empty() || obstacleGrid[0].empty()) return 0;
        
        int row = obstacleGrid.size();
        int col = obstacleGrid[0].size();
        
        vector<vector<int>> dp(row, vector<int>(col, 0));
        
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(obstacleGrid[i][j]==1) dp[i][j] = 0;
                else if(i==0 && j==0) dp[i][j] = 1;
                else if(i==0 && j!=0) dp[i][j] = dp[i][j-1];
                else if(i!=0 && j==0) dp[i][j] = dp[i-1][j];
                else dp[i][j] = dp[i-1][j] + dp[i][j-1];
                
            }
        }
        
        return dp[row-1][col-1];
    }
};


91


121. Best Time to Buy and Sell Stock
//time complexity: O(N), space complexity:O(1)
//record the min value before
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //complete at most one transaction
        //dynamic programming res = max(res, cur-mn);
        int res = 0;
        int mn = INT_MAX;
        for(int i=0; i<prices.size(); i++){
            res = max(res, prices[i]-mn);
            mn = min(mn, prices[i]);
        }
        return res;
    }
};



123. Best Time to Buy and Sell Stock III  
//easy to understand:

int maxProfit(int price[], int n) 
{ 
    // Create profit array and initialize it as 0 
    int *profit = new int[n]; 
    for (int i=0; i<n; i++) 
        profit[i] = 0; 
  
    /* Get the maximum profit with only one transaction 
       allowed. After this loop, profit[i] contains maximum 
       profit from price[i..n-1] using at most one trans. */
    int max_price = price[n-1]; 
    for (int i=n-2;i>=0;i--) 
    { 
        // max_price has maximum of price[i..n-1] 
        if (price[i] > max_price) 
            max_price = price[i]; 
  
        // we can get profit[i] by taking maximum of: 
        // a) previous maximum, i.e., profit[i+1] 
        // b) profit by buying at price[i] and selling at 
        //    max_price 
        profit[i] = max(profit[i+1], max_price-price[i]); 
    } 
  
    /* Get the maximum profit with two transactions allowed 
       After this loop, profit[n-1] contains the result */
    int min_price = price[0]; 
    for (int i=1; i<n; i++) 
    { 
        // min_price is minimum price in price[0..i] 
        if (price[i] < min_price) 
            min_price = price[i]; 
  
        // Maximum profit is maximum of: 
        // a) previous maximum, i.e., profit[i-1] 
        // b) (Buy, Sell) at (min_price, price[i]) and add 
        //    profit of other trans. stored in profit[i] 
        profit[i] = max(profit[i-1], profit[i] + 
                                    (price[i]-min_price) ); 
    } 
    int result = profit[n-1]; 
  
    delete [] profit; // To avoid memory leak 
  
    return result; 
} 


//dynamic programming
//You may complete at most two transactions.
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int hold1=INT_MIN, hold2=INT_MIN, release1=0, release2=0;
        for(auto price:prices){
            hold1 = max(hold1, -price);
            release1 = max(release1, hold1+price);
            hold2 = max(hold2, release1-price);
            release2 = max(release2, hold2+price);
        }
        return release2;
    }
}; 


714. Best Time to Buy and Sell Stock with Transaction Fee
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int sold = 0;
        int hold = -prices[0];
        for(auto p:prices){
            int t = sold;
            sold = max(sold, hold+p-fee);
            hold = max(hold, t-p);
        }
        return sold;
     }
};


801. Minimum Swaps To Make Sequences Increasing  ???
//solution 1
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> swap(n, n), noSwap(n, n);
        swap[0] = 1; noSwap[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (A[i] > A[i - 1] && B[i] > B[i - 1]) {
                swap[i] = swap[i - 1] + 1;
                noSwap[i] = noSwap[i - 1];
            }
            if (A[i] > B[i - 1] && B[i] > A[i - 1]) {
                swap[i] = min(swap[i], noSwap[i - 1] + 1);
                noSwap[i] = min(noSwap[i], swap[i - 1]);
            }
        }
        return min(swap[n - 1], noSwap[n - 1]);
    }
};
//solution 2
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n1 = 0, s1 = 1, n = A.size();
        for (int i = 1; i < n; ++i) {
            int n2 = INT_MAX, s2 = INT_MAX;
            if (A[i - 1] < A[i] && B[i - 1] < B[i]) {
                n2 = min(n2, n1);
                s2 = min(s2, s1 + 1);
            }
            if (A[i - 1] < B[i] && B[i - 1] < A[i]) {
                n2 = min(n2, s1);
                s2 = min(s2, n1 + 1);
            }
            n1 = n2;
            s1 = s2;
        }
        return min(n1, s1);
    }
};



139. Word Break
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<bool> dp(s.size()+1, false);
        dp[0] = true;  //!!!
        
        for(int i=0; i<dp.size(); i++){
            for(int j=0; j<i ;j++){
                if(dp[j] && count(wordDict.begin(), wordDict.end(), s.substr(j, i-j))){
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp.back();
    }
};


🌼🌼🌼//
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //space complexity: O(N)
        //dp
        unordered_set<string> st(wordDict.begin(), wordDict.end());
        
        vector<bool> dp(s.size()+1, false); //dp[i]: if the substr before i can be break
        dp[0] = true;
        
        for(int i=0; i<dp.size(); i++){
            for(int j=0; j<i; j++){
                if(dp[j] && st.count(s.substr(j, i-j))){
                    dp[i] = true;
                    break;   
                }
            }
        }
        
        return dp.back();
        
    }
};

140. Word Break II
//DFS  + hash table
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> m;
        return helper(s, wordDict, m);
    }
    
    vector<string> helper(string s, vector<string>& wordDict, unordered_map<string, vector<string>>& m){
        if(m.count(s)) return m[s];
        if(s.empty()) return {""};  //!!!
        vector<string> res;
        for(auto word:wordDict){
            if(s.substr(0, word.size()) != word) continue;
            vector<string> tmp = helper(s.substr(word.size()), wordDict, m);
            for(auto str:tmp){
                res.push_back(word + (str.empty()?"":" ") + str);
            }
        }
        m[s] = res;
        return res;
        
    }
};


198. House Robber
class Solution {
public:
    int rob(vector<int>& nums) {
        //note: do not rob two adjacent houses 
        //idea/plan: dynamic programming. dp[i] = max(dp[i-1], dp[i-2]+nums[i])
        //time&space complexity: O(N) O(N)
        //example: 
        //corner cases:dp[0] = nums[0], dp[1] = max(nums[0], nums[1])
        if(nums.empty()) return 0;
        
        int n = nums.size();
        vector<int> dp(n, 0);
        dp[0] = nums[0];    //dp要注意corner cases！！！一般要先手动赋值！！！
        dp[1] = max(nums[0], nums[1]);
        for(int i=2; i<n; i++){
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
        }
        return dp[n-1];
    }
};



300. Longest Increasing Subsequence
//O(n^2) dp solution  and O(nlogn) binary search solution
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int mx_len = 1;
        vector<int> dp(nums.size(), 1);
        for(int i=0; i<nums.size(); i++){
            for(int j=0; j<i; j++){
                if(nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j]+1);  // dp[i] = max(dp[i], dp[j]+1)
            }
            mx_len = max(mx_len, dp[i]);   //!!!!!!
        }
        return mx_len;

    }
};


//O(n^2) dp solution  and O(nlogn) binary search solution
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // length of longest increasing subsequence
        // return len
        //O(n^2)   --->  O(nlogn)
        //time complexity: O(n^2)  ---> dp
        /********************************************************************
        if(nums.empty()) return 0;
        int mx_len = 1;
        vector<int> dp(nums.size(), 1);
        for(int i=0; i<nums.size(); i++){
            for(int j=0; j<i; j++){
                if(nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j]+1);  // dp[i] = max(dp[i], dp[j]+1)
            }
            mx_len = max(mx_len, dp[i]);   //!!!!!!
        }
        return mx_len;
        *********************************************************************/
        //time complexity: O(nlogn)  ---> binary search + dp 这种方法返回的不一定是最后的longest subsequence
        //go through*binary search   ---> time complecity: O(nlogn)
        //swap(nums[i], the first one bigger than nums[i] in the dp) to make dp smaller
        //if there is no nums in dp bigger than nums[i], push nums[i] into dp
        //return the size of dp
        //[10,9,2,5,3,7,101,18]
        //                  ^
        //dp: 2, 3, 7, 18
        vector<int> dp;
        for(int i=0; i<nums.size(); i++){
            int index = findBigger(nums[i], dp); //!!!find >=
            if(index >= dp.size()) dp.push_back(nums[i]);    //do not exist bigger num in dp--> push
            else dp[index] = nums[i];     //exist--> swap 
        }
        return dp.size();
    }
    int findBigger(int x, vector<int> nums){   //binary search
        int left=0, right = nums.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] < x) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
};


673. Number of Longest Increasing Subsequence
//dynamic programming
//time complexity: O(N^2)
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        //dp
        if(nums.empty()) return 0;
        int n = nums.size();
        
        int mx_len = 0, res = 0;
        vector<int> len(n, 1), cnt(n, 1);
        for(int i=0; i<nums.size(); i++){
            for(int j=0; j<i; j++){
                if(nums[j] >= nums[i]) continue;
                if(len[j]+1 == len[i]){
                    cnt[i] += cnt[j];
                }else if(len[j]+1 > len[i]){
                    len[i] = len[j]+1;
                    cnt[i] = cnt[j];
                }
            }
            if(len[i]==mx_len) res += cnt[i];
            else if(len[i]>mx_len){
                mx_len = len[i];
                res = cnt[i];
            }
        }
        return res;
    }
};


//
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        //dp
        //cnt[i] means Number of LIS of subarray(0, i);
        // len[i] means length of LIS of subarray(0, i);
        
        //len[i] == len[j]+1 cnt[i] += cnt[j] 
        //len[i] < len[j]+1 cnt[i] = cnt[j] len[i] = len[j+1]
        if(nums.empty()) return 0;
        int n = nums.size();
        vector<int> cnt(n, 1), len(n, 1);
        
        int max_len=0, max_cnt=0;
        for(int i=0; i<n; i++){
            for(int j=0; j<i; j++){
                if(nums[j]<nums[i]){
                    if(len[i] == len[j]+1) cnt[i] += cnt[j];
                    else if(len[i] < len[j]+1){ 
                        len[i] = len[j]+1; 
                        cnt[i] = cnt[j];
                    }
                }
            }
            if(len[i]==max_len){max_cnt += cnt[i];}
            else if(len[i]>max_len){max_len = len[i]; max_cnt = cnt[i];}
        }
        
        return max_cnt;
    }
};

334. Increasing Triplet Subsequence
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        // O(n) time complexity and O(1) space complexity
        int n1=INT_MAX, n2=INT_MAX;
        for(auto num:nums){
            if(num<n1) n1=num; //(it's a candidate for 1st element)
            else if(num>n1 && num<n2) n2=num;  //(it's a candidate for 2st element)
            else if(num>n2) return true;  //(a candidate for 3st element appearite)
        }
        return false;
    }
};



303. Range Sum Query - Immutable
class NumArray {
private: vector<int> sum;
public:
    NumArray(vector<int> nums) {
        if(nums.empty()) return;
        //num vector ---> sum vector
        sum = vector<int>(nums.size()+1, 0);
        for(int i=1; i<=nums.size(); i++){
            sum[i] = nums[i-1] + sum[i-1];
        }
        
    }
    
    int sumRange(int i, int j) {
       return sum[j+1] - sum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * int param_1 = obj.sumRange(i,j);
 */
304. Range Sum Query 2D - Immutable
//DP
class NumMatrix {
private:
    vector<vector<int>> sum;
public:
    NumMatrix(vector<vector<int>> matrix) {    
        //my plan:
        //preprocess; num matrix ---> sum matrix
        /*
        ..............
        ..............
        ....p1...p2...
        ..............
        ....p3...p4...
        ..............
        sum(p1, p4) = sum(p4) - sum(p2) - sum(p3) + sum(p1); 
        */
        if (matrix.empty() || matrix[0].empty()) return;
        int row = matrix.size(), col = matrix[0].size();
        sum = vector<vector<int>>(row+1, vector<int>(col+1, 0));    //!!!row+1, col+1
        for(int i=1; i<=row; i++){
            for(int j=1; j<=col; j++){
                sum[i][j] = matrix[i-1][j-1] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1]; //!!!
            }
        }
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2+1][col2+1] -sum[row1][col2+1] -sum[row2+1][col1] +sum[row1][col1]; //!!!row2+1 col2+1
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

//another solution
class NumMatrix {
private:
    vector<vector<int>> sums;

public:
    NumMatrix(vector<vector<int>> matrix) {   
        if(matrix.empty() || matrix[0].empty()) return;
        
        int row = matrix.size();
        int col = matrix[0].size();
        
        sums.resize(row, vector<int>(col, 0));
        
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(i==0 && j==0) sums[i][j] = matrix[0][0];
                else if(i==0) sums[i][j] = matrix[i][j] + sums[i][j-1];
                else if(j==0) sums[i][j] = matrix[i][j] + sums[i-1][j];
                else sums[i][j] = matrix[i][j] + sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1];
            }
        }
        
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        if(row1==0 && col1==0) return  sums[row2][col2];
        else if(row1 == 0) return sums[row2][col2] - sums[row2][col1-1];
        else if(col1 == 0) return sums[row2][col2] -sums[row1-1][col2];
        else return sums[row2][col2] - sums[row2][col1-1] -sums[row1-1][col2] + sums[row1-1][col1-1];
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * int param_1 = obj.sumRegion(row1,col1,row2,col2);
 */

307. Range Sum Query - Mutable   ???
//binary indexed tree
//segment tree
class NumArray {
private:
    vector<int> num;
    vector<int> tree;
public:
    NumArray(vector<int> nums) {
        num.resize(nums.size()+1);
        tree.resize(nums.size()+1);
        for(int i=0; i<nums.size(); i++){
            update(i, nums[i]);
        }
    }
    
    void update(int i, int val) {
        int diff = val-num[i+1];
        for(int j=i+1; j<num.size(); j+=(j&-j)){
            tree[j] += diff;
        }
        num[i+1] = val;
    }
    
    int sumRange(int i, int j) {
        return getSum(j+1)-getSum(i);
    }
    
    int getSum(int i){
        int res = 0;
        for(int j=i; j>0; j-=(j&-j)){
            res += tree[j];
        }
        return res;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */




308. Range Sum Query 2D - Mutable  ???
class NumMatrix {
private:
    vector<vector<int>> tree;
    vector<vector<int>> mat;
public:
    NumMatrix(vector<vector<int>> matrix) {
        if(matrix.empty()||matrix[0].empty()) return;
        tree.resize(matrix.size()+1, vector<int>(matrix[0].size()+1, 0));
        mat.resize(matrix.size()+1, vector<int>(matrix[0].size()+1, 0));
        for(int i=0; i<matrix.size(); i++){
            for(int j=0; j<matrix[0].size(); j++){
                update(i, j, matrix[i][j]);
            }
        }
        
    }
    
    void update(int row, int col, int val) {
        int diff = val - mat[row+1][col+1];
        for(int i = row+1; i<mat.size(); i+=i&-i){
            for(int j = col+1; j<mat[0].size(); j+=j&-j){
                tree[i][j] += diff;
            }
        }
        mat[row+1][col+1] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return getSum(row2+1, col2+1) - getSum(row1, col2+1) - getSum(row2+1, col1) + getSum(row1, col1);
    }
    
    int getSum(int row, int col){
        int res = 0;
        for(int i=row; i>0; i-=i&-i){
            for(int j=col; j>0; j-=j&-j){
                res += tree[i][j];
            }
        }
        return res;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix obj = new NumMatrix(matrix);
 * obj.update(row,col,val);
 * int param_2 = obj.sumRegion(row1,col1,row2,col2);
 */



377. Combination Sum IV
 //不同顺序算不一样
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        //dynamic programming dp[i] += dp[i-val]
        //example: [1, 2, 3]
        //                ^
        //3=2+1, 3=1+2, 3=0+3;   ->  dp[3]=d[2]+dp[1]+dp[3]; dp[i] += dp[i-num]
        //for every i(1, target), for every num in nums, if(num<i) dp[i]+=sp[i-num] 
        vector<int> dp(target+1, 0);
        dp[0] = 1;    //dp[0]=1;
        for(int i=1; i<=target; i++){
            for(auto num:nums){
                if(num<=i) dp[i] += dp[i-num];   //!!!等号  
            }
        }
        return dp[target];
    }
    
};

//
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        //顺序无关 可重复
        vector<int> dp(target+1, 0);
        //dp[i] means the numer of combination ways of i
        // dp[i] = dp[i] + dp[i-num]
        dp[0] = 1;
        
        for(int i=0; i<=target; i++){
            for(int num:nums){
                if(i-num>=0) dp[i] += dp[i-num];
            }
        }
        
        return dp[target];
    }
    
};





322. Coin Change
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //fewest number of coins 
        vector<int> dp(amount+1, amount+1); //dp[amount] = fewest_num
        dp[0] = 0;   //dp[0]=0;
        for(int i=1; i<=amount; i++){
            for(auto coin:coins){
                if(coin <= i)               //!!!等号
                    dp[i] = min(dp[i], dp[i-coin]+1);  //!!!+1
            }
        }
        return dp[amount]==amount+1?-1:dp[amount];
        
    }
};

518. Coin Change 2   ！！！
//不同顺序算一种
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        vector<int> dp(amount+1, 0);
        dp[0]=1;
        for(auto coin:coins){
            for(int i=coin; i<=amount; i++){
                dp[i] += dp[i-coin];
            }
        }
        return dp[amount];
    }
};


//
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        //顺序有关 可重复
        vector<int> dp(amount+1, 0);
        dp[0] = 1;
        //dp[i] means number of combinations of i
        //dp[i] = dp[i] + dp[i-num]
        
        for(auto coin:coins){
            for(int i = coin; i<=amount; i++){
                dp[i] += dp[i-coin];
            }
        }
        
        return dp[amount];
    }
};




416. Partition Equal Subset Sum
//变成---> 找target sum/2
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        //only positive int
        //into two subsets sith same sums
        
        // if sum%2!=0 then return fasle;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum%2!=0) return false;
        
        //if sum%2==0
        int target = sum/2;
        vector<bool> dp(target+1, false);
        dp[0] = true;
        for(int num:nums){
            for(int i=target;i>=num;i--){  //nums[i]只能用一次!!!所以i要递减
                dp[i] = dp[i]||dp[i-num];
            }
        }
        return dp[target];
    }
    
};





523
647



688. Knight Probability in Chessboard
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        //(r,c) move k steps to (x,y)  = (x,y) move k steps to (r,c)
        if(K == 0) return 1;
        vector<vector<double>> dp(N, vector<double>(N, 1));
        vector<vector<int>> dirs{{-1,-2},{-2,-1},{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2}};
        for(int m=0; m<K; m++){
            vector<vector<double>> t(N, vector<double>(N, 0));
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    for(auto dir:dirs){
                        int x = i+dir[0], y = j+dir[1];
                        if (x < 0 || x >= N || y < 0 || y >= N) continue; //!!!
                        t[i][j] += dp[x][y];
                    }
                }
            }
            dp = t;
        }
        return dp[r][c]/pow(8, K);
    }
};

//
class Solution {
public:
    double knightProbability(int N, int K, int r, int c) {
        //(r,c) 位置走完当前步还剩多少 ＝ (r,c)的neighbors走完前面一步还剩多少的总和
        //dp[i][j] means: start from (i, j) and after k steps, how many elments left in the chess board.
        //dp[i][j] after k steps = sum(dp[i][j]'s neighbors after k-1 steps);
        
        vector<vector<double>> dp(N, vector<double>(N, 1));  //!!!double
        vector<vector<int>> dirs = {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-1, -2}, {-2, -1}};
        
        for(int s = 0; s<K; s++){
            vector<vector<double>> tmp(N, vector<double>(N, 0));
            for(int i=0; i<N; i++){
                for(int j=0; j<N; j++){
                    for(auto dir:dirs){
                        int x = i + dir[0], y = j + dir[1];
                        if(x<0 || y<0 || x>=N || y>=N) continue;  //!!!越界
                        tmp[i][j] += dp[x][y];
                    }
                }
            }
            dp = tmp;
        }
        
        return dp[r][c]/pow(8, K);
    }
};


689. Maximum Sum of 3 Non-Overlapping Subarrays
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        //3 k-length subarray
        //with max sum
        //check input
        if(nums.empty()) return {};
        int n = nums.size();
        
        //dynamic programming
        vector<int> sums{0};
        for(int num:nums) sums.push_back(sums.back()+num);
        
        vector<int> posLeft(n, 0), posRight(n, n-k);
        //dp of start index of mx left interval
        for(int i=k, total = sums[k] - sums[0]; i<n; i++){
            if(sums[i+1] - sums[i+1-k] > total){
                total = sums[i+1] - sums[i+1-k];
                posLeft[i] = i+1-k;
            }else{
                posLeft[i] = posLeft[i-1];   
            }
        }
        
        //dp of start index of mx right interval
        for(int i= n-k-1, total = sums[n] - sums[n-k]; i>=0; i--){
            if(sums[i+k] - sums[i] >= total){   //!!!
                total = sums[i+k] - sums[i];
                posRight[i] = i;
            }else{
                posRight[i] = posRight[i+1];
            }
        }
        
        vector<int> res;
        int mx = 0;
        //test middle index
        for(int i=k; i<=n-k*2; i++){
            int l = posLeft[i-1], r = posRight[i+k];
            int sum = (sums[i+k]-sums[i]) + (sums[l+k]-sums[l]) + (sums[r+k]-sums[r]);
            if(sum>mx){
                mx = sum;
                res = {l, i, r};
            }
        }
        return res;
        
        
    }
};


361. Bomb Enemy
//solution 1
class Solution {
private:
    vector<vector<int>> dirs = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        //return the maximum enemies you can kill using one bomb.
        if(grid.empty() || grid[0].empty()) return 0;
        int row = grid.size();
        int col = grid[0].size();
        int res = 0;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(grid[i][j] == '0') helper(grid, i, j, res);
            }
        }
        return res;
    }
    
    void helper(vector<vector<char>>& grid, int i, int j, int& res){
        int cur = 0;
        for(auto dir:dirs){
            int x = i+dir[0], y = j+dir[1];
            while(x>=0 && x<grid.size() && y>=0 && y<grid[0].size() && grid[x][y]!='W'){
                if(grid[x][y]=='E') cur++;
                x+=dir[0];
                y+=dir[1];
            }
        }
        res = max(cur, res);
    }
};



？？？//solution 2  
class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0, rowCnt, colCnt[n];
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == 0 || grid[i][j - 1] == 'W') {
                    rowCnt = 0;
                    for (int k = j; k < n && grid[i][k] != 'W'; ++k) {
                        rowCnt += grid[i][k] == 'E';
                    }
                }
                if (i == 0 || grid[i - 1][j] == 'W') {
                    colCnt[j] = 0;
                    for (int k = i; k < m && grid[k][j] != 'W'; ++k) {
                        colCnt[j] += grid[k][j] == 'E';
                    }
                }
                if (grid[i][j] == '0') {
                    res = max(res, rowCnt + colCnt[j]);
                }
            }
        }
        return res;
    }
};


221. Maximal Square
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        //largest square area
        if(matrix.empty() || matrix[0].empty()) return 0;
        int row = matrix.size();
        int col = matrix[0].size();
        
        int res = 0;
        vector<vector<int>> dp(row, vector<int>(col, 0)); //largest edge size
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(i==0 || j==0) dp[i][j] = matrix[i][j] - '0';
                else if(matrix[i][j] == '1') dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                res = max(res, dp[i][j]*dp[i][j]);
                
            }
        }
        return res;
    }
    
};


750. Number Of Corner Rectangles
//time complexity O(row*row*col)
class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        
        int row = grid.size();
        int col = grid[0].size();
        if(row < 2 || col < 2) return 0;
        
        int res = 0;
        for(int i=0; i<row; i++){   
            for(int j= i+1; j<row; j++){   //row: i, row:j
                int cnt = 0;
                for(int k =0; k<col; k++){   //row i和 row j之间的平行线
                    if(grid[i][k]==1 && grid[j][k]==1) cnt++;
                } 
                res += cnt*(cnt-1)/2;  //平行线之间两两组和
            }
        }
        
        return res;
    }

};

764. Largest Plus Sign
class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        if(N==0) return 0;
        
        
        vector<vector<int>> dp(N, vector<int>(N, N));
        for(auto mine:mines) dp[mine[0]][mine[1]]=0;
        
        for(int i=0; i<N; i++){
            int l = 0, r = 0, u = 0, d = 0;
            for(int j=0, k = N-1; j<N; j++, k--){
                dp[i][j] = min(dp[i][j], l = dp[i][j]?l+1:0);
                dp[j][i] = min(dp[j][i], u = dp[j][i]?u+1:0);
                dp[i][k] = min(dp[i][k], r = dp[i][k]?r+1:0);
                dp[k][i] = min(dp[k][i], d = dp[k][i]?d+1:0);
            }
        }
        
        int res = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};


403. Frog Jump
class Solution {
public:
    bool canCross(vector<int>& stones) {
        //new solution
        unordered_map<int, bool> dp;  //表示frog在pos上弹跳力为k是否能到达终点
        return canCross(stones, 0, 0, dp);
    }
    
    bool canCross(vector<int>& stones, int pos, int k, unordered_map<int, bool>& dp){
        int key = pos|k<<11;
        if(dp.count(key)) return dp[key];
        
        for(int i=pos+1; i<stones.size(); i++){
            int gap = stones[i]-stones[pos];
            if(gap < k-1) continue;
            if(gap > k+1) return dp[key]=false;
            if(canCross(stones, i, gap, dp)) return dp[key]=true;
        }
        return dp[key] = (pos == stones.size()-1);
    }
};




******************************************************************************************************************************************
heap
******************************************************************************************************************************************
215. Kth Largest Element in an Array
//solution 1: min_heap. time complexity: O(NlogK) space complexity:O(k)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //using min_heap to store the biggest element of array
        priority_queue<int, vector<int>, greater<int>> q;
        
        //keep the size of min_heap <= k
        for(int i = 0; i< nums.size(); i++){
            q.push(nums[i]);  
            if(q.size()>k) q.pop();
        }
        // min_heap contains k biggest element 
        // and the top num is the kth biggest element
        return q.top();  
    }
};

//solution 2: max_heap. time complexity: O(NlogN) space complexity:O(N)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> q(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; ++i) {
            q.pop();
        }
        return q.top();
    }
};

//solution 3: quick select: The worst case time complexity of this method is O(n2), but it works in O(n) on average.
//time complexity: O(n) is the average/best time complexity, T(n) = T(n/2) + O(n)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //sort 
        //min heap
        //quick sort kth pivot
        
        int left = 0, right = nums.size()-1;
        while(true){
            int pos = partition(nums, left, right);
            if(pos == k-1) return nums[pos];
            else if(pos > k-1) right = pos-1;
            else left = pos+1;
        }
    }
    
    int partition(vector<int>& nums, int left, int right){
        int pivot = nums[left], l = left+1, r = right;  //!!! left+1
        while(l<=r){
            if(nums[l] < pivot && nums[r] > pivot)
                swap(nums[l++], nums[r--]);
            if(nums[l] >= pivot)
                l++;
            if(nums[r] <= pivot)
                r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }
};





347. Top K Frequent Elements
//solution 1: min_heap
//time complexity: N(logK)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(nums.empty()) return {};
        unordered_map<int, int> m;
        for(auto num:nums) m[num]++;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; //pair<count, num> min_heap
        for(auto a:m){
            q.push({a.second, a.first});
            if(q.size()>k) q.pop();
        }
        vector<int> res;
        while(!q.empty()){
            res.push_back(q.top().second);
            q.pop();
        }
        return res;      
    }
};
//solution2: max_heap   ???为什么还是这个运行快一些？？？
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        if(nums.empty()) return {};
        unordered_map<int, int> m;
        for(auto num:nums) m[num]++;
        
        priority_queue<pair<int, int>> q; //pair<count, num> max_heap
        for(auto a:m){
            q.push({a.second, a.first});
        }
        vector<int> res;
        int i = 0;
        while(++i<=k){
            res.push_back(q.top().second);
            q.pop();
        }
        return res;      
    }
};



//solution 3: bucket sort
//time complexity: O(N), space complexity: O(N)？ O(N^2)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // max heap
        // min heap
        //bucket sort
        unordered_map<int, int> m; //map<num, count>
        for(int num:nums) m[num]++;
        
        vector<vector<int>> buckets(nums.size()+1);
        for(auto a:m){
            buckets[a.second].push_back(a.first);
        }
        reverse(buckets.begin(), buckets.end());
        
        vector<int> res;
        for(auto bucket:buckets){
            for(int i=0; i<bucket.size(); i++){
                res.push_back(bucket[i]);
                if(res.size()==k) return res;
            }    
        }
        return {};
        
    }
};


378. Kth Smallest Element in a Sorted Matrix
class Solution {
public:
    int kthSmallest(vector<vector<int> >& matrix, int k) {
        //1. using heap-->time complexity:O(n*n*logk)
        /*
        if(matrix.empty() || matrix[0].empty()) return -1;
        priority_queue<int> q;
        for(int i=0; i<matrix.size(); i++){
            for(int j =0; j<matrix[0].size(); j++){
                q.push(matrix[i][j]);
                if(q.size()>k) q.pop();
            }
        }
        return q.top();
        */
        //2. using binary search  --> time complexity: O((n+m)*log(max-min))
        int left = matrix[0][0], right=matrix.back().back();
        while(left<=right){
            int mid = left+(right-left)/2;
            if(search_less_or_equal(matrix, mid) < k) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
    
    int search_less_or_equal(vector<vector<int>>& matrix, int target){
        int n = matrix.size();
        int row = n-1, col = 0;
        int count = 0;
        while(row>=0 && col<n){
            if(matrix[row][col]<=target){
                count += row+1;
                col++;
            }
            else{
                row--;
            }
        }
        return count;
    }
};




692. Top K Frequent Words
struct cmp{
    bool operator() (pair<string, int> p1, pair<string, int> p2){
        return p1.second>p2.second || p1.second==p2.second && p1.first<p2.first;
    }
};
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        //O(n log k) time and O(n) extra space
        //hash map + min_heap
        unordered_map<string, int> m;
        for(string word:words){
            m[word]++;
        }
        
        priority_queue<pair<string, int>, vector<pair<string, int>>, cmp> q;
        for(auto a:m){
            q.push(a);
            if(q.size()>k) q.pop();
        }
        
        vector<string> res(k);
        int i = k-1;
        while(!q.empty()){
            res[i--] = q.top().first;
            q.pop();
        }
        return res;
    }
};

767. Reorganize String
class Solution {
public:
    string reorganizeString(string S) {
        string res = "";
        unordered_map<char, int> m;
        for(char c:S) m[c]++;
        
        priority_queue<pair<int, char>> q;  //max heap
        for(auto a:m){
            if (a.second > (S.size() + 1) / 2) return "";
            q.push({a.second, a.first});
        }
        while(q.size()>=2){
            auto t1 = q.top(); q.pop();
            auto t2 = q.top(); q.pop();
            res.push_back(t1.second);
            res.push_back(t2.second);
            if(--t1.first>0) q.push(t1);
            if(--t2.first>0) q.push(t2);
        }
        if(!q.empty()) {res.push_back(q.top().second);}
        return res;
    }
};

**************************************************************************************************************************
stack
**************************************************************************************************************************
20. Valid Parentheses
//solution 1: using stack, time complecity O(N), space complecity O(N)
class Solution {
public:
    bool isValid(string s) {
        //Note that an empty string is also considered valid.
        if(s.empty()) return true;
        
        stack<char> st;
        for(int i=0; i<s.size(); i++){
            char c = s[i];
            
            if(c=='{' || c=='[' || c=='(') {
              //cout<<"here"<<endl;
              st.push(c);
            }
            
            else{
              switch(c){
                case '}': if(!st.empty() && st.top()=='{') st.pop(); else return false; break;
                case ']': if(!st.empty() && st.top()=='[') st.pop(); else return false; break;
                case ')': if(!st.empty() && st.top()=='(') st.pop(); else return false; break;
              }
            }
        }
        if(st.empty()) return true;
        else return false;
               
    }
};
42

71. Simplify Path
//using vector
class Solution {
public:
    string simplifyPath(string path) {
        string res, t;
        stringstream ss(path);
        vector<string> v;
        while(getline(ss, t, '/')){
            if(t=="" || t==".") continue;
            if(t=="..") {
                if(!v.empty())    //!!!
                    v.pop_back();
            }
            else v.push_back(t);
        }
        for(string s:v){
            res += '/'+s;
        }
        return res.empty()?"/":res;  //!!!
    }
};


🌼🌼🌼//stack
class Solution {
public:
    string simplifyPath(string path) {
        string res, t;
        stack<string> st;
        istringstream is(path);
        while(getline(is, t, '/')){
            if(t=="." || t=="") continue;
            else if(t==".."){
                if(!st.empty()) st.pop();  //!!!
            }
            else st.push(t);
        }
        while(!st.empty()){
            res ="/" + st.top() + res;
            st.pop();
        }
        return res.empty()?"/":res;    //!!!
    }
};
84

94

103. Binary Tree Zigzag Level Order Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        //LIFO
        //two stacks
        if(root==NULL) return {};
        vector<vector<int>> res;
        vector<int> out;
        stack<TreeNode*> st1, st2;
        st1.push(root);
        while(!st1.empty() || !st2.empty()){
            while(!st1.empty()){
                TreeNode* node = st1.top();
                st1.pop();
                out.push_back(node->val);
                if(node->left) st2.push(node->left);
                if(node->right) st2.push(node->right);
            }
            if(!out.empty()) res.push_back(out);   //!!!!out.empty()
            out.clear();
            while(!st2.empty()){
                TreeNode* node = st2.top();
                st2.pop();
                out.push_back(node->val);
                if(node->right) st1.push(node->right);   //!!!st2->st1 right first
                if(node->left) st1.push(node->left);
            }
            if(!out.empty()) res.push_back(out);
            out.clear();
        }
        return res;
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(!root) return {};
        
        vector<vector<int>> res;
        vector<int> out;
        
        stack<TreeNode*> st1, st2;
        st1.push(root);
        while(!st1.empty() || !st2.empty()){
            while(!st1.empty()){
                TreeNode* node = st1.top();
                st1.pop();
                out.push_back(node->val);
                if(node->left) st2.push(node->left);
                if(node->right) st2.push(node->right);
            }
            if(!out.empty()) res.push_back(out);
            out.clear();
            while(!st2.empty()){
                TreeNode* node = st2.top();
                st2.pop();
                out.push_back(node->val);
                if(node->right) st1.push(node->right);
                if(node->left) st1.push(node->left);
            }
            if(!out.empty()) res.push_back(out);
            out.clear();
        }
        
        return res;
    }
};


173. Binary Search Tree Iterator
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //next smallest number in the BST. -> inorder
class BSTIterator {
private:
    stack<TreeNode*> st;
public:
    BSTIterator(TreeNode *root) {
        find_left(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(st.empty()) return false;
        else return true;
    }
    /** @return the next smallest number */
    int next() {
        TreeNode* node = st.top();
        st.pop();
        find_left(node->right);
        return node->val;
    }
    
    void find_left(TreeNode* root){
        while(root){
            st.push(root);
            root = root->left;
        }
    }
};

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
//recursion iteration
class NestedIterator {
private:
    stack<NestedInteger> st;
    
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size()-1; i>=0; i--) st.push(nestedList[i]);
    }

    int next() {
        int t = st.top().getInteger();
        st.pop();
        return t;
    }

    bool hasNext() {
        while(!st.empty()){
            auto it =  st.top();
            if(it.isInteger()) return true;
            else{
                st.pop();
                for(int i = it.getList().size()-1; i>=0; i--){
                    st.push(it.getList()[i]);
                }
            }
            
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */



394. Decode String
//"3[a]2[bc]" 
//push stack untill ']'
class Solution {
public:
    string decodeString(string s) {
        stack<char> st;
        for(char c:s){
            if(c!=']') st.push(c);
            else{
                string str = "";
                
                while(!st.empty() && st.top()!='[') {
                    str = st.top()+str; 
                    st.pop();   
                }
                st.pop();  //pop '['
                string num = "";
                while(!st.empty() && st.top()>='0' && st.top()<='9'){
                    num = st.top() + num;
                    st.pop();
                }
                int n = stoi(num);
                
                for(int i=0; i<n; i++){
                    for(char c:str){
                        st.push(c);
                    }
                }
            }
        }
        string res = "";
        while(!st.empty()){
            res = st.top() + res;
            st.pop();
        }
        return res;
    }
};



439. Ternary Expression Parser
class Solution {
public:
    string parseTernary(string expression) {
        stack<int> st;
        for(int i=0; i<expression.size(); i++){
            if(expression[i] == '?') st.push(i);   //!!!将？的index压入栈
        }
        string res = expression;
        while(!st.empty()){
            int pos = st.top(); st.pop();
            res = res.substr(0, pos-1) + cal(res.substr(pos-1, 5)) + res.substr(pos+4);
        }
        
        return res;
    }
    
    string cal(string exp){
        if(exp.size() != 5) return "";
        return exp[0]=='T' ? exp.substr(2, 1) : exp.substr(4);
    }
};




636. Exclusive Time of Functions
//using stack + pretime
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        /*
        ["0:start:0",   
         "1:start:2",  time of fun0 + 2  push()
         "1:end:5",    time of fun1 + 3  pop()
         "0:end:6"]    time of fun0 + 1
        */
        vector<int> res(n, 0);
        stack<int> st; //store id
        int pretime = 0;
        for(string log:logs){
            int pos1 = log.find(":");
            int pos2 = log.rfind(":");
            //id:type:time
            int id = stoi(log.substr(0, pos1));
            string type = log.substr(pos1+1, pos2-pos1-1);
            int time = stoi(log.substr(pos2+1));
            
            if(!st.empty()) res[st.top()] += time - pretime;
            pretime = time;
            
            if(type == "start") st.push(id);
            else if(type == "end") {int t = st.top(); st.pop(); res[t]++; pretime++;}  //"0:end:0" means function 0 ends to the very end of time 0. 
            
        }
        return res;
    }
};



class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        /*
        ["0:start:0",   
         "1:start:2",  time of fun0 + 2  push()
         "1:end:5",    time of fun1 + 3  pop()
         "0:end:6"]    time of fun0 + 1
        */
        vector<int> res(n, 0);
        stack<int> st;
        int pre_time = 0;
        for(string log:logs){
            int pos1 = log.find(":");
            int pos2 = log.rfind(":");
            
            int label = stoi(log.substr(0, pos1));
            string type = log.substr(pos1+1, pos2-pos1-1);
            int time = stoi(log.substr(pos2+1));
            
            if(type == "start") {
                if(!st.empty()) res[st.top()] += time - pre_time; 
                pre_time = time; 
                st.push(label);
            }
            else if(type == "end"){
                if(!st.empty()) res[st.top()] += time - pre_time + 1;   //!!!
                pre_time = time+1;    //!!!
                st.pop();
            }
        }
        
        return res;
    }
};




844. Backspace String Compare
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        string s = parse(S);
        string t = parse(T);
        return s==t;
    }
    
    string parse(string s){
        string res = "";
        for(char c:s){
            if(c=='#'){ if(!res.empty()) res.pop_back();}
            else res.push_back(c);
        }
        return res;
    }
    
};


150. Evaluate Reverse Polish Notation
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(auto s:tokens){
            if(s=="+" || s=="-" || s=="*" || s=="/"){
                int b = st.top();
                st.pop();
                int a = st.top();
                st.pop();
                switch(s[0]){
                    case '+': st.push(a+b); break;
                    case '-': st.push(a-b); break;
                    case '*': st.push(a*b); break;
                    case '/': st.push(a/b); break;
                }
            }
            else{
                st.push(stoi(s));
            }
        }
        return st.top();
    }
};



155. Min Stack
//one stack
class MinStack {
private:
    stack<int> st;
    int mn;
public:
    /** initialize your data structure here. */
    MinStack() {
        mn = INT_MAX;
    }
    
    void push(int x) {
        if(x<=mn){
            st.push(mn);
            mn=x;
        }
        st.push(x);
    }
    
    void pop() {
        int x = st.top(); st.pop();
        if(x==mn){mn=st.top();st.pop();}
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return mn;
    }
};

//two stack
class MinStack {
private:
    stack<int> s1;
    stack<int> s2;
public:
    void push(int x) {
        s1.push(x);
        if (s2.empty() || x <= s2.top())  s2.push(x);       
    }
    void pop() {
        if (s1.top() == s2.top())  s2.pop();
        s1.pop();
    }
    int top() {
        return s1.top();
    }
    int getMin() {
        return s2.top();
    }
};




716. Max Stack
class MaxStack {
private:
    stack<int> num_stack, max_stack;

public:
    /** initialize your data structure here. */
    MaxStack() {
        
    }
    
    void push(int x) {
        if(max_stack.empty() || x>=max_stack.top()) max_stack.push(x);
        num_stack.push(x);
    }
    
    int pop() {
        if(max_stack.top() == num_stack.top()) max_stack.pop();
        int t = num_stack.top();
        num_stack.pop();
        return t;
    }
    
    int top() {
        return num_stack.top();
    }
    
    int peekMax() {
        return max_stack.top();
    }
    
    int popMax() {
        int mx = max_stack.top();
        stack<int> t;
        while (num_stack.top() != max_stack.top()) {
            t.push(num_stack.top()); num_stack.pop();
        }
        num_stack.pop(); max_stack.pop();
        while (!t.empty()) {
            push(t.top()); t.pop();
        }
        return mx;
    }
};





***************************************************************************************************************************************************
math (+ string)
***************************************************************************************************************************************************
2. Add Two Numbers
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* p = head;
        int carry = 0;
        int sum = 0;
        while(l1 || l2 || carry){
            sum = (l1?l1->val:0) + (l2?l2->val:0) + carry; //!!!
            if(l1) l1=l1->next;   //!!!
            if(l2) l2=l2->next;
            carry = sum/10;
            ListNode* t = new ListNode(sum%10);
            p->next = t;
            p=p->next;
        }
        return head->next;
    }
};

445. Add Two Numbers II
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //using stack
        stack<int> st1, st2;
        while(l1){
            st1.push(l1->val);
            l1 = l1->next;
        }
        while(l2){
            st2.push(l2->val);
            l2=l2->next;
        }
        ListNode*  next_node = NULL;
        int carry = 0;
        int sum = 0; 
        while(!st1.empty() || !st2.empty() || carry){
            sum = carry;
            if(!st1.empty()){
                sum += st1.top();
                st1.pop();
            }
            if(!st2.empty()){
                sum += st2.top();
                st2.pop();
            }
            carry = sum/10;
            ListNode* node = new ListNode(sum%10);
            node->next = next_node;
            next_node = node;
        }
        return next_node;
    }
    
};





67. Add Binary
//time complexity: O(N) space complexity:O(1)
class Solution {
public:
    string addBinary(string a, string b) {
        string res = "";
        
        int n1 = a.size()-1, n2 = b.size()-1;
        int carry = 0;
        
        while(n1>=0 || n2>=0 || carry){
            int sum = carry;
            if(n1>=0) sum += a[n1--]-'0'; //!!! >=  !!!-'0'
            if(n2>=0) sum += b[n2--]-'0';
            
            carry = sum/2;
            res = char(sum%2+'0') + res;
            
        }
        
        return res;
    }
};

//follow up:换成其他机制（16）
string addfunc(string a, string b){
    string res = "";

    int n1 = a.size()-1, n2 = b.size()-1;
    int carry = 0, sum = 0;
    while(n1>=0 || n2>=0 || carry){
        sum = carry;
        if(n1>=0){
            sum += a[n1]<='9'? a[n1]-'0' : (a[n1]-'A' + 10);
            n1--;
        }
        if(n2>=0){
            sum += b[n2]<='9'? b[n2]-'0' : (b[n2]-'A' + 10);  
            n2--;
        }
        //cout<<"sum:"<<sum<<endl;
        carry = sum/16;
        res = char((sum%16 <= 9)? sum%16+'0': sum%16-10+'A') + res;

    }
    return res;
}





8. String to Integer (atoi)
class Solution {
public:
    int myAtoi(string str) {
        //atoi
        //whitespace
        //return 0 if first element is not num or +-
        int i=0;
        while(i<str.size() && str[i]==' ') i++;
        if(!(str[i]=='-' || str[i]=='+' || (str[i]>='0' && str[i]<='9'))) return 0;
        
        int sign = 1;
        if(str[i] == '-' || str[i] == '+') {   //!!!
            sign = str[i]=='+'?1:-1; 
            i++;
        }
        
        long long num = 0;   //!!!
        while(str[i]>='0' && str[i]<='9'){
            num = num*10 + str[i++]-'0';
            if(num>INT_MAX) return ((sign>0)?INT_MAX:INT_MIN);  //!!!
        }
        return sign*num;
    }
};


//
class Solution {
public:
    int myAtoi(string str) {
        //whitespace   +    initial plus or minus sign + many numerical digits + additional characters
        //return 0 if no valid conversion could be performed

        int sign = 1;
        int i=0;
        while(i<str.size()){
            if(str[i]==' ') i++;
            else break;
        }
        if(str[i]!='+' && str[i]!='-' && !(str[i]>='0' && str[i]<='9')) return 0;
        if(str[i]=='+') {i++; sign=1;}
        else if(str[i]=='-'){i++; sign=-1;}
        
        long long num = 0;
        for(int j=i; j<str.size(); j++){
            if(!(str[j]>='0' && str[j]<='9')) break;
            num = num*10 + str[j]-'0';
            if(num>INT_MAX) return sign<0?INT_MIN:INT_MAX;
        }
        
        return sign*num;
        
    }
};



12. Integer to Roman
class Solution {
public:
    string intToRoman(int num) {
        //integer to roman
        //int :  from 1 to 3999.
        string res = "";
        vector<int> vals{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        vector<string> str{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        for(int i=0; i<vals.size(); i++){   //!!!go through vals from big ti small
            while(num >= vals[i]){         //!!!use while, because we maybe need to use the same val for more than one time
                num -= vals[i];
                res += str[i];
            }
        }
        return res;
    }
};



13. Roman to Integer
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> m;
        /*
        I             1
        V             5
        X             10
        L             50
        C             100
        D             500
        M             1000
        */
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;
        int sum = 0;
        for(int i=0; i<s.size()-1; i++){
            if(m[s[i]] >= m[s[i+1]]) sum+=m[s[i]];
            else sum -= m[s[i]];
        }
        sum += m[s.back()];
        return sum;
    }
};
//
class Solution {
public:
    int romanToInt(string s) {
        //roman to integer
        /*
        I             1
        V             5
        X             10
        L             50
        C             100
        D             500
        M             1000
        */
        unordered_map<char, int> m;
        m['I'] = 1;
        m['V'] = 5;
        m['X'] = 10;
        m['L'] = 50;
        m['C'] = 100;
        m['D'] = 500;
        m['M'] = 1000;
        
        int res = 0;
        for(int i=0; i<s.size()-1; i++){
            int a = m[s[i]], b = m[s[i+1]];
            if(a>=b)  res += a;   //+ V + I  + I + I   !!!等号
            else if(a<b)  res -= a;   //- I + V
        }
        res += m[s.back()];   //add the last element
        return res;
    }
};



43


50. Pow(x, n)
//solution 1
//time complexity: O(logN)
class Solution {
public:
    double myPow(double x, int n) {
        //cut n to half recursively
        if(n==0) 
            return 1;
        if(n<0){
            return 1/x * pow(1/x, -(n+1));
        }
        return n%2==0 ? myPow(x*x, n/2) : x*myPow(x*x, n/2);
    }
};

🌼🌼🌼//solution 2
class Solution {
public:
    double myPow(double x, int n) {
        //cut n to half recursively
        //time complexity: O(logN)
        if(n<0) return 1/power(x, -n);
        else return power(x, n);
    }
    double power(double x, int n){
        if(n==0) return 1;
        double half = power(x, n/2);
        if(n%2 == 0) return half*half;
        else return x*half*half;
    }
};

//迭代
class Solution {
public:
    double myPow(double x, int n) {
        double res = 1.0;
        for(int i=n; i!=0; i/=2){
            if(i%2!=0) res = x*res;
            x=x*x;
        }
        return n<0? 1/res:res;
    }

};


372. Super Pow ???
class Solution {
public:
    int superPow(int a, vector<int>& b) {
        long long res = 1;
        for (int i = 0; i < b.size(); ++i) {
            res = pow(res, 10) * pow(a, b[i]) % 1337;
        }
        return res;
    }
    int pow(int x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x % 1337;
        return pow(x % 1337, n / 2) * pow(x % 1337, n - n / 2) % 1337;
    }
};


69. Sqrt(x)
//binary search
//time complexity: O(logX)
class Solution {
public:
    int mySqrt(int x) {
        if(x==0 || x==1) return x;
        int left = 1, right = x;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(mid > x/mid) right = mid-1;   //!!!不能写成mid*mid/x因为mid*mid可能会溢出！！！！
            else left = mid+1;
        }
        return right;
    }
};
//solution 2: 牛顿迭代法
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;
        double res = 1, pre = 0;
        while (abs(res - pre) > 1e-6) {
            pre = res;
            res = (res + x / res) / 2;
        }
        return int(res);
    }
};



367. Valid Perfect Square

//another solution 
bool perfectSquare(int num) {
    if(num < 0) return false;
    if(num == 0) return true;
    int left = 0, right = num;
    while(left<=right){
        int mid = left + (right-left)/2;
        if(mid == num/mid) return num%mid == 0;
        else if(mid > num/mid) right = mid-1;
        else left = mid+1;   
    }
    return false;
}



//
class Solution {
public:
    bool isPerfectSquare(int num) {
        long left = 1, right = num;
        while(left<=right){
            long mid = left + (right-left)/2;
            long t = mid*mid;
            if(t == num) return true;
            else if(t < num) left = mid+1;
            else right = mid-1;
        }
        return false;
    }
};




67


273. Integer to English Words
 //加负数 INT_MIN  res = func(INT_MAX), change last word of res from seven to eight, return  "-"+res;
//<0 except INT_MIN return "-" + func(-num)
string res = "";
if(num<0){
    if(num == INT_MIN){
        string res = func(INT_MAX);
        int pos = rfind(" "); 
        res = res.substr(0, pos) + " Eight";
        return "Minus " + res; 
    }
    else return "Minus " func(-1*num);
} 
else{
    return func(num);
}
//overflow?


🌼🌼🌼
class Solution {
public:
    string numberToWords(int num) {

        //int -> (0)billion(000)million(000)thousand(000)
        vector<string> v = {"Thousand", "Million", "Billion"};
        string res = toWord(num%1000);
        num = num/1000;
        for(int i=0; i<3; i++){
            res = (num%1000) ? toWord(num%1000)+" "+v[i]+" "+res : res;
            num = num/1000;
        }
        if(res.back()==' ') res.pop_back(); // !!!
        return res.empty()?"Zero":res;  //!!!
    }
    
    string toWord(int n){
        int a = n/100;
        int b = n%100;
        int c = n%10;v
        vector<string> v1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven",
         "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        vector<string> v2 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        string res = b<20 ? v1[b] : (v2[b/10] + (c? " "+v1[c] : ""));
        if(a>0) res = v1[a] + " Hundred" + (b?" "+res:""); //!!!
        return res;
    }
};

415. Add Strings
class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int n1 = num1.size(), n2 = num2.size();
        int idx1 = n1-1, idx2 = n2-1;
        int carry = 0;
        while(idx1>=0 || idx2>=0 || carry){
            int sum = (idx1>=0?num1[idx1--]-'0':0) + (idx2>=0?num2[idx2--]-'0':0) + carry;   //!!!对idx1和idx2的判断不要忘了
            carry = sum/10;
            res = char(sum%10 + '0') + res;
        }
        return res;
    }
};



29. Divide Two Integers
//time complexity:O(N)
class Solution {
public:
    int divide(int dividend, int divisor) {
        long long a = abs((long long)dividend);
        long long b = abs((long long)divisor);
        
        long long res=0;
        while(a>=b){
            a = a-b;
            res++;
        }
        
        if(dividend<0 ^ divisor<0) res = -res;
        return res>INT_MAX?INT_MAX:res;
    }
};


//time complecity: O(log(n))
//dividend = quotient * divisor + remainder

class Solution {
public:
    int divide(int dividend, int divisor) {
        //divide two integers
        long long a = abs((long long)dividend);  //!!!
        long long b = abs((long long)divisor);
        if(a<b) return 0;
        long long res = 0; //!!!
        while(a>=b){
            long long t = b, p =1;
            //a = quotient * b + remainder
            //find the most significant bit in the quotient. 
            while(a >= (t<<1)){   //!!!
                t<<=1;
                p<<=1;
            }
            //update p and result
            res += p;
            a -=t;
        }
        if(dividend<0 ^ divisor<0) res = -res;  //!!!
        
        return res>INT_MAX?INT_MAX:res;   //!!!
    }
};
//



311. Sparse Matrix Multiplication
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        // A*B
        vector<vector<int>> res(A.size(), vector<int>(B[0].size(), 0));
        
        for(int i=0; i<A.size(); i++){
            for(int k = 0; k<A[0].size(); k++){
                if(A[i][k]!=0){
                    for(int j=0; j<B[0].size(); j++){
                        if(B[k][j]!=0)
                            res[i][j] += A[i][k]*B[k][j];
                    }
                }
            }
        }
        return res;
        
    }
};



43. Multiply Strings

class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.size(), n2 = num2.size(), carry=0;
        vector<int> v(n1+n2, 0);

        //traverse num from left to right, but save reversely, the most significant is in the right
        int k=n1+n2-2;
        for(int i=0;i<n1;i++){
            for(int j=0;j<n2;j++){
                v[k-i-j] += (num1[i]-'0')*(num2[j]-'0');
            }
        }
        //cal result from less significant -> more significant 
        for(int i=0;i<n1+n2;i++){
            v[i]+=carry;
            carry=v[i]/10;
            v[i]%=10;
        }

        //reverse the result and remove the leading zero
        int i=n1+n2-1;
        string res;
        while(v[i]==0) i--;
        if(i<0) return "0";
        while(i>=0) res+=v[i--]+'0';
        return res;
    }
};




//time complexity: O(N1*N2)
class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.size();
        int n2 = num2.size();
        vector<int> product(n1+n2, 0);
        
        //reverse the num for calculate  "123"-->"321"  
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        
        //cal the pruduct, digit i and digit j contributes to digit i+j
        for(int i=0; i<n1; i++){
            for(int j=0; j<n2; j++){
                product[i+j] += (num1[i]-'0') * (num2[j]-'0');
                product[i+j+1] += product[i+j]/10;
                product[i+j] %= 10;
            }
        }
        //remove leading 0
        int i = n1+n2-1;    //!!!i=n1+n2-1;
        while(i>0 && product[i]==0){    //!!!i>0
            i--;
        }
        string res = "";
        while(i>=0){
            res += to_string(product[i--]);
        }
        return res;
    }
};



//another solution
class Solution {
public:
    string multiply(string num1, string num2) {
        /*
                1   2   3
                4   5   6
              ------------
                6  12  18
             5  10 15       => use vector save this part
          4  8  12
          --------------
          5  6  0  8  8
        */
        int n1 = num1.size();
        int n2 = num2.size();
        vector<int> v(n1+n2-1, 0);
        
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        /*
        321
        654
        */
        
        for(int i=0; i<n1; i++){
            for(int j=0; j<n2; j++){
                v[i+j] += (num1[i]-'0') * (num2[j]-'0');
            }
        }
  
        string res = "";
        int carry = 0, sum = 0, i=0;
        while(i<v.size() || carry){
            sum = carry;
            if(i<v.size()) sum += v[i];
            carry = sum/10;
            res = char(sum%10 + '0') + res;
            i++;
        }
        
        i=0;
        while(res[i]=='0' && i<res.size()-1) i++;
        return res.substr(i);
        
    }
};



//another solution
class Solution {
public:
    string multiply(string num1, string num2) {
        /*
                1   2   3
                4   5   6
              ------------
                6  12  18
             5  10 15       => use vector save this part
          4  8  12
          --------------
          5  6  0  8  8
        */
        int n1 = num1.size();
        int n2 = num2.size();
        vector<int> v(n1+n2, 0);
        
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        /*
        321
        654
        */
        
        for(int i=0; i<n1; i++){
            for(int j=0; j<n2; j++){
                v[i+j] += (num1[i]-'0') * (num2[j]-'0');
                v[i+j+1] += v[i+j]/10;
                v[i+j] = v[i+j]%10;
            }
        }
  
        string res = "";
        for(int i=0; i<v.size(); i++){
            res = char(v[i] + '0') + res;
        }
        
        int i=0;
        while(res[i]=='0' && i<res.size()-1) i++;
        return res.substr(i);
        
    }
};


360. Sort Transformed Array
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        //first idea: cal and then sort. time complexity: O(nlogn)
        //second idea: 
        //if a>0  the max must be in out, index decrease
        //if a<0  the min must be in out, index increase
        //time compleixty: O(N)
        int n = nums.size();
        vector<int> res(n, 0);
        int left = 0, right = n-1;
        int index = a>=0?n-1:0;   //!!! 等号
        while(left<=right){
            if(a>=0)   //!!!等号
                res[index--] = cal(nums[left], a, b, c)>=cal(nums[right], a, b, c)?cal(nums[left++], a, b, c):cal(nums[right--], a, b, c);
            else
                res[index++] = cal(nums[left], a, b, c)<=cal(nums[right], a, b, c)?cal(nums[left++], a, b, c):cal(nums[right--], a, b, c);
        }
        return res;
    }
    int cal(int x, int a, int b, int c){
        return a*x*x + b*x + c; 
    }
};

//another solution
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        //if a>0 then f(x) decrease from two sides to middle
        // if a<0 then f(x) increase from two sides to middle
        vector<int> res(nums.size());
        int index = a>=0?res.size()-1:0;
        
        int left = 0, right = nums.size()-1;
        while(left<=right){
            int p = cal(nums[left], a, b, c), q = cal(nums[right], a, b, c);
            if(p < q){
                if(a>=0){
                    res[index--] = q; right--;
                }
                else{
                    res[index++] = p; left++;
                }
            }
            else{ //cal(nums[left]) > cal(nums[right])
                if(a>=0){
                    res[index--] = p; left++;
                }
                else{
                    res[index++] = q; right--;
                }
                
            }
        }
        
        return res;
        
    }
    
    int cal(int num, int a, int b, int c){
        return a*num*num + b*num + c;
    }

};





670. Maximum Swap
//back[i] record the max num at the back of i;
//time complexity: O(N), spcace complexity: O(N)
class Solution {
public:
    int maximumSwap(int num) {
        string s = to_string(num);
        string back = s;
        //back[i] record the max num at the back of i;
        for(int i=s.size()-2; i>=0; i--){
            back[i] = max(back[i], back[i+1]);
        }
        for(int i=0; i<s.size(); i++){
            if(s[i] == back[i]) continue;  //i is the biggest num
            //swap(s[i], back[i])
            for(int j=s.size()-1; j>i; j--){  //we only need to do once
                if(s[j] == back[i]){
                    swap(s[i], s[j]);
                    return stoi(s);
                }
            }
        }
        return num;
    }
};




640. Solve the Equation   //tricky!!!
class Solution {
public:
    string solveEquation(string equation) {
        //contains only '+', '-' operation, the variable x and its coefficient.
        //  ax = b
        //If there is no solution for the equation, return "No solution".   a==0, b!=0
        //If there are infinite solutions for the equation, return "Infinite solutions"  a==0, b==0
        
        int a = 0, b = 0;
        int pos = equation.find("=");
        helper(equation.substr(0, pos), true, a, b);
        helper(equation.substr(pos+1), false, a, b);

        if(a==0 && b!=0) return "No solution";
        if(a==0 && b==0) return "Infinite solutions";
        else return "x=" + to_string(b/a);
    }
    
    void helper(string e, bool isLeft, int& a, int& b) {
        int sign = 1, num = -1;
        e += "+";
        for (int i = 0; i < e.size(); ++i) {
            if (e[i] == '-' || e[i] == '+') {
                num = (num == -1) ? 0 : (num * sign);
                b += isLeft ? -num : num;
                num = -1;
                sign = (e[i] == '+') ? 1 : -1;
            } else if (e[i] >= '0' && e[i] <= '9') {
                if (num == -1) num = 0;
                num = num * 10 + e[i] - '0';
            } else if (e[i] == 'x') {
                num = (num == -1) ? sign : (num * sign);
                a += isLeft ? num : -num;
                num = -1;
            }
        }
    }
};





319. Bulb Switcher
class Solution {
public:
    int bulbSwitch(int n) {
        //16: 2*8 4*4 1*16
        //n bulbs
        //Find how many bulbs are on after n rounds.
        //find the perfect squares from 1 to n
        int res = 1;
        while(res*res<=n) res++;
        return res-1;
        //return sqrt(n);
    }
};


66. Plus One
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for(int i=digits.size()-1; i>=0; i--){
            if(digits[i] < 9) {
                digits[i]++; 
                return digits;
            }
            else{
                digits[i] = 0;
                continue;
            }
        }
        digits[0] = 1;
        digits.push_back(0);
        return digits;
    }
};



172. Factorial Trailing Zeroes
class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        while(n>=5){
            res += n/5;
            n = n/5;
        }
        return res;
    }
};


413. Arithmetic Slices

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        //return the number of arithmetic subsequence slices in the array A.
        //consists of at least three elements 
        //sliding window/backtrack
        
        int res = 0;
        int left = 0;
        for(int right=1; right<A.size(); right++){
            int diff = A[right] - A[left];
            while(right+1<A.size() && A[right+1] - A[right] == diff){
                right++;
            }
            int len = right - left + 1;
            if(len>=3) res += (len-1)*(len-2)/2;   //(n-2 + n-3 + ... +1) = (n-1)*(n-2)/2 , the arithemic slices between left and right
            left = right;
        }
        
        return res;
    }
};




//solution 1: DP
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        // at least three elements
        //  with same step between two consecutive elements
        int res = 0;
        int n = A.size();
        vector<int> dp(n, 0);
        for(int i=2; i<n; i++){   //!!!
            if(A[i]-A[i-1] == A[i-1]-A[i-2]){
                dp[i] = dp[i-1]+1;   //!!!
            }
            res += dp[i];  //!!!
        }
        return res;
    }
};
//solution 2: two pointers
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        // at least three elements
        //  with same step between two consecutive elements
        int res = 0;
        int left = 0, right = 1;
        while(right<A.size()){
            int diff = A[right] - A[left];
            while(right+1<A.size() && A[right+1]-A[right] == diff){
                right++;
            }
            if(right-left+1 >= 3){
                int len = right-left+1;
                res += (len-1)*(len-2)/2;
            }
            left = right;
            right = left+1;
        }
        return res;
    }
};


//
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        // at least three elements
        //  with same step between two consecutive elements
        int n = A.size();
        int res = 0;
        int len = 2;
        for(int i=2; i<n; i++){
            if(A[i]-A[i-1] == A[i-1]-A[i-2]) len++;
            else{
                if(len>=3) res += (len-1)*(len-2)/2; 
                len = 2;
            }
        }
        if(len>=3) res += (len - 1) * (len - 2) * 0.5;
        return res;
        
    }
};


//


446. Arithmetic Slices II - Subsequence  ???
//可以跳着来
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        //return the number of arithmetic subsequence slices in the array A.
        //consists of at least three elements 
        //backtrack
        /*
        note:
        for [2, 4, 6, 8, 10]
        [2, 6, 10] is ok
        */
        //backtrack exceed time limit
        //using dynamic programming
        // dp[i][diff] += dp[j][diff]
        int res = 0;
        vector<unordered_map<int, int>> dp(A.size());
        for(int i=0; i<A.size(); i++){
            for(int j=0; j<i; j++){
                long long diff = (long long)A[i] - A[j];
                if(diff<INT_MIN || diff>INT_MAX) continue;
                (int)diff;
                dp[i][diff]++;  //!!!
                if(dp[j].count(diff)){
                    res += dp[j][diff];
                    dp[i][diff] += dp[j][diff];
                }
            }
        }
        return res;
        
    }
    
};




7. Reverse Integer
class Solution {
public:
    int reverse(int x) {
        long res = 0;
        while(x){
            res = res * 10 + x%10;
            x = x/10;
        }
        if(res>INT_MAX || res<INT_MIN) return 0;
        return res;
    }
};


//another solution
class Solution {
public:
    int reverse(int x){
        if(x < 0) return -1* myrevert(-1*x);
        else return myrevert(x); 
    }

    int myrevert(int input){
        int res = 0;
        int pre = 0;
        while(input>0){
            int c  =  input % 10;
            res  =  res * 10 + c;
            if( (res -  c ) / 10 != pre ) return 0; 
            input = input/10;
            pre = res;
        }
        return res;
    }


};


344. Reverse String
class Solution {
public:
    string reverseString(string s) {
        int left = 0, right = s.size()-1;
        while(left<right){
            swap(s[left++], s[right--]);
        }
        return s;
    }
};

633. Sum of Square Numbers
class Solution {
public:
    bool judgeSquareSum(int c) {
        int left = 0, right = sqrt(c);
        while(left<=right){
            int t1 = left*left + right*right;
            if(t1==c) return true;
            else if(t1<c){left++;}
            else right--;
        }
        return false;
    }
};



268. Missing Number
//solution 3
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            res ^= (i + 1) ^ nums[i];
        }
        return res;
    }
};


//solution 1
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        //linear + constant extra space
        for(int i=0; i<nums.size(); i++){
            if(nums[i] == nums.size()) continue;
            else if(nums[i] != nums[nums[i]]) {swap(nums[i], nums[nums[i]]); i--; }
        }
        for(int i=0; i<nums.size(); i++){
            if(nums[i] != i) return i;
        }
        return nums.size();
    }
};

//solution 2
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum = 0, n = nums.size();
        for (auto &a : nums) {
            sum += a;
        }
        return 0.5 * n * (n + 1) - sum;
    }
};

169. Majority Element
//bit manipulation
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //input: nums
        //output: majority num, always exist
        //1. hash table, time---O(N), space---O(N)
        //2. moore voting      O(N)        O(1)
        //3. bit manipulation  O(N)      O(1)
        int res = 0;
        int n = nums.size();
        
        for(int i=0; i<32; i++){
            int ones = 0, zeros = 0;
            for(int num:nums){
                if(ones > n/2 || zeros > n/2) break;
                if((num & (1<<i)) != 0) ones++;
                else zeros++;
            }
            if(ones > zeros) res |= (1<<i);
        }
        
        return res;
    }
};
//moore voting
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //input: nums
        //output: majority num, always exist
        //1. hash table, time---O(N), space---O(N)
        //2. moore voting      O(N)        O(1)
        //3. bit manipulation  O(N)      O(1)
        int res = 0, cnt = 0;
        for(int num:nums){
            if(cnt == 0) {res = num; cnt++;}
            else if(num == res) cnt++;
            else cnt--;
        }
        return res;
    }
};


9. Palindrome Number  //return x == reverse(x)
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0) return false;
        if(x==0) return true;
        
        int y = reverse(x);
        return x==y;
    }
    
    int reverse(int x){
        int res = 0;
        while(x){
            res = res*10 + x%10;
            x = x/10;
        }
        return res;
    }

};




166. Fraction to Recurring Decimal ???
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        int s1 = numerator >= 0 ? 1 : -1;
        int s2 = denominator >= 0 ? 1 : -1;
        long long num = abs( (long long)numerator );
        long long den = abs( (long long)denominator );
        long long out = num / den;
        long long rem = num % den;
        unordered_map<long long, int> m;
        string res = to_string(out);
        if (s1 * s2 == -1 && (out > 0 || rem > 0)) res = "-" + res;
        if (rem == 0) return res;
        res += ".";
        string s = "";
        int pos = 0;
        while (rem != 0) {
            if (m.find(rem) != m.end()) {
                s.insert(m[rem], "(");
                s += ")";
                return res + s;
            }
            m[rem] = pos;
            s += to_string((rem * 10) / den);
            rem = (rem * 10) % den;
            ++pos;
        }
        return res + s;
    }
};



65. Valid Number
class Solution {
public:
    bool isNumber(string s) {
        bool num = false, numAfterE = true, dot = false, exp = false, sign = false;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == ' ') {
                if (i < n - 1 && s[i + 1] != ' ' && (num || dot || exp || sign)) return false;
            } else if (s[i] == '+' || s[i] == '-') {
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != ' ') return false;
                sign = true;
            } else if (s[i] >= '0' && s[i] <= '9') {
                num = true;
                numAfterE = true;
            } else if (s[i] == '.') {
                if (dot || exp) return false;
                dot = true;
            } else if (s[i] == 'e') {
                if (exp || !num) return false;
                exp = true;
                numAfterE = false;
            } else return false;
        }
        return num && numAfterE;
    }
};



*********************************************************************************************************
Trie字典树
**********************************************************************************************************
208. Implement Trie (Prefix Tree)
struct TrieNode{
public:
    bool is_word;
    TrieNode* child[26];
    TrieNode(){
        is_word = false;
        for(auto &a:child) a = NULL;   //!!!‘&’不要漏
    }
};

class Trie {
private: 
    TrieNode * root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* p = root;
        for(auto c:word){
            int i = c-'a';
            if(!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->is_word = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* p = root;
        for(auto c:word){
            int i = c- 'a';
            if(!p->child[i]) return false;
            p=p->child[i];
        }
        return p->is_word;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* p = root;
        for(auto c:prefix){
            int i = c-'a';
            if(!p->child[i]) return false;
            p=p->child[i];
        }
        return true;
    }

};


211. Add and Search Word - Data structure design
/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */

struct TrieNode{
public:
    bool is_word;
    TrieNode* child[26];
    TrieNode(){
        is_word = false;
        for(auto &a:child) a = NULL;
    }
};
class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode* p = root;
        for(auto a:word){
            int t = a-'a';
            if(!p->child[t]) p->child[t] = new TrieNode();
            p = p->child[t];
        }
        p->is_word = true;
    }
    
    bool search(string word) {
        return query(word, root, 0);  //!!!
    }
    
    bool query(string word, TrieNode* root, int index){
        if(index == word.size()) return root->is_word;  //!!!
        if(word[index]=='.'){
            for(auto &a:root->child){
                if(a && query(word, a, index+1)) return true;   //!!!
            }
            return false;
        }
        else{
            return root->child[word[index]-'a'] && query(word, root->child[word[index]-'a'], index+1);  //!!!
        }
        
    }
private:
    TrieNode* root;
    
};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */



//
struct TrieNode{
    bool is_word;
    TrieNode* child[26];
    TrieNode(){
        is_word = false;
        for(auto &a:child) a=NULL;
    }
};

class WordDictionary {
private:
    TrieNode* root;

public:
    /** Initialize your data structure here. */
    WordDictionary() {
       root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode* p = root;
        for(char c:word){
            if(!p->child[c-'a']) p->child[c-'a'] = new TrieNode();  //!!!
            p = p->child[c-'a'];
        }
        p->is_word = true;
    }
    
    bool search(string word) {
        return query(word, root, 0);
    }
    
    bool query(string word, TrieNode* root, int index){
        if(index == word.size()) return root->is_word;
        if(word[index]=='.'){
            for(auto a:root->child){
                if(a && query(word, a, index+1)) return true;
            }
            return false;
        }
        else{
            return root->child[word[index]-'a'] && query(word, root->child[word[index]-'a'], index+1);
        }
    }

    
    
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */



692. Top K Frequent Words




********************************************************************************************************************
backtracking
********************************************************************************************************************
51. N-Queens
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        //placing n queens on an n×n chessboard 
        vector<vector<string>> res;
        vector<string> out(n, string(n, '.'));    //!!!
        backtrack(res, out, n, 0);
        return res;
    } 
    
    void backtrack(vector<vector<string>>& res, vector<string> out, int n, int row){
        if(row == n){
            res.push_back(out);
            return;
        }
        
        for(int col=0; col<n; col++){
            out[row][col] = 'Q';
            if(is_ok(out, row, col, n)) backtrack(res, out, n, row+1);  //!!!
            out[row][col] = '.';
        }
        
    }
    
    bool is_ok(vector<string> out, int row, int col, int n){
        //check the same col
        for(int r=0; r<row; r++) if(out[r][col] == 'Q') return false;  //!!!不用check同行
        int r = row-1, c= col-1;
        while(r>=0&&c>=0) if(out[r--][c--]=='Q') return false;
        r = row-1, c=col+1;
        while(r>=0 && c<n) if(out[r--][c++]=='Q') return false;
        return true;
    }
};

52. N-Queens II
class Solution {
public:
    int totalNQueens(int n) {
        vector<int> row_pos(n, 0);
        int res = 0;
        backtrack(res, n, row_pos, 0);
        return res;
    }
    
    void backtrack(int& res, int n, vector<int>& row_pos, int row){
        if(row == n){
            res++;
            return;
        }
        for(int col=0; col<n; col++){
            row_pos[row] = col;
            if(is_ok(row_pos, col, row, n)) backtrack(res, n, row_pos, row+1);
            row_pos[row] = -1;
        }
    }
    
    bool is_ok(vector<int> row_pos, int col, int row, int n){
        for(int r=0; r<row; r++) if(row_pos[r]==col) return false;
        int r = row-1, c = col-1;
        while(r>=0 && c>=0) if(row_pos[r--]==c--) return false; 
        r = row-1, c = col+1;
        while(r>=0 && c<n) if(row_pos[r--]==c++) return false;
        return true;
    }
    
};




17. Letter Combinations of a Phone Number
//Time complexity of above code is O(4^n)
//backtrack + hash table
class Solution {
private:
    unordered_map<char, string> m;   //!!!
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        m['2'] = "abc", m['3']="def", m['4']="ghi", m['5'] = "jkl", m['6']="mno", m['7']="pqrs", m['8'] = "tuv", m['9']="wxyz";
        vector<string> res;
        string out = "";
        backtrack(res, out, digits, 0);
        return res;
    }
    void backtrack(vector<string>& res, string& out, string digits, int index){
        if(index == digits.size()) {
            res.push_back(out);
            return;
        }
        char c = digits[index];
        for(int i=0; i<m[c].size(); i++){
            out+=m[c][i];
            backtrack(res, out, digits, index+1);
            out.pop_back();
        }   
        
    }

};

//another solution
class Solution {
private:
    unordered_map<char, string> m;
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        m = {{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};
        vector<string> res;
        string out;
        dfs(digits, 0, out, res);
        return res;
    }
    void dfs(string digits, int index, string out, vector<string>& res){
        if(index==digits.size()) {res.push_back(out); return;}
        
        string s = m[digits[index]];
        for(int i=0; i<s.size(); i++){
            out += s[i];
            dfs(digits, index+1, out, res);
            out.pop_back();
        }
    }

};


22
37. Sudoku Solver
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        //save empty positions
        vector<pair<int, int>> pos;
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j] == '.')
                    pos.push_back({i, j});
            }
        }
        //check 1-9 for every position recursively
        dfs(board, pos, 0);
        //0 is the index of positions
    }
    bool dfs(vector<vector<char>>& board, vector<pair<int, int>>& pos, int index){
        if(index==pos.size()) return true;
        
        for(int val=1; val<=9; val++){
            board[pos[index].first][pos[index].second] = '0' + val;
            if(is_ok(board, pos, index, val)) if(dfs(board, pos, index+1)) return true;
            board[pos[index].first][pos[index].second] = '.';//!!!
        }
        
        return false;
    }
    
    bool is_ok(vector<vector<char>>& board, vector<pair<int, int>>& pos, int index, int val){
        int row = pos[index].first, col = pos[index].second;
        //check row
        for(int r = 0; r<9; r++){
            if(r!=row && board[r][col] == '0' + val)
                return false;
        }
        //check col
        for(int c = 0; c<9; c++){
            if(c!=col && board[row][c] == '0'+val)
                return false;
        }
        //check small box
        for(int r = row/3*3; r<row/3*3+3; r++){
            for(int c = col/3*3; c<col/3*3+3; c++){
                if((board[r][c] == '0'+val) && (c!=col || r!=row))
                    return false;
            }
        }
        
        return true;
    }
    
};



39. Combination Sum
// (without duplicates)   --> sort not need 
// unlimited number of times.  ---> i
//find all unique combinations
//backtrack
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        
        vector<int> out;
        backtrack(candidates, target, out, 0, res);
        
        return res;
    }  
    
    void backtrack(vector<int>& candidates, int target, vector<int>& out, int start, vector<vector<int>>& res){
        if(target < 0) return;  //sum of out > target
        if(target == 0) res.push_back(out);  //out sum == target
        
        for(int i=start; i<candidates.size(); i++){
            out.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], out, i, res);      //next element -> can be same as the previous one
            out.pop_back();
        }
    }
    
};
40. Combination Sum II
//contain duplicate --> sort+pass same num in the same position
//only be used once  --> next position i+1
//find all unique combinations
//backtrack
class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        
        vector<int> out;
        sort(candidates.begin(), candidates.end());  //!!!
        backtrack(candidates, target, out, 0, res);
        
        return res;
    }  
    
    void backtrack(vector<int>& candidates, int target, vector<int>& out, int start, vector<vector<int>>& res){
        if(target < 0) return;  //sum of out > target
        if(target == 0) res.push_back(out);  //out sum == target
        
        for(int i=start; i<candidates.size(); i++){
            if(i>start && candidates[i]==candidates[i-1]) continue;  //!!! i>start
            out.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], out, i+1, res);      //!!!(i+1)next element -> can be same as the previous one
            out.pop_back();
        }
    }
    
};

46
47
51
52

60. Permutation Sequence
//backtrack
class Solution {
private:
    int count = 0;
    string res = "";
public:
    string getPermutation(int n, int k) {
        string out="";
        vector<bool> visited(n+1);
        backtrack(out, n, k, visited);
        return res;
    }
    bool backtrack(string& out, int n, int k, vector<bool>& visited){
        if(out.size()==n){
            count++;
            if(count == k){res = out; return true;}
            return false;
        } 
        for(int i=1; i<=n; i++){
            if(visited[i]) continue;
            out += char(i+'0');
            visited[i] = true;
            if(backtrack(out, n, k, visited)) return true;
            out.pop_back();
            visited[i] = false;
        }
        return false;
    }
};
//non backtrack
class Solution {
public:
    string getPermutation(int n, int k) {
        string res;
        string num = "123456789";
        vector<int> f(n, 1);
        for (int i = 1; i < n; ++i) f[i] = f[i - 1] * i;
        --k;
        for (int i = n; i >= 1; --i) {
            int j = k / f[i - 1];
            k %= f[i - 1];
            res.push_back(num[j]);
            num.erase(j, 1);
        }
        return res;
    }
};




77




78. Subsets
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        //a set of distinct integers ---> sort is no need
        vector<vector<int>> res;
        vector<int> out;
        backtrack(nums, res, out, 0);
        return res;
    }
    
    void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& out, int start){
        res.push_back(out);
        for(int i = start; i<nums.size(); i++){
            out.push_back(nums[i]);
            backtrack(nums, res, out, i+1);
            out.pop_back();
        }
    }

};


79. Word Search
//backtrack + visited
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size();
        int col = board[0].size();
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(backtrack(visited, board, word, 0, i, j)) return true;
            }
        }
        return false;
    }
    
    bool backtrack(vector<vector<bool>>& visited, vector<vector<char>>& board, string word, int idx, int row, int col){
        if(idx == word.size()) return true;
        if(row<0 || col<0 || row>=board.size() || col>=board[0].size() || visited[row][col] || word[idx]!=board[row][col]) return false;  
        //!!!visited[row][col]
        visited[row][col] = true;
        bool res = backtrack(visited, board, word, idx+1, row-1, col)
            || backtrack(visited, board, word, idx+1, row, col-1)
            || backtrack(visited, board, word, idx+1, row+1, col)
            || backtrack(visited, board, word, idx+1, row, col+1);
        visited[row][col] = false;
        return res;
    }
    
};


90. Subsets II
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        //a collection of integers that might contain duplicates --> sort and pass
        sort(nums.begin(), nums.end());  //!!!sort
        vector<vector<int>> res;
        vector<int> out;
        backtrack(res, out, nums, 0);
        return res;
    }
    void backtrack(vector<vector<int>>& res, vector<int>& out, vector<int>& nums, int start){
        res.push_back(out);
        for(int i=start; i<nums.size(); i++){
            if(i>start && nums[i] == nums[i-1]) continue; //!!!avoid same char in the same position
            out.push_back(nums[i]);
            backtrack(res, out, nums, i+1);
            out.pop_back();
        }
    }
};
140
211


491. Increasing Subsequences
//solution 1
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        //backtrack
        set<vector<int>> res;   //!!!
        vector<int> out;
        backtrack(nums, res, out, 0);
        return vector<vector<int>>(res.begin(), res.end());
    }
    void backtrack(vector<int>& nums, set<vector<int>>& res, vector<int>& out, int start){
        if(out.size()>=2) res.insert(out);
        for(int i=start; i<nums.size(); i++){
            if(!out.empty() && out.back()>nums[i]) continue;
            out.push_back(nums[i]);
            backtrack(nums, res, out, i+1);
            out.pop_back();
        }
    }
};

//solution 2
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> out;
        helper(nums, 0, out, res);
        return res;
    }
    void helper(vector<int>& nums, int start, vector<int>& out, vector<vector<int>>& res) {
        if (out.size() >= 2) res.push_back(out);
        unordered_set<int> st;
        for (int i = start; i < nums.size(); ++i) {
            if (!out.empty() && out.back() > nums[i] || st.count(nums[i])) continue;
            out.push_back(nums[i]);
            st.insert(nums[i]);
            helper(nums, i + 1, out, res);
            out.pop_back();
        }
    }
};



784. Letter Case Permutation
class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        //backtrack
        vector<string> res;
        backtrack(S, res, 0);
        return res;
    }
    void backtrack(string S, vector<string>& res, int index){
        if(index == S.size()){
            res.push_back(S);
            return;
        } 
        backtrack(S, res, index+1);
        if(S[index]>'9'){
            S[index] ^= 32;
            backtrack(S, res, index+1);
        }
        
    }
};




***********************************************************************************************************************
DFS + BFS
***********************************************************************************************************************
490. The Maze
class Solution {
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        //BFS
        int row = maze.size();
        int col = maze[0].size();
        
        queue<pair<int, int>> q;
        q.push({start[0], start[1]});
        set<pair<int, int>> visited;
        visited.insert({start[0], start[1]});
        
        vector<vector<int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        while(!q.empty()){
            auto a = q.front();
            q.pop();
            if(a.first == destination[0] && a.second == destination[1]) return true;
            for(int i=0; i<dirs.size(); i++){
                int x = a.first, y = a.second;
                while(x>=0 && y>=0 && x<row && y<col && maze[x][y]!=1){
                    x+=dirs[i][0]; y+=dirs[i][1];
                }
                x-=dirs[i][0], y-=dirs[i][1];
                if(!visited.count({x, y})) {q.push({x, y}); visited.insert({x, y});}
            }
        }
        
        return false;
    }
};
//DFS
class Solution {
private:
    vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        //DFS
        int row = maze.size();
        int col = maze[0].size();
        vector<vector<int>> dp(row, vector<int>(col, -1));
    
        return dfs(maze, dp, start[0], start[1], destination[0], destination[1]);
    }
    
    bool dfs(vector<vector<int>>& maze, vector<vector<int>>& dp, int i, int j, int di, int dj){
        if(i==di && j==dj) return true;
        if(dp[i][j]!=-1) return dp[i][j];
        bool res = false;
        maze[i][j] = -1;
        for(auto dir:dirs){
            int x = i, y = j;
            while(x>=0 && y>=0 && x<maze.size() && y <maze[0].size() && maze[x][y]!=1){
                x += dir[0], y += dir[1];
            }
            x -= dir[0], y -= dir[1];
            if(maze[x][y]!=-1){
                res |= dfs(maze, dp, x, y, di, dj);
            }
        }
        dp[i][j] = res;
        return res;
    }
    
};

505. The Maze II
class Solution {
public:
    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        vector<vector<int>> dirs={{-1,0},{0,-1},{1,0},{0,1}};
        int row = maze.size(), col = maze[0].size();
        vector<vector<int>> distances(row, vector<int>(col,INT_MAX));
        queue<pair<int, int>> q;
        distances[start[0]][start[1]] = 0;
        q.push({start[0], start[1]});
        while(!q.empty()){
            auto t = q.front(); q.pop();
            for(auto dir:dirs){
                int x = t.first, y = t.second, dis = distances[x][y];
                while(x>=0&&x<row&&y>=0&&y<col&&maze[x][y]==0){x+=dir[0];y+=dir[1];dis++;}
                x-=dir[0];y-=dir[1];dis--;
                if(dis<distances[x][y]) {distances[x][y]=dis;if(x!=destination[0]||y!=destination[1]) q.push({x,y});}
            }
        }
        int res = distances[destination[0]][destination[1]];
        return res==INT_MAX?-1:res;
    }
};





301. Remove Invalid Parentheses
//DFS
class Solution {    ???没看懂
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        helper(s, 0, 0, {'(', ')'}, res);
        return res;
    }
    void helper(string s, int last_i, int last_j, vector<char> p, vector<string>& res) {
        int cnt = 0;
        for (int i = last_i; i < s.size(); ++i) {
            if (s[i] == p[0]) ++cnt;
            else if (s[i] == p[1]) --cnt;
            if (cnt >= 0) continue;
            for (int j = last_j; j <= i; ++j) {
                if (s[j] == p[1] && (j == last_j || s[j] != s[j - 1])) {
                    helper(s.substr(0, j) + s.substr(j + 1), i, j, p, res);
                }
            }
            return;
        }
        string rev = string(s.rbegin(), s.rend());
        if (p[0] == '(') helper(rev, 0, 0, {')', '('}, res);
        else res.push_back(rev);
    }
};

//BFS
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        //bfs
        vector<string> res;
        set<string> visited({s}); // visited string
        queue<string> q({s});
        bool found = false;
        
        while(!q.empty()){
            string t = q.front();
            q.pop();
            
            if(isvalid(t)){
                res.push_back(t);
                found = true;
            }
            
            if(found == true) continue;  //if is found then we do no need to delete char
            
            
            //delete char
            for(int i=0; i<t.size(); i++){
                if(t[i] != '(' && t[i] != ')') continue;   //!!!
                string str = t.substr(0, i) + t.substr(i+1);
                if(!visited.count(str)){
                    q.push(str);
                    visited.insert(str);
                }
            }
        }
        
        return res;
    }
    
    bool isvalid(string s){
        int count = 0;
        for(int i=0; i<s.size(); i++){
            if(s[i] == '(') count++;
            if(s[i] == ')') count--;
            if(count < 0) return false;
        }
        return count == 0;   //！！！判断count==0
    }
};





545. Boundary of Binary Tree 
//DFS
class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        
        if(root==NULL) return {};
        vector<int> res;
        if(root->left || root->right) res.push_back(root->val);
        
        //traverse the left boundary
        leftboundary(root->left, res);
        
        //traverse the leaf
        leaf(root, res);
        
        //traverse the right boundary
        rightboundary(root->right, res);
        
        return res;
        
    }
    void leftboundary(TreeNode* root, vector<int>& res){
        if(root==NULL || root->left==NULL && root->right==NULL) return;
        res.push_back(root->val);  //先push
        if(root->left) leftboundary(root->left, res);
        else leftboundary(root->right, res);
    }
    
    void rightboundary(TreeNode* root, vector<int>& res){
        if(root==NULL || root->left==NULL && root->right==NULL) return;
        if(root->right) rightboundary(root->right, res);
        else rightboundary(root->left, res);
        res.push_back(root->val);    //返回后再push
    }
    
    void leaf(TreeNode* root, vector<int>& res){
        if(root==NULL) return;
        if(root->left==NULL && root->right==NULL) res.push_back(root->val);
        leaf(root->left, res);
        leaf(root->right, res);
    } 

};
//BFS
class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (!root) return {};
        vector<int> res, right;
        TreeNode *l = root->left, *r = root->right, *p = root;
        if (root->left || root->right) res.push_back(root->val);
        while (l && (l->left || l->right)) {
            res.push_back(l->val);
            if (l->left) l = l->left;
            else l = l->right;
        }
        stack<TreeNode*> st;
        while (p || !st.empty()) {
            if (p) {
                st.push(p);
                if (!p->left && !p->right) res.push_back(p->val);
                p = p->left;
            } else {
                p = st.top(); st.pop();
                p = p->right;
            }
        }
        while (r && (r->left || r->right)) {
            right.push_back(r->val);
            if (r->right) r = r->right;
            else r = r->left;
        }
        res.insert(res.end(), right.rbegin(), right.rend());
        return res;
    }
};



419. Battleships in a Board 
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        // in one-pass, using only O(1) extra memory
        //without modifying the value of the board
        int res = 0;
        if(board.empty() || board[0].empty()) return 0;
        int row = board.size();
        int col = board[0].size();
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(board[i][j]=='.' || board[i][j]=='X'&&i-1>=0&&board[i-1][j]=='X' || board[i][j]=='X'&&j-1>=0&&board[i][j-1]=='X')
                    continue;
                else res++;
            }
        }
        return res;
    }
};

200. Number of Islands
//DFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        
        int row = grid.size();
        int col = grid[0].size();
        
        int res = 0;
        // go through the grid
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(grid[i][j] == '1'){   //the first '1'
                    res++;                //island +1
                    set_zero(grid, i, j);  //set the neghbor '1' to '0'
                }
            }
        }
        
        return res;
    }
    
    void set_zero(vector<vector<char>>& grid, int i, int j){
        if(grid[i][j] == '0') return;
        grid[i][j]='0';
        if(i-1 >= 0) set_zero(grid, i-1, j);
        if(j-1 >= 0) set_zero(grid, i, j-1);
        if(i+1 < grid.size()) set_zero(grid, i+1, j);
        if(j+1 <grid[0].size()) set_zero(grid, i, j+1);
    }
      
};

305. Number of Islands II
class Solution {
public:
    vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
        int cnt = 0;
        vector<int> roots(m*n, -1);
        vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        vector<int> res;
        for(auto pos:positions){
            cnt++;
            int id = pos.first*n + pos.second;
            roots[id] = id;
            
            for(auto dir:dirs){
                int x = pos.first+dir[0], y = pos.second+dir[1];
                if(x<0 || y<0 ||x>=m || y>=n || roots[x*n+y]==-1) continue;
                int cur_id = x*n + y;
                int p = findroot(roots, cur_id), q = findroot(roots, id);
                if(p!=q){
                    roots[p] = q;
                    cnt--;
                }
            }
            res.push_back(cnt);
        }
        return res;
    }
    
    int findroot(vector<int>& roots, int s){
        if(roots[s]==s) return s;
        else return findroot(roots, roots[s]);
    }
};


694. Number of Distinct Islands
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        //distinct move(but not rotate)-->set+save positions
        if(grid.empty() || grid[0].empty()) return 0;
        set<vector<pair<int, int>>> res;
        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[0].size(); j++){
                if(grid[i][j] == 1){
                    vector<pair<int, int>> out;
                    set_zero(grid, i, j, i, j, out);
                    res.insert(out);
                } 
            }
        }
        return res.size();
    }
    void set_zero(vector<vector<int>>& grid, int x0, int y0, int i, int j, vector<pair<int, int>>& out){
        if(i<0 || i>=grid.size() || j<0 ||j>=grid[0].size() || grid[i][j]==0) return;
        out.push_back({i-x0, j-y0});
        grid[i][j] = 0;
        set_zero(grid, x0, y0, i-1, j, out);
        set_zero(grid, x0, y0, i, j-1, out);
        set_zero(grid, x0, y0, i+1, j, out);
        set_zero(grid, x0, y0, i, j+1, out);
    }
    
};

//
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        int row = grid.size();
        int col = grid[0].size();
        
        set<vector<pair<int, int>>> s;
        vector<pair<int, int>> relative_pos;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(grid[i][j] == 1){
                    dfs(grid, i, j, i, j, relative_pos);
                    s.insert(relative_pos);
                    relative_pos.clear();
                }
                    
            }
        }
        
        return s.size();
    }
    
    void dfs(vector<vector<int>>& grid, int i, int j, int i0, int j0,  vector<pair<int, int>>& relative_pos){
        if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size() || grid[i][j]==0) return;
        relative_pos.push_back({i-i0, j-j0});
        grid[i][j] = 0;                      //!!!
        dfs(grid, i+1, j, i0, j0, relative_pos);
        dfs(grid, i, j+1, i0, j0, relative_pos);
        dfs(grid, i-1, j, i0, j0, relative_pos);
        dfs(grid, i, j-1, i0, j0, relative_pos);
    }
    
};

695. Max Area of Island
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        //Find the maximum area of an island in the given 2D array
        if(grid.empty() || grid[0].empty()) return 0;
        int row = grid.size();
        int col = grid[0].size();
        int res = 0;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(grid[i][j] == 1){
                    int cur = 0;
                    dfs(grid, i, j, res, cur);
                }
            }
        }
        return res;
    }
    
    void dfs(vector<vector<int>>& grid, int i, int j, int& res, int& cur){
        if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size() || grid[i][j]==0) return;
        cur++;
        grid[i][j] = 0;
        res = max(res, cur);
        dfs(grid, i-1, j, res, cur);
        dfs(grid, i, j-1, res, cur);
        dfs(grid, i+1, j, res, cur);
        dfs(grid, i, j+1, res, cur);
    }
};



463. Island Perimeter
//solution 1
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return 0;
        vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        
        int res = 0;
        for(int i=0; i<grid.size(); i++){
            for(int j=0; j<grid[0].size(); j++){
                if(grid[i][j]==0) continue;
                for(auto dir:dirs){
                    int x = i+dir[0], y = j+dir[1];
                    if(x<0 || y<0 || x>=grid.size() || y>=grid[0].size() || grid[x][y]==0) res++;
                }
            }
        }
        return res;
    }
};


//solution 2
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        /*
        notes:
        Grid cells are connected horizontally/vertically (not diagonally)
        one island(does not have inside water)
        return the perimeter of the island
        
        idea/plan:go through grid from top left, if cell of island, and its edge(connect to water) to perimeter 
        time&space complexity: 
        time: O(N), N is the num of grid cells. ---> O(N) 
        space: need a visited array ----> O(N) N is the num of grid cells.
        
        example:
        corner cases: grid is empty; the island is empty
        */
        int row = grid.size(), col = grid[0].size();
        vector<vector<int>> visited(row, vector<int>(col, 0));
        int res = 0;
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(grid[i][j]==1) {
                    //up
                    if(i==0 || grid[i-1][j]==0) res++;
                    //left
                    if(j==0 || grid[i][j-1]==0) res++;
                    //down
                    if(i==grid.size()-1 || grid[i+1][j]==0) res++;
                    //right
                    if(j==grid[0].size()-1 || grid[i][j+1]==0) res++;
                }
            }
        }
        return res;
    }
    
};






130. Surrounded Regions
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        //note: Surrounded regions shouldn’t be on the border!
        //set the border 'O' to 'S'
        //set 'O' to 'X', set 'S' to 'O'
        if(board.empty() || board[0].empty()) return;
        int row = board.size();
        int col = board[0].size();
        //up
        for(int c=0; c<col; c++){
            if(board[0][c]=='O') dfs(0, c, board);
        }
        //down
        for(int c=0; c<col; c++){
            if(board[row-1][c]=='O') dfs(row-1, c, board);
        }
        //left
        for(int r=0; r<row; r++){
            if(board[r][0]=='O') dfs(r, 0, board);
        }
        //right
        for(int r=0; r<row; r++){
            if(board[r][col-1]=='O') dfs(r, col-1, board);
        }
        
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == 'S') board[i][j] = 'O';
            }
        }
    }
    
    void dfs(int i, int j, vector<vector<char>>& board){
        if(i<0 || j<0 || i>=board.size() || j>=board[0].size() || board[i][j]!='O') return;
        board[i][j] = 'S';
        dfs(i-1, j, board);
        dfs(i, j-1, board);
        dfs(i+1, j, board);
        dfs(i, j+1, board);
    }
  
};


733. Flood Fill
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        if(image.empty() || image[0].empty()) return {};
        if(image[sr][sc] == newColor) return image;
        
        dfs(sr, sc, image[sr][sc], newColor, image);
        return image;
    }
    
    void dfs(int i, int j, int oldColor, int newColor, vector<vector<int>>& image){
        if(i<0 || j<0 ||i>=image.size() || j>=image[0].size() || image[i][j]!=oldColor) return;
        image[i][j] = newColor;
        dfs(i-1, j, oldColor, newColor, image);
        dfs(i, j-1, oldColor, newColor, image);
        dfs(i+1, j, oldColor, newColor, image);
        dfs(i, j+1, oldColor, newColor, image);
    }
    
};
    


127. Word Ladder
//BFS
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        set<string> dict(wordList.begin(), wordList.end());
        int res = 0;
        queue<string> q;
        q.push(beginWord);
        while(!q.empty()){
            res++;
            int t = q.size();
            for(int i=0; i<t; i++){
                string word = q.front();
                if(word == endWord) return res;
                q.pop();
                for(int i=0; i<word.size(); i++){
                    string newWord = word;
                    for(char c = 'a'; c<='z'; c++){
                        newWord[i] = c;
                        if(dict.count(newWord) && newWord != word){
                            q.push(newWord);
                            dict.erase(newWord);   //!!!
                        }
                    }
                }
            }
        }
        return 0;
    }
};


286. Walls and Gates
//DFS
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if(rooms.empty() || rooms[0].empty()) return;
        
        
        for(int i=0; i<rooms.size(); i++){
            for(int j=0; j<rooms[0].size(); j++){
                if(rooms[i][j]==0){
                    dfs(rooms, i, j, 0);
                }
            }
        }
        
        return;
    }
    
    void dfs(vector<vector<int>>& rooms, int i, int j, int dis){
        if(i<0 || j<0 || i>=rooms.size() || j>=rooms[0].size() || rooms[i][j]<dis) return;  //!!!rooms[i][j]<val return;!!!
        rooms[i][j] = dis;
        dfs(rooms, i-1, j, dis+1);
        dfs(rooms, i, j-1, dis+1);
        dfs(rooms, i+1, j, dis+1);
        dfs(rooms, i, j+1, dis+1);
    }
};


//DFS
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        if(rooms.empty()) return;
        int row = rooms.size();
        int col = rooms[0].size();
        for(int i=0; i<row; i++){
            for(int j=0; j<col; j++){
                if(rooms[i][j] == 0) dfs(rooms, i, j, 0);
            }
        }
    }
    void dfs(vector<vector<int>>& rooms, int i, int j, int val){
        if(rooms[i][j] == -1 || rooms[i][j]<val) return;   //!!! rooms[i][j] == -1 || rooms[i][j]<val
        rooms[i][j] = val;
        if(i-1>=0) dfs(rooms, i-1, j, val+1);
        if(j-1>=0) dfs(rooms, i, j-1, val+1);
        if(i+1<rooms.size()) dfs(rooms, i+1, j, val+1);
        if(j+1<rooms[0].size()) dfs(rooms, i, j+1, val+1);
        return;
    }
    
};


//BFS
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        //BFS
        queue<pair<int, int>> q;
        vector<vector<int>> dirs{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
        for (int i = 0; i < rooms.size(); ++i) {
            for (int j = 0; j < rooms[0].size(); ++j) {
                if (rooms[i][j] == 0) q.push({i, j});   
            }
        }
        while(!q.empty()){
            int i = q.front().first, j = q.front().second; 
            q.pop();
            for(int k=0; k<dirs.size(); k++){
                int x = i+dirs[k][0], y = j+dirs[k][1];
                if(x<0 || x>=rooms.size() || y<0 || y>=rooms[0].size() || rooms[x][y]<rooms[i][j]+1)
                    continue;
                rooms[x][y] = rooms[i][j] + 1;
                q.push({x, y});
            }
        }
    }
};




282. Expression Add Operators
//DFS
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        /*
        it is not the right way! because it is not cal from left to right
        if(num.empty()) return {};
        
        vector<string> res;
        int n = num.size();
        
        unordered_map<int, vector<string>> m;
        m[num[0]-'0'].push_back(num.substr(0, 1));
        for(int i=1; i<num.size(); i++){
            unordered_map<int, vector<string>> t;
            for(auto a:m){
                vector<string> v = a.second;
                for(auto s:v){
                    t[a.first + (num[i]-'0')].push_back(s+"+"+num[i]);
                    t[a.first - (num[i]-'0')].push_back(s+"-"+num[i]);
                    t[a.first * (num[i]-'0')].push_back(s+"*"+num[i]);
                    if((num[i]-'0')!=0) t[a.first / (num[i]-'0')].push_back(s+"/"+num[i]);
                }
            }
            m = t;
        }
        
        return m[target];
        */
        vector<string> res;
        helper(num, res, target, 0, 0, "");
        return res;
    }
    
    void helper(string num, vector<string>& res, int target, long long diff, long long curNum, string out){
        if(num.size()==0 && curNum == target) res.push_back(out);
        
        for(int i=1; i<=num.size(); i++){
            string cur = num.substr(0, i);
            if(cur.size()>1 && cur[0]=='0') return;
            string next = num.substr(i);
            if(out.size()>0){
                helper(next, res, target, +stoll(cur), curNum+stoll(cur), out+"+"+cur);
                helper(next, res, target, -stoll(cur), curNum-stoll(cur), out+"-"+cur);
                helper(next, res, target, diff*stoll(cur), (curNum-diff) + diff*stoll(cur), out+"*"+cur);
            }else{
                helper(next, res, target, stoll(cur), stoll(cur), cur);
            }
        }
    }
};

*********************************************************************************************************************************
two pointers
*********************************************************************************************************************************

27. Remove Element
//solution 1:
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //in place
        if(nums.empty()) return 0;
        int cur = 0;
        for(int i=0; i<nums.size(); i++){
            if(nums[i]!=val) nums[cur++] = nums[i];
        }
        return cur;
    }
};
//solution 2:
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //in place
        if(nums.empty()) return 0;
        int index = nums.size()-1;
        for(int i=0; i>=0&&i<=index; i++){
            if(nums[i] == val) swap(nums[i--], nums[index--]);
        }
        return index+1;
    }
};

283. Move Zeroes
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int index = 0;
        for(int i=0; i<nums.size(); i++){
            if(nums[i] != 0)
                swap(nums[index++], nums[i]);
        }
    }
    
};

125. Valid Palindrome
//two points. time complexity: O(N), space complexity: O(1)
class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty()||s.size()==1) return true;
        int left = 0, right = s.size()-1;
        while(left <= right){
            while(!isalnum(s[left])) left++;
            while(!isalnum(s[right])) right--;
            if(left>=right) return true;
            if(tolower(s[left]) == tolower(s[right])) {left++; right--;}
            else return false;        
        }
        return true;
    }
};



680. Valid Palindrome II
//time complexity: O(N), space complexity: O(1)
class Solution {
public:
    bool validPalindrome(string s) {
        
        int left = 0, right = s.size()-1;
        while(left<=right){
            if(s[left] == s[right]) {
                left++; 
                right--; 
                continue;
            }
            //s[left] != s[right]
            int left1 = left + 1, right1 = right; //remove the left char
            int left2 = left, right2 = right-1;   //remove the right char
            
            while(left1<=right1 && s[left1] == s[right1]) {
                    left1++; 
                    right1--; 
            }
            
            while(left2<=right2 && s[left2] == s[right2]) {
                    left2++; 
                    right2--; 
            }
            
            return left1>=right1 || left2>=right2;
        }
        return true;
    }
};

88. Merge Sorted Array  从后往前！！！
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int index = m+n-1;
        int idx1 = m-1, idx2=n-1;
        while(idx1>=0 && idx2>=0){
            if(nums2[idx2] > nums1[idx1]) nums1[index--] = nums2[idx2--];
            else nums1[index--] = nums1[idx1--];
        }
        while(idx2>=0) nums1[index--] = nums2[idx2--];
    }
};

75. Sort Colors
class Solution {
public:
    void sortColors(vector<int>& nums) {
        //sort in place 0...01...12...2
        //basic solution: two pass. first: go through and count, second: go through and modify the array
        /*
        vector<int> count(3, 0);
        for(int a:nums) count[a]++;
        int index = 0;
        for(int i=0; i<3; i++){
            for(int j=0; j<count[i]; j++){
                nums[index++] = i;
            }
        }
        */
        //one pass + in place? ---> two pointers(red, blue)
        int red = 0, blue = nums.size()-1;
        for(int i=0; i<=blue; i++){   //!!!i<=blue
            if(nums[i] == 0 && red != i){
                swap(nums[i--], nums[red++]);   //!!!  加了res!=i的判断，那么一开始就不会把开头的0扫掉，所以就可能把0换过来。不加的话，就不会把0换过来    if swap then i do not change
            }
            else if(nums[i] == 2 && blue != i){
                swap(nums[i--], nums[blue--]);   //!!!  blue!=i if swap then i do not change
            }
        }
        
    }
};

//另一种写法
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int len = nums.size();
        int red = 0; int blue = len-1;
        for(int i=0;i<=blue;i++){   //blue之后的都拍好顺序了
            if (nums[i]==0){
                swap(nums[i], nums[red++]); //换过来的不可能是0所以不用，不用i--
            }
            else if(nums[i]==2){
                swap(nums[i--], nums[blue--]);  //换过来的可能又是个2，所以要i--，并且blue--
            }
            else
                continue;
            
        }
    }
};


28. Implement strStr()
//time complexity:  O(N*M), N is the size of hayatack, M is the size of needle.
//two pointer: i, j
class Solution {
public:
    int strStr(string haystack, string needle) {
        //the index of the first occurrence of needle in haystack
        // return -1 if needle is not part of haystack
        if(needle.empty()) return 0;
        int n = haystack.size(), m = needle.size();
        for(int i=0; i<=n-m; i++){   //cut down
            int j=0;
            for(j=0; j<m; j++){    //cut down 
                if(needle[j] != haystack[i+j]) break;
            }
            if(j==m) return i;
        }
        return -1;
    }
};

// KMP 算法, time complexity: O(N)
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m = haystack.length(), n = needle.length();
        if (!n) {
            return 0;
        }
        vector<int> lps = kmpProcess(needle);
        for (int i = 0, j = 0; i < m; ) {
            if (haystack[i] == needle[j]) { 
                i++;
                j++;
            }
            if (j == n) {
                return i - j;
            }
            if ((i < m) && (haystack[i] != needle[j])) {
                if (j) {
                    j = lps[j - 1];
                }
                else {
                    i++;
                }
            }
        }
        return -1;
    }
private:
    vector<int> kmpProcess(string& needle) {
        int n = needle.length();
        vector<int> lps(n, 0);
        for (int i = 1, len = 0; i < n; ) {
            if (needle[i] == needle[len]) {
                lps[i++] = ++len;
            } else if (len) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
        return lps;
    }
};







151. Reverse Words in a String
class Solution {
public:
    void reverseWords(string &s) {
        if(s.empty()) return;
        int index = 0;
        reverse(s.begin(), s.end());
        //...the...blue...   ----> ...eulb...eht...
        for(int left=0; left<s.size(); left++){
            if(s[left] != ' '){
                if(index!=0) s[index++] = ' ';  //!!!
                int right = left;
                while(right<s.size() && s[right]!=' '){
                    s[index++] = s[right++];
                }
                reverse(s.begin()+index-(right-left), s.begin()+index);  //!!!
                left = right;   //!!!
            }
        }
        s.resize(index);
    }
};


186. Reverse Words in a String II
class Solution {
public:
    void reverseWords(vector<char>& str) {
        if(str.empty()) return;
        //in place without extra space ->swap()? reverse?
        for(int left=0; left<str.size(); left++){
            int right = left;
            while(right<str.size() && str[right]!=' ') right++;
            reverse(str.begin()+left, str.begin()+right);
            left = right;
        }
        reverse(str.begin(), str.end());
    }
};

//using swap
class Solution {
public:
    void reverseWords(vector<char>& str) {
        int left = 0;
        for(int i=0; i<str.size(); i++){
            if(str[i]==' ' || i==str.size()-1){
                int right =  (i==str.size()-1)? i: i-1;
                int start = left, end = right;
                while(start<=end){
                    swap(str[start++], str[end--]);
                }
                left = i+1;
            }
        }
        int start = 0, end = str.size()-1;
        while(start<=end){
            swap(str[start++], str[end--]);
        }
    }
};

//implement swap
class Solution {
public:
    void myswap(char &a, char &b){
        char temp = a;
        a = b;
        b = temp;
    }
    void reverseWords(vector<char>& str) {
        int left = 0;
        for(int i=0; i<str.size(); i++){
            if(str[i]==' ' || i==str.size()-1){
                int right =  (i==str.size()-1)? i: i-1;
                int start = left, end = right;
                while(start<=end){
                    myswap(str[start++], str[end--]);
                }
                left = i+1;
            }
        }
        int start = 0, end = str.size()-1;
        while(start<=end){
            myswap(str[start++], str[end--]);
        }
    }
};




674. Longest Continuous Increasing Subsequence
//solution 1
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int res = 0, cnt = 0, cur = INT_MAX;
        for (int num : nums) {
            if (num > cur) ++cnt;
            else cnt = 1;
            res = max(res, cnt);
            cur = num;
        }
        return res;
    }
};
//solution 2
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int left = 0;
        int max_len = 1;  //!!!
        for(int right =1; right<nums.size(); right++){
            while(right<nums.size() && nums[right]>nums[right-1]){
                right++;
            }
            max_len = max(max_len, right-left);  //!!!
            left = right;
        }
        
        return max_len;
    }
};

//
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.empty()) return 0;
        int left = 0;
        int res = 1;
        for(int right=1; right<nums.size(); right++){
            while(right<nums.size() && nums[right]>nums[right-1]) {
                res = max(res, right-left+1);
                right++;
            }
            left = right;
        }
        return res;
    }
};


//solution 2
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int res = 0, cnt = 0, cur = INT_MAX;
        for (int num : nums) {
            if (num > cur) ++cnt;
            else cnt = 1;
            res = max(res, cnt);
            cur = num;
        }
        return res;
    }
};


26. Remove Duplicates from Sorted Array
//two pointers
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //Given a sorted array nums, remove the duplicates in-place with O(1) space complexity
        //return the new len
        if(nums.empty()) return 0;
        int index = 0;
        for(int i=1; i<nums.size(); i++){
            if(nums[i] != nums[index]) nums[++index] = nums[i];
            else continue;
        }
        return index+1;   
    }
};




80. Remove Duplicates from Sorted Array II
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        if(nums.size()<=2) return nums.size();
        //in place
        int index = 2;
        for(int i = 2; i<nums.size(); i++){
            if(nums[i] != nums[index-2]) nums[index++] = nums[i];
        }
        return index;
    }
};



524. Longest Word in Dictionary through Deleting ？？？
class Solution {
public:
    string findLongestWord(string s, vector<string>& d) {
        //longest string in dictionary(by deleting some characters of the given string)
        //return in smallest lexicographical order
        string res = "";
        for(string word:d){
            if(subStr(word, s)){
                res = (word.size()>res.size() || word.size()==res.size()&&word<res)?word:res;
            }
        }
        return res;
    }
    
    bool subStr(string word, string s){
        int index1 = 0, index2=0;
        while(index1<word.size() && index2<s.size()){
            if(word[index1]==s[index2]){
                index1++;
                index2++;
            }
            else{
                index2++;
            }
        }
        return index1==word.size();
    }
};


11. Container With Most Water
//移小不移大
class Solution {
public:
    int maxArea(vector<int>& height) {
        if(height.empty() || height.size()<2) return 0;
        
        int left = 0, right = height.size()-1;
        int res = 0;
        while(left<right){
            res = max(res, min(height[left], height[right]) * (right-left));
            if(height[left] < height[right]) left++; //move the lower side
            else right--;
        }
        
        return res;
    }
};


42. Trapping Rain Water
//移小不移大
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        int left = 0, right = n-1;
        int res = 0;
        while(left<right){
            int mn = min(height[left], height[right]);
            if(mn == height[left]){
                left++;
                while(left<right && height[left]<mn) {res += mn-height[left]; left++;} //!!!left<right
            }
            else{
                right--;
                while(left<right && height[right]<mn){res += mn-height[right]; right--;}
            }
        }
        return res;
    }
};



class Solution {
public:
    int trap(vector<int>& height) {
        int left = 0, right = height.size()-1;
        
        int res = 0;
        
        while(left<right){
            int mn = min(height[left], height[right]);
            if(mn == height[left]){
                while(left<right && height[left] <= mn){ //!!!left<right
                    res += mn - height[left];
                    left++;
                }
            }
            else if(mn == height[right]){
                while(right>left && height[right] <= mn){
                    res += mn - height[right];
                    right--;
                }
            }
        }
        
        return res;
    }
};



********************************************************************************************************
subarray
********************************************************************************************************
862. Shortest Subarray with Sum at Least K
//>=k
// 有负数  不能用sliding window 只能用map
class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
       //Shortest Subarray with Sum >= K
        //two pointer. no! there is negtive integer in this issue
        //map
        map<int, int> m; //map<sum, index>
        int sum = 0;
        int res = INT_MAX;
        for(int i=0; i<A.size(); i++){
            sum += A[i];
            if(sum >= K) res = min(res, i+1);
            while(!m.empty() && sum - m.begin()->first >= K){
                res = min(res, i-m.begin()->second);
                m.erase(m.begin());
            }
            
            m[sum] = i;
        }
        
        return res==INT_MAX? -1 : res;
        
    }
};

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
       //Shortest Subarray with Sum >= K
        //two pointer. no! there is negtive integer in this issue
        //map
        map<int, int> m;  //map<sum, index>
        int sum = 0;
        int res = A.size()+1;
        for(int i=0; i<A.size(); i++){
            sum+=A[i];
            if(sum>=K) res = min(res, i+1);  //!!!
            while(!m.empty() && sum - m.begin()->first >= K){
                auto it = m.begin();
                res = min(res, i-it->second);
                m.erase(it);               //!!!
            }
            m[sum] = i;
        }
        return res==A.size()+1 ? -1:res;
        
        //Shortest Subarray with Sum == K
        /*
        unordered_map<int, int> m; //map<sum, index>
        m[0] = -1;
        int sum = 0;
        int res = A.size()+1;
        for(int i=0; i<A.size(); i++){
            sum += A[i];
            if(m.count(sum-K)) res = min(res, i-m[sum-K]);
            m[sum] = i;
        }
        return res==A.size()+1 ? -1 : res;
        */
    }
};


209. Minimum Size Subarray Sum
//two points; time complexity: O(N), space complexity:O(1)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        // two points
        if(nums.empty()) return 0;
        int left = 0, sum = 0, min_len = INT_MAX;
        for(int right = 0; right<nums.size(); right++){
            sum += nums[right];
            while(left<=right && sum>=s){
                min_len = min(min_len, right-left+1);
                sum -= nums[left++];
            }
        }
        return min_len==INT_MAX?0:min_len;
    }
};

//">=" -----> "=" , solution 1: two pointers
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        // two points
        if(nums.empty()) return 0;
        int left = 0, sum = 0, min_len = INT_MAX;
        for(int right = 0; right<nums.size(); right++){
            sum += nums[right];
            while(left<=right && sum>=s){
                if(sum==s) min_len = min(min_len, right-left+1);
                sum -= nums[left++];
            }
        }
        return min_len==INT_MAX?0:min_len;
    }
};

//">=" -----> "=" , solution 2: hash table




//binary search solution: time complexity: O(NlogN), space complexity:O(N)
// O(nlgn)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = nums.size(), sums[len + 1] = {0}, res = len + 1;
        for (int i = 1; i < len + 1; ++i) sums[i] = sums[i - 1] + nums[i - 1];
        for (int i = 0; i < len + 1; ++i) {
            int right = searchRight(i + 1, len, sums[i] + s, sums);
            if (right == len + 1) break;
            if (res > right - i) res = right - i;
        }
        return res == len + 1 ? 0 : res;
    }
    int searchRight(int left, int right, int key, int sums[]) {
        while (left <= right) {
            int mid = (left + right) / 2;
            if (sums[mid] >= key) right = mid - 1;
            else left = mid + 1;
        }
        return left;
    }
};









560. Subarray Sum Equals K
//hash table. time complexity: O(N); space complexity: O(N)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m; //<sum, count>
        int res = 0;
        int sum = 0;
        m[0] = 1;   //m[0]==1！！！为了从index为0开始的subarray
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];
            if(m.count(sum-k)) res += m[sum-k];
            m[sum]++;
        }
        return res;
    }
};



525. Contiguous Array
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> m;   //map<sum, index>
        int sum = 0;
        int res = 0;
        m[0] = -1;
        for(int i=0; i<nums.size(); i++){
            sum += (nums[i]==0 ? -1 : 1);
            if(m.count(sum)) res = max(res, i-m[sum]);
            if(!m.count(sum)) m[sum] = i;
        }
        return res;
    }
};



325. Maximum Size Subarray Sum Equals k
//hash table
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> m; //m<sum, index>
        
        int sum = 0, res = 0;
        m[0] = -1;     //!!!
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];
            if(m.count(sum-k)) res = max(res, i-m[sum-k]);
            if(!m.count(sum)) m[sum] = i;
        }
        
        return res; 
    }
    
};

523. Continuous Subarray Sum
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        //non-negative numbers and a target integer k
        //continuous subarray of size at least 2 that sums up to the multiple of k
        
        //first idea: two nested loop
        //time complexity: O(N^2), space complexity: O(1)
        
        //second idea: save sum%k to map
        //the sum of difference array A of two arrays with same sum%k is k*n

        // A = B - C. if B and C has the same value of sum%k, then A is k*n.
        
        //time complexity: O(N), space complexity: O(N)
        unordered_map<int, int> m; //map<sum%k, index> m[0] = -1;
        m[0] = -1;                  //!!!
        int sum = 0;
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];
            int t = k==0?sum:sum%k;    //!!!
            if(m.count(t)){
                if(i - m[t] >= 2)    //!!! nested if
                    return true;
            }
            else m[t] = i;   //!!!不存在才需要m[t] = i,存在不需要更新
        }
        return false;  
    }
};


class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        //mod, what if k ==0
        unordered_map<int, int> m; //!!! map<sum%k, index> 
        m[0] = -1; //!!! [0, 0]
        int sum = 0;
        for(int i=0; i<nums.size(); i++){
            sum += nums[i];
            int t = k==0?sum:sum%k;  //!!!
            if(m.count(t) && i-m[t]>=2) return true; //!!!
            if(!m.count(t)) m[t] = i;  //!!!
        }
        
        return false;
    }
};


***********************************************************************************************************************
regular expression match
***********************************************************************************************************************
10. Regular Expression Matching 
//recursion
class Solution {
public:
    bool isMatch(string s, string p) {
        return helper(s, p, 0, 0);
    }
    
    bool helper(string s, string p, int idx1, int idx2){
        if(idx2 >= p.size()) return idx1>=s.size();
        
        if(idx2+1<p.size() && p[idx2+1]=='*'){  //  abbbb ab*(idx1+1)     adddd ab*(idx2+2) 
            return idx1<s.size() && (s[idx1]==p[idx2]||p[idx2]=='.')&&helper(s, p, idx1+1, idx2) || helper(s, p, idx1, idx2+2);
        }
        else{
            return idx1<s.size() && (s[idx1]==p[idx2]||p[idx2]=='.') && helper(s, p, idx1+1, idx2+1);
        }
        
    }
};
//DP方法？？？？
/*
1.  DP[i][j] = DP[i - 1][j - 1], if p[j - 1] != '*' && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
2.  DP[i][j] = DP[i][j - 2], if p[j - 1] == '*' and the pattern repeats for 0 times;
3.  DP[i][j] = DP[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'), if p[j - 1] == '*' and the pattern repeats for at least 1 times.
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int n1 = s.size();
        int n2 = p.size();
        vector<vector<bool>> dp(n1+1, vector<bool>(n2+1, false));
        dp[0][0] = true;
            
        for(int i=0; i<=n1; i++){  //!!!
            for(int j=1; j<=n2; j++){
                if(j>1 && p[j-1]=='*'){
                    dp[i][j] = dp[i][j-2] || i>0 && (s[i-1]==p[j-2]||p[j-2]=='.') && dp[i-1][j];  //!!!
                }
                else{
                    dp[i][j] = i>0 && (s[i-1]==p[j-1]||p[j-1]=='.') && dp[i-1][j-1];  //!!!
                }
                
            }
        }
        return dp[n1][n2];
        
    }
    
};

//
class Solution {
public:
    bool isMatch(string s, string p) {
        int row = s.size();
        int col = p.size();
        vector<vector<bool>> dp(row+1, vector<bool>(col+1, false));
        
        //edge cases
        dp[0][0] = true; //empty string and empty pattern match
        
        for(int r=1; r<=row; r++) dp[r][0] = false; //nonempty string and empty pattern do not match
        for(int c=1; c<=col; c++) dp[0][c] = c>1 && p[c-1]=='*' && dp[0][c-2] ; //empty string with nonempty pattern
        
        //normal cases
        for(int i=1; i<=row; i++){
            for(int j=1; j<=col; j++){
                if(p[j-1]=='*'){
                    //the char before * can have 0 occurances or more than 0 occurances
                    // (ab*c  ac)     (ab*c  abc)  
                    dp[i][j] = dp[i][j-2] || (p[j-2]==s[i-1] || p[j-2]=='.') && dp[i-1][j];
                }
                else{
                    dp[i][j] = (p[j-1]==s[i-1] || p[j-1]=='.') && dp[i-1][j-1];
                }
            }
        }
        
        return dp[row][col];
        
    }
    
};




**********************************************************************************************************************
Calculator
**********************************************************************************************************************
224. Basic Calculator
//using stack + sign  
class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int res = 0, sign = 1;   //!!!sign
        // num '+' '-': -----> cal res
        // '(': push res into stack
        //  ')': -----> stack pop, cal res
        for(int i=0; i<s.size(); i++){
            char c = s[i];
            if(c >= '0'){
                int num = 0;
                while(i<s.size() && s[i]>='0'){
                    num = num*10 + s[i]-'0';
                    i++;
                }
                res += sign*num;
                i--;   //!!!
            }
            else if(c == '+'){
                sign = 1;
            }
            else if(c == '-'){
                sign = -1;
            }
            else if(c == '('){
                st.push(res);
                st.push(sign);
                res = 0;    //!!!res = 0, sign = 1;
                sign = 1;
            }
            else if(c == ')'){
                res *= st.top(); st.pop();
                res += st.top(); st.pop();
            }
        }
        return res;
    }
};

227. Basic Calculator II
//stack + op  (op+num)
class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int num = 0;
        char op = '+';
        
        for(int i=0; i<s.size(); i++){
            if(s[i]>='0' && s[i]<='9'){
                num = 0;
                while(s[i]>='0' && s[i]<='9'){
                    num = num*10 + s[i]-'0';
                    i++;
                }
                if(op=='-') num = -1*num;
                st.push(num);
                i--;
            }
            
            if(i==s.size()-1 || s[i]=='*' || s[i]=='/' || s[i]=='-' || s[i]=='+'){
                if(op == '*' || op=='/'){
                    int b = st.top();
                    st.pop();
                    int a = st.top();
                    st.pop();
                    if(op=='*') st.push(a*b);
                    else st.push(a/b);
                    
                }
                op = s[i];
            }
        }
        int res = 0;
        while(!st.empty()){
            res += st.top();
            st.pop();
        }
        return res;
    }
};


772. Basic Calculator III


***********************************************************************************************************************
tree
***********************************************************************************************************************
314. Binary Tree Vertical Order Traversal

//用DFS不能保证从上到下哦

//BFS(queue, pair) + map
//time complexity: O(NlogN)
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        //from top to bottom, column by column ->  bfs queue
        //from left to right. -> increase map
        if(root==NULL) return {};
        
        map<int, vector<int>> m;  //key increase
        queue<pair<TreeNode*, int>> q; // pair<node, distance>
        q.push({root, 0});
        
        while(!q.empty()){
            auto t = q.front();
            q.pop();
            TreeNode* node = t.first;
            int dis = t.second;
            m[dis].push_back(node->val);
            if(node->left) q.push({node->left, dis-1});
            if(node->right) q.push({node->right, dis+1});
        }
        
        //map increasing with distance from root, from left to right
        //m-->res
        vector<vector<int>> res;
        for(auto a:m){
            res.push_back(a.second);
        }
        return res;
    }

    
};

//Time Complexity of above implementation is O(n Log n). Note that above implementation uses map which is implemented using self-balancing BST.
//We can reduce time complexity to O(n) using unordered_map. To print nodes in desired order, we can have 2 variables denoting min and max horizontal distance. 
//We can simply iterate from min to max horizontal distance and get corresponding values from Map. So it is O(n)
// unordered_map can replace map, time complexity: O(N).
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        // left to right
        // from top to bottom
        if(root==NULL) return {};
        
        unordered_map<int, vector<int>> m;
        int min_dis = INT_MAX, max_dis = INT_MIN;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});
        while(!q.empty()){
            auto t = q.front();
            q.pop();
            
            TreeNode* node = t.first;
            int dis = t.second;
            min_dis = min(min_dis, dis);
            max_dis = max(max_dis, dis);
            m[dis].push_back(node->val);
            
            if(node->left) q.push({node->left, dis-1});
            if(node->right) q.push({node->right, dis+1});
        }
        
        vector<vector<int>> res;
        
        for(int i=min_dis; i<=max_dis; i++){
            res.push_back(m[i]);
        }
        return res;
    }

    
};






114. Flatten Binary Tree to Linked List
//recursion
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    void flatten(TreeNode* root) {
        if(root == NULL) return;
        
        flatten(root->left);
        flatten(root->right);
        
        TreeNode* tmp = root->right;
        root->right = root->left;
        root->left = NULL;
        
        while(root->right) root = root->right;
        root->right = tmp;
        
    }
    
};
🌼🌼🌼// Non-recursion
class Solution {
public:
    void flatten(TreeNode *root) {
        if(root==NULL) return;
        TreeNode* cur = root;
        while(cur){
            if(cur->left){
                TreeNode* p = cur->left;
                while(p->right) p = p->right;
                p->right = cur->right;
                cur->right = cur->left;
                cur->left = NULL;   
            }
            
            cur = cur->right;
        }
        
    }
};


// Non-recursion
class Solution {
public:
    void flatten(TreeNode *ro
        ot) {
        TreeNode* node = root;
        while(node){
            if(node->left){
                TreeNode* t = node->right;
                node->right = node->left;
                node->left = NULL;
                TreeNode* p = node;
                while(p->right){
                    p = p->right;
                }
                p->right = t;
            }
            node = node->right;
        }
    }
};

426 Convert Binary Search Tree to Sorted Doubly Linked List
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        //left => pre
        //rigth =>next
        //the predecessor of the first element is the last element, and the successor of the last element is the first element.
        if(!root) return NULL;
        Node* dummy = new Node(-1, NULL, NULL);
        Node* pre = dummy;
        inorder(root, pre);  //!!!
        
        
        dummy->right->left = pre; //the predecessor of the first element is the last element
        pre->right = dummy->right; //  the successor of the last element is the first element.
        
        return dummy->right;
    }
    
    void inorder(Node* root, Node*& pre){   //!!!
        if(!root) return;
        inorder(root->left, pre);
        root->left = pre;
        pre->right = root;  //!!!
        pre = root; 
        inorder(root->right, pre);
    }    
};


257. Binary Tree Paths
//Time Complexity: O(2^h)＝O(N),  where N is number of nodes.
//但是如果print out所有符合的path，那么最坏是n方的  
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//注意leaf
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        string out = "";
        dfs(root, res, out);
        return res;
    }
    void dfs(TreeNode* root, vector<string>& res, string out){
        if(root==NULL) return;
        if(root->left == NULL && root->right == NULL) 
            res.push_back(out+to_string(root->val));   //!!!
        else{
            dfs(root->left, res, out + to_string(root->val) + "->");
            dfs(root->right, res, out + to_string(root->val) + "->");
        }
    }

};


173. Binary Search Tree Iterator
//using stack to iterator!!!
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 //next smallest number in the BST. -> inorder
class BSTIterator {
private:
    stack<TreeNode*> st;
public:
    BSTIterator(TreeNode *root) {
        find_left(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(st.empty()) return false;
        else return true;
    }
    /** @return the next smallest number */
    int next() {
        TreeNode* node = st.top();
        st.pop();
        find_left(node->right);   //!!!
        return node->val;
    }
    
    void find_left(TreeNode* root){
        while(root){
            st.push(root);
            root = root->left;
        }
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

98. Validate Binary Search Tree
//用 min 和 max来判断
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


//Time Complexity: O(n)， Auxiliary Space : O(1) if Function Call Stack size is not considered, otherwise O(n)
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
    bool helper(TreeNode* root, long mn, long mx){    //long
        if(root==NULL) return true;
        if(root->val <= mn || root->val >= mx) return false;   //!!!=  ||
        return helper(root->left, mn, root->val) && helper(root->right, root->val, mx);
    }
};



🌼🌼🌼//inorder dfs, Time Complexity: O(n)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode* pre = NULL;
        return isValid(root, pre);
    }
    
    bool isValid(TreeNode* root, TreeNode* &pre){
        if(root==NULL) return true;
        if(!isValid(root->left, pre)) return false;
        if(pre!=NULL && root->val <= pre->val) return false;
        pre = root;
        return isValid(root->right, pre);
    }
};


// Non-recursion with stack
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> st;
        TreeNode *p = root, *pre = NULL;  //!!!
        while (p || !s.empty()) {
            while (p) {
                st.push(p);
                p = p->left;
            }
            TreeNode *t = st.top(); st.pop();
            if (pre && t->val <= pre->val) return false;  //!!!
            pre = t;
            p = t->right;
        }
        return true;
    }
};






543. Diameter of Binary Tree
// dfs + hash table(save the intermidiate answer)
//time complexity: O(N^2)
class Solution {
private:
    unordered_map<TreeNode*, int> m;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        //The diameter of a binary tree is the length of the longest path between any two nodes
        int res = deep(root->left) + deep(root->right); 
        int left = diameterOfBinaryTree(root->left);
        int right = diameterOfBinaryTree(root->right);
        return max(res, max(left, right));
    }
    int deep(TreeNode* root){
        if(root == NULL) return 0;
        if(m.count(root)) return m[root];
        int res =  1+max(deep(root->left), deep(root->right));
        return m[root] = res;
    }
};
//在求deepth的过程中， 直接求res. Time complexity: O(N)
class Solution {
private:
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        int res = 0;
        deep(root, res);
        return res;
    }
    int deep(TreeNode* root, int& res){
        if(root == NULL) return 0;
        int left = deep(root->left, res);
        int right = deep(root->right, res);
        int local_max = left + right;
        res = max(res, local_max);
        int h =  1+max(left, right);
        return h;
    }
};

//优化: 用hash table存中间结果
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    unordered_map<TreeNode*, int> m;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(root==NULL || !root->left&&!root->right) return 0;
        int res = 0;
        height(root, res);
        return res;
    }
    int height(TreeNode* root, int& res){
        if(root==NULL) return 0;
        if(m.count(root)) return m[root];
        int left = height(root->left, res);
        int right = height(root->right, res);
        
        int localmax = left + right;
        res = max(res, localmax);
        
        return m[root] = 1 + max(left, right);
    }

};


//follow up: multiple children   ???实现！！！
//We can make a hash table to store heights of all nodes. 
//If we precompute these heights, we don’t need to call depthOfTree() for every node.


/*
In this post a different DFS based solution is discussed. 
After observing above tree we can see that the longest path will always occur between two leaf nodes. 
We start DFS from a random node and then see which node is farthest from it. Let the node farthest be X. 
It is clear that X will always be a leaf node and a corner of DFS. 
Now if we start DFS from X and check the farthest node from it, we will get the diameter of the tree.
*/
Step 1: Run bfs to find the farthest node from rooted tree let say A
Step 2: Then run bfs from A to find farthest node from A let B
Step 3: Distance between node A and B is the diameter of given tree





235 Lowest Common Ancestor of a Binary Search Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        /***********1. binary tree solution
        if(root == NULL) return NULL;
        if(root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if(left && right) return root;
        else return left?left:right;
        ***************/
        /***********2. BST solution(recursive)
        if(!root) return NULL;
        int t1 = p->val - root->val;
        int t2 = q->val - root->val;
        if(t1 * t2 <= 0) return root;    //!!!等号
        else if(t1 + t2 > 0)  return lowestCommonAncestor(root->right, p, q);
        else return lowestCommonAncestor(root->left, p, q);
        ***************/
        
        //3. BST solution(not recursive) time comlexity: O(logN)
        if(!root) return NULL;
        while(true){
            int t1 = p->val - root->val;
            int t2 = q->val - root->val;
            if(t1*t2 <= 0) return root;
            else if(t1+t2 > 0) root = root->right;
            else root = root->left;
        }
 
        
    }
};


236. Lowest Common Ancestor of a Binary Tree
//p and q are both tree node
class Solution {
public:s

};
//if p or q is not tree node!!!!!
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res = dfs(root, p, q);
        if(check(res, p, q)==2) return res;     ////check if p or q is not tree node!!!!!
        else return NULL;
    }
    
    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root == NULL) return NULL;
        if(root == p || root==q) return root;
        //if left subtree contain p or q ?
        TreeNode* left = dfs(root->left, p, q);
        //if right subtree contain p or q ?
        TreeNode* right = dfs(root->right, p, q);
        //left and right both contain p or q, then return root
        if(left&&right) return root;
        //return left or right
        return left?left:right;
    }
    
    int check(TreeNode* root, TreeNode* p, TreeNode* q){
        int count = 0;
        if(root==p || root==q) count++;
        if(root->left) count += check(root->left, p, q);
        if(root->right) count += check(root->right, p, q);
        return count;
    }

};



//follow up: 如何优化到O(logN)
// 输的节点加一个parent指针，这样只需要往回匹配parent指针就好了，时间复杂度为树的高度。






//优化
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root==NULL || root==p || root==q) return root;
        //checck left substr contian p q
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        if(left && left!=p && left!=q) return left;
        //checck right substr contian p q
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if(right && right!=p && right!=q) return right;
        
        if(left&&right) return root;
        return left?left:right;     
    }
};








111. Minimum Depth of Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        //1. first solution: DFS
        /**************************
        if(root==NULL) return 0;
        if(!root->left && !root->right) return 1;
        else if(!root->left) return 1+ minDepth(root->right);
        else if(!root->right) return 1 + minDepth(root->left);
        else return 1 + min(minDepth(root->left), minDepth(root->right)); 
        *************************/
        
        //2. second solution: BFS
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int res = 0;
        while(!q.empty()){
            res++;    //!!!
            int t = q.size();
            for(int i=0; i<t; i++){
                TreeNode* node = q.front();
                q.pop();
                if(!node->left && !node->right) return res;   //!!!
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return res;
    }
};


104 Maximum Depth of Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        //DFS
        /**************************
        if(root == NULL) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right)); 
        **************************/
        //BFS
        if(!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int res = 0;
        while(!q.empty()){
            res++;
            int t = q.size();
            for(int i=0; i<t; i++){
                TreeNode* node = q.front();
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return res;
    }
};

662. Maximum Width of Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        //width: length between the leftmost and right most non-null nodes in the level
        //maybe in the middle level
        //first idea: BFS push every node into queue, including NULL, update width in every level(remove NULL from the end of queue)
        //1. DFS
        /**********
        int res = 0;
        vector<int> lefts;  //!!!leftmost idx of every level
        dfs(root, 0, 1, res, lefts);
        return res;
        **********/
        //2. BFS
        if(!root) return NULL;
        queue<pair<TreeNode*, int>> q; //pair<node, idx>
        q.push({root, 1});
        int res = 0;
        while(!q.empty()){
            int left = q.front().second, right = left, t = q.size();
            for(int i=0; i<t; i++){
                TreeNode* node = q.front().first;
                right = q.front().second;
                q.pop();   //!!!
                if(node->left) q.push({node->left, right*2});
                if(node->right) q.push({node->right, right*2+1});
            }
            res = max(res, right-left+1);   //!!!
        }
        return res;
    }
    void dfs(TreeNode* root, int h, int idx, int& res, vector<int>& lefts){
        if(!root) return;
        if(h >= lefts.size()) lefts.push_back(idx);  //!!!
        
        res = max(res, idx - lefts[h] + 1);
        dfs(root->left, h+1, idx*2, res, lefts);
        dfs(root->right, h+1, idx*2+1, res, lefts);
    }
};


285. Inorder Successor in BST

//solution 3, using the property of BST, time complexity: O(logN)!!!
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* res = NULL;
        while(root){
            if(root->val > p->val){  //p in th left subtree of root
                res = root;
                root = root->left;
            }else{                   // p in the right of root
                root = root->right;
            }
        }
        return res;
    }
};


//Predecessor
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        TreeNode* res = NULL;
        while(root){
            if(root->val < p->val){  //p in th right subtree of root
                res = root;
                root = root->right;

            }else{     //p in the left subtree of root              
                root = root->left;
            }
        }
        return res;
    }
};

//Recursive
//Successor
public TreeNode successor(TreeNode root, TreeNode p) {
  if (root == null)
    return null;

  if (root.val <= p.val) {
    return successor(root.right, p);
  } else {
    TreeNode left = successor(root.left, p);
    return (left != null) ? left : root;
  }
}
//Predecessor
public TreeNode predecessor(TreeNode root, TreeNode p) {
  if (root == null)
    return null;

  if (root.val >= p.val) {
    return predecessor(root.left, p);
  } else {
    TreeNode right = predecessor(root.right, p);
    return (right != null) ? right : root;
  }
}




//假如有parent指针！！！
/*
Let’s denote the Inorder Successor of inputNode as successorNode. To arrive to the solution, we distinguish between two cases:
1. inputNode has a right child. In this case successorNode would be the node with the minimum key in inputNode's right subtree.
2. inputNode doesn’t have a right child. In this case successorNode would be one of inputNode's ancestors. More specifically, 
within inputNode's ancestor chain (starting from inputNode all the way up to the root), 
successorNode is the first parent that has a left child in that chain.

we are visiting only O(H) number of nodes, where H is the height of the BST. For a balanced BST, since H = log(N), 
where N is the number of nodes in the BST, the time complexity is O(log(N)). For an unbalanced BST, the time complexity is O(N).
*/
Node* findInOrderSuccessor( Node *root, Node *inputNode )
{
   // your code goes here
  if(inputNode->right){
    Node* p = inputNode->right;
    while(p->left){
      p=p->left;
    }
    return p;
  } 
  else{
    Node* child = inputNode;
    Node* ancestor = inputNode->parent;
    while(ancestor!=NULL && child == ancestor->right){
      child = ancestor;
      ancestor = child->parent;
    }
    return ancestor;
  }
  
}







//solution 1
//DFS inorder     time complexity: O(N)!!!
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* pre, *res;
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(root==NULL || p==NULL) return NULL;
        pre = NULL; res = NULL;
        inorder(root, p);
        return res;
    }
    
    TreeNode* inorder(TreeNode* root, TreeNode* p){
        if(root == NULL) return NULL;
        inorder(root->left, p);
        if(pre == p) res = root;
        pre = root;
        inorder(root->right, p);
        return NULL;
    }
};






//solution 2
//BFS inorder
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        //BFS
        stack<TreeNode*> st;
        TreeNode* node = root;
        bool flag = false;    //root一开始不要push到stack
        while(node || !st.empty()){
            while(node){
                st.push(node);
                node = node->left;
            }
            TreeNode* t = st.top();
            st.pop();
            if(flag) return t;
            if(t == p) flag = true;
            node = t->right;
        }
        return NULL;
    }
};




 
124. Binary Tree Maximum Path Sum
//DFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        //DFS
        if(root==NULL) return 0;
        int res = root->val;
        helper(root, res);
        return res;
    }
    
    int helper(TreeNode* root, int& res){
        if(!root) return 0;
        //left max sum path
        int left = max(helper(root->left, res), 0);
        //right max sum path
        int right = max(helper(root->right, res), 0);
        
        //update ressult
        int localmax = root->val+left+right;
        res = max(res, localmax);
        
        return root->val + max(left, right);
    }

};
//follow up: return the array of that path ???





230. Kth Smallest Element in a BST
//inorder DFS
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    int count = 0, res = 0;
public:
    int kthSmallest(TreeNode* root, int k) {
        inorder(root, k);
        return res;
    }
    void inorder(TreeNode* root, int k){
        if(root == NULL) return;
        inorder(root->left, k);
        count++;
        if(count==k) res = root->val;
        inorder(root->right, k);
    }
    
};
//using stack
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {

public:
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* p = root;
        int count = 0;
        while(p || !st.empty()){
            while(p){
                st.push(p);
                p = p->left;
            }
            TreeNode* node = st.top();
            st.pop();
            count++;
            if(count == k) return node->val;
            p = node->right;
        }
        return 0;
    }
    
};
/*
Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? 
How would you optimize the kthSmallest routine?
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
class Solution {
public:
    struct MyTreeNode{
        int count;   //the count of nodes in left or right subtree 
        int val;
        MyTreeNode* left;
        MyTreeNode* right;
        MyTreeNode(int x):val(x), left(NULL), right(NULL), count(1){}
    };

    MyTreeNode* build(TreeNode* root){
        if(root==NULL) return NULL;
        MyTreeNode* node = new MyTreeNode(root->val);
        node->left = build(root->left);
        node->right = build(root->right);
        if(node->left) node->count += node->left->count;
        if(node->right) node->count += node->right->count;
        return node;
    }

    int kthSmallest(TreeNode* root, int k) {
        MyTreeNode* node = build(root);
        return helper(node, k);
    }

    int helper(MyTreeNode* node, int k){
        if(node->left){
            int cnt = node->left->count;
            if(cnt>=k) return helper(node->left, k);
            else if(cnt==k-1) return node->val;
            else return helper(node->right, k-cnt-1);
        }
        else{
            if(k==1) return node->val;
            return helper(node->right, k-1);
        }
    }
    
};



105. Construct Binary Tree from Preorder and Inorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        /*
        preorder = [3,9,20,15,7]
                    ^| |      |
        inorder = [9,3,15,20,7]
                  | |^|       |
        */
        //recursively
        return buildTree(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1);
    }
    
    TreeNode* buildTree(vector<int>& preorder, int pleft, int pright, vector<int>& inorder, int ileft, int iright){
        if(pleft>pright || ileft>iright) return NULL;
        int i = 0;
        for(i = ileft; i<=iright; i++){
            if(inorder[i] == preorder[pleft]) break;
        }
        TreeNode* node = new TreeNode(preorder[pleft]);
        node->left = buildTree(preorder, pleft+1, pleft+i-ileft,inorder, ileft, i-1);
        node ->right = buildTree(preorder, pright+i-iright+1, pright,inorder, i+1, iright);
        return node;
    }

};




106. Construct Binary Tree from Inorder and Postorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        /*
        inorder =   [9,3,15,20,7]
                    | |^|      |
        postorder = [9,15,7,20,3]
                    | |       |^
        */  
        //recursion
        return buildTree(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
    }
    TreeNode* buildTree(vector<int>& inorder, int ileft, int iright, vector<int>& postorder, int pleft, int pright){
        if(ileft>iright || pleft>pright) return NULL;
        
        int i = 0;
        for(i=ileft; i<=iright; i++){
            if(inorder[i] == postorder[pright]) break;
        }
        TreeNode* node = new TreeNode(postorder[pright]);
        node->left = buildTree(inorder, ileft, i-1, postorder, pleft, pleft+i-1-ileft); 
        node->right = buildTree(inorder, i+1, iright, postorder, pright-iright+i, pright-1);
        return node;
    }
};


449. Serialize and Deserialize BST
//preorder tranverse
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream os;
        serialize(root, os);
        return os.str();
    }
    void serialize(TreeNode* root, ostringstream &os){
        if(root){
            os<<root->val<<" ";
            serialize(root->left, os);
            serialize(root->right, os);   
        }
        else 
            os<<"# ";
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream is(data);
        return deserialize(is);
    }
    TreeNode* deserialize(istringstream &is){
        string val;
        is>>val;
        if(val=="#") return NULL;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(is);
        root->right = deserialize(is);
        return root;
    }
    
    
};


//level order traverse
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL) return "NULL";  //!!!
        queue<TreeNode*> q;
        q.push(root);
        ostringstream out;
        while(!q.empty()){
            TreeNode* t = q.front();
            q.pop();
            if(t!=NULL){
                out<<t->val<<" ";
                q.push(t->left);
                q.push(t->right);
            }
            else{
                out<<"NULL ";
            }
        }
        return out.str();
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "NULL") return NULL;  //!!!
        istringstream is(data);
        string val;
        is>>val;
        TreeNode* root = new TreeNode(stoi(val));
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* t = q.front();
            q.pop();
            if(!(is>>val)) break;
            if(val != "NULL"){
                t->left = new TreeNode(stoi(val));
                q.push(t->left);
            }
            else{
                t->left = NULL;
            }
            if(!(is>>val)) break;
            if(val != "NULL"){
                t->right = new TreeNode(stoi(val));
                q.push(t->right);
            }
            else{
                t->right = NULL;
            }
        }
        return root;
    }
};

297. Serialize and Deserialize Binary Tree  
//preorder tranverse
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream os;
        serialize(root, os);
        return os.str();
    }
    void serialize(TreeNode* root, ostringstream &os){
        if(root){
            os<<root->val<<" ";
            serialize(root->left, os);
            serialize(root->right, os);   
        }
        else 
            os<<"# ";
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream is(data);
        return deserialize(is);
    }
    TreeNode* deserialize(istringstream &is){
        string val;
        is>>val;
        if(val=="#") return NULL;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(is);
        root->right = deserialize(is);
        return root;
    }
    
    
};


//BFS!!!
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(root == NULL) return "NULL";
        queue<TreeNode*> q;
        q.push(root);
        ostringstream out;
        while(!q.empty()){
            TreeNode* t = q.front();
            q.pop();
            if(t!=NULL){
                out<<t->val<<" ";
                q.push(t->left);
                q.push(t->right);
            }
            else{
                out<<"NULL ";
            }
        }
        return out.str();
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "NULL") return NULL;
        istringstream is(data);
        string val;
        is>>val;
        TreeNode* root = new TreeNode(stoi(val));
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* t = q.front();
            q.pop();
            if(!(is>>val)) break;
            if(val != "NULL"){
                t->left = new TreeNode(stoi(val));
                q.push(t->left);
            }
            else{
                t->left = NULL;
            }
            if(!(is>>val)) break;
            if(val != "NULL"){
                t->right = new TreeNode(stoi(val));
                q.push(t->right);
            }
            else{
                t->right = NULL;
            }
        }
        return root;
    }
};






108. Convert Sorted Array to Binary Search Tree
//solution 1 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        //a height balanced BST.   --->   the middle num > root
        if(nums.empty()) return NULL;
        int n = nums.size();
        int mid = n/2;   //!!!
        //root;
        TreeNode* root = new TreeNode(nums[mid]);
        //left
        if(mid-1>=0){   //!!!判断
            vector<int> front(nums.begin(), nums.begin()+mid);   //!!!最后一个不算
            root->left = sortedArrayToBST(front);   
        }
        else root->left = NULL;
        //right
        if(mid+1<n){ //!!!判断
            vector<int> back(nums.begin()+mid+1, nums.end());
            root->right = sortedArrayToBST(back);   
        }
        else root->right = NULL;
        return root;
    }
};

//solution 2
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        //a height balanced BST.   --->   the middle num > root
        return sortedArrayToBST(nums, 0, nums.size()-1);
    }
    TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right){
        if(left > right) return NULL;
        int mid = left + (right-left)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, left, mid-1);
        root->right = sortedArrayToBST(nums, mid+1, right);
        return root;
    }
};





109. Convert Sorted List to Binary Search Tree
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
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
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        //height-balanced binary tree
        //[-10, -3 , 0 , 5 , 9]
        //       ^   ^
        //      pre mid
        if(head == NULL) return NULL;
        ListNode *pre = head, *slow = head, *fast = head;
        while(fast && fast->next){
            pre = slow;         //!!!pre
            slow = slow->next;
            fast = fast->next->next;
        }
        //root slow(middle)
        ListNode* mid = slow;
        TreeNode* root = new TreeNode(mid->val);
        pre->next = NULL;    //!!!pre
        
        //left
        if(head!=mid) root->left =  sortedListToBST(head);  //!!!head!=mid
        //right
        root->right = sortedListToBST(mid->next);
            
        return root;
    }
};


102. Binary Tree Level Order Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root==NULL) return {};
        vector<vector<int>> res;
        vector<int> out;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int t = q.size();
            out.clear();   //!!!
            for(int i=0; i<t; i++){
                TreeNode* node = q.front();
                q.pop();
                out.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            res.push_back(out);
        }
        return res;
    }

};
//Recursive
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > res;
        levelorder(root, 0, res);
        return res;
    }
    void levelorder(TreeNode *root, int level, vector<vector<int> > &res) {
        if (!root) return;
        if (res.size() == level) res.push_back({});
        res[level].push_back(root->val);
        if (root->left) levelorder(root->left, level + 1, res);
        if (root->right) levelorder(root->right, level + 1, res);
    }
};



199. Binary Tree Right Side View
//BFS:
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == NULL) return {};
        
        vector<int> res;
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()){
            int t = q.size();
            for(int i=0; i<t; i++){
                TreeNode* node = q.front();
                q.pop();
                if(i==t-1) res.push_back(node->val);  //the last one of this level
    
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        
        return res;
    }
};
//DFS:
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root == NULL) return {};
        
        vector<int> res;
        dfs(root, 1, res);
        return res;
    }
    
    void dfs(TreeNode* root, int level, vector<int>& res){
        if(root==NULL) return;
        if(res.size()<level) res.push_back(root->val);   //!!!
        dfs(root->right, level+1, res);  //!!!先right再left
        dfs(root->left, level+1, res);
    }
};



116. Populating Next Right Pointers in Each Node
//solution 1: DFS
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        /*
        constant extra space.
        perfect binary tree
        stack space does not count as extra space
        recursive or stack
        */
        if(root==NULL) return;
        if(root->left) root->left->next = root->right;
        if(root->right) root->right->next = root->next ? root->next->left : NULL;
        connect(root->left);
        connect(root->right);
    }

};

//solution 2: BFS
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        queue<TreeLinkNode*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeLinkNode *t = q.front(); q.pop();
                if (i < size - 1) {
                    t->next = q.front();   //堆先进先出FIFO
                }
                else t->next = NULL;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
    }
};
//solution 3: BFS  !!!
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        TreeLinkNode* start = root, *cur = NULL;
        while(start->left){
            cur = start;   //level i
            while(cur){
                cur->left->next = cur->right;
                if(cur->next) cur->right->next = cur->next->left;
                cur = cur->next;
            }
            start = start->left;  //level i+1;
        }
    }
};


117. Populating Next Right Pointers in Each Node II
//solution 2: BFS
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        queue<TreeLinkNode*> q;
        q.push(root);
        while(!q.empty()){
            int len = q.size();
            for(int i=0;i<len;i++){
                TreeLinkNode* node = q.front();
                q.pop();
                if(i<len-1) node->next = q.front();
                else node->next = NULL;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
    }
};
//solution 3: BFS   !!!？？？
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode *h = new TreeLinkNode(0), *t =h;
        while(root){
            if(root->left){
                t->next = root->left;
                t=t->next;
            }
            if(root->right){
                t->next = root->right;
                t=t->next;
            }
            root = root->next;  
            //next level
            if(!root){
                root = h->next;
                h->next = NULL;
                t = h;
            }
        }
    }
};


94. Binary Tree Inorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        //DFS or stack
        //first: DFS
        /*
        if(root==NULL) return {};
        vector<int> res;
        inorder(root, res);
        return res;
        */
        //second: stack
        if(root == NULL) return {};
        stack<TreeNode*> st;
        TreeNode* p = root;
        vector<int> res;
        while(p || !st.empty()){
            while(p){
                st.push(p);
                p=p->left;
            }
            TreeNode* node = st.top();
            st.pop();
            res.push_back(node->val);
            p = node->right;
        }
        return res;
        
    }
    void inorder(TreeNode* root, vector<int>& res){
        if(root==NULL) return;
        inorder(root->left, res);
        res.push_back(root->val);
        inorder(root->right, res);
    }
};


145. Binary Tree Postorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        //DFS, stack
        /*
        //first: DFS
        if(root==NULL) return {};
        vector<int> res;
        postorder(root, res);
        return res;
        */
        //second: stack
        if(!root) return {};
        stack<TreeNode*> st;
        st.push(root);
        vector<int> res;
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            res.insert(res.begin(), node->val); ///!!!insert
            if(node->left) st.push(node->left);   //!!!
            if(node->right) st.push(node->right);
        }
        return res;
    }
    
    void postorder(TreeNode* root, vector<int>& res){
        if(root==NULL) return;
        postorder(root->left, res);
        postorder(root->right, res);
        res.push_back(root->val);
    }
};

144. Binary Tree Preorder Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        //DFS, stack
        /*
        //first: DFS
        if(root==NULL) return {};
        vector<int> res;
        preorder(root, res);
        return res;
        */
        //second: stack
        if(!root) return {};
        stack<TreeNode*> st;
        st.push(root);
        vector<int> res;
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            res.push_back(node->val);       //!!!
            if(node->right) st.push(node->right);   //!!!
            if(node->left) st.push(node->left);
        }
        return res;
    }
    
    void preorder(TreeNode* root, vector<int>& res){
        if(root==NULL) return;
        res.push_back(root->val);
        preorder(root->left, res);
        preorder(root->right, res);
    }
};



103. Binary Tree Zigzag Level Order Traversal
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        //LIFO
        //two stacks
        if(root==NULL) return {};
        vector<vector<int>> res;
        vector<int> out;
        stack<TreeNode*> st1, st2;
        st1.push(root);
        while(!st1.empty() || !st2.empty()){
            while(!st1.empty()){
                TreeNode* node = st1.top();
                st1.pop();
                out.push_back(node->val);
                if(node->left) st2.push(node->left);
                if(node->right) st2.push(node->right);
            }
            if(!out.empty()) res.push_back(out);   //!!!!out.empty()
            out.clear();
            while(!st2.empty()){
                TreeNode* node = st2.top();
                st2.pop();
                out.push_back(node->val);
                if(node->right) st1.push(node->right);   //!!!st2->st1 right first
                if(node->left) st1.push(node->left);
            }
            if(!out.empty()) res.push_back(out);
            out.clear();
        }
        return res;
    }
};


298. Binary Tree Longest Consecutive Sequence
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        //binary tree
        // return the length of the longest consecutive sequence path
        // from parent to child 
        if(!root) return NULL;
        int res = 0;
        helper(root, NULL, res, 0);
        return res;
    }
    void helper(TreeNode* root, TreeNode* p, int& res, int len){
        if(!root) return;
        if(p && p->val+1 == root->val) len++;
        else len = 1;
        res = max(res, len);
        helper(root->left, root, res, len);
        helper(root->right, root, res, len);
    }

};


549. Binary Tree Longest Consecutive Sequence II
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private: int res = 0;
public:
    int longestConsecutive(TreeNode* root) {
        //can be in the child-Parent-child order
        //can be either increasing or decreasing
        if(root == NULL) return 0;
        int res = 1 + helper(root, 1) + helper(root, -1); //!!!
        return max(res, max(longestConsecutive(root->left), longestConsecutive(root->right)));
    }
    
    int helper(TreeNode* root, int diff){
        if(root==NULL) return 0;
        int left = 0, right = 0;
        if(root->left && root->left->val == root->val+diff){
            left = 1 + helper(root->left, diff);
        }
        if(root->right && root->right->val == root->val+diff){
            right = 1 + helper(root->right, diff);
        }
        return max(left, right);
    }
    
};


101 Symmetric Tree 
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        //deque
        //two queue
        /*
        if(root==NULL) return true;
        
        queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);
        
        while(!q1.empty() && !q2.empty()){
            TreeNode* n1 = q1.front(), *n2 = q2.front();
            q1.pop();
            q2.pop();
            if(n1==NULL&&n2!=NULL || n1!=NULL&&n2==NULL) return false;
            if(n1==NULL && n2==NULL) continue;
            
            if(n1->val != n2->val) return false;
            
            q1.push(n1->left);
            q1.push(n1->right);
            
            q2.push(n2->right);
            q2.push(n2->left);
        }
        
        return q1.empty() && q2.empty();
        */
        
        //recursive
        if(root==NULL) return true;
        return same(root->left, root->right);
    }
    bool same(TreeNode* left, TreeNode* right){
        if(left==NULL && right == NULL) return true;
        if(left&&!right || !left&&right) return false;
        return (left->val==right->val) && same(left->right, right->left) && same(left->left, right->right);
    }
};




//solution 2: iteratively
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        //recurslively or iteratively
        //recursively
        if(root==NULL) return true;
        queue<TreeNode*> q1, q2;
        q1.push(root->left);   //!!!
        q2.push(root->right);
        while(!q1.empty() && !q2.empty()){
            TreeNode* left = q1.front();
            q1.pop();
            TreeNode* right = q2.front();
            q2.pop();
            if(!left&&!right) continue;   //!!!
            else if(!left&&right || left&&!right || left->val!=right->val) return false;
            else{
                q1.push(left->left);
                q1.push(left->right);
                q2.push(right->right);   //!!!
                q2.push(right->left);
            }
        }
        return true;
    }
};







100. Same Tree
//递归
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p&&q || p&&!q) return false;
        if(!p&&!q) return true;
        return (p->val==q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};
//非递归
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        stack<TreeNode*> s1, s2;
        if (p) s1.push(p);
        if (q) s2.push(q);
        while (!s1.empty() && !s2.empty()) {
            TreeNode *t1 = s1.top(); s1.pop();
            TreeNode *t2 = s2.top(); s2.pop();
            if (t1->val != t2->val) return false;
            if (t1->left) s1.push(t1->left);
            if (t2->left) s2.push(t2->left);
            if (s1.size() != s2.size()) return false;
            if (t1->right) s1.push(t1->right);
            if (t2->right) s2.push(t2->right);
            if (s1.size() != s2.size()) return false;
        }
        return s1.size() == s2.size();
    }
};

255. Verify Preorder Sequence in Binary Search Tree  
//solution 1: dfs
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.empty()) return true;
        int n = preorder.size();
        return helper(preorder, 0, n-1, INT_MIN, INT_MAX);
    }
    bool helper(vector<int>& preorder, int left, int right, int mn, int mx){
        if(left > right) return true;   //!!!
        if(preorder[left] <= mn || preorder[left] >= mx) return false;
        int i = 0;
        for(i=left+1; i<=right; i++){
            if(preorder[i]>preorder[left]) break;
        }
        return helper(preorder, left+1, i-1, mn, preorder[left]) && helper(preorder, i, right, preorder[left], mx);
    }
};
//solution 2: stack  ？
class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        //solution 3 stack
        int low = INT_MIN;
        stack<int> s;
        for(auto a:preorder){
            if(a<low) return false;
            while(!s.empty() && a>s.top()){
                low = s.top();   //!!!
                s.pop();
            }
            s.push(a);   //!!!
        }
        return true;
    }
};


112. Path Sum
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(root==NULL) return 0;
        if(!root->left && !root->right) return sum == root->val;
        else return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

113. Path Sum II
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if(!root) return {};
        vector<vector<int>> res;
        vector<int> out;
        helper(root, sum, res, out);
        return res;
    }
    void helper(TreeNode* root, int sum, vector<vector<int>>& res, vector<int>& out){
        if(root == NULL) return;
        out.push_back(root->val);
        if(root->val==sum && !root->left && !root->right) res.push_back(out);  //!!!
        
        helper(root->left, sum - root->val, res, out);
        helper(root->right, sum - root->val, res, out);   
        
        out.pop_back();   //!!!
    }
};

437. Path Sum III
//
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if(root==NULL) return 0;
        int res = 0;
        helper(root, sum, res);
        return  res + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
    void helper(TreeNode* root, int sum, int& res){
        if(root==NULL) return;
        if(sum == root->val) res++;
        helper(root->left, sum - root->val, res);
        helper(root->right, sum - root->val, res);
    }
    
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if(!root) return 0;
        return helper(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
    }
    int helper(TreeNode* root, int sum){
        if(!root) return 0;
        int res = 0;
        if(root->val==sum) res++;  //!!!不需要leaf
        
        res += helper(root->left, sum - root->val);
        res += helper(root->right, sum - root->val);   
    
        return res;
    }

};





129. Sum Root to Leaf Numbers
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        return dfs(root, 0);
    }
    int dfs(TreeNode* root, int sum){
        if(!root) return 0;
        sum = sum*10 + root->val;
        if(!root->left && !root->right) return sum;
        return dfs(root->left, sum) + dfs(root->right, sum);
    }
};




110. Balanced Binary Tree
//solution 1: time complexity: O(NlogN)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        int left = dfs(root->left);
        int right = dfs(root->right);
        return  abs(left-right)<=1 && isBalanced(root->left) && isBalanced(root->right);
    }
    int dfs(TreeNode* root){
        if(!root) return 0;
        int res = 1 + max(dfs(root->left), dfs(root->right));
        return res;
    }
};

//solution 2: time complexity: O(N)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        if(dfs(root)==-1) return false;
        return true;
    }
    int dfs(TreeNode* root){
        if(!root) return 0;
        int left = dfs(root->left);
        if(left == -1) return -1;
        int right = dfs(root->right);
        if(right == -1) return -1;
        if(abs(left-right)>1) return -1;
        else return 1+ max(left, right);
    }
};




450. Delete Node in a BST
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==NULL) return NULL;
        if(root->val == key){
            if(!root->left) return root->right;
            else if(!root->right) return root->left;

            TreeNode* node = root->right;
            while(node->left) node= node->left;  //find min
            root->val = node->val;
            root->right = deleteNode(root->right, node->val);  //!!!
            
        }
        else if(key < root->val){
            root->left = deleteNode(root->left, key);
        }
        else{
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
   
};


654. Maximum Binary Tree(max heap???)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if(nums.empty()) return NULL;
        int mx = INT_MIN, mx_idx=0;
        for(int i=0; i<nums.size(); i++){
            if(nums[i] > mx){
                mx = nums[i];
                mx_idx = i;
            }
        }
        TreeNode* root = new TreeNode(mx);
        vector<int> front(nums.begin(), nums.begin()+mx_idx);
        vector<int> back(nums.begin()+mx_idx+1, nums.end());
        root->left = constructMaximumBinaryTree(front);
        root->right = constructMaximumBinaryTree(back);
        return root;
    }
};


404. Sum of Left Leaves
//dfs
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        int res = 0;
        dfs(root, false, res);
        return res;
    }
    void dfs(TreeNode* root, bool left, int& res){
        if(root==NULL) return;
        if(!root->left && !root->right && left) res += root->val;
        if(root->left) dfs(root->left, true, res);
        if(root->right) dfs(root->right, false, res);
    }
};
//dfs2
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root) return 0;
        if (root->left && !root->left->left && !root->left->right) {
            return root->left->val + sumOfLeftLeaves(root->right);
        }
        return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
};
//bfs
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if (!root || (!root->left && !root->right)) return 0;
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *t = q.front(); q.pop();
            if (t->left && !t->left->left && !t->left->right) res += t->left->val;  //!!!
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        return res;
    }
};


572. Subtree of Another Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(t==NULL) return true;
        if(s==NULL) return false;
            
        if(same(s, t)) return true;
        else return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    bool same(TreeNode* s, TreeNode* t){
        if(!t && !s) return true;
        if(!s && t || s && !t) return false;
        return (s->val == t->val) && same(s->left, t->left) && same(s->right, t->right);
    }
    
};


637. Average of Levels in Binary Tree
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        if(!root) return {};
        
        vector<double> res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int t = q.size();
            double sum = 0;
            for(int i=0; i<t; i++){
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            res.push_back(sum/t);
        }
        return res;
    }
};
//dfs
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res, cnt;   //level sum, level count array
        helper(root, 0, cnt, res);  
        for (int i = 0; i < res.size(); ++i) {
            res[i] /= cnt[i];
        }
        return res;
    }
    void helper(TreeNode* node, int level, vector<double>& cnt, vector<double>& res) {
        if (!node) return;
        if (res.size() <= level) {
            res.push_back(0);
            cnt.push_back(0);
        }
        res[level] += node->val;
        ++cnt[level];
        helper(node->left, level + 1, cnt, res);
        helper(node->right, level + 1, cnt, res);
    }
};

865. Smallest Subtree with all the Deepest Nodes
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if(!root) return NULL;
        int left = deepth(root->left);
        int right = deepth(root->right);
        if(left == right) return root;
        else if(left < right) return subtreeWithAllDeepest(root->right);
        else return subtreeWithAllDeepest(root->left);
        
    }
    int deepth(TreeNode* root){
        if(root==NULL) return 0;
        return 1 + max(deepth(root->left), deepth(root->right));
    }
};



99. Recover Binary Search Tree
//solution 1: space complexity: O(N) 
class Solution {
public:
    void recoverTree(TreeNode *root) {
        if(root == NULL) return;
        
        vector<int> vals;
        vector<TreeNode*> nodes;
        
        inorder(root, vals, nodes);
        
        sort(vals.begin(), vals.end());
        for(int i=0; i<vals.size(); i++){
            nodes[i]->val = vals[i];
        }
    }
    
    void inorder(TreeNode* root, vector<int>& vals, vector<TreeNode*>& nodes){
        if(root==NULL) return;
        inorder(root->left, vals, nodes);
        vals.push_back(root->val);
        nodes.push_back(root);
        inorder(root->right, vals, nodes);
        
    }

};


//space complexity: O(h)
class Solution {
private:
    TreeNode* pre;
    TreeNode* first;
    TreeNode* second;
    
public:
    void recoverTree(TreeNode *root) {
        if(root == NULL) return;
        pre = NULL;
        first = NULL;
        second = NULL;
        inorder(root);
        if(first && second) swap(first->val, second->val);
        
    }
    
    void inorder(TreeNode* root){
        if(root==NULL) return;
        inorder(root->left);
        
        if(pre && root->val < pre->val){
            if(!first) first = pre;
            second = root;
        }
        pre = root;
        

        inorder(root->right);
    }

};


//space complexity: O(1) 
//???Morris遍历
// Now O(1) space complexity
class Solution {
public:
    void recoverTree(TreeNode *root) {
        TreeNode *first = NULL, *second = NULL, *parent = NULL;
        TreeNode *cur, *pre;
        cur = root;
        while (cur) {
            if (!cur->left) {
                if (parent && parent->val > cur->val) {
                    if (!first) first = parent;
                    second = cur;
                }
                parent = cur;
                cur = cur->right;
            } else {
                pre = cur->left;
                while (pre->right && pre->right != cur) pre = pre->right;
                if (!pre->right) {
                    pre->right = cur;
                    cur = cur->left;
                } else {
                    pre->right = NULL;
                    if (parent->val > cur->val) {
                        if (!first) first = parent;
                        second = cur;
                    }
                    parent = cur;
                    cur = cur->right;
                }
            }
        }
        if (first && second) swap(first->val, second->val);
    }
};





*********************************************************************************************************************
Greedy
*********************************************************************************************************************
55. Jump Game
//greedy
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0;
        for(int i=0; i<nums.size()&&i<=reach; i++){   //!!!i<=reach
            reach = max(reach, i+nums[i]);
        }
        return reach >= nums.size()-1;
    }
 
};


122. Best Time to Buy and Sell Stock II
// You may complete as many transactions as you like
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //Greedy
        int res = 0;
        for(int i=1; i<prices.size(); i++){
            if(prices[i]>prices[i-1])
                res += prices[i]-prices[i-1];
        }
        return res;
        
    }
};

135
253. Meeting Rooms II
//solutio 1: map, time complexity: O(N) space complexity: O(NlogN)
//can be reduced to O(N)
//[0, 2] [1, 3] [4, 5]
//0(1) 1(1) 2(-1) 3(-1) 4(1) 5(-1)
//----> 2: max_size
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        map<int, int> m;
        for(auto itv:intervals){
            m[itv.start]++;
            m[itv.end]--;
        }
        int res = 0;
        int cur = 0;
        for(auto a:m){
            cur+=a.second;
            res = max(res, cur);
        }
        return res;
    }
   
};


//reduced to O(N)
class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        int mx = 0, mn = INT_MAX;
        for(auto itv:intervals){
            mx = max(mx, itv.end);
            mn = min(mn, itv.start);
        }
        
        vector<int> v(mx+1, 0);
        for(auto a:intervals){
            v[a.start]++;
            v[a.end]--;
        }
        
        int res = 0, cur = 0;
        for(int i=mn; i<=mx; i++){
            cur += v[i];
            res = max(res, cur);
        }
        return res;
    }
   
};







//solution 2: min_heap(save end time) + sort + greedy. time complexity: O(NlogN)
class Solution {
public:
    static bool cmp(Interval itv1, Interval itv2){
        return itv1.start<itv2.start;
    }
    int minMeetingRooms(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        priority_queue<int, vector<int>, greater<int>> q; //min_heap to save end time of meeting
        
        for(auto itv:intervals){
            if(!q.empty() && itv.start >= q.top()) q.pop();  //pop the meeting end firstly  !!!是>= !!!判断q不空
            q.push(itv.end);   //push the end time of current Interval
            
        }
        
        return q.size();
    
    }
   
};

class Solution {
public:

    int minMeetingRooms(vector<Interval>& intervals) {
        //solution 1 map<time, count>
        //solution 2 sort + heap<end>
        
        /*
        //solution 1 time----O(N)  space----O(N)
        map<int, int> m;  //map<time, +1/-1>
        for(auto itv:intervals){
            m[itv.start]++;
            m[itv.end]--;
        }
        int res = 0;
        int cur = 0;
        for(auto a:m){
            cur += a.second;
            res = max(res, cur);
        }
        return res;
        */
        
        //solution 2 time---O(NlogN) space---O(N)
        sort(intervals.begin(), intervals.end(), [](Interval itv1, Interval itv2){ return itv1.start< itv2.start;}); //sort
        priority_queue<int, vector<int>, greater<int>> ends;  //min_heap
        
        for(auto itv:intervals){
            if(!ends.empty() && itv.start >= ends.top()) {ends.pop(); ends.push(itv.end);}
            else ends.push(itv.end);
        }
        
        return ends.size();
    }
   
};



392. Is Subsequence
//solution 1: two pointers + greedy, time complexity: O(T)
class Solution {
public:
    bool isSubsequence(string s, string t) {
        //check if s is subsequence of t.
        int index1 = 0, index2 = 0;
        while(index1<s.size() && index2<t.size()){
            if(s[index1] == t[index2]){
                index1++;
                index2++;
            }
            else{
                index2++;
            }
        }
        return index1==s.size();
    }
    

};

//solution 2: binary search, time complexity: O(T + S*logC) C is the Count of char. 
//follow up假如有很多个S，这种方法比较好。因为T只需要遍历一次， 之后只需要遍历S。！！！
class Solution {
public:
    bool isSubsequence(string s, string t) {
        //check if s is subsequence of t.
        unordered_map<char, vector<int>> m;  //list of index
        for(int i=0; i<t.size(); i++) m[t[i]].push_back(i);
        int pre = -1;
        for(char c:s){
            if(!m.count(c)) return false;
            vector<int> v = m[c];
            int pos = binary_search(pre, v);   //the first one > pre 
            if(pos>=v.size()) return false;
            pre = v[pos];
        }
        return true;
    }
    int binary_search(int target, vector<int>& v){
        int left = 0, right = v.size()-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(v[mid] <= target) left = mid+1;
            else right = mid-1;
        }
        return left;
    }
    
};



621. Task Scheduler
//solution 1: greedy
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // at least n intervals between 2 same tasks
        //return the least num of intervals
        //record the count of tasks
        unordered_map<char, int> m;
        int len = tasks.size();
        int mx = 0;
        for(auto task:tasks) {
            m[task]++; 
            mx = max(mx, m[task]);
        }
        int res = (mx-1)*(n+1);
        for(auto a:m){
            if(a.second == mx) res++;
        }
        //partCount * partLen + mx_count
        return max(len, res);
          
    }
};


//solution 2: 
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int res = 0, cycle = n + 1;
        unordered_map<char, int> m;
        priority_queue<int> q;
        for (char c : tasks) ++m[c];
        for (auto a : m) q.push(a.second);
        while (!q.empty()) {
            int cnt = 0;
            vector<int> t;
            for (int i = 0; i < cycle; ++i) {
                if (!q.empty()) {
                    t.push_back(q.top()); q.pop();
                    ++cnt;
                }
            }
            for (int d : t) {
                if (--d > 0) q.push(d);
            }
            res += q.empty() ? cnt : cycle;
        }
        return res;
    }
};
714
767


*****************************************************************************************************************  
linked List
*****************************************************************************************************************
141. Linked List Cycle
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head, *fast = head;
        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
            if(slow==fast) return true;
        }
        return false;
    }
};

143. Reorder List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        
        if(!head) return;
        // 1 -> 2 -> 3 -> 4
        //     slow
        ListNode *slow=head, *fast=head;
        while(fast->next && fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
        } 
        ListNode* head2 = reverse(slow->next);
        slow->next = NULL;
        /*
        head1   1->2
        head2  3->4
        */
        ListNode* head1 = head;
        while(head1 && head2){
            ListNode* t1 = head1->next;
            ListNode* t2 = head2->next;
            head1->next = head2;
            head2->next = t1;
            head1 = t1;
            head2 = t2;
        }
        
    }
    
    ListNode* reverse(ListNode* head){
        ListNode* q = NULL;
        ListNode* p = head;
        while(p){
            ListNode* t = p->next;
            p->next = q;
            q = p;
            p = t;
        }
        return q;
    }

};

206. Reverse Linked List
//ListNode 不要写成 TreeNode
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //1->2->3->4->5
        //q <- 1  ->     2    -> 3
        //q  head   head->next
        //NULL<-  1  ->   2
        //        q     head
        //1->2->3->4->5
        //            q<-head
        ListNode* q = NULL;
        while(head){
            ListNode* p = head->next;
            head->next = q;
            q = head;
            head = p;
        }
        return q;
    }
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        //1->2->3->4->5
        //q <- 1  ->     2    -> 3
        //q  head   head->next
        //NULL<-  1  ->   2
        //        q     head
        //1->2->3->4->5
        //            q<-head
        //递归
        if(!head || !head->next) return head;
        ListNode* p = head;
        head = reverseList(p->next);
        p->next->next = p;
        p->next = NULL;
        return head;
    }
};


//递归 recursion

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !(head -> next)) {
            return head;
        }
        ListNode* node = reverseList(head -> next);
        head -> next -> next = head;
        head -> next = NULL;
        cout<<node->val<<endl;
        return node;
    }
};






92. Reverse Linked List II
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        //1-> 2 -> 3 -> 4 -> 5 -> NULL, m = 2, n = 4
        //pre node      q    p
        ListNode* new_head = new ListNode(-1);
        new_head -> next = head;
        ListNode* pre = new_head, *node = head;
        int i=1;
        while(i<m){pre = pre->next; node = node->next; i++;}
        
        ListNode* q = NULL;
        ListNode* p = node;
        for(int i=m ;i<=n; i++){
            ListNode* t = p->next;
            p->next = q;
            q = p;
            p = t;
        }
        pre -> next = q;
        node -> next = p;
        return new_head->next;
    }
};



21. Merge Two Sorted Lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* p = head;
        while(l1 && l2){
            if(l1->val <= l2->val){
                p->next = l1;
                l1=l1->next;
            }
            else{
                p->next = l2;
                l2=l2->next;
            }
            p=p->next;
        }
        if(l1) p->next = l1;
        else if(l2) p->next = l2;
        return head->next;
    }
};
//
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode(-1);
        ListNode* p = head;
        while(l1&&l2){
            if(l1->val <= l2->val) {p->next = l1;l1 = l1->next;}
            else {p->next = l2; l2 = l2->next;}
            p=p->next;
        }
        if(l1) p->next = l1;
        if(l2) p->next = l2;
        return head->next;
    }
};

 
23. Merge k Sorted Lists
//time complexity: O(nk Log k), T(K) = 2T(k/2) + O(NK)   ＝ O(NKlogK)
/*
We already know that merging of two linked lists can be done in O(n) time and O(1) space (For arrays O(n) space is required). 
The idea is to pair up K lists and merge each pair in linear time using O(1) space. After first cycle, K/2 lists are left each of size 2*N. 
After second cycle, K/4 lists are left each of size 4*N and so on. We repeat the procedure until we have only one list left.
*/
//divide and conquer
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return NULL;
        int n = lists.size();
        int k = 0;
        while(n>1){    //!!!n>1
            k = (n+1)/2;   //!!!
            for(int i=0; i<n/2; i++){
                lists[i] = mergeTwoLists(lists[i], lists[i+k]);   //!!!
            }
            n = k;   //!!!
        }
        return lists[0];
    }
    
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        ListNode* head = new ListNode(-1);
        ListNode* p = head;
        while(l1&&l2){
            if(l2->val < l1->val){
                p->next = l2;
                l2 = l2->next;   //!!!
            }
            else{
                p->next = l1;
                l1 = l1->next;
            }
            p = p->next;
        }
        if(l1) p->next = l1;
        else if(l2) p->next = l2;
        return head->next;
    } 
};

//min_heap
//time complexity: O(nk Log k)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct cmp{
    bool operator() (ListNode* l1, ListNode* l2){
        return l1->val > l2->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return NULL;
        //merge k sorted ...----> min_heap
        priority_queue<ListNode*, vector<ListNode*>, cmp> q;
        //push k head into min_heap
        for(auto list:lists){
            if(list) q.push(list);  //!!!if(list)
        }
        ListNode* head = new ListNode(-1);
        ListNode* p = head;   //!!!p
        while(!q.empty()){
            ListNode* tmp = q.top();
            q.pop();
            p->next = tmp;
            if(tmp->next) q.push(tmp->next);
            p = p->next;
        }
        return head->next;
    }
};



24. Swap Nodes in Pairs
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        //Your algorithm should use only constant extra space.
        //You may not modify the values in the list's nodes, only nodes itself may be changed.
        ListNode* newHead = new ListNode(-1);
        newHead->next = head;
        
        ListNode* p = newHead;
        while(p->next && p->next->next){  //!!!
            ListNode* t = p->next->next;
            p->next->next = t->next;
            t->next = p->next;
            p->next = t;
            p = p->next->next;
        }
        
        return newHead->next;
    }
};



160. Intersection of Two Linked Lists
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        ListNode* a = headA;
        ListNode* b = headB;
        while(a!=b){
            a = a==NULL?headB:a->next;
            b = b==NULL?headA:b->next;
        }
        return a;
    }
};



19. Remove Nth Node From End of List
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* p1 = head, *p2 = head;
        for(int i=0; i<n; i++){
            p1 = p1->next;
        }
        if(!p1) return head->next;
        while(p1->next){
            p1 = p1->next;
            p2 = p2->next;
        }
        p2->next = p2->next->next;
        return head;
    }
};


234. Palindrome Linked List
//time complexity: O(N), space complexity: O(1)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head) return true;
        //O(n) time and O(1) space
        //1->  2->   2 -> 1
        //    pre  slow
        ListNode *slow=head, *fast=head;
        while(fast->next&&fast->next->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* head2 = reverse(slow->next);
        slow->next = NULL;
        
        while(head&&head2){
            if(head->val != head2->val) return false;
            head = head->next;
            head2 = head2->next;
        }
        return true;
    }
    
    ListNode* reverse(ListNode* node){
        ListNode* q = NULL;
        while(node){
            ListNode* t = node->next;
            node->next = q;
            q = node;
            node = t;
        }
        return q;
    }
};

708. Insert into a Cyclic Sorted List
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if(head == NULL){   //!!!
            Node* a = new Node(insertVal, NULL);
            a->next = a;
            return a;
        }
        Node* pre = head, *node = head->next;
        while(true){
            if(insertVal>=pre->val && insertVal<=node->val||  //!!!
              node->val<pre->val && insertVal<node->val||
              node->val<pre->val && insertVal>pre->val){
                pre->next = new Node(insertVal, node);
                return head;
            }
            pre = pre->next;
            node = node->next;
            if(pre == head) break;    //!!!
        }
        pre -> next = new Node(insertVal, node);   //!!!
        return head;
    }
};

//
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if(head == NULL){
            head = new Node(insertVal);
            //head->val = insertVal;
            head->next = head;
            return head;
        }
        
        Node* p = head;
        while(true){
            if(p->next->val >= insertVal &&  p->val <= insertVal ||   //1 (2) 3;  4 (5) 1;  4 (1) 3
               p->next->val < p->val &&  insertVal > p->val ||
               p->next->val < p->val &&  insertVal < p->next->val){
                Node* tmp = p->next;
                p->next = new Node(insertVal, tmp);
                return head;
            }
            p = p->next;
            if(p == head) break; //!!! 3 3 3(0)这种情况插哪里都可以
        }
        Node* tmp = p->next;
        p -> next = new Node(insertVal, tmp);  //!!! 3 3 3(0)这种情况插哪里都可以
        return head;
    
    }
};


430. Flatten a Multilevel Doubly Linked List
/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    Node* prev = NULL;
    Node* next = NULL;
    Node* child = NULL;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    Node* flatten(Node* head) {
        if(head == NULL) return NULL;
        Node* p = head;
        while(p){
            if(!p->child){
                p = p->next;
                continue;
            }
            Node* tmp = p->next;
            Node* c = p->child;
            while(c->next) c= c->next;
            c->next = tmp;
            if(tmp) tmp->prev = c;
            p->next = p->child;
            p->child->prev = p;
            p->child = NULL;  //!!!
            //p = p->next;
        }
        return head;
    }
};

//
/*
// Definition for a Node.
class Node {
public:
    int val = NULL;
    Node* prev = NULL;
    Node* next = NULL;
    Node* child = NULL;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};
*/
class Solution {
public:
    Node* flatten(Node* head) {
        Node* p = head;
        while(p){
            if(p->child){
                Node* tmp = p->next;
                p->next = p->child;
                p->next->prev = p;   //!!!
                p->child = NULL;   //!!!
                
                Node* q = p;   //!!!
                while(q->next){
                    q = q->next;
                }
                q->next = tmp;   
                if(tmp) tmp->prev = q;  //!!!if(tmp)
            }
            
            p= p->next;
            
        }
        
        return  head;
    }
};
***************************************************************************************************************
sort
***************************************************************************************************************
252. Meeting Rooms
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    static bool cmp(Interval itv1, Interval itv2){
        return itv1.start < itv2.start;
    }
    bool canAttendMeetings(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp);
        for(int i=1; i<intervals.size(); i++){
            if(intervals[i].start < intervals[i-1].end) 
                return false;
        }
        
        return true;
        
    }

};

//another solution
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) {
        vector<int> starts, ends;
        for(auto itv:intervals){
            starts.push_back(itv.start);
            ends.push_back(itv.end);
        } 
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        for(int i=1; i<ends.size(); i++){
            if(starts[i] < ends[i-1])
                return false;
        }
        return true;
    }

};




******************************************************************************************************************
Array
******************************************************************************************************************
128. Longest Consecutive Sequence
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        int res = 0;
        for(int num:nums){
            if(s.count(num)) s.erase(num);
            int pre = num-1, tail = num+1;
            while(s.count(pre)) s.erase(pre--);
            while(s.count(tail)) s.erase(tail++);
            res = max(res, tail-pre-1);
        }
        return res;
    }
};



31  Next Permutation
//time complexity: O(N), space complexity:O(1)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //下一个字典序排列
        int n =  nums.size();
        for(int i = n-1; i >= 1; i--){
            if(nums[i-1] < nums[i]){
                for(int j = n-1; j>=i; j--){
                    if(nums[j] > nums[i-1]){
                        swap(nums[j], nums[i-1]);
                        reverse(nums.begin()+i, nums.end());
                        return;
                    }
                        
                }
            }
        }
        reverse(nums.begin(), nums.end());
        
    }
};


556. Next Greater Element III
class Solution {
public:
    int nextGreaterElement(int n) {
        string s = to_string(n);
        int i=0;
        for(i=s.size()-1; i>0; i--){
            if(s[i]>s[i-1]){
                for(int j=s.size()-1; j>=i; j--) {
                    if(s[j]>s[i-1]) { 
                        swap(s[i-1], s[j]); 
                        reverse(s.begin()+i, s.end()); 
                        break;
                    }   
                }
                long long res = stoll(s);
                return res>INT_MAX?-1:res;
            }
        }
        return -1;
    }
};


56. Merge Intervals
//sort and then merge
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
    
public:
    static bool cmp(Interval itv1, Interval itv2){
        return itv1.start < itv2.start;
    }
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.empty()) return {};
        vector<Interval> res;
        //sort intervals as start increase
        sort(intervals.begin(), intervals.end(), cmp);
        res.push_back(intervals[0]);
        //go through and merge duplicate between every two intervals
        for(int i=1; i<intervals.size(); i++){
            if(intervals[i].start <= res.back().end)
                res.back().end = max(res.back().end, intervals[i].end);
            else res.push_back(intervals[i]);
        }
        return res;
    }
};


//solution 2
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
    
public:
    
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.empty()) return {};
        vector<int> starts, ends;
        for(auto itv:intervals){
            starts.push_back(itv.start);
            ends.push_back(itv.end);
        }
        
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        
        vector<Interval> res;
        int j = 0;
        for(int i=0; i<ends.size(); i++){
            if(i==ends.size()-1 || starts[i+1]>ends[i]){
                res.push_back( Interval(starts[j], ends[i]) );
                j = i+1;
            }
        }
        return res;
    }
};




57. Insert Interval
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
//insert+merge

class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> res;
        int i=0;
        //find first overlap
        while(i<intervals.size()){
            if(intervals[i].end < newInterval.start) res.push_back(intervals[i++]);
            else break;
        }
        //deal with and merge overlap
        while(i<intervals.size() && intervals[i].start <= newInterval.end){
            newInterval.start = min(intervals[i].start, newInterval.start);
            newInterval.end = max(intervals[i].end, newInterval.end);
            i++;
        }
        //deal with left intervals
        res.push_back(newInterval);
        
        while(i<intervals.size()){
            res.push_back(intervals[i++]);
        }
        
        return res;
        
    }
};



277. Find the Celebrity
//time complexity: O(N)
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        //a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.
        //no --> return -1
        //find out or verify there is not one by ask as few questions as possible
        int res = 0;
        for(int i=0; i<n; i++){
            if(knows(res, i)) res = i;
        }
        for(int i=0; i<n; i++){
            if(i!=res && (knows(res, i) ||!knows(i, res))) return -1;
        }
        
        return res;
    }
};



// time complexity:O(N^2)
bool knows(int a, int b);

class Solution {
public:
    int findCelebrity(int n) {
        //a celebrity is that all the other n - 1 people know him/her but he/she does not know any of them.
        //no --> return -1
        //find out or verify there is not one by ask as few questions as possible
        for(int i=0; i<n; i++){
            int j;
            for(j=0; j<n; j++){
                if(j!=i && (knows(i, j) || !knows(j, i)))
                    break;
            }
            if(j==n) return i;
        }
        
        return -1;
        
        
    }
};



238. Product of Array Except Self
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
        //Please solve it without division and in O(n).
        //Follow up: Could you solve it with constant space complexity?
        
        //first idea: product of all nums and then go through the array and divide self
        //time complexity: O(N) space: O(1)
        
        //second idea: go ahead save the intermedia product to vector(left prodect)
        //then go back cal the right product(right product)
        // the answer = left product * right product 
        int n = nums.size();
        vector<int> back_product(n, 1);
        int pro = 1;
        for(int i=n-1; i>=0; i--){
            back_product[i] = pro;
            pro *= nums[i];
        }
        
        vector<int> res(n, 0);
        int front_product = 1;
        for(int i=0; i<n; i++){
            res[i] = front_product * back_product[i];
            front_product *= nums[i];
        }
        return res;
    }
};




73. Set Matrix Zeroes
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        /*
        notes: in-place, no extra space
        
        idea/plan: col_zero/row_zero shows first col/row is 0 or not, first/row shows other places is 0 or not.
        1. go through first col & first row to see if it should be "0", if true set col_zero/row_zero = 1;
        2. go through other places except first col&row, if matrix[i][j] is "0". set matrix[i][0]&matrix[0][j] = 0
        3. go through other places except first col&row, if(matrix[i][0]||matrix[0][j] = 0) we set matrix[i][j]=0
        4. according to col_zero&row_zero, set first col&row
        
        time & space complexity:
        time: O(N+N) = O(N) space: col_zero&row_zero O(1)
        
        example:
        [1,0,1]       col_zero=0 row_zero=0
        [0,0,0]       
        [1,0,1]
        
        corner cases:
        matrix is empty or matrix[0] is empty
        */
        
        if(matrix.empty() || matrix[0].empty()) return;
        int row = matrix.size(), col = matrix[0].size();
        int col_zero = 0, row_zero = 0;
        
        for(int c=0; c<col; c++) if(matrix[0][c]==0) row_zero = 1;
        for(int r=0; r<row; r++) if(matrix[r][0]==0) col_zero = 1;
        
        for(int i=1; i<row; i++){
            for(int j=1; j<col ;j++){
                if(matrix[i][j]==0) matrix[0][j] = matrix[i][0] = 0;
            }
        }
        
        for(int i=1; i<row; i++){
            for(int j=1; j<col; j++){
                if(matrix[0][j]==0 || matrix[i][0]==0) matrix[i][j] = 0;
            }
        }
        
        if(row_zero) for(int c=0; c<col; c++) matrix[0][c] = 0;
        if(col_zero) for(int r=0; r<row; r++) matrix[r][0] = 0;
        
    }
};


54. Spiral Matrix
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return {};
        int row = matrix.size();
        int col = matrix[0].size();
        vector<int> res;
        int up = 0, down = row-1, left = 0, right = col-1;
        while(true){   //while(condition) condition改变时，while不会马上检查，会等运行下一次循环再检查
            //left->right
            for(int i=left; i<=right; i++) res.push_back(matrix[up][i]);
            if(++up>down) break;   //!!!
            //up->down
            for(int i=up; i<=down; i++) res.push_back(matrix[i][right]);
            if(--right<left) break;  //!!!
            //right->left
            for(int i=right; i>=left; i--) res.push_back(matrix[down][i]);
            if(--down<up) break;   //!!!
            //down->up
            for(int i=down; i>=up; i--) res.push_back(matrix[i][left]);
            if(++left>right) break;   /!!!
        }
        return res;
    }
};


498. Diagonal Traverse
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return {};
        int row = matrix.size();
        int col = matrix[0].size();
        
        vector<int> res(row*col);
        vector<vector<int>> dirs = {{-1, 1}, {1, -1}}; //!!!
        int r=0, c=0, k=0;
        for(int i=0; i<row*col; i++){
            res[i] = matrix[r][c];
            r += dirs[k][0];
            c += dirs[k][1];
            if(r>=row){r = row-1; c = c+2; k = 1-k;}
            if(c>=col){c = col-1; r = r+2; k = 1-k;}  //!!!顺序很重要
            if(r<0){r = 0; k = 1-k;}
            if(c<0){c = 0; k = 1-k;}
        }
        return res;
        
    }
};




825. Friends Of Appropriate Ages
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        //brute force O(N^2)
        //sort + binary search O(NlogN)
        //O(N)?
        vector<int> counts(120+1, 0);
        for(auto age:ages) counts[age]++;
        
        int res = 0;
        for(int i=1; i<=120; i++){
            for(int j=0.5*ages[i]+7+1; j<=i; j++){
                res += counts[i]*(counts[j]-(i==j));
            }
        }
        
        return res;
        /*
        time complexity: O(N + 120*120) = O(N)
        space complexity: O(1)
        */
    }
};

189. Rotate Array  ???
//solution 1
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.empty() || (k %= nums.size()) == 0) return;
        int n = nums.size();
        reverse(nums.begin(), nums.begin() + n - k);
        reverse(nums.begin() + n - k, nums.end());
        reverse(nums.begin(), nums.end());
    }
};
//solution 2???
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if (nums.empty() || (k %= nums.size()) == 0) return;
        int n = nums.size(), start = 0, i = 0, cur = nums[i], cnt = 0;
        while (cnt++ < n) {
            i = (i + k) % n;
            int t = nums[i];
            nums[i] = cur;
            if (i == start) {
                ++start; ++i;
                cur = nums[i];
            } else {
                cur = t;
            }
        }
    }
};



48. Rotate Image
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        //n*n matrix, rotate clockwise 90 degrees
        // in place
        int n = matrix.size();
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                swap(matrix[i][j], matrix[j][i]);
            }
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};


280. Wiggle Sort
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i=2; i<nums.size(); i+=2){
            swap(nums[i], nums[i-1]);
        }
    }
};

324. Wiggle Sort II
//solution 1: time complexity: O(NlogN), space complexity: O(N)
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int len = nums.size();
        vector<int> tmp=nums;
        sort(tmp.begin(),tmp.end());
        int k=(len+1)/2, j=len;
        for(int i=0;i<len;i++){
            nums[i] = i&1?tmp[--j]:tmp[--k];
        }
        
    }
};

//solution 2: time complexity:O(N) space complexity: O(1)???
// O(1) space
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        #define A(i) nums[(1 + 2 * i) % (n | 1)]
        int n = nums.size(), i = 0, j = 0, k = n - 1;
        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        int mid = *midptr;
        while (j <= k) {
            if (A(j) > mid) swap(A(i++), A(j++));
            else if (A(j) < mid) swap(A(j), A(k--));
            else ++j;
        }
    }
};


414. Third Maximum Number
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        //The time complexity must be in O(n).
        long mx1 = LONG_MIN, mx2 = LONG_MIN, mx3 = LONG_MIN;   //!!!
        for(auto num:nums){
            if(num > mx1) {mx3 = mx2; mx2 = mx1; mx1 = num; }  //!!!
            else if(num < mx1 && num > mx2) {mx3 = mx2; mx2 = num; }
            else if(num < mx2 && num > mx3) {mx3 = num;}
        }
        return mx3==LONG_MIN?mx1:mx3;
    }
};




724. Find Pivot Index
class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int res = -1;
        int sum = 0;
        for(int num:nums) sum+=num;
        
        int cur = 0;
        for(int i=0; i<nums.size(); i++){
            cur += nums[i];
            if(cur - nums[i]== sum - cur) return i;
        }
        return res;
    }
};



442. Find All Duplicates in an Array
class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        //without extra space and in O(n) runtime
        if(nums.empty()) return {};
        vector<int> res;
        for(int i=0; i<nums.size(); i++){
            if(nums[i] != nums[nums[i]-1]) {swap(nums[i], nums[nums[i]-1]); i--;}
        }
        for(int i=0; i<nums.size(); i++){
            if(nums[i] != i+1) res.push_back(nums[i]);
        }
        return res;
    }
};

***********************************************************************************************************************
graph
***********************************************************************************************************************
133. Clone Graph
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;
        //map(node, cloneNode)
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
        UndirectedGraphNode* cloneNode = new UndirectedGraphNode(node->label);
        m[node] = cloneNode;
        
        //BFS
        queue<UndirectedGraphNode*> q;
        q.push(node);
        while(!q.empty()){
            UndirectedGraphNode* n = q.front();
            q.pop();
            //clone neighbors of n
            for(auto nb:n->neighbors){
                if(!m.count(nb)){
                    m[nb] = new UndirectedGraphNode(nb->label);
                    q.push(nb);
                }
                m[n]->neighbors.push_back(m[nb]);
            }
        }
        
        return cloneNode;
    }
};


785. Is Graph Bipartite?
//coloring
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        //every edge in the graph has one node in A and another node in B
        vector<int> colors(graph.size(), 0);
        for(int i=0; i<graph.size(); i++){
            if(colors[i]==0 && !valid(1, i, graph, colors)) //!!
                return false;
        }
        return true;
    }
    bool valid(int color, int index, vector<vector<int>>& graph, vector<int>& colors){
        //node was colored
        if(colors[index]!=0) return colors[index] == color;   //!!!
        //check the neighbors
        colors[index] = color;
        for(auto nb:graph[index]){
            if(!valid(-1*color, nb, graph, colors)) return false;  //!!!
        }
        return true;
    }
    
    
};



886. Possible Bipartition
//coloring
class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        if(dislikes.empty()) return true;
        //coloring graph
        //people->node dislike->edge
        vector<vector<int>> graph(N);
        //construct graph   //!!!
        for(auto a:dislikes){
            //a: [1, 2]
            graph[a[0]-1].push_back(a[1]-1);  //!!!"-1"别忘了
            graph[a[1]-1].push_back(a[0]-1);
        }
        //coloring
        vector<int> colors(N, 0);
        for(int i=0; i<graph.size(); i++){
            if(colors[i]==0 && !valid(1, i, graph, colors))
                return false;
        }
        return true;
    }
    bool valid(int color, int index, vector<vector<int>>& graph, vector<int>& colors){
        if(colors[index]!=0) return colors[index]==color;
        colors[index] = color;
        for(auto nb:graph[index]){
            if(!valid(-1*color, nb, graph, colors)) return false;
        }
        return true;
    }
};



323. Number of Connected Components in an Undirected Graph
///solution 1: dfs
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        //dfs or union find
        vector<vector<int>> graph(n);   //!!!初始化
        vector<bool> visited(n, false); //!!!初始化
        for(auto a:edges){
            graph[a.first].push_back(a.second);
            graph[a.second].push_back(a.first);
        }
        int res = 0;
        for(int i=0; i<n; i++){
            if(!visited[i]){
                res++;
                dfs(graph, visited, i);
            }
        }
        return res;
    }
    void dfs(vector<vector<int>>& graph, vector<bool>& visited, int i){
        if(visited[i]) return;
        visited[i] = true;
        for(auto a:graph[i]){
            dfs(graph, visited, a);   
        }
    }
};



//solution 2: union find
class Solution {
public:
    int countComponents(int n, vector<pair<int, int>>& edges) {
        //dfs or union find
        int res = n;
        vector<int> root(n);
        for(int i=0; i<n; i++) root[i] = i;
        for(auto a:edges){
            int p = findroot(a.first, root);
            int q = findroot(a.second, root);
            if(p!=q){
                root[q] = p;
                res--;
            }
        }
        return res;
    }
    int findroot(int x, vector<int>& root){
        return root[x]==x?x:findroot(root[x], root);
    }
 
};



207. Course Schedule
//directed graph + topological sort
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        //topological sort --> check if it is a directed graph contain no circle
        //firstly. constrct directed graph; secondly, push nodes(with 0 ins) into queue,
        vector<vector<int>> graph(numCourses, vector<int>(0));
        vector<int> in(numCourses, 0);
        for(auto a:prerequisites){
            graph[a.second].push_back(a.first);
            in[a.first]++;
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++){
            if(in[i]==0) q.push(i);
        }
        //after queue is empty, check if all nodes are with 0 ins
        while(!q.empty()){
            int t=q.front();
            q.pop();
            for(auto a:graph[t]){
                in[a]--;
                if(in[a]==0) q.push(a);
            }
            
        }
        for(int i=0; i<numCourses; i++){
            if(in[i]!=0)
                return false;
        }
        return true;
    }
};


210. Course Schedule II
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        //topological sort
        vector<vector<int>> graph(numCourses, vector<int>(0));
        vector<int> in(numCourses, 0);
        for(auto a:prerequisites){
            graph[a.second].push_back(a.first);   //!!!
            in[a.first]++;
        }
        queue<int> q;
        for(int i=0; i<numCourses; i++){
            if(in[i]==0) q.push(i);   //!!!
        }
        vector<int> res;
        while(!q.empty()){
            int t = q.front();
            q.pop();
            res.push_back(t);
            for(auto a:graph[t]){
                in[a]--;
                if(in[a]==0) q.push(a);  //!!!
            }
        }
        if(res.size()!=numCourses) res.clear(); //!!!
        return res;
    }
};

//
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        //topological sort
        //find circle in direct graph
        //firstly, constract direct graph
        
        vector<vector<int>> graph(numCourses);
        vector<int> ins(numCourses, 0);
        for(auto a:prerequisites){
            graph[a.second].push_back(a.first);
            ins[a.first]++;
        }
        
        //secondly, topological sort
        queue<int> q;
        for(int i=0; i<ins.size(); i++){
            if(ins[i]==0)
                q.push(i);
        }
        
        vector<int> res;
        while(!q.empty()){
            int t = q.front();
            q.pop();
            res.push_back(t);
            for(auto a:graph[t]){
                ins[a]--;
                if(ins[a]==0) q.push(a);
            }
        }
        
        if(res.size()==numCourses) return res;
        else return {};
        
    }
};

332. Reconstruct Itinerary
class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        //有向图边的遍历
        unordered_map<string, multiset<string>> m;  //!!!
        for(auto ticket:tickets){
            m[ticket.first].insert(ticket.second);
        }
        vector<string> res;
        dfs("JFK", m, res);
        return vector<string>(res.rbegin(), res.rend());  //!!!
    }
    void dfs(string s, unordered_map<string, multiset<string>>& m, vector<string>& res){
        while(m[s].size()){
            string t = *m[s].begin();   //!!!
            m[s].erase(m[s].begin());
            dfs(t, m, res);
        }
        res.push_back(s);
    }
};



261. Graph Valid Tree
//solution 1: bfs
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        //无环 连通
        //dfs bfs union find
        vector<unordered_set<int>> graph(n);
        for(auto edge:edges){
            graph[edge.first].insert(edge.second);
            graph[edge.second].insert(edge.first);    
        }
        
        unordered_set<int> s({0});
        queue<int> q({0});
        while(!q.empty()){
            int t = q.front();
            q.pop();
            for(auto a:graph[t]){
                if(s.count(a)) return false;
                s.insert(a);
                q.push(a);
                graph[a].erase(t);
            }
        }
        return s.size()==n;
    }
    
};

//solution 2: union find
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        //无环 连通
        //dfs bfs union find
        vector<int> roots(n, -1);
        for(auto edge:edges){
            int x = find_root(edge.first, roots);
            int y = find_root(edge.second, roots);
            if(x==y) return false;
            roots[x] = y;
        }
        return edges.size()==n-1;
    }
    int find_root(int i, vector<int>& roots){
        while(roots[i]!=-1) i= roots[i];
        return i;
    }
    
};

//solution 3: dfs
// DFS
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        vector<vector<int>> g(n, vector<int>());
        vector<bool> v(n, false);  //visited
        for (auto a : edges) {
            g[a.first].push_back(a.second);
            g[a.second].push_back(a.first);
        }
        if (!dfs(g, v, 0, -1)) return false;
        for (auto a : v) {
            if (!a) return false;   // a is not connected
        }
        return true;
    }
    bool dfs(vector<vector<int>> &g, vector<bool> &v, int cur, int pre) {
        if (v[cur]) return false;  //conatin circle
        v[cur] = true;
        for (auto a : g[cur]) {
            if (a != pre) {
                if (!dfs(g, v, a, cur)) return false;
            }
        }
        return true;
    }
};






399. Evaluate Division




269. Alien Dictionary  //不要吝啬用{}
class Solution {
public:
    string alienOrder(vector<string>& words) {
        //topological sort of directed grpah
        //first: build graph
        vector<int> in(256, 0);
        
        unordered_set<char> ch;
        for(auto word:words) ch.insert(word.begin(), word.end());
        
        set<pair<char, char>> pairs;
        for(int i=0; i<words.size()-1; i++){
            int j = 0, mn = min(words[i].size(), words[i+1].size());
            for(; j < mn; j++){
                if(words[i][j] != words[i+1][j]){ pairs.insert({words[i][j], words[i+1][j]}); break; }
            }
            if(j==mn && words[i].size() > words[i+1].size()) return "";
        }
        
        for(auto a:pairs){
            in[a.second] ++;
        }
        
        //second: topological sort
        string res = "";
        queue<char> q;
        for(auto c:ch){
            if(in[c]==0) q.push(c);
        }
        //cout<<q.front() <<endl;
        while(!q.empty()){
            char t = q.front();
            q.pop();
            res += t;
            //cout<< res <<endl;
            for(auto a:pairs){
                if(a.first == t){
                    in[a.second]--;
                    if(in[a.second]==0) q.push(a.second);
                } 
            }
        }
        
        return res.size()==ch.size()?res:"";
    }
};




******************************************************************************************************************
string
******************************************************************************************************************
157. Read N Characters Given Read4
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read!!!
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        if(n==0) return 0;
        int res = 0;
        for(int i=0; i<=n/4; i++){
            int cur = read4(buf+res);
            if(cur==0) break;
            res += cur;
        }
        return min(res, n);
    }
};

//
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read!!!
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        if(n==0) return 0;
        int N = n;
        int res = 0;
        while(n>0){
            int cur = read4(buf+res); //!!!
            if(cur==0) break;
            res += cur;
            n -= cur;
        }
        return min(N, res);
    }
};

158. Read N Characters Given Read4 II - Call multiple times  ???
// Forward declaration of the read4 API.
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
private:
    int ptr=0, cur=0;
    char buf4[4];
public:
    int read(char *buf, int n) {
        for(int i=0; i<n ;i++){
            if(ptr==cur){
                cur = read4(buf4);
                ptr = 0;
                if(cur == 0) return i;
            }
            buf[i] = buf4[ptr++];
        }
        return n;
    }

};
//按行read
// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
private:
    int ptr = 0, cur = 0;
    char buf4[4];
public:
    int read(char *buf) {
        int i =0;
        while(true) {
            if (ptr == cur) {
                cur = read4(buf4);
                ptr = 0;
                if (cur == 0) break;
            }
            buf[i] = buf4[ptr++];
            if(buf[i] == '\n') break;
            i++;
        }
        return i;
    }
};






161. One Edit Distance
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int n1 = s.size(), n2 = t.size();
        //go through the short string
        for(int i=0; i<min(n1, n2); i++){
            if(s[i] != t[i]){
                if(s.size() > t.size()) {s.erase(s.begin()+i); return s == t;}
                else if(t.size() > s.size()) {t.erase(t.begin()+i); return s == t;}
                else return s.substr(i+1) == t.substr(i+1);
            }
        }
        //前面的全部匹配
        // two situations left: 
        //ab abc  ---> return true   
        //ab ab   ---> return false; 
        if(abs(n1 - n2) == 1) return true;
        else return false;
    }
};

38. Count and Say
//iterate
class Solution {
public:
    string countAndSay(int n) {
        string res = "1";
        while(--n){
            string cur = "";
            char c = res[0];
            int count = 0, i=0;
            while(i<res.size()){
                while(res[i]==c) {count++; i++;}
                cur += to_string(count) + c;
                c = res[i];
                count = 0;
            }
            res = cur;
        }
        return res;
    }
    
};


791. Custom Sort String
//solution 1: sort. time complexity: O(S+TlogT)
class Solution {
public:
    string customSortString(string S, string T) {
        // T sort -> order of S
        unordered_map<char, int> m;
        for(int i=0; i<S.size(); i++) m[S[i]]=i;  //map<char, index>
        sort(T.begin(), T.end(), [&](char a, char b){return m[a]<m[b];});  //[&] capture all variables within scope by reference
        return T;
    }
};
// solution 2: using hash table. time complexity: O(S+T)
class Solution {
public:
    string customSortString(string S, string T) {
        // T sort -> order of S
        string res = "";
        unordered_map<char, int> m;
        for(char c:T) m[c]++;
        
        for(char c:S){
            res += string(m[c], c);   //string(count, char)
            m.erase(c);
        }
        for(auto a:m){
            res += string(a.second, a.first);
        }
        return res;
    }
};

468. Validate IP Address
class Solution {
public:
    string validIPAddress(string IP) {
        string res = "Neither";
        istringstream is(IP);
        string t = "";
        int cnt = 0;
        if(IP.find(":") == string::npos){  //IPV4
            while(getline(is, t, '.')){
                cnt++;
                if(cnt>4 || t.empty() || t.size()>4 || t.size()>1&&t[0]=='0') return "Neither";
                for(char c:t){
                    if(c<'0' || c>'9') return "Neither";
                }
                int val = stoi(t);
                if(val>255) return "Neither";
            }
            return (cnt==4 && IP.back()!='.')?"IPv4":"Neither";
        }
        else{                              //IPV6
            
            while(getline(is, t, ':')){
                cnt++;
                if(cnt>8 || t.empty() || t.size()>4) return "Neither";
                for(char c:t){
                    if(!(c>='0'&&c<='9') &&!(c>='a'&&c<='f') &&!(c>='A'&&c<='F')) return "Neither";
                }
            }
            return (cnt==8 && IP.back()!=':')?"IPv6":"Neither";
        }
    }
};

824. Goat Latin
class Solution {
public:
    string toGoatLatin(string S) {
        istringstream ss(S);
        string str, res;
        int i=1;
        while(ss>>str){
            if(str[0]=='a'||str[0]=='e'||str[0]=='i'||str[0]=='o'||str[0]=='u'||str[0]=='A'||str[0]=='E'||str[0]=='I'||str[0]=='O'||str[0]=='U') str+="ma";
            else str = str.substr(1)+str[0]+"ma";
            for(int j=1;j<=i;j++) str=str+'a';
            res += str+" ";
            i++;
        }
        return res.substr(0, res.size()-1);
    }
};
//
class Solution {
public:
    string toGoatLatin(string S) {
        string res = "";
        istringstream is(S);
        string str;
        int i=1;
        while(is>>str){
            if(str[0]!='a' && str[0]!='e' && str[0]!='i' && str[0]!='o' && str[0]!='u' && str[0]!='A' && str[0]!='E' && str[0]!='I' && str[0]!='O' && str[0]!='U') str = str.substr(1)+str[0]; 
            str += "ma" + string(i, 'a');
            res += str + " ";
            i++;
        }
        res.pop_back();
        return res;
    }
};


14. Longest Common Prefix
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        string res = "";
        
        for(int j=0; j<strs[0].size(); j++){
            char c = strs[0][j];
            
            for(int i=1; i<strs.size(); i++){
                if(j>=strs[i].size() || strs[i][j]!=c)
                    return res;
            }

            res.push_back(c);
        }
        
        return res;
        
    }
};


844. Backspace String Compare
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        string s = parse(S);
        string t = parse(T);
        return s==t;
    }
    string parse(string str){
        string res = "";
        for(char c:str){
            if(c=='#') {
                if(!res.empty()) res.pop_back();
            }
            else res.push_back(c);
        }
        return res;
    }
};


681. Next Closest Time
class Solution {
public:
    string nextClosestTime(string time) {
        string res = time;
        set<int> s{time[0], time[1], time[3], time[4]};
        string str(s.begin(), s.end());
        for(int i=time.size()-1; i>=0; i--){
            if(res[i]==':') continue;
            int pos = str.find(res[i]);
            if(pos == str.size()-1){
                res[i] = str[0];
            }
            else{
                char next = str[pos+1];
                if(i==4){
                    res[i] = next;
                    return res;
                }
                else if(i==3 && next<='5'){
                    res[i] = next;
                    return res;
                }
                else if(i==1 && (res[i-1]!='2'||res[i-1]=='2'&&next<='3')){
                    res[i] = next;
                    return res;
                }
                else if(i==0 && next<='2'){
                    res[i] = next;
                    return res;
                }
                res[i] = str[0];
            }
        }
        return res;
    }
};


443. String Compression
class Solution {
public:
    int compress(vector<char>& chars) {
        
        //in-place.
        //return the new length 
        int index = 0;
        int cnt = 1;
        for(int i=0; i<chars.size(); i++){
            char c = chars[i];
            while(i+1<chars.size() && chars[i+1]==c){
                i++;
                cnt++;
            }
            chars[index++] = c;  //!!!
            
            if(cnt==1) continue;   //!!!
            string s = to_string(cnt);
            for(auto a:s){
                chars[index++] = a;
            }
            cnt = 1;    //!!!
        }
        return index;
    }
};



722. Remove Comments
class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> res;
        string s = "";
        bool  comment = false;
        for(int i=0; i<source.size(); i++){
            for(int j=0; j<source[i].size(); j++){
                if(!comment && source[i].substr(j, 2) == "//"){
                    break;
                } 
                else if(!comment && source[i].substr(j, 2) == "/*"){
                    comment = true;
                    j++ ;
                }
                else if(comment && source[i].substr(j, 2) == "*/"){
                    comment = false;
                    j++;
                }
                else if(!comment) s.push_back(source[i][j]);
            }
            if(!comment && s.size()) res.push_back(s), s.clear();
        }
        return res;
    }
};


165. Compare Version Numbers
//solution 1
class Solution {
public:
    int compareVersion(string version1, string version2) {
        istringstream s1(version1+"."), s2(version2+".");
        int t1, t2;
        char dot;
        while(s1.good() || s2.good()){
            if(s1.good()) s1>>t1>>dot;
            if(s2.good()) s2>>t2>>dot;
            if(t1 < t2) return -1;
            else if (t1 > t2) return 1;
            t1 = t2 = 0;
        }
        return 0;
    }
};
//solution 2
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int n1 = version1.size(), n2 = version2.size();
        int i=0, j=0;
        int num1 = 0, num2 = 0;
        while(i<n1 || j<n2){
            while(i<n1 && version1[i]!='.'){
                num1 = num1*10 + version1[i++]-'0';
            }
            i++;
            while(j<n2 && version2[j]!='.'){
                num2 = num2*10 + version2[j++]-'0';
            }
            j++;
            if(num1<num2) return -1;
            else if(num1>num2) return 1;
            num1 = num2 = 0;
        }
        return 0;
    }
};


686. Repeated String Match
class Solution {
public:
    int repeatedStringMatch(string A, string B) {
        //input: 2 string(A, B)
        //output: how many times
        if(B=="") return 0;
        if(A=="") return -1;
        int n1 = A.size(), n2 = B.size();
        string t = A;
        int cnt = 1;
        while(A.size() < n2){
            A += t;
            cnt++;
        }
        if(A.find(B) != string::npos) return cnt;
        A += t;
        if(A.find(B)!=string::npos) return cnt+1;
        else return -1;
        
    }
};


893. Groups of Special-Equivalent Strings
class Solution {
public:
    int numSpecialEquivGroups(vector<string>& A) {
        if(A.empty()) return 0;
        
        unordered_set<string> s;
        for(string str:A){
            string even, odd;
            for(int i=0; i<str.size(); i++){
                if(i%2) even += str[i];
                else odd += str[i];
            }
            sort(even.begin(), even.end());
            sort(odd.begin(), odd.end());
            s.insert(even+odd);
        }
        return s.size();
    }
    

};


***************************************************************************************************************************
Sudoku
***************************************************************************************************************************
36. Valid Sudoku
//brute force
class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
       //hash table
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j] != '.'){
                    if(!is_ok(board, i, j)) return false;
                    else continue;
                }
            }
        }
        
        return true;
    }
    
    
    bool is_ok(vector<vector<char>>& board, int row, int col){
        char val = board[row][col];
        //check row
        for(int r=0; r<9; r++){
            if(r!=row && board[r][col] == val)
                return false;
        }
        //check col
        for(int c=0; c<9; c++){
            if(c!=col && board[row][c] == val)
                return false;
        }
        //check small box
        for(int r=row/3*3; r<row/3*3+3; r++){
            for(int c = col/3*3; c<col/3*3+3; c++){
                if((r!=row || c!=col) && board[r][c] == val)
                    return false;
            }
        }
        return true;
    }
};
//用空间换时间
class Solution {
public:
    bool isValidSudoku(vector<vector<char> > &board) {
       //hash table
        int used1[9][9]={0}, used2[9][9]={0}, used3[9][9] = {0};
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j] != '.'){
                    int num = board[i][j] -'0'-1, k = i/3*3+j/3;
                    if(used1[i][num] || used2[j][num] || used3[k][num])
                        return false;
                    else used1[i][num] = used2[j][num] = used3[k][num] = 1;
                }
            }
        }
        
        return true;
    }
    

};

37. Sudoku Solver
//brute force
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        //save empty positions
        vector<pair<int, int>> pos;
        for(int i=0; i<9; i++){
            for(int j=0; j<9; j++){
                if(board[i][j] == '.')
                    pos.push_back({i, j});
            }
        }
        //check 1-9 for every position recursively
        dfs(board, pos, 0);
        //0 is the index of positions
    }
    bool dfs(vector<vector<char>>& board, vector<pair<int, int>>& pos, int index){
        if(index==pos.size()) return true;
        
        for(int val=1; val<=9; val++){
            board[pos[index].first][pos[index].second] = '0' + val;
            if(is_ok(board, pos, index, val)) if(dfs(board, pos, index+1)) return true;
            board[pos[index].first][pos[index].second] = '.';//!!!
        }
        
        return false;
    }
    
    bool is_ok(vector<vector<char>>& board, vector<pair<int, int>>& pos, int index, int val){
        int row = pos[index].first, col = pos[index].second;
        //check row
        for(int r = 0; r<9; r++){
            if(r!=row && board[r][col] == '0' + val)
                return false;
        }
        //check col
        for(int c = 0; c<9; c++){
            if(c!=col && board[row][c] == '0'+val)
                return false;
        }
        //check small box
        for(int r = row/3*3; r<row/3*3+3; r++){
            for(int c = col/3*3; c<col/3*3+3; c++){
                if((board[r][c] == '0'+val) && (c!=col || r!=row))
                    return false;
            }
        }
        
        return true;
    }
    
};


**********************************************************************************************************************
hash table
**********************************************************************************************************************
217. Contains Duplicate
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        //input: array
        //output: contain duplicates?
        //empty? return false;
        //0. brute force time----O(N^2)
        //1. hash table<num, count> / Set, if count>1 return true, time----O(N) space-----O(N)  
        //2. sort. if negihbors same return true, time----O(NlogN) space---O(1)
        
        if(nums.empty()) return false;
        
        unordered_map<int, int> m;
        for(int num:nums){
            m[num]++;
            if(m[num]>1) return true;
        }
        
        return false;
        
    }
};

219. Contains Duplicate II
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        for(int i=0; i<nums.size(); i++){
            if(m.count(nums[i]) && i-m[nums[i]]<=k) return true;
            m[nums[i]] = i;
        }
        return false;
    }
};


383. Ransom Note
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        //is_substr(ransomNote, magazine)
        //the order does matter
        vector<int> v(26, 0);
        for(char c:magazine) v[c-'a']++;
        for(char c:ransomNote){
            v[c-'a']--;
            if(v[c-'a']<0) return false;
        } 
        return true;
    }
};


387. First Unique Character in a String
//space complexity: O(N)
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> m;
        for(char c:s){
            m[c]++;
        }
        
        for(int i=0; i<s.size(); i++){
            if(m[s[i]] == 1) return i;
        }
        return -1;
    }
};

//space complexity: O(1)
class Solution {
public:
    int firstUniqChar(string s) {
        //only lowercase leeters
        if(s.empty()) return -1;
        
        vector<int> counts(26, 0);
        for(char c:s) counts[c-'a']++;
        
        for(int i=0; i<s.size(); i++){
            if(counts[s[i]-'a']==1) return i;
        }
        
        return -1;
    }
};


140. Word Break II
//DFS
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> m;
        return helper(s, wordDict, m);
    }
    
    vector<string> helper(string s, vector<string>& wordDict, unordered_map<string, vector<string>>& m){
        if(m.count(s)) return m[s];
        if(s.empty()) return {""};  //!!!
        vector<string> res;
        for(auto word:wordDict){
            if(s.substr(0, word.size()) != word) continue;
            vector<string> tmp = helper(s.substr(word.size()), wordDict, m);
            for(auto str:tmp){
                res.push_back(word + (str.empty()?"":" ") + str);
            }
        }
        m[s] = res;
        return res;
        
    }
};
133. Clone Graph
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;
        //map(node, cloneNode)
        unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> m;
        UndirectedGraphNode* cloneNode = new UndirectedGraphNode(node->label);
        m[node] = cloneNode;
        
        //BFS
        queue<UndirectedGraphNode*> q;
        q.push(node);
        while(!q.empty()){
            UndirectedGraphNode* n = q.front();
            q.pop();
            //clone neighbors of n
            for(auto nb:n->neighbors){
                if(!m.count(nb)){
                    m[nb] = new UndirectedGraphNode(nb->label);
                    q.push(nb);
                }
                m[n]->neighbors.push_back(m[nb]);
            }
        }
        
        return cloneNode;
    }
};

138. Copy List with Random Pointer
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> m;
        RandomListNode* cloneHead = new RandomListNode(head->label);
        m[head] = cloneHead;
        RandomListNode* p = head;
        RandomListNode* q = cloneHead;
        //map every element of list
        while(p->next){
            RandomListNode* node = new RandomListNode(p->next->label);
            m[p->next] = node;
            q->next = node;
            p = p->next;
            q = q->next;
        }
        p = head;
        q = cloneHead;
        while(p){
            q->random = m[p->random];
            q = q->next;
            p = p->next;
        }
        
        return cloneHead;
    }
};

//another solution
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head==NULL) return NULL;
        
        unordered_map<RandomListNode*, RandomListNode*> m;
        RandomListNode* cloneHead = new RandomListNode(head->label);
        m[head] = cloneHead;
        
        RandomListNode* p = head;
        RandomListNode* q = cloneHead;
        while(p->next){
            RandomListNode* node = new RandomListNode(p->next->label);
            m[p->next] = node;
            q->next = node;
            p = p->next;
            q = q->next;
        }
        
        p = head;
        while(p){
            m[p]->random = m[p->random];
            p = p->next;
        }
        return cloneHead;
    }
};


//  !!!??? 空间复杂度优化
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (!head) return NULL;
        RandomListNode *cur = head;
        while (cur) {
            RandomListNode *node = new RandomListNode(cur->label);
            node->next = cur->next;
            cur->next = node;
            cur = node->next;
        }
        cur = head;
        while (cur) {
            if (cur->random) {
                cur->next->random = cur->random->next;
            }
            cur = cur->next->next;
        }
        cur = head;
        RandomListNode *res = head->next;
        while (cur) {
            RandomListNode *tmp = cur->next;
            cur->next = tmp->next;
            if(tmp->next) tmp->next = tmp->next->next;
            cur = cur->next;
        }
        return res;
    }
};

349. Intersection of Two Arrays
//3 solutions
//hash table
//sort + two pointers
//sort + binary search
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        //output nums1 intersection nums2
        //1. fist idea: hash table(save nums1 to map, then check nums2 with map)
        //time complexity: O(N1+N2),  space complexity: O(N1)
        /*****************
        set<int> s(nums1.begin(), nums1.end());
        set<int> res;
        for(int j=0; j<nums2.size(); j++){
            if(s.count(nums2[j]))
                res.insert(nums2[j]);
        }
        return vector<int>(res.begin(), res.end());
        *******************/
        //2. second idea: sort 2 arrays + two pointers 
        //time complexity: O(N1logN1 + N1logN2),  space complexity: O(1)
        /******************
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int idx1 = 0, idx2 = 0;
        vector<int> res;
        while(idx1<nums1.size() && idx2<nums2.size()){
            if(nums1[idx1] == nums2[idx2]){
                if(res.empty() || nums1[idx1] != res.back()) res.push_back(nums1[idx1]);   //!!!
                idx1++;   //!!!相等的时候index不要忘了++ --
                idx2++;
            }
            else if(nums1[idx1] < nums2[idx2])
                idx1++;
            else idx2++;
        }
        return res;
        ********************/
        //3. third idea: sort 1 array + binary search
        //time complexity: O(N1logN1 + N2logN1) = O((N1+N2)*logN1), space complexity: O(1)
        //we can choose the shorter array to sort
        set<int> res;
        sort(nums2.begin(), nums2.end());
        for(int num:nums1){
            if(binary_search(num, nums2))
                res.insert(num);
        }
        return vector<int>(res.begin(), res.end());
    }
    bool binary_search(int target, vector<int> v){
        int left = 0, right = v.size()-1;
        while(left <= right){
            int mid = left + (right-left)/2;
            if(v[mid] == target) return true;
            else if(v[mid] < target) left = mid + 1;
            else right = mid -1;
        }
        return false;
    }
};

350. Intersection of Two Arrays II
//intersection can contain duplicate num
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //1. hash map--->save count
        /*****************
        unordered_map<int, int> m;
        for(int num:nums1){
            m[num]++;
        }
        vector<int> res;
        for(int num:nums2){
            if(m[num] > 0){
                res.push_back(num);
                m[num]--;
            }
        }
        return res;
        ****************/
        //2. sort + two pointers
        /*****************
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int idx1 = 0, idx2 = 0;
        vector<int> res;
        while(idx1<nums1.size() && idx2<nums2.size()){
            if(nums1[idx1] == nums2[idx2]){
                res.push_back(nums1[idx1]);
                idx1++;
                idx2++;
            }
            else if(nums1[idx1] < nums2[idx2])
                idx1++;
            else
                idx2++;
        }
        return res;
        ****************/
        //3. sort + binary search
        sort(nums2.begin(), nums2.end());
        vector<int> res;
        for(int num:nums1){
            int t = binary_search(num, nums2);
            if(t!=-1) {
                res.push_back(num);
                nums2.erase(nums2.begin() + t);
            }
            else continue;
        }
        return res;
    }
    int binary_search(int target, vector<int> v){
        int left = 0, right = v.size()-1;
        while(left<=right){
            int mid = left + (right - left)/2;
            if(v[mid] == target) return mid;
            else if(v[mid] < target) left = mid+1;
            else right = mid-1;
        }
        return -1;
    }
};

438. Find All Anagrams in a String
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        //input:
        //return all the start indices of p's anagrams in s
        // lowercase English letters only 
        
        //first idea: go throught s and compare every substr of s with p
        //time complexity: O(N1*N2), space complexity: O(1)
        
        //second idea: hash table
        // push p->vector1.
        // push first substr of s -> vector2
        //go through s and update vector2
        //compare vector1 with vector2
        //time complexity: O(N1*N2) 
        vector<int> res, v1(26, 0), v2(26, 0);
        for(int i=0; i<p.size(); i++){
            v1[p[i]-'a']++;
            v2[s[i]-'a']++;
        }
        if(v1 == v2) res.push_back(0);
        for(int i=p.size(); i<s.size(); i++){
            v2[s[i]-'a']++;
            v2[s[i-p.size()]-'a']--;
            if(v1 == v2) res.push_back(i-p.size()+1);  //!!!i-p.size()+1
        }
        return res;
    }
   
};
//two pointers
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> m;
        for(char c:p) m[c]++;
        
        vector<int> res;
        int left = 0, cnt = 0;
        for(int right=0; right<s.size(); right++){
            if(--m[s[right]]>=0) cnt++;
            while(cnt==p.size()){
                if(right-left+1==p.size()) res.push_back(left);
                if(++m[s[left++]]>0) cnt--;
            }
        }
        return res;
    }
   
};


49. Group Anagrams
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for(string s:strs){
            string t = s;
            sort(t.begin(), t.end());  //!!!
            m[t].push_back(s);
        }
        
        vector<vector<string>> res;
        for(auto a:m){
            res.push_back(a.second);
        }
        return res;
    }
};

242. Valid Anagram
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size()) return false;   //!!!
        vector<int> v(26, 0);
        for(char c:s) v[c-'a']++;
        for(char c:t){
            v[c-'a']--;
            if(v[c-'a'] < 0) return false;  
        }
        return true;
    }
};



554. Brick Wall
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        if(wall.empty() || wall[0].empty()) return 0;
        
        unordered_map<int, int> breaks;
        for(int i=0; i<wall.size(); i++){
            int sum = 0;
            for(int j=0; j<wall[i].size()-1; j++){   //!!! j<wall[i].size()-1 不然最后一排会被算进去，最后答案肯定是0
                sum += wall[i][j];
                breaks[sum]++;
            }
        }
        int mx = 0;
        for(auto a:breaks){
            mx = max(mx, a.second);
        }
        return wall.size() - mx;
    }
};


290. Word Pattern
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char, string> m;
        istringstream is(str);
        string word;
        int i = 0;
        while(is>>word){
            if(m.count(pattern[i])){
                if(word != m[pattern[i]]) return false;  //!!!
            }
            else{
                for(auto a:m){
                    if(a.second == word) return false;  //!!!
                }
            }
            m[pattern[i++]] = word;
        }
        return i==pattern.size();   //!!!
        
    }
};



274. H-Index
class Solution {
public:
    int hIndex(vector<int>& citations) {
        //solution 1: sort, time complecity O(NlogN), spce complexity: O(1)
        /*
        if(citations.empty()) return 0;
        sort(citations.begin(), citations.end(), greater<int>()); //decreasing
        int res  = 0;
        for(int i=0; i<citations.size(); i++){
            if(citations[i] >= i+1) res = i+1;
            else break;
        }
        return res;
        */
        //solution 2: map, time complexity: O(N), space complexity: O(N)
        unordered_map<int, int> m;
        int n = citations.size();
        for(auto a:citations){
            if(a<n) m[a]++;
            else m[n]++;
        }
        int papers = 0;
        for(int i=n; i>=0; i--){
            papers += m[i];
            if(papers>=i) return i;
        }
        return 0;
    }
};




275. H-Index II
class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        //O(logN)
        int n = citations.size();
        int left = 0, right = n-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(citations[mid] == n-mid) return citations[mid];
            else if(citations[mid] > (n-mid)) right = mid-1;
            else left = mid+1;
        }
        return n-left;
    }
};


447. Number of Boomerangs
class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int res = 0;
        for(int i=0; i<points.size(); i++){
            unordered_map<int, int> m;
            for(int j=0; j<points.size(); j++){
                int a = points[j].first - points[i].first;
                int b = points[j].second - points[i].second;
                m[a*a + b*b]++;
            }
            for(auto a:m){
                res += a.second*(a.second-1);
            }
        }
        return res;
    }
};


896. Monotonic Array
class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        if(A.empty()||A.size()<=2) return true;
        bool inc = false, dec = false;
        for(int i=0; i<A.size()-1; i++){
            if(A[i+1]>A[i]) inc = true;
            if(A[i+1]<A[i]) dec = true;
            if(inc&&dec) return false;
        }
        return true;
    }
};


535. Encode and Decode TinyURL
class Solution {
private:
    unordered_map<string, string> long2short, short2long;
    string dict = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        if(long2short.count(longUrl)) return "http://tinyurl.com/" + long2short[longUrl];
        string randstr;
        for(int i=0; i<6; i++) randstr.push_back(dict[rand()%62]);
        int idx = 0;
        while(short2long.count(randstr)){
            randstr[idx] = dict[rand()%62];
            idx = (idx+1)%6;
        }
        short2long[randstr] = longUrl;
        long2short[longUrl] = randstr;
        return "http://tinyurl.com/" + randstr;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        string randstr = shortUrl.substr(shortUrl.find_last_of("/")+1);
        return short2long.count(randstr)?short2long[randstr]:shortUrl;
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));


336. Palindrome Pairs
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        if(words.empty()) return {};
        
        vector<vector<int>> res;
        
        //brute force: O(N^2 * k)
        //O(N*k*k) solution
        unordered_map<string, int> m; // map<word, index>
        for(int i=0; i<words.size(); i++){
            m[words[i]] = i;
        }
        
        for(int i=0; i<words.size(); i++){
            for(int j=0; j<=words[i].size(); j++){
                if(j>0 && is_palindrome(words[i], 0, j-1) ){
                    string back = words[i].substr(j);
                    reverse(back.begin(), back.end());
                    if(m.count(back) && m[back]!=i) res.push_back({m[back], i});
                }
                if( is_palindrome(words[i], j, words[i].size()-1) ){
                    string front = words[i].substr(0, j);
                    reverse(front.begin(), front.end());
                    if(m.count(front) && m[front]!=i) res.push_back({i, m[front]});
                }
                
            }
        }
        return res;
        
    }
    
    bool is_palindrome(string word, int left, int right){
        while(left < right){
            if(word[left++] != word[right--]) return false;
        }
        return true;
    }
};



**********************************************************************************************************
Nested Linked list
***********************************************************************************************************
339. Nested List Weight Sum
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int res = 0;
        for(auto a:nestedList){
            res += getSum(a, 1);
        }
        return res;
    }
    int getSum(NestedInteger ni, int level){
        if(ni.isInteger()) return ni.getInteger()*level;
        else{
            int res = 0;
            for(auto a:ni.getList()){
                res += getSum(a, level+1);
            }
            return res;
        }
    }

};


341. Flatten Nested List Iterator
//solution 1: using recursion
class NestedIterator {
private:
    vector<int> list;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        flatten(nestedList);
    }

    int next() {
        int t = list.front();
        list.erase(list.begin());
        return t;
    }

    bool hasNext() {
        if(list.empty()) return false;
        else return true;
    }
    
    void flatten(vector<NestedInteger> &nestedList){
        for(auto ni:nestedList){
            if(ni.isInteger())
                list.push_back(ni.getInteger());
            else{
                flatten(ni.getList());
            }
        }
    }
};
//solution 2: using iteration + stack
class NestedIterator {
private:
    stack<NestedInteger> st;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        for(int i = nestedList.size()-1; i>=0; i--){
            st.push(nestedList[i]);
        }
    }

    int next() {
        int t = st.top().getInteger();
        st.pop();
        return t;
    }

    bool hasNext() {
        while(!st.empty()){
            NestedInteger t = st.top();
            if(t.isInteger()) return true;
            st.pop();
            if(!t.isInteger()){
                for(int i = t.getList().size()-1; i>=0; i--){
                    st.push(t.getList()[i]);
                }
            }
        }
        return false;
    }
};


364. Nested List Weight Sum II
class Solution {
public:
    int depthSumInverse(vector<NestedInteger>& nestedList) {
        vector<int> v; //!!! record the sum of every level
        int res = 0;
        for(auto a:nestedList){
            helper(a, v, 0);
        }
        for(int i=0; i<v.size(); i++){
            res += v[i] * (v.size()-i);
        }
        return res;
    }
    void helper(NestedInteger ni, vector<int>& v, int level){
        if(level >= v.size()) v.resize(level+1);
        if(ni.isInteger()) v[level] += ni.getInteger();
        else{
            for(auto a:ni.getList())
                helper(a, v, level+1);
        }
    }
};

********************************************************************************************************************************************
design
********************************************************************************************************************************************
348. Design Tic-Tac-Toe
//marks in a horizontal, vertical, or diagonal row wins the game
//n*n grid
class TicTacToe {
private:
    vector<int> rows, cols;
    int diag, rev_diag, N;
public:
    /** Initialize your data structure here. */
    TicTacToe(int n): rows(n), cols(n), diag(0), rev_diag(0), N(n){}
    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        int t = player==1?1:-1;
        rows[row] += t;
        cols[col] += t;
        if(row == col) diag += t;
        if(row + col == N-1) rev_diag += t;
        if(abs(rows[row]) == N || abs(cols[col]) == N || abs(diag) == N || abs(rev_diag) == N) return player;
        else return 0;
    }
    
    
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe obj = new TicTacToe(n);
 * int param_1 = obj.move(row,col,player);
 */
346. Moving Average from Data Stream
//first in first out ---> queue
class MovingAverage {
private:
    queue<int> q;
    int win_size;
    double sum;
public:
    MovingAverage(int size) {
        win_size = size;
        sum = 0;
    }
    
    double next(int val) {
        if(q.size()>=win_size){
            sum -= q.front();
            q.pop();
        }
        sum += val;
        q.push(val);
        return sum/q.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */

//


class MovingAverage {
private:
    queue<int> win;
    int max_size; 
    double sum = 0;
public:
    MovingAverage(int size) {
        //win.resize(size);
        max_size = size;
    }
    
    double next(int val) {
        if(win.size() == max_size){
            sum-=win.front();
            win.pop();
        }
        win.push(val);
        sum+=val;
        return sum/win.size();
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */


251. Flatten 2D Vector
class Vector2D {
private:
    vector<vector<int>>::iterator it, end;
    int y=0;
public:
    Vector2D(vector<vector<int>>& vec2d) {
        it = vec2d.begin();
        end = vec2d.end();
    }

    int next() {
        return  (*it)[y++];
    }

    bool hasNext() {
        while(it!=end && y == (*it).size()){  //[[1], []]
            it++;
            y=0;
        }
        return it!=end;
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */


380. Insert Delete GetRandom O(1)
class RandomizedSet {
//insert remove getrandom all in average O(1) time.
private:
    vector<int> v;
    unordered_map<int, int> m;
    
public:
    /** Initialize your data structure here. */
    RandomizedSet() {  
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(m.count(val)) return false;
        v.push_back(val);
        m[val] = v.size()-1;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {    //交换vector最后一个元素和当前要删除的元素
        if(m.count(val)){
            v[m[val]] = v.back();
            m[v.back()] = m[val];
            v.pop_back();
            m.erase(val);
            return true;
        }
        else return false;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return v[rand()%v.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet obj = new RandomizedSet();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */

384. Shuffle an Array
class Solution {
private:
    vector<int> v;
public:
    Solution(vector<int> nums) {
        v = nums;
    }
    
    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return v;
    }
    
    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> res=v;
        for(int i=0; i<res.size(); i++){
            int t = i + rand()%(res.size()-i);
            swap(res[i], res[t]);
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * vector<int> param_1 = obj.reset();
 * vector<int> param_2 = obj.shuffle();
 */

170. Two Sum III - Data structure design
class TwoSum {
private:
    unordered_map<int, int> m;

public:
    /** Initialize your data structure here. */
    TwoSum() {
    }
    
    /** Add the number to an internal data structure.. */
    void add(int number) {
        m[number]++;
    }
    
    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value) {
        for(auto a:m){
            if(m.count(value - a.first)&&value - a.first!=a.first || value - a.first==a.first&&m[a.first]>1) return true;
        }
        return false;
    }
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum obj = new TwoSum();
 * obj.add(number);
 * bool param_2 = obj.find(value);
 */


284. Peeking Iterator
//solution 1:
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        
        
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        return Iterator(*this).next();
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        return Iterator::next();
    }

    bool hasNext() const {
        return Iterator::hasNext();
    }
};

//solution 2:
// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
private:
    int value;
    int peeked;
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        peeked=false;
        
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if(!peeked){
            value = Iterator::next();
            peeked = true;
        }
        return value;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if(!peeked){
            value = Iterator::next();
        }
        peeked = false;
        return value;
    }

    bool hasNext() const {
        if(peeked || Iterator::hasNext()) return true;
        return false;
    }
};


281. Zigzag Iterator
//solution 1
class ZigzagIterator {
private:
    vector<int> v;
    int k;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        int n1 = v1.size(), n2 = v2.size(), n = max(n1, n2);
        for(int i=0; i<n; i++){
            if(i<n1) v.push_back(v1[i]);
            if(i<n2) v.push_back(v2[i]);
        }
        k = 0;
    }

    int next() {
        return v[k++];
    }

    bool hasNext() {
        return k<v.size();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

//solution 2
class ZigzagIterator {
private:
    vector<vector<int>> v;
    int i, j;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        v.push_back(v1);
        v.push_back(v2);
        i=j=0;
    }

    int next() {
        return i<=j?v[0][i++]:v[1][j++];
    }

    bool hasNext() {
        if(i>=v[0].size()) i=INT_MAX;
        if(j>=v[1].size()) j=INT_MAX;
        return i<v[0].size()||j<v[1].size();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */

622. Design Circular Queue
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int tail;
    bool empty;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
        head = 0;
        tail = 0;
        empty = true;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if(isFull()) return false;
        if(tail == head && empty) empty = false;
        data[tail] = value;
        tail = (tail+1)%data.size();
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if(isEmpty()) return false;
        head = (head+1)%data.size();
        if(tail == head && !empty) empty=true;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if(isEmpty()) return -1;
        return data[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if(isEmpty()) return -1;
        return data[(tail+data.size()-1) % data.size()];
        
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        if(head == tail && empty) return true;
        return false;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        if(head == tail && !empty) return true;
        return false;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * bool param_1 = obj.enQueue(value);
 * bool param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * bool param_5 = obj.isEmpty();
 * bool param_6 = obj.isFull();
 */


146. LRU Cache
class LRUCache {
private:
    list<pair<int, int>> l;
    unordered_map<int, list<pair<int, int>>::iterator> m;
    int cap;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        //O(1) time complexity
        auto it = m.find(key);
        if(it==m.end()) return -1;
        l.splice(l.begin(), l, it->second);
        return it->second->second;
    }
    
    void put(int key, int value) {
        // invalidate the least recently used item
        //O(1) time complexity
        auto it = m.find(key);
        if(it!=m.end()) l.erase(it->second);
        l.push_front({key, value});
        m[key] = l.begin();
        if(m.size()>cap){
            int k = l.rbegin()->first;
            l.pop_back();
            m.erase(k);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */



**************************************************************************************************************
Strobogrammatic Number
**************************************************************************************************************
246. Strobogrammatic Number
//solution 1
//using two pointer
class Solution {
public:
    bool isStrobogrammatic(string num) {
        //a number that looks the same when rotated 180 degrees 
        /*
        6   9
        1   1
        0   0
        8   8
        9   6
        */
        int left = 0, right = num.size()-1;
        while(left <= right){
            if(num[left] == '6'&& num[right] == '9' || num[left] == '9'&& num[right] == '6' || num[left] == '8'&& num[right] == '8' 
                || num[left] == '1'&& num[right] == '1' || num[left] == '0'&& num[right] == '0'){
                left++;
                right--;
            }
            else return false;
        }
        return true;
    }
};
//solution 2
//using hash table
class Solution {
public:
    bool isStrobogrammatic(string num) {
        //a number that looks the same when rotated 180 degrees 
        /*
        6   9
        1   1
        0   0
        8   8
        9   6
        */
        unordered_map<char, char> m{{'6', '9'}, {'9', '6'}, {'1', '1'}, {'0', '0'}, {'8', '8'}};
        int left = 0, right = num.size()-1;
        while(left <= right){
            if(m[num[left]] == num[right]){
                left++;
                right--;
            }
            else return false;
        }
        return true;
    }
};

247. Strobogrammatic Number II
//recursion
class Solution {
public:
 
    vector<string> findStrobogrammatic(int n) {
        //recursion
        return find(n, n);
    }
    vector<string> find(int m, int n){
        if(m==0) return {""};
        if(m==1) return {"8", "1", "0"};
        vector<string> res;
        vector<string> t = find(m-2, n);
        for(string s:t){
            res.push_back("6"+s+"9");
            res.push_back("9"+s+"6");
            res.push_back("8"+s+"8");
            res.push_back("1"+s+"1");
            if(m!=n) res.push_back("0"+s+"0");
        }
        return res;
    }
};
//iterate!!!
class Solution {
public:
 
    vector<string> findStrobogrammatic(int n) {
        //00 11 69 96 88
        //0 1 8
        vector<string> one = {"0","1","8"}, two={""}, res;
        if(n%2==1) res=one;
        else res=two;
        for(int i=0;i<n/2;i++){
            vector<string> t;
            for(auto a:res){
                if(i!=n/2-1) t.push_back("0"+a+"0");
                t.push_back("1"+a+"1");
                t.push_back("8"+a+"8");
                t.push_back("6"+a+"9");
                t.push_back("9"+a+"6");
                
            }
            res=t;
        }
        return res;
    }
    
    
};


****************************************************************************************************************************************
Palindrom
****************************************************************************************************************************************

125. Valid Palindrome
//two points. time complexity: O(N), space complexity: O(1)
class Solution {
public:
    bool isPalindrome(string s) {
        if(s.empty() || s==" ") return true;
        int left = 0, right = s.size()-1;
        
        while(left<=right){
            if(!isalnum(s[left])) left++;
            else if(!isalnum(s[right])) right--;    //isalnum, decimal digit or an uppercase or lowercase letter. isalpha, an alphabetic letter. 
            else if(tolower(s[left++]) == tolower(s[right--])) continue;   //!!!tolower !!!left++ right--
            else return false;
        }
        return true;
    }
};

680. Valid Palindrome II
//time complexity: O(N), space complexity: O(1)
class Solution {
public:
    bool validPalindrome(string s) {
        
        int left = 0, right = s.size()-1;
        while(left<=right){
            if(s[left] == s[right]) {
                left++; 
                right--; 
                continue;
            }
            //s[left] != s[right]
            int left1 = left + 1, right1 = right; //remove the left char
            int left2 = left, right2 = right-1;   //remove the right char
            
            while(left1<=right1){
                if(s[left1] == s[right1]) {
                    left1++; 
                    right1--; 
                    continue;
                }
                else break;
            }
            
            while(left2<=right2){
                if(s[left2] == s[right2]) {
                    left2++; 
                    right2--; 
                    continue;
                }
                else break;
            }
            
            return left1>=right1 || left2>=right2;
        }
        return true;
    }
};


5. Longest Palindromic Substring
//!!!  2d-DP
//time complexity: O(N^2), space complexity: O(N^2)
class Solution {
public:
    string longestPalindrome(string s) {
        //dp[l][r] = s[l]==s[r] && (r-l<=2||dp[l+1][r-1])
        if(s.empty()) return "";
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int max_len = 0; 
        string res = "";
        for(int r=0; r<n; r++){
            for(int l=0; l<=r; l++){ //!!!l<=r
                dp[l][r] = (s[l]==s[r])&&(r-l<=2||dp[l+1][r-1]);  //!!!
                if(dp[l][r] && (r-l+1) > max_len){
                    res = s.substr(l, r-l+1);
                    max_len = r-l+1;  
                } 
            }
        }
        return res;
    }
};

647. Palindromic Substrings
//2d-dp
class Solution {
public:
    int countSubstrings(string s) {
        //dynamic programming
        //dp[i][j] = s[i]==s[j] && (dp[i+1][j-1]||j-i<=2)
        if(s.empty()) return 0;
        int res = 0;
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int j=0; j<n; j++){
            for(int i=0; i<=j; i++){   //!!!i<=j
                dp[i][j] = (s[i]==s[j]) && (j-i<=2||dp[i+1][j-1]);  //j-i<=2
                if(dp[i][j]==1) res++;
            }
        }
        return res;
    }
};



***************************************************************************************************************************
substes combinations Permutations
***************************************************************************************************************************
78. Subsets
//time complexity:O(n*2^n);      space complexity: O(n*2^n)
//Subset总共产生2^n个Subset，但是每个Subset的长度是n数量级的，所以Subset的复杂度应该是O(n*2^n)
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        //a set of distinct integers ---> sort is no need
        vector<vector<int>> res;
        vector<int> out;
        backtrack(nums, res, out, 0);
        return res;
    }
    
    void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& out, int start){
        res.push_back(out);
        for(int i = start; i<nums.size(); i++){
            out.push_back(nums[i]);
            backtrack(nums, res, out, i+1);
            out.pop_back();
        }
    }

};

77. Combinations
//time complexity:O(k * C(n, k));      space complexity: O(k * C(n, k))
//O(k * C(n, k))
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> out;
        backtrack(res, out, n, 1, k);
        return res;
    }
    void backtrack(vector<vector<int>>& res, vector<int>& out, int n, int start, int k){
        if(out.size()>=k) {res.push_back(out); return;}
        for(int i=start; i<=n; i++){
            out.push_back(i);
            backtrack(res, out, n, i+1, k);
            out.pop_back();
        }
    }
};

46. Permutations
//time complexity:O(n!*n);       space complexity: O(n!*n)
//N个数的全排列是N!种，故共有N!个解，每个解需要O(N)时间构造，所以总时间是O(N!*N)
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.empty()) return {};
        vector<vector<int>> res;
        vector<int> out;
        vector<int> visited(nums.size(), 0);
        backtrack(res, out, visited, nums);
        return res;
    }
    void backtrack(vector<vector<int>>& res, vector<int>& out, vector<int>& visited, vector<int>& nums){
        if(out.size() == nums.size()) {res.push_back(out); return;}
        for(int i=0; i<nums.size(); i++){
            if(visited[i]==0){
                visited[i]=1;
                out.push_back(nums[i]);
                backtrack(res, out, visited, nums);
                visited[i]=0;
                out.pop_back();
            }
        }
        
    }

};


//
class Solution {
public:
    vector<vector<int> > permute(vector<int> &num) {
        vector<vector<int> > res;
        permuteDFS(num, 0, res);
        return res;
    }
    void permuteDFS(vector<int> &num, int start, vector<vector<int> > &res) {
        if (start >= num.size()) res.push_back(num);
        for (int i = start; i < num.size(); ++i) {
            swap(num[start], num[i]);
            permuteDFS(num, start + 1, res);
            swap(num[start], num[i]);
        }
    }
};



47. Permutations II
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if(nums.empty()) return {};
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> out;
        vector<int> visited(nums.size(), 0);
        backtrack(res, out, visited, nums);
        return res;
    }
    void backtrack(vector<vector<int>>& res, vector<int>& out, vector<int>& visited, vector<int>& nums){
        if(out.size()==nums.size()) {res.push_back(out); return;}
        for(int i=0; i<nums.size(); i++){
            if(visited[i]==0){
                if(i>0 && nums[i]==nums[i-1] && visited[i-1]==0) continue;  //!!!!here visited[i-1]==0保持了相同数字的顺序
                visited[i]=1;
                out.push_back(nums[i]);
                backtrack(res, out, visited, nums);
                visited[i]=0;
                out.pop_back();
            }
        }
    }
};


*****************************************************************************************************************************
sliding window
*****************************************************************************************************************************
76. Minimum Window Substring
//sliding window
//Minimum Window conatin  Substring
class Solution {
public:
    string minWindow(string s, string t) {
        //O(n)
        //hash map + two pointers
        if(s.empty() || t.empty()) return "";
        
        string res = "";
        unordered_map<int, int> m;
        int cnt = 0, left = 0; 
        int min_len = INT_MAX;
        
        for(char c:t) m[c]++;
        
        for(int right=0; right<s.size(); right++){
            //move right boundary until cnt == t.size()
            if(--m[s[right]]>=0) cnt++;
            while(cnt == t.size()){
                if(right-left+1 < min_len){
                    min_len = right-left+1;
                    res = s.substr(left, min_len);
                }
                //when cnt== t.size(), move left boundary
                if(++m[s[left]]>0) cnt--;
                left++;
            }
        }
        
        return res;
    }
};

567. Permutation in String
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        // s2 contains the permutation of s1
        unordered_map<char, int> m;
        for(char c:s1) m[c]++;
        int cnt=0;
        int left = 0;
        for(int right =0; right<s2.size(); right++){
            if(--m[s2[right]] >=0) cnt++;
            while(cnt == s1.size()){
                if(right-left+1 == s1.size()) return true;
                //move left
                if(++m[s2[left]]>0) cnt--;
                left++;
            }
        }
        return false;
    }
};
//two pointers
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> m;
        for(char c:s1) m[c]++;
        
        int left = 0, cnt=0;
        for(int right = 0; right<s2.size(); right++){
            if(--m[s2[right]]>=0) cnt++;
            while(cnt==s1.size()){
                if(right-left+1 == s1.size()) return true;
                if(++m[s2[left++]]>0) cnt--; 
            }
        }
        return false;
    }
};

//another solution(438)
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        string s = s2, p = s1;
        vector<int> res;
        vector<int> v1(26), v2(26);
        for(int i=0; i<p.size(); i++){
            v1[s[i]-'a']++;
            v2[p[i]-'a']++;
        }
        if(v1 == v2) return true;
        for(int i=p.size(); i<s.size(); i++){
            v1[s[i]-'a']++;
            v1[s[i-p.size()]-'a']--;
            if(v1==v2) return true;
        }
        return false;
    }
};


3. Longest Substring Without Repeating Characters
//sliding window
//example: a  b  c  a  b  c  b  b
//                             ^^


🌼🌼🌼//another solution 窗口不用一步一步移动
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> m(256, -1);   //map<char, pos>
        int res = 0, left = -1;
        for(int i =0; i<s.size(); i++){
            left = max(left, m[s[i]]);
            m[s[i]] = i;
            res = max(res, i-left);
        }
        return res;
    }
};


//sliding window
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty()) return 0;
        //longest substring without repeating characters.
        unordered_map<char, int> m; //map<char, count>
        int left = 0;
        int max_len = INT_MIN;
        for(int right=0; right<s.size(); right++){
            m[s[right]]++;
            while(m[s[right]] > 1){   //repeating
                //move left
                m[s[left]]--;
                left++;
            }
            max_len = max(max_len, right-left+1);
        }
        return max_len;
    }
};


//
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        //sliding window + hash table
        int res = 0;
        unordered_map<char, int> m;
        int left = 0;
        for(int right=0; right<s.size(); right++){
            m[s[right]]++;
            while(m[s[right]] > 1){
                m[s[left++]]--;
            }
            res = max(res, right-left+1);
        }
        return res;
    }
};

//
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int res = 0, left = 0, i = 0, n = s.size();
        unordered_map<char, int> m;
        for (int i = 0; i < n; ++i) {
            left = max(left, m[s[i]]);
            m[s[i]] = i + 1;
            res = max(res, i - left + 1);
        }
        return res;
    }
};




239. Sliding Window Maximum
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //linear time
        if(nums.empty() || nums.size()<k) return {};
        vector<int> res;
        deque<int> q;
        for(int i=0; i<nums.size(); i++){
            if(!q.empty() && q.front() == i-k) q.pop_front();
            while(!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i);
            if(i>=k-1) res.push_back(nums[q.front()]);
        }
        return res;
    }
};


//
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //deque
        int n = nums.size();
        vector<int> res;
        deque<int> q;
        
        for(int i=0; i<nums.size(); i++){
            if(q.empty() || nums[i]<nums[q.back()]) q.push_back(i);
            else{
                while(!q.empty() && nums[i] > nums[q.back()]) q.pop_back();
                q.push_back(i);   
            }
            if(q.front() == i-k) q.pop_front();
            if(i>=k-1) res.push_back(nums[q.front()]);
        }
        
        return res;
    }
};

713. Subarray Product Less Than K
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        //positive integers
        if(nums.empty() || k<=1) return 0;  //!!!<=1
        
        int product = 1;
        int left = 0;
        int res = 0;
        for(int right = 0; right<nums.size(); right++){
            product *= nums[right];
            while(product >= k){
                product /= nums[left];
                left++;
            }
            res += right - left + 1; //(加上以right为结尾的subarray5)
        }
        return res;
    }
};




*****************************************************************************************************************************
union find
*****************************************************************************************************************************
721. Accounts Merge
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, string> root;
        unordered_map<string, string> owner;
        unordered_map<string, set<string>> m;   //<root, vector<string>>
        //initialize root
        for(auto account:accounts){
            for(int i=1; i<account.size(); i++){
                root[account[i]] = account[i];
                owner[account[i]] = account[0];
            }
        }
        //union find
        for(auto account:accounts){
            string p = findroot(account[1], root);
            for(int i=2; i<account.size(); i++){
                root[findroot(account[i], root)] = p;
            }
        }
        //construact union find to map <root, vector<string>>
        for(auto account:accounts){
            for(int i=1; i<account.size(); i++){
                m[findroot(account[i], root)].insert(account[i]);
            }
        }
        //map+owner ---> result
        vector<vector<string>> res;
        for(auto a:m){
            vector<string> v(a.second.begin(), a.second.end());
            v.insert(v.begin(), owner[a.first]);
            res.push_back(v);
        }
        return res;
        
    }
    
    string findroot(string s, unordered_map<string, string>& root){
        if(root[s]!=s) return findroot(root[s], root);
        else return s;
    }

};


//BFS:




**************************************************************************************************************************************
sum
**************************************************************************************************************************************
494. Target Sum
//solution 1: DP
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        vector<unordered_map<int, int>> dp(n+1);
        dp[0][0] = 1;
        for(int i=0; i<n; i++){
            for(auto a:dp[i]){
                int sum = a.first, count = a.second;
                dp[i+1][sum+nums[i]] += count;
                dp[i+1][sum-nums[i]] += count;
            }
        }
        return dp[n][S];
    }    
};
//solution 2: modify DP
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int n = nums.size();
        unordered_map<int, int> m;
        m[0] =1;
        for(int num:nums){
            unordered_map<int, int> t;
            for(auto a:m){
                t[a.first-num] += a.second;
                t[a.first+num] += a.second;
            }
            m=t;
        }
        return m[S];
    }    
    
};
//solution 3: DFS
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int res = 0;
        helper(nums, S, 0, res);
        return res;
    }    
    void helper(vector<int>& nums, int S, int index, int& res){
        if(index >= nums.size()){
            if(S==0) res++;
            return;
        }
        helper(nums, S-nums[index], index+1, res);
        helper(nums, S+nums[index], index+1, res);
    }
    
};

//solution 4: DFS + DP   ???
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        vector<unordered_map<int, int>> dp(nums.size());
        return helper(nums, S, 0, dp);
    }
    int helper(vector<int>& nums, int sum, int start, vector<unordered_map<int, int>>& dp) {
        if (start == nums.size()) return sum == 0;
        if (dp[start].count(sum)) return dp[start][sum];
        int cnt1 = helper(nums, sum - nums[start], start + 1, dp);
        int cnt2 = helper(nums, sum + nums[start], start + 1, dp);
        return dp[start][sum] = cnt1 + cnt2;
    }
};



377. Combination Sum IV

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        //dynamic programming dp[i] += dp[i-val]
        //example: [1, 2, 3]
        //                ^
        //3=2+1, 3=1+2, 3=0+3;   ->  dp[3]=d[2]+dp[1]+dp[3]; dp[i] += dp[i-num]
        //for every i(1, target), for every num in nums, if(num<i) dp[i]+=sp[i-num] 
        vector<int> dp(target+1, 0);
        dp[0] = 1;
        for(int i=1; i<=target; i++){
            for(auto num:nums){
                if(num<=i) dp[i] += dp[i-num];
            }
        }
        return dp[target];
    }
    
};

*************************************************************************************************************************************
Reservoir Sampling
*************************************************************************************************************************************
398. Random Pick Index
//solution 1:
class Solution {
private:
    vector<int> Nums;
public:
    Solution(vector<int> nums) {
        //array not sorted
        //contain duplicates
        //randomly return index
        Nums = nums;
    }
    
    int pick(int target) {
        vector<int> index;   //nums could be very large!!!
        for(int i=0; i<Nums.size(); i++){
            if(target == Nums[i])
                index.push_back(i);
        }
        return index[rand()%index.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */
//solution 2:  Reservoir Sampling
class Solution {
private:
    vector<int> Nums;
public:
    Solution(vector<int> nums) {
        //array not sorted
        //contain duplicates
        //randomly return index
        Nums = nums;
    }
    
    int pick(int target) {
        int cnt = 0, res = -1;
        for(int i=0; i<Nums.size(); i++){
            if(target != Nums[i]) continue;
            cnt++;
            if(rand()%cnt == 0) res = i;   //以1/count的概率，返回第count个数
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */


//
class Solution {
private:
    vector<int> Nums;
public:
    Solution(vector<int> nums) {
        Nums = nums;
    }
    
    int pick(int target) {
        int cnt = 0, res = -1;
        for(int i=0; i<Nums.size(); i++){
            if(Nums[i] == target) cnt++;
            else continue;
            if(rand()%cnt == 0) res = i;
        }
        return res;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution obj = new Solution(nums);
 * int param_1 = obj.pick(target);
 */

**************************************************************************************************************************************
Bit manipulation
***************************************************************************************************************************************
191. Number of 1 Bits
class Solution {
public:
    int hammingWeight(uint32_t n) {
        // >> & 1
        int count = 0;
        while(n>0){
            count += n&1;
            n>>=1;
        }
        return count;
    }
};

190. Reverse Bits 
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i=0;i<32;i++){
            res = res<<1;
            if(n&1==1) res++;
            n=n>>1;
        }
        return res;
    }
};



461. Hamming Distance
class Solution {
public:
    int hammingDistance(int x, int y) {
        int t = x^y;
        int res = 0;
        while(t){
            if(t&1) res++;
            t>>=1;
        }
        return res;
    }
};

477. Total Hamming Distance
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        //the count of 0 * the count of 1
        int res = 0;
        int n = nums.size();
        for(int i=0; i<31; i++){
            int count = 0;
            for(auto num:nums){
                if(num & 1<<i) count++;
            }
            res += count*(n - count);
        }
        return res;
    }
};


136. Single Number
//  a xor a = 0;
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for(int num:nums){
            res = res^num;
        }
        return res;
    }
};

137. Single Number II
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        //linear runtime  -> can not sort
        //without extra space -> 
        //first idea, go throgh save count to a map, then check map, return the key if the value map is 1(extra space)
        //second idea, sort the nums, go through, return the one that different from its neighbors(not linear)
        //---->bit manipulation
        int res = 0;
        for(int i=0; i<32; i++){
            int sum = 0;
            for(int j=0; j<nums.size(); j++){
                sum += nums[j]>>i & 1;
            }
            res |= sum%3<<i;
        }
        return res;
    }
};


260. Single Number III
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int diff = 0;
        for(int num:nums) diff = diff^num;
        diff &= -diff;
        vector<int> res(2, 0);
        for(int num:nums){
            if(num&diff) res[0]^=num;
            else res[1]^=num;
        }
        return res;
    }
};


371. Sum of Two Integers
class Solution {
public:
    int getSum(int a, int b) {
        if(b==0) return a;
        int sum = a^b;
        int carry = (a&b)<<1;
        return getSum(sum, carry);
    }
};


393. UTF-8 Validation
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int cnt = 0;
        for(int a:data){
            if(cnt == 0){
                if(a>>5 == 0b110) cnt = 1;
                else if(a>>4 == 0b1110) cnt = 2;
                else if(a>>3 == 0b11110) cnt = 3;
                else if(a>>7) return false;   
            }
            else{
                if(a>>6 != 0b10) return false;
                cnt--;
            }
        }
        return cnt == 0;
    }
};

//
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int i=0;
        while(i<data.size()){
            if(data[i]>>7 == 0){
                i++;
            }   
            else if(data[i]>>5 == 0b110){
                i++;
                if(i<data.size() && data[i]>>6 == 0b10) i++; 
                else return false;
            }
            else if(data[i]>>4 == 0b1110){
                for(int j=i+1; j<i+3; j++){
                    if(j<data.size() && data[j]>>6 == 0b10) continue;
                    else return false;
                }
                i+=3;
                
            }
            else if(data[i]>>3 == 0b11110){
                for(int j=i+1; j<i+4; j++){
                    if(j<data.size() && data[j]>>6 == 0b10) continue;
                    else return false;
                }
                i+=4;
            }
            else return false;
        }
        
        return true;
    }
};


//
class Solution {
public:
    bool validUtf8(vector<int>& data) {
        int i=0;
        int cnt = 0;
        for(int a:data){
            if(cnt == 0){
                if(a>>7 == 0) cnt = 0;  
                else if(a>>5 == 0b110) cnt = 1;
                else if(a>>4 == 0b1110) cnt = 2;
                else if(a>>3 == 0b11110) cnt = 3;
                else return false;
            }
            else{
                if(a>>6!=0b10) return false;
                cnt--;
            }
        }
        
        return cnt==0;
    }
};

231. Power of Two
//solution 1
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n==0) return false;
        int cnt = 0;
        while(n){
            if(n&1==1) cnt++;
            n >>= 1;
            if(cnt>1) return false;
        }
        return true;
    }
};
//solution 2 
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n>0 && !(n&(n-1))) return true;
        else return false;
    }
};

**************************************************************************************************************************************
Excel
**************************************************************************************************************************************
168. Excel Sheet Column Title
class Solution {
public:
    string convertToTitle(int n) {
        string res = "";
        while(n>0){
            res = char((--n)%26 + 'A') + res;
            n = n/26;
        }
        return res;
    }
};



171. Excel Sheet Column Number
class Solution {
public:
    int titleToNumber(string s) {
        int res = 0;
        for(char c:s){
            res = res*26 + c-'A' + 1;
        }
        return res;
    }
};



**********************************************************************************************************************************
vector sort
**********************************************************************************************************************************
179. Largest Number
class Solution {
public:
    static 
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int a, int b){return to_string(a)+to_string(b) > to_string(b)+to_string(a);});
        string res = "";
        for(int i=0; i<nums.size(); i++){
            res += to_string(nums[i]);
        }
        return res[0]=='0' ? "0" : res;
    }
   
};


所有tag（13天）
********************************************************************************************************************************************
🌟273 Integer to English Words    23.1%   Hard    
!!!🌟301 Remove Invalid Parentheses  36.5%   Hard    
🌟67  Add Binary  35.7%   Easy    
🌟91  Decode Ways 21.0%   Medium  
🌟283 Move Zeroes 52.4%   Easy    
🌟15  3Sum 22.1%   Medium  
🌟10  Regular Expression Matching 24.4%   Hard    
!!!🌟158 Read N Characters Given Read4 II - Call multiple times 24.3%   Hard    
🌟17  Letter Combinations of a Phone Number   38.1%   Medium  
🌟29  Divide Two Integers 15.7%   Medium  
🌟278 First Bad Version   27.1%   Easy    
!!!🌟76  Minimum Window Substring    28.1%   Hard   
🌟621 Task Scheduler 42.8%   Medium  
🌟297 Serialize and Deserialize Binary Tree 36.6%   Hard  
🌟253 Meeting Rooms II 40.1%   Medium  
🌟325 Maximum Size Subarray Sum Equals k 43.5%   Medium  
🌟125 Valid Palindrome    28.5%   Easy    
🌟211 Add and Search Word - Data structure design 26.9%   Medium  
🌟31  Next Permutation    29.3%   Medium  
🌟314 Binary Tree Vertical Order Traversal 38.7%   Medium  
🌟114 Flatten Binary Tree to Linked List 38.5%   Medium  
🌟23  Merge k Sorted Lists    30.2%   Hard    
🌟121 Best Time to Buy and Sell Stock 44.3%   Easy    
🌟257 Binary Tree Paths 43.0%   Easy    
🌟311 Sparse Matrix Multiplication 53.6%   Medium  (what if we change matrix to vector!!!??? two pointer)
🌟200 Number of Islands 38.0%   Medium  
🌟56  Merge Intervals 33.0%   Medium  
🌟133 Clone Graph 25.1%   Medium  
🌟173 Binary Search Tree Iterator 44.6%   Medium  
🌟1   Two Sum 38.9%   Easy    
🌟157 Read N Characters Given Read4 28.2%   Easy    
282 Expression Add Operators    31.1%   Hard    
🌟277 Find the Celebrity 35.2%   Medium  
🌟43  Multiply Strings 28.7%   Medium  
336 Palindrome Pairs    28.0%   Hard    
🌟98  Validate Binary Search Tree 24.4%   Medium  
🌟！！！65  Valid Number    13.1%   Hard    
🌟138 Copy List with Random Pointer   25.6%   Medium  
146 LRU Cache   21.4%   Hard    
🌟215 Kth Largest Element in an Array 42.8%   Medium  
57  Insert Interval 29.7%   Hard    
🌟124 Binary Tree Maximum Path Sum  28.0%   Hard  
🌟88  Merge Sorted Array  33.3%   Easy    
🌟42  Trapping Rain Water 39.2%   Hard  
🌟543 Diameter of Binary Tree 45.2%   Easy  
🌟304 Range Sum Query 2D - Immutable  28.8%   Medium  
🌟139 Word Break 32.6%   Medium
689 Maximum Sum of 3 Non-Overlapping Subarrays  42.0%   Hard    
🌟300 Longest Increasing Subsequence  39.2%   Medium  
🌟680 Valid Palindrome II 32.5%   Easy    
358 Rearrange String k Distance Apart 31.8%   Hard    
🌟161 One Edit Distance 31.3%   Medium  
🌟143 Reorder List    28.1%   Medium  
🌟78  Subsets 47.7%   Medium  
51  N-Queens    35.2%   Hard    
🌟349 Intersection of Two Arrays  49.7%   Easy    
🌟33  Search in Rotated Sorted Array  32.1%   Medium  
🌟75  Sort Colors 39.9%   Medium 
🌟560 Subarray Sum Equals K   40.1%   Medium  
340 Longest Substring with At Most K Distinct Characters 38.4%   Hard    
🌟236 Lowest Common Ancestor of a Binary Tree 31.9%   Medium  (if p or q is not tree node)
🌟140 Word Break II   25.3%   Hard  
🌟438 Find All Anagrams in a String   34.3%   Easy  
317 Shortest Distance from All Buildings 35.3%   Hard    
🌟79  Word Search 28.9%   Medium  
🌟350 Intersection of Two Arrays II 44.8%   Easy 
🌟238 Product of Array Except Self    51.7%   Medium  
🌟227 Basic Calculator II 31.1%   Medium  (+ - * /)   
🌟20  Valid Parentheses   34.6%   Easy  
🌟206  Reverse Linked List 49.3%   Easy   
🌟341 Flatten Nested List Iterator 44.4%   Medium
🌟348 Design Tic-Tac-Toe 46.9%   Medium  
🌟252 Meeting Rooms 49.8%   Easy    
32  Longest Valid Parentheses 23.8%   Hard    
🌟426 Convert Binary Search Tree to Sorted Doubly Linked List 36.2%   Medium  
🌟285 Inorder Successor in BST 33.9%   Medium  
🌟523 Continuous Subarray Sum 23.4%   Medium  
🌟123 Best Time to Buy and Sell Stock III 31.4%   Hard    
🌟127 Word Ladder 21.1%   Medium  
44  Wildcard Matching   21.6%   Hard


🌟239 Sliding Window Maximum  35.3%   Hard  
🌟38  Count and Say   37.8%   Easy    
212 Word Search II  25.8%   Hard   
🌟18  4Sum    28.3%   Medium  
🌟415 Add Strings 42.1%   Easy    
🌟636 Exclusive Time of Functions 45.3%   Medium  
🌟13  Roman to Integer    49.5%   Easy    
🌟230 Kth Smallest Element in a BST   47.4%   Medium 
🌟71  Simplify Path   27.0%   Medium  
🌟360 Sort Transformed Array 45.5%   Medium  
🌟49  Group Anagrams  41.2%   Medium  
🌟105 Construct Binary Tree from Preorder and Inorder Traversal 36.6%   Medium  
🌟449  Serialize and Deserialize BST   43.3%   Medium  
🌟247 Strobogrammatic Number II 41.9%   Medium  
🌟208 Implement Trie (Prefix Tree)    33.5%   Medium  
🌟34  Find First and Last Position of Element in Sorted Array 32.0%   Medium 
🌟224 Basic Calculator    29.8%   Hard    
🌟111 Minimum Depth of Binary Tree    34.1%   Easy   
269 Alien Dictionary27.6%   Hard    
🌟209 Minimum Size Subarray Sum   33.1%   Medium  
🌟122 Best Time to Buy and Sell Stock II  49.1%   Easy    
🌟109 Convert Sorted List to Binary Search Tree   37.3%   Medium 
4   Median of Two Sorted Arrays 23.9%   Hard    
🌟53  Maximum Subarray 41.2%   Easy
🌟346 Moving Average from Data Stream 62.1%   Easy  
295 Find Median from Data Stream    31.6%   Hard    
🌟394 Decode String   42.2%   Medium  
🌟28  Implement strStr()  29.9%   Easy  
🌟246 Strobogrammatic Number 40.7%   Easy 
218 The Skyline Problem 29.9%   Hard    
🌟721 Accounts Merge  35.4%   Medium  
126 Word Ladder II  15.6%   Hard    
🌟5   Longest Palindromic Substring   25.6%   Medium  
🌟39  Combination Sum 43.6%   Medium  
🌟286 Walls and Gates 46.4%   Medium 
🌟46  Permutations 50.0%   Medium  
84  Largest Rectangle in Histogram  28.7%   Hard    
305 Number of Islands II 40.1%   Hard    
🌟21  Merge Two Sorted Lists  43.1%   Easy 
🌟102 Binary Tree Level Order Traversal   44.6%   Medium  
🌟494 Target Sum 44.0%   Medium   ！！！
545 Boundary of Binary Tree 33.0%   Medium  
99  Recover Binary Search Tree  32.3%   Hard    
🌟128 Longest Consecutive Sequence  39.3%   Hard    
🌟322 Coin Change 27.3%   Medium 
🌟3   Longest Substring Without Repeating Characters 25.0%   Medium
632 Smallest Range  43.9%   Hard    
🌟670 Maximum Swap    38.8%   Medium  
🌟518 Coin Change 2   37.9%   Medium  
🌟398 Random Pick Index   46.2%   Medium  （reservoir smapling）
🌟347 Top K Frequent Elements 50.9%   Medium  
🌟151 Reverse Words in a String   15.7%   Medium 
🌟62  Unique Paths 44.4%   Medium  
🌟785 Is Graph Bipartite? 39.8%   Medium  
🌟251 Flatten 2D Vector 42.1%   Medium  
🌟50  Pow(x, n)   26.6%   Medium  
308 Range Sum Query 2D - Mutable 28.1%   Hard    
🌟69  Sqrt(x) 29.5%   Easy    
🌟116 Populating Next Right Pointers in Each Node 36.6%   Medium 
381 Insert Delete GetRandom O(1) - Duplicates allowed   30.1%   Hard    
🌟90  Subsets II 39.7%   Medium  
🌟191 Number of 1 Bits    40.9%   Easy 
🌟199 Binary Tree Right Side View 44.3%   Medium 
🌟73  Set Matrix Zeroes   37.6%   Medium  
🌟463 Island Perimeter    58.6%   Easy  
🌟393 UTF-8 Validation    34.9%   Medium  
68  Text Justification  21.0%   Hard    
🌟567 Permutation in String   36.7%   Medium  
🌟94  Binary Tree Inorder Traversal 52.2%   Medium  
🌟106 Construct Binary Tree from Inorder and Postorder Traversal  35.7%   Medium 
🌟198 House Robber 40.4%   Easy    
🌟186 Reverse Words in a String II 33.4%   Medium  
🌟378 Kth Smallest Element in a Sorted Matrix 46.3%   Medium 
🌟145 Binary Tree Postorder Traversal 44.4%   Hard    
🌟694 Number of Distinct Islands 46.2%   Medium  
🌟791 Custom Sort String  59.4%   Medium 
41  First Missing Positive  26.8%   Hard    
???399 Evaluate Division   43.4%   Medium 
🌟477 Total Hamming Distance  47.8%   Medium 
🌟235 Lowest Common Ancestor of a Binary Search Tree  41.2%   Easy    
🌟81  Search in Rotated Sorted Array II   32.5%   Medium
30  Substring with Concatenation of All Words   22.4%   Hard    
🌟419 Battleships in a Board  63.9%   Medium  
🌟152 Maximum Product Subarray 27.5%   Medium 
🌟117 Populating Next Right Pointers in Each Node II  33.6%   Medium  
🌟380 Insert Delete GetRandom O(1)    40.5%   Medium 
🌟392 Is Subsequence  45.0%   Medium 
🌟103 Binary Tree Zigzag Level Order Traversal    38.4%   Medium 
🌟298 Binary Tree Longest Consecutive Sequence 42.4%   Medium 
772 Basic Calculator III 41.4%   Hard   
72  Edit Distance 34.2%   Hard    
🌟162 Find Peak Element   39.7%   Medium 
🌟692 Top K Frequent Words    42.4%   Medium  
296 Best Meeting Point 52.9%   Hard    
🌟24  Swap Nodes in Pairs 40.8%   Medium
🌟640 Solve the Equation  38.9%   Medium  
🌟36  Valid Sudoku    39.4%   Medium  
🌟8   String to Integer (atoi)    14.1%   Medium  
149 Max Points on a Line    15.3%   Hard    
🌟377 Combination Sum IV 43.2%   Medium  
🌟323 Number of Connected Components in an Undirected Graph 49.7%   Medium
🌟101 Symmetric Tree 41.4%   Easy    
642 Design Search Autocomplete System 31.6%   Hard    
🌟242 Valid Anagram   48.9%   Easy    
🌟319 Bulb Switcher   43.3%   Medium  
🌟674 Longest Continuous Increasing Subsequence   42.8%   Easy  
🌟47  Permutations II 36.8%   Medium  
403 Frog Jump   33.5%   Hard    
🌟210 Course Schedule II  31.6%   Medium  
🌟74  Search a 2D Matrix  34.5%   Medium  
🌟12  Integer to Roman    47.7%   Medium  
???395 Longest Substring with At Least K Repeating Characters  36.3%   Medium  
🌟549 Binary Tree Longest Consecutive Sequence II 43.0%   Medium  
85  Maximal Rectangle 30.8%   Hard    
🌟658 Find K Closest Elements 34.7%   Medium 
🌟468 Validate IP Address 20.5%   Medium 
🌟54  Spiral Matrix   28.2%   Medium  
🌟2   Add Two Numbers 29.2%   Medium  
🌟100 Same Tree   48.4%   Easy   
🌟270 Closest Binary Search Tree Value 41.7%   Easy 
🌟647 Palindromic Substrings  54.5%   Medium 
🌟26  Remove Duplicates from Sorted Array 37.8%   Easy  
🌟55  Jump Game 30.2%   Medium  
？？？548 Split Array with Equal Sum 38.4%   Medium  
🌟108 Convert Sorted Array to Binary Search Tree 46.6%   Easy 
🌟339 Nested List Weight Sum 64.8%   Easy    
🌟384 Shuffle an Array    48.0%   Medium 
🌟524 Longest Word in Dictionary through Deleting 43.6%   Medium 
🌟240 Search a 2D Matrix II   39.4%   Medium  
363 Max Sum of Rectangle No Larger Than K   34.2%   Hard    
🌟66  Plus One    40.0%   Easy    
🌟37  Sudoku Solver 33.5%   Hard  (time complexity pow(9, n), backtrack)  
🌟167 Two Sum II - Input array is sorted  47.6%   Easy
272 Closest Binary Search Tree Value II 41.5%   Hard    
🌟63  Unique Paths II 32.6%   Medium 
???🌟361 Bomb Enemy 41.2%   Medium  
🌟77  Combinations 43.4%   Medium 
🌟554 Brick Wall  46.7%   Medium  
🌟255 Verify Preorder Sequence in Binary Search Tree 41.7%   Medium  
🌟825 Friends Of Appropriate Ages 32.1%   Medium 
87  Scramble String 30.3%   Hard    
🌟678 Valid Parenthesis String    29.9%   Medium
🌟556 Next Greater Element III    29.1%   Medium
🌟334 Increasing Triplet Subsequence  39.4%   Medium  
🌟387 First Unique Character in a String  47.6%   Easy  
432 All O`one Data Structure    28.1%   Hard    
🌟284 Peeking Iterator    36.9%   Medium  
🌟104 Maximum Depth of Binary Tree    56.9%   Easy 
🌟281 Zigzag Iterator 53.9%   Medium  
🌟445 Add Two Numbers II  47.4%   Medium 
25  Reverse Nodes in k-Group    33.2%   Hard    
🌟207 Course Schedule 34.9%   Medium  
639 Decode Ways II  24.2%   Hard    

185 Department Top Three Salaries   21.2%   Hard    
🌟22  Generate Parentheses    50.2%   Medium  
🌟303 Range Sum Query - Immutable 34.1%   Easy   
🌟383 Ransom Note 48.3%   Easy   
🌟862 Shortest Subarray with Sum at Least K   18.7%   Hard    
🌟437 Path Sum III 40.5%   Easy   
132 Palindrome Partitioning II  25.7%   Hard    
460 LFU Cache   26.1%   Hard    
🌟439 Ternary Expression Parser 52.1%   Medium  
446 Arithmetic Slices II - Subsequence  28.0%   Hard    
🌟189 Rotate Array    26.9%   Easy 
🌟153 Find Minimum in Rotated Sorted Array    41.6%   Medium 
＋复习带字典书Trie！！！每道题目确定一种写法🌼。分析时空复杂度。


🌟490 The Maze 44.3%   Medium  
🌟144 Binary Tree Preorder Traversal  48.4%   Medium  
🌟416 Partition Equal Subset Sum  38.7%   Medium  
🌟11  Container With Most Water   38.7%   Medium 
🌟219 Contains Duplicate II   33.6%   Easy  
🌟332 Reconstruct Itinerary   30.0%   Medium  
🌟367 Valid Perfect Square    38.9%   Easy  
🌟92  Reverse Linked List II  32.5%   Medium  
🌟261 Graph Valid Tree 38.8%   Medium  
135 Candy   26.1%   Hard    
97  Interleaving String 26.0%   Hard    
🌟40  Combination Sum II  37.8%   Medium  
🌟498 Diagonal Traverse   44.4%   Medium  
🌟688 Knight Probability in Chessboard    40.8%   Medium
🌟824 Goat Latin  54.8%   Easy    
🌟48  Rotate Image    44.0%   Medium  
🌟280 Wiggle Sort 59.3%   Medium  
493 Reverse Pairs   21.0%   Hard    
🌟372 Super Pow   34.9%   Medium  
329 Longest Increasing Path in a Matrix 37.8%   Hard    
🌟491 Increasing Subsequences 39.6%   Medium  
🌟160 Intersection of Two Linked Lists 30.8%   Easy    
🌟19  Remove Nth Node From End of List    33.7%   Medium  
🌟171 Excel Sheet Column Number   49.7%   Easy 
🌟290 Word Pattern    33.9%   Easy 
🌟27  Remove Element  42.0%   Easy 
489 Robot Room Cleaner49.3%   Hard    
🌟110 Balanced Binary Tree 39.2%   Easy  
🌟461 Hamming Distance    69.5%   Easy 
🌟695 Max Area of Island 53.1%   Easy    
🌟14  Longest Common Prefix   31.9%   Easy   
🌟172 Factorial Trailing Zeroes   37.0%   Easy    
🌟260 Single Number III   54.5%   Medium  
115 Distinct Subsequences   33.1%   Hard    
52  N-Queens II 48.6%   Hard    
410 Split Array Largest Sum 40.2%   Hard    
188 Best Time to Buy and Sell Stock IV  25.3%   Hard    
🌟371 Sum of Two Integers 50.9%   Easy   
🌟129 Sum Root to Leaf Numbers    39.4%   Medium 
🌟413 Arithmetic Slices 54.5%   Medium  
🌟274 H-Index 34.1%   Medium  
🌟190 Reverse Bits    29.3%   Easy    
🌟844 Backspace String Compare    43.8%   Easy  
🌟307 Range Sum Query - Mutable   24.6%   Medium 
315 Count of Smaller Numbers After Self 35.6%   Hard    
🌟166 Fraction to Recurring Decimal   18.5%   Medium  
🌟450 Delete Node in a BST 37.9%   Medium  
🌟137 Single Number II    43.8%   Medium  
🌟622 Design Circular Queue   36.3%   Medium
🌟505 The Maze II 39.7%   Medium  
🌟234 Palindrome Linked List  34.2%   Easy 
🌟141 Linked List Cycle 34.7%   Easy 
🌟708 Insert into a Cyclic Sorted List 22.2%   Medium  
🌟113 Path Sum II 37.4%   Medium  
🌟60  Permutation Sequence    30.7%   Medium  
🌟259 3Sum Smaller 43.0%   Medium  
🌟443 String Compression  35.7%   Easy
🌟7   Reverse Integer 24.4%   Easy   
🌟221 Maximal Square 31.2%   Medium  
🌟525 Contiguous Array    42.0%   Medium  
🌟179 Largest Number  24.2%   Medium  
🌟722 Remove Comments 29.0%   Medium
🌟168 Excel Sheet Column Title    27.9%   Easy   
🌟662 Maximum Width of Binary Tree    38.5%   Medium  
🌟430 Flatten a Multilevel Doubly Linked List 33.0%   Medium  
🌟654 Maximum Binary Tree 70.9%   Medium
🌟447 Number of Boomerangs    47.7%   Easy
🌟896 Monotonic Array 55.2%   Easy  
🌟130 Surrounded Regions  20.8%   Medium  
🌟886 Possible Bipartition    38.3%   Medium
🌟170 Two Sum III - Data structure design 27.7%   Easy 
🌟150 Evaluate Reverse Polish Notation    29.8%   Medium  
🌟713 Subarray Product Less Than K    33.5%   Medium  
🌟633 Sum of Square Numbers   32.4%   Easy    
🌟112 Path Sum    35.8%   Easy    
🌟324 Wiggle Sort II  26.6%   Medium  
🌟231 Power of Two 41.1%   Easy    
🌟724 Find Pivot Index    39.4%   Easy
🌟714 Best Time to Buy and Sell Stock with Transaction Fee    47.7%   Medium  
🌟767 Reorganize String   38.7%   Medium 
🌟414 Third Maximum Number    28.2%   Easy  
🌟733 Flood Fill 48.0%   Easy    
🌟404 Sum of Left Leaves  48.0%   Easy   
🌟344 Reverse String  61.4%   Easy   
🌟442 Find All Duplicates in an Array 58.1%   Medium  
🌟412 Fizz Buzz   58.0%   Easy    
🌟165 Compare Version Numbers 21.5%   Medium  
🌟268 Missing Number  46.1%   Easy    
🌟169 Majority Element    49.5%   Easy   
🌟681 Next Closest Time 41.4%   Medium
🌟217 Contains Duplicate  48.8%   Easy   
🌟686 Repeated String Match   31.5%   Easy    
🌟9   Palindrome Number   38.4%   Easy    
🌟80  Remove Duplicates from Sorted Array II  38.1%   Medium  
🌟136 Single Number   57.0%   Easy    
🌟287 Find the Duplicate Number 46.0%   Medium 
265 Paint House II 39.3%   Hard    
🌟764 Largest Plus Sign   41.3%   Medium  
🌟572 Subtree of Another Tree 40.4%   Easy  
???801 Minimum Swaps To Make Sequences Increasing  32.2%   Medium  
🌟637 Average of Levels in Binary Tree    56.5%   Easy
🌟535 Encode and Decode TinyURL   74.3%   Medium  
🌟784 Letter Case Permutation 53.3%   Easy  
🌟865 Smallest Subtree with all the Deepest Nodes 51.8%   Medium  
745 Prefix and Suffix Search    26.9%   Hard    
🌟673 Number of Longest Increasing Subsequence    32.0%   Medium  
🌟653 Two Sum IV - Input is a BST 50.6%   Easy    
🌟893 Groups of Special-Equivalent Strings    60.4%   Easy 
🌟750 Number Of Corner Rectangles 59.0%   Medium 
🌟275 H-Index II  35.0%   Medium  
🌟93. Restore IP Addresses
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        if(s.size()>12) return {};
        vector<string> res;
        //0-255
        restore(res, s, 4, "");
        return res;
    }
    void restore(vector<string> &res, string s, int k, string out){
        if(k==0){
            if(s.empty()) res.push_back(out);
        }
        for(int i=1; i<=3; i++){
            if(s.size()>=i && isvalid(s.substr(0, i))){
                if(k==1) restore(res, s.substr(i), k-1, out+s.substr(0,i));
                else restore(res, s.substr(i), k-1, out+s.substr(0,i)+'.');
            }
        }
    }
    bool isvalid(string num){
        if(num.empty() || num.size()>1&&num[0]=='0' || num.size()>3) return false;
        int res = stoi(num);
        return res>=0 && res<=255;
    }
};






近6个月tag 208（4天 hard也做）
********************************************************************************************************************************************
🌟273 Integer to English Words    23.2%   Hard    
🌟301 Remove Invalid Parentheses  36.6%   Hard
DFS的解法没看懂    
🌟15  3Sum 22.1%   Medium  
🌟158 Read N Characters Given Read4 II - Call multiple times24.3%   Hard    
🌟621 Task Scheduler 42.8%   Medium  
🌟31  Next Permutation    29.3%   Medium  
🌟67  Add Binary  35.9%   Easy    
🌟253 Meeting Rooms II 40.2%   Medium  
🌟121 Best Time to Buy and Sell Stock 44.5%   Easy    
🌟10  Regular Expression Matching 24.4%   Hard    
🌟426 Convert Binary Search Tree to Sorted Doubly Linked List38.8%   Medium  
🌟91  Decode Ways 21.0%   Medium  
🌟297 Serialize and Deserialize Binary Tree36.8%   Hard    
用BFS解题！
🌟215 Kth Largest Element in an Array 43.0%   Medium  
三种方法
🌟438 Find All Anagrams in a String   34.5%   Easy 
🌟143 Reorder List    28.2%   Medium  
🌟76  Minimum Window Substring    28.3%   Hard    
🌟689 Maximum Sum of 3 Non-Overlapping Subarrays  42.0%   Hard   
用DP 
🌟173 Binary Search Tree Iterator 44.7%   Medium  
🌟680 Valid Palindrome II 32.6%   Easy    
🌟！！！65  Valid Number    13.2%   Hard    
🌟560 Subarray Sum Equals K   40.1%   Medium  
🌟211 Add and Search Word - Data structure design 27.1%   Medium  
🌟56  Merge Intervals 33.2%   Medium  
🌟29  Divide Two Integers 15.7%   Medium  
🌟349 Intersection of Two Arrays  50.0%   Easy    
🌟124 Binary Tree Maximum Path Sum    28.0%   Hard  (vs 298 594)    
🌟277 Find the Celebrity 35.2%   Medium  
🌟278 First Bad Version   27.2%   Easy    
🌟236 Lowest Common Ancestor of a Binary Tree 32.2%   Medium  
🌟543 Diameter of Binary Tree 45.2%   Easy    
🌟98  Validate Binary Search Tree 24.5%   Medium  
🌟785 Is Graph Bipartite? 39.9%   Medium  
🌟！！！269 Alien Dictionary 27.8%   Hard    
🌟523 Continuous Subarray Sum 23.5%   Medium  
🌟283 Move Zeroes 52.4%   Easy    
🌟325 Maximum Size Subarray Sum Equals k 43.5%   Medium  
🌟314 Binary Tree Vertical Order Traversal 38.8%   Medium  
🌟238 Product of Array Except Self    51.8%   Medium  
🌟257 Binary Tree Paths 43.2%   Easy    
🌟125 Valid Palindrome    28.6%   Easy    
🌟199 Binary Tree Right Side View 44.5%   Medium  
🌟721 Accounts Merge  35.8%   Medium  
🌟！！！146 LRU Cache   21.6%   Hard   
用list和map 
🌟227 Basic Calculator II 31.2%   Medium  
🌟！！！282 Expression Add Operators    31.2%   Hard    
🌟88  Merge Sorted Array  33.4%   Easy    
🌟！！！336 Palindrome Pairs    28.1%   Hard    
🌟825 Friends Of Appropriate Ages 32.3%   Medium  
🌟133 Clone Graph 25.1%   Medium  
用BFS
🌟200 Number of Islands 38.1%   Medium 






🌟42  Trapping Rain Water 39.4%   Hard    
🌟791 Custom Sort String  59.4%   Medium  
🌟636 Exclusive Time of Functions 45.6%   Medium  
🌟350 Intersection of Two Arrays II 45.0%   Easy       
🌟246 Strobogrammatic Number 40.8%   Easy    
🌟20  Valid Parentheses   34.7%   Easy    
🌟304 Range Sum Query 2D - Immutable  29.0%   Medium  
🌟43  Multiply Strings 28.7%   Medium  
🌟17  Letter Combinations of a Phone Number 38.3%   Medium  
!!!432 All O`one Data Structure    28.2%   Hard    
🌟99  Recover Binary Search Tree  32.4%   Hard    
🌟247 Strobogrammatic Number II 42.0%   Medium  
🌟387 First Unique Character in a String  47.6%   Easy    
🌟446 Arithmetic Slices II - Subsequence  28.2%   Hard    
🌟50  Pow(x, n)   26.6%   Medium  
🌟23  Merge k Sorted Lists    30.4%   Hard    
🌟348 Design Tic-Tac-Toe 47.0%   Medium  
🌟57  Insert Interval 29.8%   Hard    
🌟300 Longest Increasing Subsequence  39.3%   Medium  
🌟!!!32  Longest Valid Parentheses 23.9%   Hard    
🌟139 Word Break 32.7%   Medium  
🌟33  Search in Rotated Sorted Array  32.1%   Medium  
！！！772 Basic Calculator III 41.5%   Hard    
🌟51  N-Queens    35.4%   Hard    
!!!317 Shortest Distance from All Buildings 35.4%   Hard    
🌟415 Add Strings 42.2%   Easy    
🌟157 Read N Characters Given Read4 28.1%   Easy    
！！！399 Evaluate Division   43.6%   Medium  
381 Insert Delete GetRandom O(1) - Duplicates allowed   30.2%   Hard    
493 Reverse Pairs   21.1%   Hard    
🌟491 Increasing Subsequences 39.8%   Medium  
🌟206 Reverse Linked List 49.6%   Easy    
🌟34  Find First and Last Position of Element in Sorted Array 32.1%   Medium  
🌟862 Shortest Subarray with Sum at Least K   18.9%   Hard    
🌟1   Two Sum 38.9%   Easy    
🌟270 Closest Binary Search Tree Value 41.8%   Easy    
🌟3   Longest Substring Without Repeating Characters 25.1%   Medium  
🌟239 Sliding Window Maximum  35.4%   Hard  
将index压入deque  
🌟252 Meeting Rooms 49.9%   Easy    
🌟674 Longest Continuous Increasing Subsequence   42.9%   Easy    
🌟305 Number of Islands II 40.3%   Hard    
每增加一个pos，用union find和周围四个位置的island合并，又可能增加一个岛之后，总数反而变少！
🌟490 The Maze 44.4%   Medium  
568 Maximum Vacation Days 36.0%   Hard    
🌟398 Random Pick Index   46.4%   Medium  
489 Robot Room Cleaner 52.3%   Hard    
🌟346 Moving Average from Data Stream 62.3%   Easy    
🌟430 Flatten a Multilevel Doubly Linked List 34.4%   Medium  
123 Best Time to Buy and Sell Stock III 31.5%   Hard    
🌟18  4Sum    28.4%   Medium  
🌟286 Walls and Gates 46.6%   Medium  









🌟692 Top K Frequent Words    42.6%   Medium  
161 One Edit Distance 31.3%   Medium  
🌟114 Flatten Binary Tree to Linked List 38.7%   Medium  
🌟449 Serialize and Deserialize BST   43.5%   Medium  
🌟824 Goat Latin  54.9%   Easy    
🌟127 Word Ladder 21.2%   Medium  
🌟210 Course Schedule II  31.8%   Medium  
🌟403 Frog Jump   33.7%   Hard    
🌟463 Island Perimeter    58.7%   Easy    
🌟694 Number of Distinct Islands 46.5%   Medium  
🌟567 Permutation in String   36.6%   Medium  
🌟360 Sort Transformed Array 45.5%   Medium  
🌟103 Binary Tree Zigzag Level Order Traversal    38.5%   Medium  
30  Substring with Concatenation of All Words   22.4%   Hard    
642 Design Search Autocomplete System 32.1%   Hard    
329 Longest Increasing Path in a Matrix 37.9%   Hard    
🌟138 Copy List with Random Pointer   25.6%   Medium  
716 Max Stack 37.6%   easy   
155 Min Stack


🌟209 Minimum Size Subarray Sum   33.2%   Medium  
🌟658 Find K Closest Elements 34.9%   Medium  
注意越界
🌟347 Top K Frequent Elements 51.0%   Medium  
🌟8   String to Integer (atoi)    14.1%   Medium  
🌟688 Knight Probability in Chessboard    40.8%   Medium  
416 Partition Equal Subset Sum  38.8%   Medium  
🌟673 Number of Longest Increasing Subsequence    32.1%   Medium  
🌟53  Maximum Subarray 41.3%   Easy    
128 Longest Consecutive Sequence    39.4%   Hard    
🌟708 Insert into a Cyclic Sorted List 23.7%   Medium  
🌟393 UTF-8 Validation    34.9%   Medium  
🌟678 Valid Parenthesis String    30.0%   Medium  
🌟21  Merge Two Sorted Lists  43.3%   Easy    
🌟494 Target Sum 44.0%   Medium  
4   Median of Two Sorted Arrays 24.0%   Hard    
🌟251 Flatten 2D Vector 42.2%   Medium  
🌟445 Add Two Numbers II  47.4%   Medium  
212 Word Search II  26.0%   Hard    
🌟13  Roman to Integer    49.6%   Easy    
🌟281 Zigzag Iterator 54.1%   Medium  
🌟78  Subsets 47.9%   Medium  
🌟886 Possible Bipartition    39.1%   Medium  
🌟266 Palindrome Permutation 58.7%   Easy 
class Solution {
public:
    bool canPermutePalindrome(string s) {
        set<char> m;
        for(char c:s){
            if(m.count(c)) m.erase(c);
            else m.insert(c);
        }
        return m.size()==0 || m.size()==1;
    }
};   
🌟162 Find Peak Element   39.8%   Medium  
🌟437 Path Sum III 40.5%   Easy    
🌟101 Symmetric Tree 41.5%   Easy    
🌟341 Flatten Nested List Iterator 44.6%   Medium  
🌟170 Two Sum III - Data structure design 27.9%   Easy    
🌟395 Longest Substring with At Least K Repeating Characters  36.4%   Medium
class Solution {
public:
    int longestSubstring(string s, int k) {
        unordered_map<char, int> m;
        for(char c:s) m[c]++;
        
        bool flag = true;
        int res = 0;
        int left = 0;
        for(int i=0; i<s.size(); i++){
            if(m[s[i]] < k) {
                res = max(res, longestSubstring(s.substr(left, i-left), k));
                flag = false;
                left = i+1;
            }
        }
        
        if(flag == true) return s.size();
        else return max(res, longestSubstring(s.substr(left, s.size() - left), k));
        
        
    }
};  
🌟75  Sort Colors 40.1%   Medium  
🌟844 Backspace String Compare    43.5%   Easy    
🌟26  Remove Duplicates from Sorted Array 37.9%   Easy    
🌟52  N-Queens II 48.8%   Hard    









81  Search in Rotated Sorted Array II   32.4%   Medium  
647 Palindromic Substrings  54.4%   Medium  
261 Graph Valid Tree 38.8%   Medium  
498 Diagonal Traverse   44.3%   Medium  
767 Reorganize String   38.9%   Medium  
208 Implement Trie (Prefix Tree)    33.8%   Medium  
260 Single Number III   54.6%   Medium  
116 Populating Next Right Pointers in Each Node 36.6%   Medium  
339 Nested List Weight Sum 65.0%   Easy    
622 Design Circular Queue   36.5%   Medium  
280 Wiggle Sort 59.4%   Medium  
315 Count of Smaller Numbers After Self 35.6%   Hard    
703 Kth Largest Element in a Stream 36.4%   Easy    
137 Single Number II    43.9%   Medium  
340 Longest Substring with At Most K Distinct Characters 38.4%   Hard    
207 Course Schedule 35.0%   Medium  
518 Coin Change 2   38.2%   Medium  
733 Flood Fill 48.1%   Easy    
392 Is Subsequence  45.1%   Medium  
153 Find Minimum in Rotated Sorted Array    41.7%   Medium  
111 Minimum Depth of Binary Tree    34.1%   Easy    
151 Reverse Words in a String   15.7%   Medium  
295 Find Median from Data Stream    31.8%   Hard    
109 Convert Sorted List to Binary Search Tree   37.5%   Medium  
140 Word Break II   25.4%   Hard    
681 Next Closest Time 41.1%   Medium  
129 Sum Root to Leaf Numbers    39.6%   Medium  
44  Wildcard Matching   21.6%   Hard    
371 Sum of Two Integers 50.9%   Easy    
84  Largest Rectangle in Histogram  28.8%   Hard    
896 Monotonic Array 54.8%   Easy    
46  Permutations 50.3%   Medium  
102 Binary Tree Level Order Traversal   44.8%   Medium  
176 Second Highest Salary   24.4%   Easy    
19  Remove Nth Node From End of List    33.6%   Medium  
113 Path Sum II 37.6%   Medium  
74  Search a 2D Matrix  34.4%   Medium  
73  Set Matrix Zeroes   37.7%   Medium  
94  Binary Tree Inorder Traversal 52.4%   Medium  
11  Container With Most Water   39.1%   Medium  
36  Valid Sudoku    39.6%   Medium  
24  Swap Nodes in Pairs 41.0%   Medium  
79  Word Search 29.0%   Medium  
39  Combination Sum 43.8%   Medium  
38  Count and Say   38.0%   Easy    
110 Balanced Binary Tree 39.3%   Easy    
160 Intersection of Two Linked Lists 30.7%   Easy    
242 Valid Anagram   49.0%   Easy    
122 Best Time to Buy and Sell Stock II  49.2%   Easy    
49  Group Anagrams  41.5%   Medium  
141 Linked List Cycle 34.6%   Easy    
66  Plus One    40.0%   Easy    
136 Single Number   57.1%   Easy    
5   Longest Palindromic Substring   25.6%   Medium  
7   Reverse Integer 24.4%   Easy    
2   Add Two Numbers 29.2%   Medium









****************************************************************************************************************************************
862（有负数，不能用slidingwindow）和 209（可以用sliding window和hash table，但是sliding window空间复杂度更好）的区别
****************************************************************************************************************************************
438 和 567 的区别 都可以用sliding window和比较两个vector做
****************************************************************************************************************************************
300 和 673
****************************************************************************************************************************************
377 322 518 416 494 区别
****************************************************************************************************************************************
416. 不可重复 顺序有关
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int num:nums) sum+=num;
        if(sum%2!=0) return false;
        
        int target = sum/2;
        vector<bool> dp(target+1, false);
        dp[0] = true;
        //不可重复 顺序有关
        for(auto num:nums){
            for(int i= target; i>=num; i--){
                dp[i] = dp[i]||dp[i-num]; 
            }
        }
        
        return dp[target];
    }
    
};

518. 顺序有关 可重复
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        //顺序有关 可重复
        vector<int> dp(amount+1, 0);
        dp[0] = 1;
        //dp[i] means number of combinations of i
        //dp[i] = dp[i] + dp[i-num]
        
        for(auto coin:coins){
            for(int i = coin; i<=amount; i++){
                dp[i] += dp[i-coin];
            }
        }
        
        return dp[amount];
    }
};


377. 可重复顺序无关
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        //可重复顺序无关
        vector<int> dp(target+1, 0);
        //dp[i] means the numer of combination ways of i
        dp[0] = 1;
        
        for(int i=0; i<=target; i++){
            for(int num:nums){
                if(i-num>=0) dp[i] += dp[i-num];
            }
        }
        
        return dp[target];
    }
    
};

322. 可重复，顺序可有关可无关
//solution 1
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //fewest number of coins
        //可重复
        //int res = coins.size()+1;
        vector<int> dp(amount+1, amount+1);
        dp[0] = 0;
        
        for(int coin:coins){
            for(int i=coin; i<=amount; i++){
                dp[i] = min(dp[i], dp[i-coin]+1);
            }
        }
        
        return dp[amount]==amount+1 ? -1 : dp[amount];
    }
};

//solution 2
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //fewest number of coins
        //可重复
        //int res = coins.size()+1;
        vector<int> dp(amount+1, amount+1); //!!! amount+1
        dp[0] = 0;
        
        for(int i=0; i<=amount; i++){
            for(int coin:coins){
                if(i-coin>=0) dp[i] = min(dp[i], dp[i-coin]+1);
            }
        }
        
        return dp[amount]==amount+1 ? -1 :dp[amount];
    }
};

494
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        //顺序有关
        unordered_map<int, int> dp;
        dp[0] = 1;
        
        for(int num:nums){
            unordered_map<int, int> t;
            for(auto a:dp){
                t[a.first + num] += a.second;
                t[a.first - num] += a.second;
            }
            dp = t;
        }
        
        return dp[S];
    }
};






