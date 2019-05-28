// https://github.com/gatieme/CodingInterviews

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <bitset>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include<unordered_set>

#include <functional>
#include <climits>
#include <algorithm>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>    


using namespace std;


struct TreeNode {
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) :value(x), left(NULL), right(NULL) {}
};

struct ListNode {
	int value;
	ListNode *next;
	//ListNode(int x) :value(x), next(NULL) {}
};

// 预先定义的数值，链表，二叉树等，
vector<int> a = {2,0,1,5,2,4,6};


// (1) 快速排序
/*
快速排序的思想、时间复杂度、实现以及优化方法
答：快速排序的三个步骤：
(1)选择基准：在待排序列中，按照某种方式挑出一个元素，作为 "基准"（pivot）；
(2)分割操作：以该基准在序列中的实际位置，把序列分成两个子序列。此时，在基准左边的元素都比该基准小，在基准右边的元素都比基准大；
(3)递归地对两个序列进行快速排序，直到序列为空或者只有一个元素。
*/

void quicksort(vector<int> &v, int left, int right) {
	if (left >= right) {
		return;
	}
	int key = v[left];
	int lower = left;
	int upper = right;
	while (lower < upper) {
		while (lower < upper && v[upper] >= v[lower]) {    //从后向前搜索
			upper--;
		}
		swap(v[lower], v[upper]);

		while (lower < upper && v[lower] <= v[upper]) {			//从前向后搜索
			lower++;
		}
		swap(v[lower], v[upper]);

		quicksort(v, left, lower - 1);		//左段
		quicksort(v, upper + 1, right);     //右段
	}
}

/*
int main() {
	quicksort(a, 0, 6);
	for (int i = 0; i <= 6; i++) {
		cout << a[i]<<"  ";
	}
	cout << endl;
	return 0;
}
*/

// <2>  堆排序：堆排序是不稳定排序
// 堆的性质：每个节点的值小于等于其父节点 或 大于等于父节点；前者称为“最大堆”，用于升序，后者为“最小堆”，用于降序， 堆是一棵完全二叉树，因此常用数组进行模拟
//完全二叉树：假设一个二叉树有n层，那么如果第1到n-1层的每个节点都达到最大的个数：2，且第n层的排列是从左往右依次排开的，那么就称其为完全二叉树
//注意：此排序方法不适用于个数少的序列，因为初始构建堆需要时间；
//平均时间复杂度O(n log n)， 最差空间复杂度O(n)
//例1：编写算法，从10亿个浮点数当中，选出其中最大的10000个。
//辅助交换函数
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//堆排序的核心是建堆,传入参数为数组，根节点位置，数组长度
void Heap_build(int a[], int root, int length)
{
	int lchild = root * 2 + 1;//根节点的左子结点下标
	if (lchild < length)//左子结点下标不能超出数组的长度
	{
		int flag = lchild;//flag保存左右节点中最大值的下标
		int rchild = lchild + 1;//根节点的右子结点下标
		if (rchild < length)//右子结点下标不能超出数组的长度(如果有的话)
		{
			if (a[rchild] > a[flag])//找出左右子结点中的最大值
			{
				flag = rchild;
			}
		}
		if (a[root] < a[flag])
		{
			//交换父结点和比父结点大的最大子节点
			Swap(a[root], a[flag]);
			//从此次最大子节点的那个位置开始递归建堆
			Heap_build(a, flag, length);
		}
	}
}

void Heap_sort(int a[], int len)
{
	for (int i = len / 2; i >= 0; --i)//从最后一个非叶子节点的父结点开始建堆
	{
		Heap_build(a, i, len);
	}

	for (int j = len - 1; j > 0; --j)//j表示数组此时的长度，因为len长度已经建过了，从len-1开始
	{
		Swap(a[0], a[j]);//交换首尾元素,将最大值交换到数组的最后位置保存
		Heap_build(a, 0, j);//去除最后位置的元素重新建堆，此处j表示数组的长度，最后一个位置下标变为len-2
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 剑指offer 66




// 003-二维数组中的查找
//在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，
//判断数组中是否含有该整数。
bool Find(vector<vector<int>> array, int v) {
	int row = array.size();
	int colum = array[0].size();
	cout << row << endl;
	cout << colum << endl;
	bool found = false;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < colum; j++) {
			if (found == false && array[i][j] == v) {
				found = true;
			}
		}
	}
	return found;
}

/*
int main() {
vector<vector<int>> array = { {1,1,1},{2,2,2},{3,3,3}, {4,4,4 } };
cout << Find(array, 0);

return 0;
}
*/


// 004-替换空格
//请实现一个函数，将一个字符串中的空格替换成“%20”。 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy
void replaceSpace(char *str, int length) {
	int count = 0;
	for (int i = 0; i < length; i++) {
		if (str[i] == ' ') {
			count++;
		}
	}

	int old_length = length;
	int new_length = length + 2 * count;
	int old_length_Index = old_length - 1;
	int new_length_Index = new_length - 1;

	while (old_length_Index >= 0 && new_length_Index >= 0) {
		if (str[old_length_Index] == ' ') {
			str[new_length_Index--] = '0';
			str[new_length_Index--] = '2';
			str[new_length_Index--] = '%';
			old_length_Index--;
		}
		else {
			str[old_length_Index--] = str[new_length_Index--];
		}
	}
	str[new_length] = '\0';
}

/*
int main() {
	char str[] = "df wf e";
	
	replaceSpace(str, 7);
	cout << sizeof(str) << endl;
	//for (int i = 0; i <=5; i++) {
	//	cout << str[i] << " ";
	//	}
	//cout << endl;
}
*/


// 005-从尾到头打印链表
//输入一个链表，从尾到头打印链表每个节点的值。(stack)

void printListFromTailToHead(ListNode* head) {
	stack<ListNode* > reverse_list;
	while (head != NULL) {
		reverse_list.push(head);
		head = head->next;
		//cout << head->value << endl;
	}

	while (!reverse_list.empty()) {
		cout << reverse_list.top()->value << endl;
		reverse_list.pop();
	}
}

/*
int main() {

	ListNode list[4];
	list[0].value = 1;
	list[0].next = &list[1];
	list[1].value = 2;
	list[1].next = &list[2];
	list[2].value = 3;
	list[2].next = &list[3];
	list[3].value = 4;
	list[3].next = NULL;

printListFromTailToHead( list );
}

*/

// 006-重建二叉树
//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字

void reConstructBinaryTree(vector<int> pre, vector<int> in) {
	int in_lenght = in.size();
	int pre_length = pre.size();

	vector<int> in_left, in_right, pre_left, pre_right;

	int root_index_in = 0;

	for (int i = 0; i < in_lenght; i++) {
		if (in[i] = pre[0]) {
			root_index_in = i;
			break;
		}
	}

	for (int i = 0; i < root_index_in; i++) {
		in_left.push_back(in[i]);
	}

	for (int i = root_index_in; i < in_lenght; i++) {
		in_right.push_back(in[i]);
	}

	for (int i = 1; i < root_index_in + 1; i++) {
		pre_left.push_back(pre[i]);
	}


	for (int i = root_index_in + 1; i < pre_length; i++) {
		pre_right.push_back(pre[i]);
	}

	reConstructBinaryTree(in_left, pre_left);
	reConstructBinaryTree(in_right, pre_right);
}


// 007-用两个栈实现队列
class Solution_7 {
public:
	void push(int node) {
		stackIn.push(node);
	}

	int pop() {
		int node = -1;
		//  两个栈都是NULL的时候，整个队列为空
		if (this->empty() == true) {
			return -1;
		}
		else {
			//  否则队列中有元素
			//  此时分两种情况，
			//  当输出栈不为空的时候, 直接将输出栈中元素弹出即可
			//  当输出栈为NULL, 但是输入栈不为空的时候，需要将输入栈的元素全部倒入输出栈中
			if (stackOut.empty() == true) {     //  此时输出栈为空, 输入栈必不为空
												//  此时缓冲栈（输出栈）中没有元素
												//  需要将输入栈中的元素倒入输出栈
												// 看输入栈中有没有元素
												//  否则将元素从输入栈导入输出栈
				while (stackIn.empty() != true) {
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

	bool empty() {
		return (stackIn.empty() == true && stackOut.empty() == true);
	}
private:
	stack<int> stackIn;
	stack<int> stackOut;
};




// 008-旋转数组的最小数字
class Solution_8 {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.size() == 0) {
			return 0;
		}
		int min = INT_MAX;
		for (int i = 0; i < rotateArray.size(); i++) {
			if (rotateArray[i] < min) {
				min = rotateArray[i];
			}
		}
		return min;
	}
};



// 009-斐波那契数列


// 010-二进制中1的个数
//输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示
// bitse()
int Bits(int n) {
	int res = 0;
	while (n) {
		if (n & 1 == 1) {
			res++;
		}
		n >>= 1;
	}
	return res;

}

/*
int main() {
	int aa = 2;
	cout << Bits(aa) << endl;
}
*/


// 011-数值的整数次方
//写出指数的二进制表达，例如13表达为二进制1101。
/*
举例 : 10 ^ 1101 = 10 ^ 000110 ^ 010010 ^ 1000。
通过 & 1和 >> 1来逐位读取1101，为1时将该位代表的乘数累乘到最终结果。
简单明了，看来结果根指数中1的个数和位置有关系，那么就简单了，还记得剑指Offer--010 - 二进制中1的个数
*/

double PowerNormal(double base, int exponent) {
	if (exponent == 0) {
		return 1;
	}
	else if (exponent == 1) {
		return base;
	}

	int res = 1, temp = base;
	while (exponent != 0) {
		if ((exponent & 1) == 1) { //  当前指数为不为0
			res *= temp;        //  就计算一个乘积
		}
		//  移位后, curr需要翻倍, 这样到下个
		temp *= temp;           // 翻倍
		exponent >>= 1;         // 右移一位
	}
	return res;
}


// 012-打印1到最大的N位数





// 014-调整数组顺序使奇数位于偶数前面
//输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
//所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。//暴力解法以及冒泡解法

void sort_even_odd(vector<int>& aa, int lower, int upper) {
	for (int i = lower; i <= upper; i++) {
		for (int j = i + 1; j <= upper; j++) {
			if (aa[j] % 2 == 1) {
				swap(aa[j], aa[i]);
			}
		}
	}
}

/*
int main() {
	sort_even_odd(a, 0, 6);
	for (int i = 0; i <= 6; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
*/


// 015 - 链表中倒数第k个结点
// 双指针法

// 016-反转链表
// 思路一： 遍历原链表，将每个元素插入到一个新的链表中的头部
// 思路二： 三指针滑动pPrev -> pNode -> pNext


// 017-合并两个排序的链表
// 用两个指针同步遍历两个链表，每次找到小的那个插入到新的链表中


// 018-树的子结构
// 第二步再判断树A中以R为根结点的子树是不是包含和树B一样的结构。 这个过程其实就是要要判断两棵树对应的节点数据是否相同。这个是一个递归的过程
bool DoesParentHasChild(TreeNode* parent, TreeNode* child) {
	if (child == NULL) {
		return true;
	}
	else if (parent == NULL) {
		return false;
	}

	if (parent->value != child->value) {
		return false;
	}
	else {
		return DoesParentHasChild(parent->left, child->left) && DoesParentHasChild(parent->right,child->right);
	}

}

// 第一步在树A中找到和B的根节点的值一样的结点R； 这实际上就是树的遍历。可以用递归实现
bool has_tree(TreeNode* parent, TreeNode* child) {
	if (child == NULL || parent == NULL) {
		return false;
	}
	bool result;
	if (parent->value == child->value) {
		result = DoesParentHasChild(parent->left, child) || DoesParentHasChild(parent->right, child);//  从左子树查找 从右子树中查找
	}
	else {
		return true;
	}

}



// 019-二叉树的镜像
void Mirror_Tree(TreeNode *root) {
	if (root != NULL) {
		swap(root->left, root->right);
	}
	Mirror_Tree(root->left);
	Mirror_Tree(root->right);
}


// 020-顺时针打印矩阵 


// 021-包含min函数的栈




// 022-栈的压入弹出序列
//如果下一个弹出的数字刚好是栈顶数字，那么直接弹出。
//如果下一个弹出的数字不在栈顶，我们把压栈序列中还没有入栈的数字压入辅助栈，直到把下一个需要弹出的数字压入栈顶为止。
//如果所有的数字都压入栈了仍然没有找到下一个弹出的数字，那么该序列不可能是一个弹出序列

bool Is_PopOrder(vector<int> pushV, vector<int> popV) {
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


// 023-从上往下打印二叉树
// 从上往下打印出二叉树的每个节点，同层节点从左至右打印
vector<int> BFS(TreeNode *root) {
	queue<TreeNode *> tree_queue;
	vector<int> res;

	if (root != NULL) {
		tree_queue.push(root);
		while (!tree_queue.empty()) {
			TreeNode * temp = tree_queue.front();
			tree_queue.pop();
			res.push_back(temp->value);
			if (temp->left != NULL) {
				tree_queue.push(temp->left);
			}
			if (temp->right != NULL) {
				tree_queue.push(temp->right);
			}
		}
	}
	return res;
}

/*
int main() {

	TreeNode tree_1(1);
	TreeNode tree_2(2);
	TreeNode tree_3(3);
	TreeNode tree_4(4);
	TreeNode tree_5(5);
	TreeNode tree_6(6);
	TreeNode tree_7(7);
	
	tree_1.left = &tree_2;
	tree_1.right = &tree_3;

	tree_2.left = &tree_4;
	tree_2.right = &tree_5;

	tree_3.left = &tree_6;
	tree_3.right = &tree_7;


	vector<int>res = BFS(&tree_1);

	for (int i = 0; i < 7; i++) {
		cout << res[i] << " ";
	}
	cout << endl;
		return 0;
}
*/

// 024-二叉搜索树的后序遍历序列
//输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。左右后

bool Judge(vector<int> &a, int left, int right) {
	if (left <= right) {
		return true;
	}
	int i = left;
	while (a[i] < a[right]) {
		i++;
	}
	for (int j = i; i < right; j++) {
		if (a[j] < a[right]) {
			return false;
		}
	}
	return Judge(a, 0, i - 1) && Judge(a, i, right);
}

bool VerifySequenceOfBST(vector<int> a) {
	if (a.size() <= 0) {
		return false;
	}
	return Judge(a, 0, a.size() - 1);
}


//int main() {
//	
//	/*
//		  12
//		 /  \
//	    5    18
//	 / \     / \
//    2    9  15  19
//	         \
//	          17
//	         /
//			16
//	
//	*/
//
//	vector<int> a = { 2, 9, 5, 16, 17, 15, 19, 18, 12 };
//	cout << VerifySequenceOfBST(a) << endl;
//	return 0;
//}


// 025-二叉树中和为某一值的路径
// 输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径



// 026-复杂链表的复制



// 027-二叉搜索树与双向链表



// 028-字符串的排列
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
			swap(str[j], str[start]);
			Permutation(str, j + 1, end);
			swap(str[j], str[start]);
		}
	}
}





// 029-数组中出现次数超过一半的数字

//解法一
int More_than_half_number(vector<int> numbers) {
	unordered_map< int, int> map;
	for (int i = 0; i < numbers.size(); i++) {
		map[numbers[i]]++;
	}
	for (int i = 0; i < numbers.size(); i++) {
		if (map[numbers[i]] * 2 > numbers.size()) {
			return  numbers[i];
		}
	}
}

/*
int main() {
	vector<int> a = {1,1,1,1,1,3,4,5};
	cout << More_than_half_number(a) << endl;
}
*/



//解法二
class Solution_29{
public:
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{
		map<int, int> hmap;  //  建立数字到出现次数的映射

		int nsize = numbers.size();

		for (int i = 0; i < nsize; i++)
		{
			if (hmap.find(numbers[i]) != hmap.end())
			{
				hmap[numbers[i]] += 1;
			}
			else
			{
				hmap[numbers[i]] = 1;
			}
		}



		//  查找到出现次数最多的那个元素
		for (map<int, int>::iterator it = hmap.begin();	it != hmap.end();	++it)
		{
			
			if (it->second * 2 > nsize)
			{
				return it->first;
			}
		}
		return 0;
	}
};


// 030-最小的K个数
// 方法一 排序

// 031-连续子数组的最大和 DP
//dp[i]= array[i]; if dp[i-1]<=0;
//dp[i]=array[i-1]+array[i];  if dp[i-1]>0;
int FindGreatestSumOfSubArray(vector<int> array) {
	if (array.empty()) {
		return 0;
	}
	int max_sum = INT_MIN;
	int DP[1000];
	DP[0] = array[0];
	for (int i = 1; i < array.size(); i++) {
		if (DP[i - 1] <= 0) {
			DP[i] = array[i];
		}
		else {
			DP[i] = DP[i - 1] + array[i];
		}
		if (DP[i] > max_sum) {
			max_sum = DP[i];
		}
	}
	return max_sum;
}

/*
int main() {
	vector<int> a = { 6, -3, -2, 7, -15, 1, 2, 2 };
	cout << FindGreatestSumOfSubArray(a) << endl;
	return 0;
}
*/


// 032-从1到n整数中1出现的次数




// 033-把数组排成最小的数
bool cmp(int& a, int& b) {
	string A, B;
	A += to_string(a);
	A += to_string(b);

	B += to_string(b);
	B += to_string(a);
	return (A < B);
}

string PrintMinNumString(vector<int> numbers) {
	string res;
	sort(numbers.begin(), numbers.end(), cmp);
	for (auto i : numbers) {
		res += to_string(i);
	}
	return res;
}

/*
int main() {
	vector<int> a = {2,1,0,4};
	cout << PrintMinNumString(a) << endl;

	return 0;
}
*/

// 034-丑数
//第一步：定义判断一个书是不是丑数的函数
//第二步：循环遍历




// 035-第一个只出现一次的字符位置
int FirstNotRepeatingChar_1(string str) {
	unordered_map<char, int> mp;
	for (int i = 0; i < str.size(); i++) {
		mp[str[i]]++;
	}
	for (int i = 0; i < str.size(); i++) {
		if (mp[str[i]] == 1) {
			return i;
		}
	}
}


// 036-数组中的逆序对
// 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。 输入一个数组，求出这个数组中的逆序对的总数
// 冒泡的方法，每换一次，计数加一



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
		int left_depth = TreeDepthRecursion(root->left);
		int right_depth = TreeDepthRecursion(root->right);
		return max(left_depth, right_depth) + 1;
	}
}

/*
int main() {
	
	TreeNode tree[7]{1,2,3,4,5,6,7};

	tree[0].left = &tree[1];
	tree[0].right = &tree[2];

	tree[1].left = &tree[3];
	tree[1].right = &tree[4];

	tree[2].left = &tree[5];
	tree[2].right = &tree[6];

	cout << TreeDepthRecursion(tree) << endl;

	return 0;
}

*/

//39-平衡二叉树
bool IsBanlancedTree(TreeNode *root) {
	if (root == NULL) {
		return true;
	}
	int left_depth = TreeDepthRecursion(root->left);
	int right_depth = TreeDepthRecursion(root->right);

	if (abs(left_depth - right_depth) <= 1) {
		return IsBanlancedTree(root->left) && IsBanlancedTree(root->right);
	}
	else {
		return false;
	}
}



// 040 数组中只出现一次的数字
// 此题考察的是异或运算的特点：即两个相同的数异或结果为0


// 041 和为S的两个数字
// 输入一个递增排序的数组和一个数字s，在数组中查找两个数，得它们的和正好是s。如果有多对数字的和等于s，输出乘积最小的即可
vector<int> FindNumbersWithSum(vector<int> array, int sum) {
	vector<int> res;
	int start = 0;
	int end = array.size() - 1;
	int current_sum = array[start] + array[end];
	if (current_sum == sum) {
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



// 042-左旋转字符串 
//string.substr()
string LeftRotateString_1(string str, int n) {
	string New_string = str + str;
	string res = "";
	res = New_string.substr(n, str.size());
	return res;
}


// 044-扑克牌顺子
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


// 045-孩子们的游戏(圆圈中最后剩下的数)
//约瑟夫环




// 046-求1+2+3+...+n
// 短路运算 n && (sum(n-1))



// 047-不用加减乘除做加法



// 049-把字符串转换成整数

// 050


// 051-数组中重复的数字
// a[a[i]]





// 055-字符流中第一个不重复的字符 
// hash table


// 056-链表中环的入口结点

ListNode * meetingNode(ListNode *head) {
	if (head == NULL) {
		return NULL;
	}
	ListNode *slow = head;
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


// 057-删除链表中重复的结点






// 058-二叉树的下一个结点
//分情况讨论



// 059-对称的二叉树

bool IsSymerical_Recursion(TreeNode *left, TreeNode *right) {
	if (left == NULL && right == NULL) {
		return true;
	}
	if (left == NULL || right == NULL) {
		return false;
	}
	if (right->value != left->value) {
		return false;
	}
	return IsSymerical_Recursion(left->left, right->right) && IsSymerical_Recursion(left->right, right->left);
}

bool IsSymerical(TreeNode *root) {
	if (root == NULL) {
		return true;
	}
	return IsSymerical_Recursion(root->left, root->right);
}



// 060-把二叉树打印成多行  BFS

// 061-按之字形顺序打印二叉树



// 062 - 序列化二叉树
// 遍历采用先序, 中序, 后序或者层次都可以
 
// 063-二叉搜索树的第K个结点
void In_order(TreeNode *root, vector<int> res) {
	if (root != NULL) {
		In_order(root->left, res);
		//cout << root->value;
		res.push_back(root->value);
		In_order(root->right, res);
	}
}

int Kth_TreeNode(TreeNode *root, int k) {
	vector<int> res;
	In_order(root, res);
	return res[k - 1];
}


//64-数据流之中的中位数
//堆排序


//65-滑动窗口的最大值
int GetMax(const int a[], int size) {
	int max = a[0];
	for (int i = 0; i <= size; i++) {
		max = max > a[i] ? max : a[i];
	}
	return max;
}

vector<int> maxInWindows(const int A[], int n, int size) {
	vector<int> res;
	for (int i = 0; i < n - size; i++) {
		res.push_back(GetMax(A + i, size));
	}
	return res;
}



/*
int main() {


	return 0;
}

*/