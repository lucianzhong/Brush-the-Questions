#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include <string>
#include<map>

using namespace std;


//https://github.com/gatieme/CodingInterviews




//28-字符串的排列
//从集合中依次选出每一个元素，作为排列的第一个元素，然后对剩余的元素进行全排列，如此递归处理，从而得到所有元素的全排列。
void Permutation(string str, int start, int end) {
	if (end <= 1) {
		return;
	}
	if (start == end) {
		for (int i = 0; i < end; i++) {
			cout << str[i];
			}
		cout << endl;
	}
	else {
	for (int j = 0; j < end; j++) {
		swap(str[j],str[start]);
		Permutation(str, j + 1, end);
		swap(str[j], str[start]);
	}
	}
}



//29-数组中出现次数超过一半的数字





//30-最小的K个数



//31-连续子数组的最大和 DP
int FindGreatestSumOfSubArray(vector<int> array) {
	if (array.empty()) {
		return 0;
	}	
	int max_sum=array[0];
	int temp_sum = array[0];
	for (int i = 1; i < array.size(); i++) {
		if (array[1] > 0) {
			temp_sum += array[i];
		}
		if (temp_sum > max_sum) {
			max_sum = temp_sum;
		}
	}
	return max_sum;
}



//32-从1到n整数中1出现的次数


//33-把数组排成最小的数
bool cmp(int a, int b) {
	string A = "";
	string B = "";
	A += to_string(a);
	A += to_string(b);

	B += to_string(b);
	B += to_string(a);
	return A > B;
}

string PrintMinNumString(vector<int> numbers) {
	string res = "";
	sort(numbers.begin(), numbers.end(), cmp);
	for (int i = 0; i < numbers.size(); i++) {
		res += numbers[i];
	}
	return res;
}


//34-丑数
//第一步：定义判断一个书是不是丑数的函数
//第二步：循环遍历



//35-第一个只出现一次的字符位置
int FirstNotRepeatingChar(string str) {
	map<char, int> mp;
	for (int i = 0; i < str.size(); i++) {
		mp[str[i]]++;
	}
	for (int i = 0; i < str.size(); i++) {
		if (mp[str[i]] == 1) {
			return i;
		}
	}
}


//36-数组中的逆序对
//冒泡的方法，每换一次，计数加一



//37-两个链表的第一个公共结点
//如果两个链表有公共节点，则它们的形状必然是一个Y字形。长链表先走，实现右对齐



//38-数字在排序数组中出现的次数
//a[a[i]]


//39-二叉树的深度
int TreeDepthRecursion(TreeNode *root) {
	if (root == NULL) {
		return 0;
	}

	while (root != NULL) {
		int depth_left = TreeDepthRecursion(root->left);
		int depth_right = TreeDepthRecursion(root->right);
		return max(depth_left,depth_right)+1;
	}
}

//39-平衡二叉树
bool IsBanlancedTree(TreeNode *root) {
	if (root == NULL)
	{
		return true;
	}

	int leftDepth = TreeDepthRecursion(root->left);
	int rightDepth = TreeDepthRecursion(root->right);

	if (fabs(leftDepth - rightDepth) <= 1)
	{
		return  IsBanlancedTree(root->left) && IsBanlancedTree(root->right);
	}
	else
	{
		return false;
	}

}



//40 数组中只出现一次的数字


//41 和为S的两个数字
vector<int> FindNumbersWithSum(vector<int> array, int sum) {
	vector<int> res;
	int start = 0;
	int end = array.size() - 1;
	int current_sum = array[start] + array[end];
	if (current_sum == sum){
		res.push_back(array[start]);
		res.push_back(array[end]);
	}
	else if (current_sum > sum) {
		end--;
	}
	else {
		start++;
	}
	return res;
}


//42-左旋转字符串 
//string.substr()
string LeftRotateString(string str, int n) {
	string New_string = str + str;
	string res = "";
	res = New_string.substr(n, str.size());
	return res;
}




//44-扑克牌顺子
bool IsContinuous(vector<int> numbers) {
	sort(numbers.begin(), numbers.end());
	int number_of_zero = 0;
	while (numbers[number_of_zero] == 0) {
		number_of_zero++;
	}
	for (int i = number_of_zero + 1; i < numbers.size(); i++) {
		if (numbers[i] == numbers[i - 1]) {
			return false;
		}		
		number_of_zero -= (numbers[i] - numbers[i - 1] - 1);
	}
	if (number_of_zero >= 0) {
		return true;
	}
	else {
		return false;
	}
}

//45-孩子们的游戏(圆圈中最后剩下的数)
//约瑟夫环




//46-求1+2+3+...+n
//短路运算 n && (sum(n-1))



//47-不用加减乘除做加法



//49-把字符串转换成整数

//50


//51-数组中重复的数字
//a[a[i]]




//












//55-字符流中第一个不重复的字符 
//hash table
class solution_55 {
public:	
	string s;
	char hash[256] = { 0 };

	void Insert(char ch) {
		s += ch;
		hash[ch]++;
	}


	char FirstAppearenceingOnce(string s) {
		int size = s.size();
		for (int i = 0; i < size; i++) {
			if (hash[s[i]] == 1) {
				return s[i];
			}
		}
		return '#';
	}
};




//56-链表中环的入口结点

ListNode * meetingNode(ListNode *head) {
	if (head == NULL) {
		return NULL;
	}
	ListNode *slow=head;
	ListNode *fast = slow->next;

	while (slow != NULL &&fast != NULL) {
		if (slow == fast) {
			return fast;
		}
		slow = slow->next;
		fast = fast->next;
		if (slow != fast) {
			fast = fast->next;
		}
	}
}


ListNode *EntryNodeOfLoop(ListNode *head) {
	ListNode * meeting_node = meetingNode(head);
	ListNode *p1 = meeting_node;
	int nodes_in_loop = 0;
	while (p1->next != meeting_node) {
		p1 = p1->next;
		nodes_in_loop++;
	}
		p1 = head;
	for (int i = 0; i<nodes_in_loop; i++) {
		p1 = p1->next;
	}
	//      移动p1，p2
	ListNode *p2 = head;
	while (p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}


//57-删除链表中重复的结点






//58-二叉树的下一个结点
//分情况讨论



//59-对称的二叉树
	
bool IsSymerical_Recursion(TreeNode *left,TreeNode *right) {
	if (left == NULL && right == NULL) {
		return true;
	}
	if (left == NULL || right == NULL) {
		return false;
	}
	if (right->value != left->value) {
		return false;
	}
	return IsSymerical_Recursion(left->left, right->right) && IsSymerical_Recursion(left->right,right->left);
}

bool IsSymerical(TreeNode *root) {
	if (root == NULL) {
		return true;
	}
	return IsSymerical_Recursion(root->left, root->right);
}




//60-把二叉树打印成多行  BFS

//61-按之字形顺序打印二叉树



//62 - 序列化二叉树


//63-二叉搜索树的第K个结点
void In_order(TreeNode *root,vector<int> res) {
	if (root != NULL) {
		In_order(root->left,res);
		//cout << root->value;
		res.push_back(root->value);
		In_order(root->right,res);
	}
}

int Kth_TreeNode(TreeNode *root,int k) {
	vector<int> res;
	//In_order(root, res);
	return res[k-1];
}


//64-数据流之中的中位数
//堆排序


//65-滑动窗口的最大值
int GetMax(const int a[],int size) {
	int max = a[0];
	for (int i = 0; i <= size; i++) {
		max = max > a[i] ? max : a[i];
	}
	return max;
}

vector<int> maxInWindows(const int A[], int n,int size) {
	vector<int> res;
	for (int i = 0; i < n - size; i++) {
		res.push_back(GetMax(A + i, size));
	}
	return res;
}






int main() {


	return 0;
}