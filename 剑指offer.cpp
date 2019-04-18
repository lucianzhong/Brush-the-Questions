#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include <string>
#include<map>

using namespace std;


//https://github.com/gatieme/CodingInterviews





//3
//在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，
//判断数组中是否含有该整数。
bool Find(vector<vector<int> > array, int target) {
	int row = array.size();
	int colum = array[0].size();
	bool found = false;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < colum; j++) {
			if (found == false && array[i][j] == target) {
				found = true;
			}
		}
	}
	return found;
}


//4
//请实现一个函数，将一个字符串中的空格替换成“%20”。 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy
void replaceSpace(char *str, int length) {
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (str[i] == ' ') {
			count++;
		}
	}	
	int len_new = length + count;	
	int index_old = length - 1;
	int index_new = len_new - 1;
	while (index_old >= 0 && index_new >= 0) {
		if (str[index_old] == ' ') {
			str[index_new--] = '0';
			str[index_new--] = '2';
			str[index_new--] = '%';
			index_old--;
		}
		else {
			str[index_new--] = str[index_old--];
		}
	}
	str[index_new] = '\0';
}






//5
//输入一个链表，从尾到头打印链表每个节点的值。(stack)
struct ListNode {
	int value;
	ListNode *next;
    ListNode(int x):value(x),next(NULL){}
};

void printListFromTailToHead( ListNode* head) {
	stack<int> reverse_list;
	while (head->next != NULL) {
		reverse_list.push(head->value);
		head = head->next;
	}

	while (!reverse_list.empty()) {
				cout << reverse_list.top() << endl;
				reverse_list.pop();
	}
}




//6
//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字
struct TreeNode {
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):value(x),left(NULL),right(NULL){}
};


void reConstructBinaryTree(vector<int> pre, vector<int> in) {
	int length_pre = pre.size();
	int length_in = in.size();

	vector<int> pre_left, pre_right, in_left, in_right;
	int root_index_pre = 0;
	int root_index_in = 0;
	for (int i = 0; i < length_in;i++) {
		if (in[i]==pre[root_index_pre]) {
			root_index_in = i;
			break;
		}	
	}


	for (int i = 0; i < root_index_in - 1;i++ ) {
		in_left[i] = in[i];
	}
			
	for (int i = 0; i < length_in-1-root_index_in; i++) {
		in_right[i] = in[i+root_index_in+1];
	}


	for (int i = 0; i < root_index_in; i++) {
		pre_left[i] = pre[1 + i];
	}

	for (int i = 0; i<length_in - 1 - root_index_in; i++) {
		pre_right[i] = pre[1+i+ root_index_in];
	}
	reConstructBinaryTree(pre_left, in_left);
	reConstructBinaryTree(pre_right, in_left);

}



//7 用两个栈实现队列
class Solution_7
{
public:
	void push(int node)
	{
		stackIn.push(node);
	}

	int pop()
	{
		int node = -1;

		//  两个栈都是NULL的时候，整个队列为空
		if (this->empty() == true)
		{
			

			return -1;
		}
		else
		{
			//  否则队列中有元素
			//  此时分两种情况，
			//  当输出栈不为空的时候, 直接将输出栈中元素弹出即可
			//  当输出栈为NULL, 但是输入栈不为空的时候，需要将输入栈的元素全部倒入输出栈中

			if (stackOut.empty() == true)     //  此时输出栈为空, 输入栈必不为空
			{
				//  此时缓冲栈（输出栈）中没有元素
				//  需要将输入栈中的元素倒入输出栈
				// 看输入栈中有没有元素

				//  否则将元素从输入栈导入输出栈
				while (stackIn.empty() != true)
				{
					node = stackIn.top();
					stackIn.pop();
					stackOut.push(node);
				
				}
			}

			node = stackOut.top();
			stackOut.pop();

			
		}

		return node;
	}

	bool empty()
	{
		return (stackIn.empty() == true && stackOut.empty() == true);
	}

private:
	stack<int> stackIn;
	stack<int> stackOut;
};





//8   旋转数组的最小数字
class Solution_8
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		if (rotateArray.size() == 0)
		{
			return 0;
		}

		int min = INT_MAX;
		for (int i = 0; i < rotateArray.size(); i++)
		{
			if (rotateArray[i] < min)
			{
				min = rotateArray[i];
			}
		}
		return min;
	}


};


//9 斐波那契数列
int Fibonacci(int n)
{
	if (n <= 1)
	{
		return n;
	}
	else
	{
		return Fibonacci(n - 1) + Fibonacci(n - 2);
	}
}



//10
//输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示
// bitse()
int Bits(int n) {
	int count = 0;
	while (n) {
		if (n & 1 == 1) {
			count++;
		}
		n >>= 1;
	}
	return count;
}


//11数值的整数次方
//写出指数的二进制表达，例如13表达为二进制1101。
/*
举例 : 10 ^ 1101 = 10 ^ 000110 ^ 010010 ^ 1000。
	通过 & 1和 >> 1来逐位读取1101，为1时将该位代表的乘数累乘到最终结果。
	简单明了，看来结果根指数中1的个数和位置有关系，那么就简单了，还记得剑指Offer--010 - 二进制中1的个数
	*/

	double PowerNormal(double base, int exponent)
{
	if (exponent == 0)
	{
		return 1;
	}
	else if (exponent == 1)
	{
		return base;
	}

	int res = 1, temp = base;
	while (exponent != 0)
	{
		if ((exponent & 1) == 1) //  当前指数为不为0
		{
			res *= temp;        //  就计算一个乘积
		}
		//  移位后, curr需要翻倍, 这样到下个
		temp *= temp;           // 翻倍
		exponent >>= 1;         // 右移一位
	}
	return res;
}

//12 打印1到最大的N位数






//13



//14
//输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
//所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。//暴力解法以及冒泡解法
//qucick_sort

int partition(vector<int> &vi, int low, int up) {
	int pivot = vi[up];
	int i = low - 1;
	for (int j = low; j < up; j++) {
		if (vi[j] < pivot) {
			swap(vi[i], vi[j]);
			i++;
		}
		swap(vi[i+1],pivot);
	}
	return i + 1;
}


void Quick_Sort(vector<int> &vi, int low, int up) {
	int mid = partition(vi, low,up);
	while (low < up) {
		Quick_Sort(vi, low, mid - 1);
		Quick_Sort(vi, mid + 1, up);
	}
}



//15
//树的子结构
//1.第一步在树A中找到和B的根节点的值一样的结点R,2.第二步再判断树A中以R为根结点的子树是不是包含和树B一样的结构。 这个过程其实就是要要判断两棵树对应的节点数据是否相同。这个是一个递归的过程。

bool DoesParentHasChild(TreeNode *parent, TreeNode *child) {
	if (child == NULL) {
		return true;
	}
	if (parent == NULL) {
		return false;
	}
	
	if (parent->value == child->value) {
		return true;
	}
	else {
		return DoesParentHasChild(parent->left, child->left) && DoesParentHasChild(parent->right, child->left);
	}
}

bool HasSubTree(TreeNode *parent, TreeNode *child) {
	if (parent == NULL || child == NULL) {
		return false;
	}

	bool result=false;
	if (parent->value == child->value) {
		result= DoesParentHasChild(parent, child);
	}

	if (!result) {
		result = DoesParentHasChild(parent->left, child) || DoesParentHasChild(parent->right, child);
	}

	return result;
}


//16  反转链表



// 17



// 18


//19-二叉树的镜像
void Mirror_Tree(TreeNode *root) {
	if (root != NULL) {
		return;
	}
	swap(root->left, root->right);
	Mirror_Tree(root->left);
	Mirror_Tree(root->right);
}




//20-顺时针打印矩阵






//21-包含min函数的栈





//22-栈的压入弹出序列
bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	int i = 0;
	int j = 0;
	stack<int> buffer;
	for (i; i < pushV.size(); i++) {
		buffer.push(pushV[i]);
		while (j<popV.size() && buffer.top() == popV[j]) {
			buffer.pop();
			j++;
		}
	}
	return buffer.empty();
}


//23-从上往下打印二叉树,BFS
vector<int> BFS(TreeNode *root) {
	vector<int> res;
	queue<TreeNode *> Tree_queue;
	if (root!=NULL) {
		Tree_queue.push(root);
		while (!Tree_queue.empty()) {
			TreeNode *temp = Tree_queue.front();
			Tree_queue.pop();
			res.push_back(temp->value);
			if (temp->left != NULL) {
				Tree_queue.push(temp->left);
			}
			if (temp->right) {
				Tree_queue.push(temp->right);
			}
		}
	}
	return res;
}




//24-二叉搜索树的后序遍历序列
//输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
bool Judge(vector<int> &a, int left,int right) {
	if (left >= right) {
		return true;
	}
	int i = left;
	while (a[i]<a[right]) {
		i++;
	}
	for (int j = i; j < right; j++) {
		if (a[j] < a[right]) {
			return false;
		}
	}
	return Judge(a, left, i - 1) && Judge(a, i, right);
}

bool VerifySequenceOfBST(vector<int> a) {
	if (!a.size()) {
		return false;
	}
	return Judge(a, 0, a.size() - 1);
}



//25-二叉树中和为某一值的路径

//26复杂链表的复制



//27-二叉搜索树与双向链表




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
	else {}
	for (int j = 0; j < end; j++) {
		swap(str[j],str[start]);
		Permutation(str, j + 1, end);
		swap(str[j], str[start]);
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