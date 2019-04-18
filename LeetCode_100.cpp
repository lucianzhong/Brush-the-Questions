#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include <string>
#include<map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct ListNode {
	int value;
	ListNode *next;
	ListNode(int x) :value(x), next(NULL) {}
};

struct TreeNode {
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :value(x), left(NULL), right(NULL) {}
};



//01 Two Sum(E)
//先使用排序，然后取数值的头和尾，相加，如果大于sum就把尾向前移，如果小于sum，把头向前移动，直到等于sum



//02 Add two numbers(M)




// 03 longest substring without repeating characters(M)
int lengthOfLongestSubstring(string s) {
	int res = 0;
	map<char, int> mp;
	for (int i = 0; i < s.size(); i++) {
		mp[s[i]]++;
	}
	
	for (int i = 0; i < mp.size(); i++) {
		if (mp[s[i]] == 1) {
			res++;
		}
	}
	return res;
}



//04 median of two sorted arrays(H)
//将两个数组合并，并排序，然后去合并后数组的中位数



//05 longest palindromic substring(M)
//最大回文子串：分两种情况，回文子串长度为偶数和奇数：偶数的话直接向两边搜索，偶数的话和下一个数一起向两边搜索
void search_Palindrome(string s, int left, int right, int &start, int &maxLen) {
	while (left >= 0 && right <= s.size() && (s[left] == s[right])) {
		left--;
		right++;
	}
	if (maxLen < (right - left -1)) {
		start = left + 1;
		maxLen = right - left -1;
	}
}

string Longest_Palindrome(string s) {
	if (s.size() < 2) {
		return s;
	}
	int maxLEN = 0;
	int start = 0;	
	for (int i = 0; i < s.size()-1; i++) {
		search_Palindrome(s, i, i, start, maxLEN);
		search_Palindrome(s, i, i+1, start, maxLEN);
	}
	return s.substr(start, maxLEN);
}



//06  regular expression matching(H)
//正则表达式匹配：递归&分情况讨论


bool isMatch(string s, string p) {
	if (p.empty()) return s.empty();
	if (p.size() == 1) {
		return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
	}
	if (p[1] != '*') {
		if (s.empty()) return false;
		return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
	}
	while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
		if (isMatch(s, p.substr(2))) return true;
		s = s.substr(1);
	}
	return isMatch(s, p.substr(2));
}




//07container with most water(M) 
//我们可以用两个指针，一个指针left指向开始，另一个right指向结尾，如果left木板比right木板矮，那就让left指针右移；
//如果left木板比right木板高，那么right指针左移。为什么不是left木板比right木板高就右移left呢？因为木桶效应，盛水量多少，取决于那块最短的板
int maxArea(vector<int>& height) {
	int left = 0;
	int right = height.size();
	int res = 0;
	while (left < right) {
		res = max(res,min(height[left],height[right])*(left-right));
		height[left] < height[right] ? left++ : right--;
	}
	return res;
}



// three sum(M)

//two sum
//先排序
vector<int> twoSum(vector<int>& nums, int target, int start, int end) {
	sort(nums.begin(),nums.end());
	vector<int> res;
	int left = start;
	int right = end;
	while (left <= right) {
		if (nums[left] + nums[right] > target) {
			right--;
		}
		else if (nums[left] + nums[right] > target){
			left++;
		}
		else {
			res.push_back(nums[left]);
			res.push_back(nums[right]);			
		}
	}
	return res;
}



vector<int> three_Sum(vector<int>& nums, int target) {
	vector<int> res_three;
	vector<int> res_two_sum;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); i++) {
		int start = i;
		int end = nums.size() - 1;
		res_two_sum=(twoSum(nums, target - nums[i],start,end));
		if (!res_two_sum.empty()) {
			res_three.push_back(nums[i]);
			res_three.push_back(res_two_sum[0]);
			res_three.push_back(res_two_sum[1]);
			break;
		}
	}
	return res_three;
}


//09 letter combinations of a phone number
//建立字典：每个数字代表的字符串，然后递归：DFS
vector<string> letterCombinations(string digits) {
	if (digits.empty()) {
		return{};
	}

	vector<string> res = {""};
	string dict[] = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	for (int i = 0; i < digits.size(); i++) {
		vector<string> temp;
		string str = dict[digits[i] - '0'];
		for (int j = 0; i < str.size(); j++) {
			for (string s : res) {
				temp.push_back(s + str[j]);
			}
		}
		res = temp;
	}
	return res;
}

//10 remove Nth node from end of list(M)
//先找到第N个链表，快慢两个指针
void removeNthFromEnd(ListNode* head, int n) {
	ListNode *fast = head;;
	ListNode *slow = head;
	for (int i = 0; i <= n; i++) {
		fast = fast->next;
	}
	while (fast) {
		fast = fast->next;
		slow = slow->next;
	}
	slow->next = slow->next->next;
}



//11 valid parenthese 验证括号(E)
//使用栈，如果为左括号，就将其入栈，如果遇到右括号，就拿出栈顶元素比较

bool isValid(string s) {
	stack<char> parenthese;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			parenthese.push(s[i]);
		}
		else {
			if (parenthese.empty()) {
				return false;
			}
			if (s[i] == ')' && parenthese.top() != '(') return false;
			if (s[i] == '}' && parenthese.top() != '{') return false;
			if (s[i] == ']' && parenthese.top() != '[') return false;
			parenthese.pop();
		}
		
	}
	return parenthese.empty();
}



//Merge two sorted list(E)
//递归
ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) {
	ListNode * res=NULL;
	if (l1->value > l2->value) {
		res = l1;
		mergeTwoLists(l1->next, l2);	
	}
	else {
		res = l2;
		mergeTwoLists(l1,l2->next);
	}
	return res;
}



//13 generate parenthese(M)
class Solution_13 {
public:
	vector<string> result;
	vector<string> generateParenthesis(int n) {
		generate(0, 0, "", n);
		return result;
	}
	void generate(int left, int right, string s, int n) {
		if (right == n) {
			result.push_back(s);
		}
		else
		{
			if (left < n)
			{
				generate(left + 1, right, s + "(", n);
			}
			if (right < left)
			{
				generate(left, right + 1, s + ")", n);
			}
		}
	}
};



//merge k sorted list(H)
//ListNode* mergeTwoLists(ListNode *l1, ListNode *l2) 
//分治
ListNode *mergeKLists(vector<ListNode *> &lists) {
	int n = lists.size();
	while (n > 1) {
		int k = (n + 1) / 2;
		for (int i = 0; i < n / 2; i++) {
			mergeTwoLists(lists[i], lists[i+k]);
		}
		n = k;
	}
	return lists[0];
}


//15 longest valid parenteses(H)
//寻找最大子串问题：栈和DP
int longestValidParentheses(string s) {
	if (s.length() == 0)
		return 0;
	int res = 0;
	stack<int> st;
	st.push(-1);
	for (int i = 0; i<s.length(); ++i) {
		if (s[i] == '(') {
			st.push(i);
		}
		else {
			st.pop();
			if (!st.empty()) {
				res = max(res, i - st.top());
			}
			else {
				st.push(i);
			}
		}
	}

	return res;
}


//16 search in rotated sorted array(M)
//二分搜索，left,mid,right
int search(vector<int>& nums, int target) {
	int len = nums.size(), left = 0, right = len - 1;
	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] == target) return mid;
		if (nums[mid] >= nums[0])
		{
			if (target < nums[mid] && target >= nums[0]) right = mid - 1;
			else left = mid + 1;
		}
		else
		{
			if (target > nums[mid] && target < nums[0]) left = mid + 1;
			else right = mid - 1;
		}
	}
	return -1;
}



//17 find first and last postion of element in sorted array(m)
//两遍二分查找 binary search
vector<int> searchRange(vector<int> nums, int target) {
	vector<int> res;
	int ll = 0;
	int lr = nums.size() - 1;
	int mid = 0;
	while (ll <= lr) {
		mid = ll + (lr - ll) / 2;
		if (nums[mid] > target) {
			lr = mid - 1;
		}
		else {
			ll = mid + 1;
		}
	}


	int rl = 0;
	int rr = nums.size() - 1;
	while (rl <= rr) {
		int mid = rl + (rr - rl) / 2;
		if (nums[mid] <= target) {
			rl = mid + 1;
		}
		else {
			rr = mid - 1;
		}
	}

	if (ll > rr) {
		res[0] = ll;
		res[1] = rr;
	}
	return res;
}


// 18 search insert position (E)
//二分查找
int searchInsert(vector<int>nums, int target) {
	int ll = 0;
	int lr = nums.size() - 1;
	int mid = 0;
	while (ll <= lr) {
		mid = ll + (lr - ll) / 2;
		if (nums[mid] > target) {
			lr = mid - 1;
		}
		else if (nums[mid] < target) {
			ll = mid + 1;
		}
		else {
			return mid;
		}
	}
}

//19 combination sum(M)
//先排序再递归
vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
	vector<vector<int>> res;
	sort(candidates.begin(),candidates.end());

	for (int i = 0; i < candidates.size(); i++) {
		if (candidates[i] > target) {
			break;
		}
		else if (candidates[i] == target) {
			res.push_back({candidates[i]});
			continue;
		}
		
		vector<int> remaining = vector<int>(candidates.begin() + 1, candidates.end());
		vector<vector<int>> tmp=combinationSum(remaining, target - candidates[i]);
		for (auto a : tmp) {
			a.insert(a.begin(), candidates[i]);
			res.push_back(a);
		}
	}
	return res;
}


//trapping rain water(H)
//1. 从左往右扫描一遍，对于每一个坐标，求取左边最大值。
//2. 从右往左扫描一遍，对于每一个坐标，求最大右值。
//3. 再扫描一遍，求取容积并加和。volume[i] = [min(left[i], right[i]) - A[i]] * 1，这里的1是宽度，如果the width of each bar is 2, 那就要乘以2了
//front & back,   start &end
int trap(vector<int> A) {
	int res = 0;
	int max;
	int i = 0;
	int j = 0;
	vector<int> left;
	vector<int> right;

	for ( i = 0, max = A.front(),left[0]=A.front(); i < A.size(); i++) {
		if (A[i] < max) {
			left[i] = max;
		}
		else {
			left[i] = A[i];
			max = A[i];
		}
	}

	for (j = A.size()-2,max=A.back(),right.front()=A.back(); j >= 0; j--) {
		if (A[i] < max) {
			right[i] = max;
		}
		else {
			right[i] = A[i];
			max = A[i];
		}
	}

	int volume = 0;
	for (int i = 0; i < A.size() - 2; i++) {
		volume = min(left[i], right[i]) - A[i];
		if (volume > 0) {
			volume += volume;
		}

	}
	return volume;
}


//21 permutation (M)
//全排序

void permutation_DFS(vector<int> &num, int start, vector<vector<int>> res) {
	if (start >= num.size()) {
		res.push_back(num);
	}
	for (int i = start; i < num.size(); i++) {
		swap(num[start], num[i]);
		permutation_DFS(num, start + 1, res);
		swap(num[start], num[i]);
	}
}

vector<vector<int>> Permutation(vector<int>&num) {
	vector<vector<int>>res;
	permutation_DFS(num,0,res);
	return res;
}


//22 Rotate image(M)
//先沿对角线旋转，在沿x轴旋转
void rotate(vector<vector<int> > &matrix) {
  // Start typing your C/C++ solution below  
   // DO NOT write int main() function  
 int len = matrix[0].size();
  for (int i = 0; i<len - 1; i++) {		
	  for (int j = 0; j<len - i; j++) {
		         swap(matrix[i][j], matrix[len - 1 - j][len - 1 - i]);
		       }
	 }

   for (int i = 0; i<len / 2; i++) {
		        for (int j = 0; j<len; j++) {
			          swap(matrix[i][j], matrix[len - i - 1][j]);
			        }
		 }	
}



//23 Group anagrams(M)
//错位词就是两个字符串中字母出现的次数都一样，只是位置不同，比如abc，bac, cba等它们就互为错位词
//把错位词，排序后都是一样的，使用map
vector<vector<string>> groupAnagrams(vector<string>& strs) {
	vector<vector<string>> res;
	unordered_map<string, vector<string>> m;
	for (string sr : strs) {
		string temp = sr;
		sort(sr.begin(),sr.end());
		m[sr].push_back(sr);
	}

	for (auto a : m) {
		res.push_back(a.second);
	}
	return res;
}


//24 maximum subarray(E)
int maxSubArray(vector<int>& nums) {
	int res = INT_MIN, curSum = 0;
	for (int num : nums) {
		curSum = max(curSum + num, num);
		res = max(res, curSum);
	}
	return res;
}

//25 Jump game(M)
//greedy  or DP
bool canJump(vector<int>& nums) {
	
	int n = nums.size(), reach = 0;
	for (int i = 0; i < n; ++i) {
		if (i > reach || reach >= n - 1) break;
		reach = max(reach, i + nums[i]);
	}
	return reach >= n - 1;
}

//26 Merge intervals (M)


struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		int n = intervals.size();
		vector<Interval> res;
		vector<int> starts, ends;
		for (int i = 0; i < n; ++i) {
			starts.push_back(intervals[i].start);
			ends.push_back(intervals[i].end);
		}
		sort(starts.begin(), starts.end());
		sort(ends.begin(), ends.end());
		for (int i = 0, j = 0; i < n; ++i) {
			if (i == n - 1 || starts[i + 1] > ends[i]) {
				res.push_back(Interval(starts[j], ends[i]));
				j = i + 1;
			}
		}
		return res;
	}
};



//26 Flatten binary tree to linked list(M)
//将二叉树转换成链表
//这道题要求把二叉树展开成链表，根据展开后形成的链表的顺序分析出是使用先序遍历，那么只要是数的遍历就有递归和非递归的两种方法来求解，这里我们也用两种方法来求解。首先来看递归版本的，思路是先利用DFS的思路找到最左子节点，然后回到其父节点，把其父节点和右子节点断开，将原左子结点连上父节点的右子节点上，然后再把原右子节点连到新右子节点的右子节点上，然后再回到上一父节点做相同操作
// Recursion
class Solution_26 {
public:
	void flatten(TreeNode *root) {
		if (!root) return;
		if (root->left) flatten(root->left);
		if (root->right) flatten(root->right);
		TreeNode *tmp = root->right;
		root->right = root->left;
		root->left = NULL;
		while (root->right) root = root->right;
		root->right = tmp;
	}
};



//28  Unique path(M)
int uniquePaths(int m, int n) {
	vector<int>DP;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			DP[j] += DP[j - 1];
		}
	}
	return DP[n - 1];
}


//29 minimum path sum(M)
int minPathSum(vector<vector<int> > &grid) {
	int m = grid.size();
	int n = grid[0].size();
	vector<vector<int>> dp;
	dp[0][0] = grid[0][0];
	for (int i = 1; i < m; ++i) dp[i][0] = grid[i][0] + dp[i - 1][0];
	for (int i = 1; i < n; ++i) dp[0][i] = grid[0][i] + dp[0][i - 1];
	for (int i = 1; i < m; ++i) {
		for (int j = 1; j < n; ++j) {
			dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[m - 1][n - 1];
}


//30 climbing stairs(M)
int climbStairsRecur(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;
	return climbStairsRecur(n - 1) + climbStairsRecur(n - 2);
}


//31 Edit distance (H)
//DP
class Solution_31 {
public:
	int minDistance(string word1, string word2) {
		int n1 = word1.size(), n2 = word2.size();
		vector<vector<int>> dp;		
		for (int i = 0; i <= n1; ++i) dp[i][0] = i;
		for (int i = 0; i <= n2; ++i) dp[0][i] = i;
		for (int i = 1; i <= n1; ++i) {
			for (int j = 1; j <= n2; ++j) {
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
				}
			}
		}
		return dp[n1][n2];
	}
};


//32 sort colours(M)
//count[A[i]]
void sortColors(int A[], int n) {
	int count[2] = {};
	for (int i = 0; i < n; i++) {
		count[A[i]]++;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < count[A[i]]; j++) {
			A[j] =i;
		}		
	}
}


//33 minimum window substring (H)
//下面是具体的步骤啦：

//-我们最开始先扫描一遍T，把对应的字符及其出现的次数存到HashMap中。

//- 然后开始遍历S，就把遍历到的字母对应的HashMap中的value减一，如果减1后仍大于等于0，cnt自增1。

//- 如果cnt等于T串长度时，开始循环，纪录一个字串并更新最小字串值。然后将子窗口的左边界向右移，如果某个移除掉的字母是T串中不可缺少的字母，那么cnt自减1，表示此时T串并没有完全匹配。
class Solution_33 {
public:
	string minWindow(string s, string t) {
		string res = "";
		unordered_map<char, int> letterCnt;
		int left = 0, cnt = 0, minLen = INT_MAX;
		for (char c : t) ++letterCnt[c];
		for (int i = 0; i < s.size(); ++i) {
			if (--letterCnt[s[i]] >= 0) ++cnt;
			while (cnt == t.size()) {
				if (minLen > i - left + 1) {
					minLen = i - left + 1;
					res = s.substr(left, minLen);
				}
				if (++letterCnt[s[left]] > 0) --cnt;
				++left;
			}
		}
		return res;
	}
};

//34 subsets (M)
//子集合
// Non-recursion
class Solution_34 {
public:
	vector<vector<int> > subsets(vector<int> &S) {
		vector<vector<int> > res(1);
		sort(S.begin(), S.end());
		for (int i = 0; i < S.size(); ++i) {
			int size = res.size();
			for (int j = 0; j < size; ++j) {
				res.push_back(res[j]);
				res.back().push_back(S[i]);
			}
		}
		return res;
	}
};



//35 word search(M)
//如果二维数组board的当前字符和目标字符串word对应的字符相等，则对其上下左右四个邻字符分别调用DFS的递归函数，只要有一个返回true，
//那么就表示可以找到对应的字符串，否则就不能找到
class Solution_35 {
public:
	bool exist(vector<vector<char>>& board, string word) {
		if (board.empty() || board[0].empty()) return false;
		int m = board.size(), n = board[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (search(board, word, 0, i, j, visited)) return true;
			}
		}
		return false;
	}
	bool search(vector<vector<char>>& board, string word, int idx, int i, int j, vector<vector<bool>>& visited) {
		if (idx == word.size()) return true;
		int m = board.size(), n = board[0].size();
		if (i < 0 || j < 0 || i >= m || j >= n || visited[i][j] || board[i][j] != word[idx]) return false;
		visited[i][j] = true;
		bool res = search(board, word, idx + 1, i - 1, j, visited)
			|| search(board, word, idx + 1, i + 1, j, visited)
			|| search(board, word, idx + 1, i, j - 1, visited)
			|| search(board, word, idx + 1, i, j + 1, visited);
		visited[i][j] = false;
		return res;
	}
};

// 36 largest rectangle in histogram (H)
//37 
//https://siddontang.gitbooks.io/leetcode-solution/content/array/largest_rectangle_in_histogram.html




// 38 Binary tree inorder traverse (M)
void inorderTraversal(TreeNode *root, vector<int> res) {
	if (root != NULL) {
		inorderTraversal(root->left, res);
		cout << root->value;
		res.push_back(root->value);
		inorderTraversal(root->right, res);
	}
}

vector<int> Inorder(TreeNode *root) {
	vector<int> res;
	inorderTraversal(root, res);
	return res;
}



//39 unique binary search tree (M)
//可以得出Count的递推公式为,Count[i] = ∑ Count[0...k] * [k + 1....i]     0 <= k<i - 1,问题至此划归为一维动态规划。

int numTrees(int n) {
	vector<int> count(n + 1, 0);
    count[0] = 1;
    count[1] = 1;
	for (int i = 2; i <= n; i++){
	 for (int j = 0; j<i; j++) {
		count[i] += count[j] * count[i - j - 1];
		  }
	 }
 return count[n];
}


//40 validate binary search tree (M)
// 解法1：递归判断数值的大小：左、右、根 
//解法2：中序遍历，然后判断数值的递增
bool IsValidBST(TreeNode *root) {
	vector<int> tmp= Inorder(root);
	for (vector<int>::iterator it = tmp.begin(); it<tmp.end()-1; it++) {
		if (*it >= *(it + 1)) {
			return false;
		}
	}
}


//41 same tree (E)
bool Is_SameTree(TreeNode *p, TreeNode *q) {
	if (p == NULL && q == NULL) {
		return true;
	}
	if ((p == NULL && q != NULL) || (p != NULL && q == NULL) || p->value != q->value) {
		return false;
	}

	return Is_SameTree(p->left, p->left) && Is_SameTree(p->right, p->right);
}



//42 Symmetric tree(E)
bool IsSymmetric_recursive(TreeNode *left, TreeNode *right) {
	if (left && right) {
		return true;
	}
	if ((left && !right) || (!left &&right) || (left->value != right->value)) {
		return false;
	}
	return IsSymmetric_recursive(left->left, right->right) && IsSymmetric_recursive(left->right, right->left);
}


bool IsSymmetric(TreeNode *root) {
	if (root == NULL) {
		return true;
	}
	return IsSymmetric_recursive(root->left,root->right);
}


//43 Binary tree level order traverse (M)
void LevelTraverse(TreeNode *root) {
	if (root == NULL) {
		return;
	}
	queue<TreeNode *>res;
	res.push(root);
	if (!res.empty()) {
		TreeNode *tmp = res.front();
		cout << tmp->value;
		res.pop();
		if (root->left != NULL) {
			res.push(root->left);
		}
		if (root->right != NULL) {
			res.push(root->right);
		}
	}
}


//44 Maximum depth of binary Tree(E)
int maxDepth(TreeNode* root) {
	if (root == NULL) {
		return 0;
	}
	return 1 + max((maxDepth(root->right)), maxDepth(root->left));
}


// 45 Construct binary tree from pre-order and in-order traverse (M)



//46 Best time to buy and sell stock (M)
int maxProfit(vector<int>& prices) {
	int res = 0;
		int buy = INT_MIN;
	for (int price : prices) {
		buy = min(buy,price);
		res = max(res,(price-buy));
	}
	return res;
}

// 47 Binary tree maximum path sum (H)
//在递归函数中，如果当前结点不存在，那么直接返回0。否则就分别对其左右子节点调用递归函数，由于路径和有可能为负数，
//而我们当然不希望加上负的路径和，所以我们和0相比，取较大的那个，就是要么不加，加就要加正数。然后我们来更新全局最大值结果res，
//就是以左子结点为终点的最大path之和加上以右子结点为终点的最大path之和，还要加上当前结点值，这样就组成了一个条完整的路径。
//而我们返回值是取left和right中的较大值加上当前结点值，因为我们返回值的定义是以当前结点为终点的path之和，
//所以只能取left和right中较大的那个值，而不是两个都要

int Max_PathSum_recursive(TreeNode *root, int res) {
	if (root == NULL) {
		res=0;
		return res;
	}
	int left = max(Max_PathSum_recursive(root->left, res), 0);
	int right = max(Max_PathSum_recursive(root->right, res), 0);
	res = max((left + right + root->value), res);
	return max(left, right) + root->value;
}


int Max_PathSum(TreeNode *root) {
	int res=INT_MIN;
	Max_PathSum_recursive(root,res);
	return res;
}



//48 Largest consecutive sequence (H)
//对数组中的每一个元素进行：在set中查找该value,然后删除value,去该数的前一个数pre=value-1,和后一个数behind=value+1;
//在数组中查找，然后res=behind-pre+1;再取每个res中的最大res;
int longestConsecutive(vector<int>& nums) {
	int res = 0;
	unordered_set<int> tmp(nums.begin(),nums.end());
	for (int val : tmp) {
		if (!tmp.count(val)) {
			continue;
		}		
		tmp.erase(val);
		int pre = val - 1;
		int beh = val + 1;
		while (tmp.count(pre)) {
			tmp.erase(pre);
			pre--;
		}
		while (tmp.count(beh)) {
			tmp.erase(beh);
			beh++;
		}
		res = max(res, (beh - pre + 1));
	}
	return res;
}


//49 Single number (E)
//异或
class Solution_49 {
public:
	int singleNumber(vector<int>& nums) {
		int res = 0;
		for (auto num : nums) res ^= num;
		return res;
	}
};



// 50 Word break (M)
class Solution_50 {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
		vector<bool> dp(s.size() + 1);
		dp[0] = true;
		for (int i = 0; i < dp.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (dp[j] && wordSet.count(s.substr(j, i - j))) {
					dp[i] = true;
					break;
				}
			}
		}
		return dp.back();
	}
};



//51 Linked list cycle (E)
//这道题就是判断一个链表是否存在环
bool hasCycle(ListNode *head) {
	if (!head || !head->next) {
		return false;
	}
	ListNode *fast = head;
	ListNode *slow = head;
	while (fast->next != NULL && fast->next->next != NULL) {
		fast = fast->next->next;
		slow = slow->next;
		if (slow->value == fast->value) {
			return true;
		}
	}
}


// 52 Linked list cycle II (M)
ListNode *detectCycle(ListNode *head) {
	if ( head && head->next) {
		return false;
	}
	ListNode *fast = head;
	ListNode *slow = head;
	while (fast->next != NULL && fast->next->next != NULL && slow->value!=fast->value) {
		fast = fast->next->next;
		slow = slow->next;		
	}
	ListNode *tmp = head;
	while (tmp->value != fast->value) {
		tmp = tmp->next;
		fast = fast->next;
	}
	return tmp;
}




// 53 LRU cache (M)


//54 sort list(M)
//quick_sort
int partition(vector<TreeNode *>num, int left, int right) {
	int k = left;
	TreeNode * pivot = num[right];
	for (int i = left; i < right; i++) {
		if (num[i]->value < pivot->value) {
			swap(num[i]->value, num[k++]->value);
		}
	}
	swap(num[k]->value, num[right]->value);
	return k;
}

void Qucik_sort(vector<TreeNode *> num,int left, int right) {
	while (left < right) {
		int pivot_index = partition(num,left,right);
		Qucik_sort(num,left,pivot_index-1);
		Qucik_sort(num,pivot_index+1,right);
	}
}


//55 Maximum product subarray (M)
//DP:两个数值，一个保存最大值，一个保存，最小值

int maxProduct(vector<int>& nums) {
	int res = nums[0];
	int length = nums.size();
	vector<int> f_max(length,0);
	vector<int> f_min(length,0);
	f_max[0] = f_min[0] = nums[0];

	for (int i = 1; i < length; i++) {
		f_max[i] = max(max(f_max[i - 1] * nums[i], f_min[i - 1] * nums[i]), nums[i]);
		f_min[i]= min(min(f_max[i - 1] * nums[i], f_min[i - 1] * nums[i]), nums[i]);
		res = max(res,f_max[i]);
	}
	return res;
}


// 56 Min stack (E)
int Min_stack(stack<int> s) {
	stack<int> s1;
	int res =s.top();
	while (!s.empty()) {
		s.pop();
		if (res < s.top()) {
			res = s.top();
		}
	}
	return res;
}


// 57  Intersection of two linked lists (M)

int Get_length_of_list(ListNode *head) {
	int length = 0;
	while (!head) {
		length++;
		head = head->next;
	}
	return length;
}

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	int length_A = Get_length_of_list(headA);
	int length_B = Get_length_of_list(headB);

	if (length_A < length_B) {
		for (int i = 0; i < length_B - length_A; i++) {
			headB = headB->next;
		}
	}

	if (length_A > length_B) {
		for (int i = 0; i < length_A - length_B; i++) {
			headA = headA->next;
		}
	}

	while (headA && headB && headA!=headB) {
		headA = headA->next;
		headB = headB->next;
	}
	return headA == headB ? headA : NULL;
}


// 58 Majority element (E)
int majorityElement(vector<int> &num) {
	unordered_map<int, int> count;
	int res = 0;
	for (int i = 0; i < num.size(); i++) {
		count[num[i]]++;
	}
	for (unordered_map<int, int>::iterator iter = count.begin(); iter != count.end(); iter++) {
		if (iter->second > num.size() / 2) {
			res = iter->first;
		}
	}
	return res;
}


// 59 House robber (E)
int rob(vector<int> &num) {
	vector<int> res = {num[0],max(num[0],num[1])};
	for (int i = 2; i < num.size(); i++) {
		res.push_back(max((num[i]+res[i-2]),num[i]));
	}
	return res.back();
}

// 60 Number of islands (M)

void Number_of_Islands_DFS(vector<vector<char>> &grid, vector<vector<bool>> visited, int x, int y) {
	if (x < 0 || x >= grid.size()) return;
	if (y < 0 || y >= grid[0].size()) return;
	if (grid[x][y] != '1' || visited[x][y]) return;
	visited[x][y] = true;
	Number_of_Islands_DFS(grid, visited, x - 1, y);
	Number_of_Islands_DFS(grid, visited, x + 1, y);
	Number_of_Islands_DFS(grid, visited, x, y - 1);
	Number_of_Islands_DFS(grid, visited, x, y + 1);
}

int Number_of_Islands(vector<vector<char>> &grid) {
	int res = 0;
	int row = grid.size();
	int colume = grid[0].size();
	vector<vector<bool>> visited(row,vector<bool>(colume,false));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < colume; j++) {
			if (!visited[i][j] &&grid[i][j]=='1') {
				Number_of_Islands_DFS(grid, visited, i, j);
				res++;
			}
		}
	}
	return res;
}


// 61 Reverse linked list (E)
ListNode * reverseList(ListNode *head) {
	stack<ListNode *> st;
	ListNode *res=NULL;
	while (head) {
		st.push(head);
		head = head->next;
	}

	res = st.top();
	while (!st.empty()) {
		st.pop();
		res->next = st.top();
	}
	return res;
}



// 62 course schedule (M)
//这个问题等价于判定一个有向图中是否存在环。如果存在环，就不存在拓扑序，也就是不可能上完所有的课程
//Topological Sort via DFS 拓扑排序可以用深度优先搜索来实现。
// Topological sort could also be done via BFS 拓扑排序可以用广度优先搜索来实现。
//http://www.cnblogs.com/grandyang/p/4484571.html


//63 Implement trie(Prefix tree)  (M)
// http://www.cnblogs.com/grandyang/p/4491665.html




//64 Kth largest element in an array (M)
int findKthLargest(vector<int>& nums, int k) {
	sort(nums.begin(), nums.end());
	return *(nums.begin() + k);
}




//65 Maximal square(M)

class Solution_65 {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.empty() || matrix[0].empty()) return 0;
		int m = matrix.size(), n = matrix[0].size(), res = 0;
		vector<vector<int>> dp(m, vector<int>(n, 0));
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == 0 || j == 0) dp[i][j] = matrix[i][j] - '0';
				else if (matrix[i][j] == '1') {
					dp[i][j] = min(dp[i - 1][j - 1], min(dp[i][j - 1], dp[i - 1][j])) + 1;
				}
				res = max(res, dp[i][j]);
			}
		}
		return res * res;
	}
};



//66 Invert binary tree (E)
TreeNode* invertTree(TreeNode* root) {
	if (root == NULL) {
		return NULL;
	}
	swap(root->left, root->right);
	invertTree(root->left);
	invertTree(root->right);
}

//67 Palindrome linked list (E)
//回文链表
bool isPalindrome(ListNode* head) {
	ListNode *slow=head;
	ListNode *fast=head;
	stack<int> front_half;
	while (fast && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
		front_half.push(slow->value);
	}
	while (slow) {
		slow = slow->next;
		int tmp = front_half.top();
		front_half.pop();
		if (slow->value != tmp) {			
			return false;
		}
	}
	return true;
}


// 68 Lowest common ancestor of binary tree (M)
//二叉树的最小共同父节点
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (!root || p == root || q == root) {
		return root;
	}
	TreeNode *left = lowestCommonAncestor(root->left,p,q);
	TreeNode *right = lowestCommonAncestor(root->right,p,q);
	if (left && right) {
		return root;
	}
	return left ? left : right;
}


//69 Product of array except self (M)
//前面所有数乘以后面所有数
vector<int> productExceptSelf(vector<int>& nums) {
	int n = nums.size();
	vector<int> res(n, 1);
	vector<int> behind(n, 1);
	vector<int> forward(n, 1);
	for (int i = 0; i < n - 1; i++) {
		forward[i + 1] = forward[i] * nums[i];
	}
	for (int i = n - 1; i > 0; --i) {
		behind[i - 1] = behind[i] * nums[i];
	}
	for (int i = 0; i < n; ++i) {
		res[i] = forward[i] * behind[i];
	}
	return res;
}

//70 Sliding window maximum (H)
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> res;
	deque<int> q;
	for (int i = 0; i < n; ++i) {
		if (!q.empty() && q.front() == i - k)         //窗口向右移动了，需要pop最左边的元素下标
			q.pop_front();
		while (!q.empty() && nums[q.back()] < nums[i]) //把最大值向前移动到双向队列的队头
			q.pop_back();
		q.push_back(i);                             //入队下标值i
		if (i >= k - 1)
			res.push_back(nums[q.front()]);         //从i=k-1开始，需要存入最大值，此时开始存入队头到res
	}
	return res;
}

/*
class Solution_70 {
	public int[] maxSlidingWindow(int[] nums, int k) {
		if (nums == null || nums.length == 0) return new int[0];
		LinkedList<Integer> deque = new LinkedList<Integer>();
		int[] res = new int[nums.length + 1 - k];
		for (int i = 0; i < nums.length; i++) {
			// 每当新数进来时，如果发现队列头部的数的下标，是窗口最左边数的下标，则扔掉
			if (!deque.isEmpty() && deque.peekFirst() == i - k) deque.poll();
			// 把队列尾部所有比新数小的都扔掉，保证队列是降序的
			while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) deque.removeLast();
			// 加入新数
			deque.offerLast(i);
			// 队列头部就是该窗口内第一大的
			if ((i + 1) >= k) res[i + 1 - k] = nums[deque.peek()];
		}
		return res;
	}
}
*/


//71 Search a 2D matrix II (M)
bool searchMatrix(vector<vector<int> > &matrix, int target) {
	int colume = matrix.size();
	int row = matrix[0].size();
	int y = 0;
	int x = colume;
	if (matrix[colume][y] > target) {
		colume--;
	}
	else if (matrix[colume][y] < target) {
		y++;
	}
	else {
		return true;
	}
	if (x < 0 || y >= matrix[0].size()) {
		return false;
	}

}




//72 Meeting rooms II (M)
struct intervals {
	int start;
	int end;
};

int minMeetingRooms(vector<Interval>& intervals) {
	vector<int>starts;
	vector<int>ends;
	for (auto x : intervals) {
		starts.push_back(x.start);
		ends.push_back(x.end);
	}
	sort(starts.begin(),starts.end());
	sort(ends.begin(),ends.end());

	int end_index=0;
	int res = 0;
	for (int i = 0; i < starts.size(); i++) {
		if (starts[i] < ends[end_index]) {
			res++;
		}
		else {
			end_index++;
		}
	}
	return res;
}


//73 Perfect squares (M)
int numSquares(int n) {
	vector<int> dp(n+1,INT_MAX);
	dp[0] = 0;
	for (int a = 0; a <= n; a++) {
		for (int b = 0; a + b*b <= n; b++) {
			dp[a + b*b] = min(dp[a + b*b], dp[a]+1);
		}
	}
	return dp.back();
}



//74 Move zeroes (M)
void moveZeroes(vector<int>& nums) {
	for (int i = 0, j = nums.size() - 1; i < nums.size(); i++) {
		if (nums[i] == 0) {
			swap(nums[i], nums[j--]);
		}
	}
}



//75 Find the Duplicate Number 寻找重复数(M)
// 二分搜索
int findDuplicate(vector<int>& nums) {
	int left = 0;
	int right = nums.size() - 1;
	int cnt = 0;
	while (left < right) {
		int mid = left + (right - left) *0.5;
		for (auto a : nums) {
			if (a <= mid) {
				cnt++;
			}
		}

		if (cnt > mid) {
			right = mid;
		}
		else {
			left = mid + 1;
		}
		
	}
	return left;
}


//76 Seriallize and deserialize binary tree (H)
// http://www.cnblogs.com/grandyang/p/4913869.html







// 77 Longest increasing subsequence (M)
class Solution_77 {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> dp(nums.size(), 1);
		int res = 0;
		for (int i = 0; i < nums.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (nums[i] > nums[j]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
			res = max(res, dp[i]);
		}
		return res;
	}
};




//78 Remove invalid parentheses (H)









//79  Best time to buy and sell stock with cooldown (M)




// 80 Burst balloons (M)




// 81 Coin change (M)



//82 House robber II (M)





//83 Counting bits (M)




//84 Top k frequent elements (M)




// 85 Decode string (M)





//86 Queue reconstruction by height (M)




//87 Partition equal subset sum (M)




// 88 Path sum III (E)




// 89 Find all anagrams in a string (E)



//90 Find all numbers disappeared in an array (E)





//91 Hamming distance (E)





// 92 Target sum (M)




// 93 Convert BST to greater tree (E)



// 94 Diameter of binary tree (E)


//95 Subarray sum equals to k (M)





//96 subtree of another tree (E)





// 97











int main() {


	return 0;
}