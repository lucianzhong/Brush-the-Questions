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
#include <set>
#include <list>

#include <functional>
#include <climits>
#include <algorithm>

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



// （2）
//翻转链表
ListNode * ReverseList(ListNode *head) {
	if (head == NULL || head->next == NULL) {  //链表为空直接返回，而H->next为空是递归基
		return head;
	}

	ListNode* new_ListNode = ReverseList(head->next);//一直循环到链尾 
	
	head->next->next = head;  //翻转链表的指向
	head->next = NULL;  //记得赋值NULL，防止链表错乱
	return new_ListNode;  //新链表头永远指向的是原链表的链尾
}


//（3）合并链表
ListNode* MergeList(ListNode* ListHeadNodeOne, ListNode* ListHeadNodeTwo) {
	if (ListHeadNodeOne == NULL) {
		return ListHeadNodeTwo;
	}
	else if (ListHeadNodeTwo == NULL) {
		return ListHeadNodeTwo;
	}

	ListNode *Merged_List = NULL;
	if (ListHeadNodeOne->value <= ListHeadNodeTwo->value) {
		Merged_List = ListHeadNodeOne;
		Merged_List->next = MergeList(ListHeadNodeOne->next, ListHeadNodeTwo);
	}
	else if (ListHeadNodeOne->value > ListHeadNodeTwo->value) {
		Merged_List = ListHeadNodeTwo;
		Merged_List->next = MergeList(ListHeadNodeOne, ListHeadNodeTwo->next);
	}
	return Merged_List;
}


// （4） 求树的高度
int Height_tree(TreeNode * root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int height = Height_tree(root->left) > Height_tree(root->right) ? Height_tree(root->left) + 1 : Height_tree(root->right) + 1;
		return height;
	}
}


// （5） 树的距离 
int TreeDistance(TreeNode *root) {
	int maxDisatnce = 0;
	int distanceTree = 0;
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL || root->right == NULL) {
		return 0;
	}
	distanceTree = max(TreeDistance(root->left), TreeDistance(root->right));
	distanceTree = max((Height_tree(root->left) + Height_tree(root->right)), distanceTree);
	if (maxDisatnce < distanceTree) {
		maxDisatnce = distanceTree;
	}
	return maxDisatnce;
}



// （6） 链表中第k个节点
ListNode * Kth_Node(ListNode *root, int k) {
	ListNode *fast_node = root + k;
	ListNode *slow_node = root;

	while (fast_node != NULL) {
		slow_node = slow_node->next;
	}
	return slow_node;
}


// （7） Fibonacii数列
int Fibonacci(int n) {
	if (n == 1 || n == 2) {
		return n;
	}
	else {
		return (Fibonacci(n - 1) + Fibonacci(n - 2));
	}
}

// （8） 求数组中和为一值得子数组
vector<int> findAns(vector<int> data, int sum) {
	vector<int> res;
	int start = 0;
	int end = data.size() - 1;

	while (start < end) {
		if ((data[start] + data[end]) > sum) {
			end--;
		}
		else if ((data[start] + data[end])<sum) {
			start++;
		}
		else {
			res = { start,end };
			return  res;
		}
	}
	return res;
}


// （9） 树的镜像
TreeNode * Mirror_TreeNode(TreeNode *root) {
	if (root != NULL) {
		swap(root->left, root->right);
		Mirror_TreeNode(root->left);
		Mirror_TreeNode(root->right);
	}
	return root;
}



// （10） 广度优先遍历
void BreadthTraverse(TreeNode *root) {
	queue<TreeNode *> node_queue;
	node_queue.push(root);
	TreeNode *node;

	while (!node_queue.empty()) {
		node = node_queue.front();
		cout << node->value << endl;
		node_queue.pop();
		if (node->left != NULL) {
			node_queue.push(node->left);
		}
		if (node->right != NULL) {
			node_queue.push(node->right);
		}
	}
}


// （11） 字符串中的一个不重复的字符
// 哈希表
int FirstNotRepeatingChar(string str) {
	int hash[] = { 0 };
	for (int i = 0; i < str.length(); i++) {
		hash[str[i]]++;
	}
	for (int i = 0; i < str.length(); i++) {
		if (hash[str[i]] == 1) {
			return i;
		}
	}
	return -1;
}



//（12） 单链表反序（反转），使用stack
void Reverse_List(ListNode *head) {
	if (head == NULL || head->next == NULL) {
		return;
	}
	stack<ListNode *>reverse_list;
	while (head->next != NULL) {
		reverse_list.push(head->next);
		head = head->next;
	}
	while (!reverse_list.empty()) {
		head->next = reverse_list.top();//让头节点指向（栈顶元素中所存的第一个节点的地址）
		head = reverse_list.top();//链表指针后移
		reverse_list.pop();
	}
	head->next = NULL; // 令链表末尾指向NULL
}


//（13） 在字符串中找出连续最长的数字串，并把这个串的长度返回，
int LongestNumberString(string str) {
	int len = str.size();
	string buffer;
	string out;
	int max = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] >= '0'  && str[i] <= '9') {
			buffer += str[i];

			while (str[i + 1] >= '0' && str[i + 1] <= '9') {
				buffer += str[i + 1];
				i++;
				if (buffer.size() > max) {
					max = buffer.size();
					out = buffer;
				}
				else if (buffer.size() == max) {
					out += buffer;
				}
				buffer.clear();
			}
			return max;
		}
	}
	return 0;
}


//（14） 左旋转字符串（字符串）
string LeftRotateString(string str, int n) {
	int len = str.size();
	if (len == 0) {
		return " ";
	}
	n = n%len;
	str += str;
	return (str.substr(n, len));
}


// （15） 一个数字二进制中1的个数
int NumberOfOne(int n) {
	int i = 0;
	while (n) {
		if (n && 1 == 1) {
			i++;
		}
		n >>=1; //右移一位
	}
	return i;
}


// （16）输入两个整数序列。其中一个序列表示栈的push顺序，判断另一个序列有没有可能是对应的pop顺序
bool IsPopOrder(vector<int> pushV, vector<int> popV) {
	stack<int> buffer;

	for (int i = 0; i < pushV.size(); i++) {
		buffer.push(pushV[i]);
	}
	int j = 0;
	while (j < buffer.size() && buffer.top() == popV[j]) {
		j++;
		buffer.pop();
	}
	return (buffer.empty());
}


//（17）在从1到n的正数中1出现的次数（数组）
int ComputeNum1(int n) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		while (i) {
			if (i % 10 == 1) {
				count++;
			}
			i /= 10;
		}
	}
	return count;
}


// （18）
//求一个矩阵中最大的二维矩阵(元素和最大)
// max sub-array of an array of number n
int Max_Array(int a[], int n) {
	int buffer = 0;
	int sum = a[0];
	for (int i = 0; i < n; i++) {
		if (buffer > 0) {
			buffer += a[0];
		}
		else {
			buffer = a[i];
		}

		if (buffer > sum) {
			sum = buffer;
		}
		return sum;
	}
}


int maxSubMatrix(int array[][3], int n){
	int i, j, k, max = 0, sum = -100000000;
	int b[] = { 0 };

	for (k = 0; k<n; k++){//初始化b[]
		b[k] = 0;
	}
	for (i = 0; i<n; i++){

		for (j = i; j<n; j++){//把第i行到第j行相加,对每一次相加求出最大值
		  for (k = 0; k<n; k++){
				b[k] += array[j][k];//j行的所有列
			}
			max = Max_Array(b, n);
			if (max>sum){
				sum = max;
			}
		}
	}
	return sum;
}



// (19)
/*
（数组）
2010年中兴面试题
编程求解：
输入两个整数 n 和 m，从数列1，2，3.......n 中 随意取几个数,
使其和等于 m, 要求将其中所有的可能组合列出来.
类似这种组合问题一般都是使用递归的策略，考虑到n个数和为m,假设要解决的函数为f(n,m), 假设我们选择了第n个数，那么问题就变成了f(n-1,m-n)，
否则的话问题就是f(n-1,m), 再考虑下边界条件： 如果n<1 或者 m<1显然不会有结果， 如果n==m，那么显然可以输出一个结果了,然后问题就变成了f(m-1,m)
*/
void BagProblem(int n, int m) {
	vector<int> res;
	if (n == 1 || m == 1) {
		return;
	}
	if (m>n) {
		res.push_back(n);
		BagProblem(n - 1, m - n);//选择n
		res.pop_back();
		BagProblem(n - 1, m);//not choose n
	}
	else {
		vector<int>::iterator it;
		for (it = res.begin(); it < res.end(); it++) {
			cout << *it << endl;
		}
		cout << m << endl; //当m<n时，一定可以输出m，然后在递归
		BagProblem(m - 1, m);
	}
}





// (20)
int sum(int n) {
	int res = n;
	res && (res += sum(n - 1));
	return res;
}


// (21) 二分查找
int binary_search(vector<int> nums, int v) {
	sort(nums.begin(), nums.end());
	if (nums.size() < 1) {
		return -1;
	}

	int left = 0;
	int right = nums.size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] == v) {
			return mid;
		}
		else if (nums[mid] > v) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1;
}


// (22)
// 题目描述:给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
// 异或： 相同为假，不同为真 

int singleNumber(vector<int>& nums) {
	int ret = 0;
	for (auto i : nums)
		ret ^= i; //按位异或
	return ret;
}



// (23)
// atoi() 将字符串转换为整数
int atoi_my(const char * const str) {
	if (str == NULL) {
		return 0;
	}

	int res = 0;
	int sign = 1;
	auto *p = str;

	while (isspace(*p)) {
		p++;
	}
	if (*p == '-') {
		sign = -1;
	}
	if (*p == '-' || *p == '+') {
		p++;
	}
	while (*p > '0' && *p < '9') {
		int new_res = res * 10 + (*p - '0');
		if (new_res / 10 != res) {
			return sign > 0 ? INT_MIN : INT_MAX;
		}
		res = new_res;
		p++;
	}
	return res*sign;
}




// <4>  快速幂算法  
// 求 3^20 = 9^10 = 81^5 (= 81*81^4) = 81*6561^2 = 81*43046721
// 基本解法（连乘连除） - O(n) 速幂运算 - O(logN)

double quickPow(double base, int p) {
	double res = 0;
	int q = abs(p);
	if (q > 0) {
		if (q & 1) {  //如果指数为奇数；一个数不断除 2 至少有一次会变成奇数，2/2 = 1
			res *= base;
			base *= base;
			q >>= 1;  //除以2，右移一位
		}
	}

	return res > 0 ? res : 1 / res;
}



// <9>
//输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323
static bool cmp(int &left, int & right) { // 需要静态方法
	string left_right = to_string(left) + to_string(right);
	string right_left = to_string(right) + to_string(left);
	return left_right < right_left;
}

string Print_min_number(vector<int> numbers) {
	sort(numbers.begin(), numbers.end(), cmp);
	string str;
	for (auto i : numbers) {
		str.append(to_string(i));
	}
	return str;

}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//剑指offer

//3
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


//4
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
	int old_length_Index = old_length-1;
	int new_length_Index = new_length - 1;

	while (old_length_Index >= 0 && new_length_Index >= 0) {
		if (str[old_length_Index] == ' ') {
			str[new_length_Index--] = '0';
			str[new_length_Index--] = '2';
			str[new_length_Index--] = '%';
			old_length_Index--;
		}
		else {
			str[old_length_Index--]=str[new_length_Index--];
		}
	}
	str[new_length] = '\0';
}



//5
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
	list[2].value= 3;
	list[2].next = &list[3];
	list[3].value = 4;
	list[3].next = NULL;
	

	printListFromTailToHead( list );
}
*/


//6
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

	for (int i = 1; i < root_index_in+1; i++) {
		pre_left.push_back(pre[i]);
	}


	for (int i = root_index_in + 1; i < pre_length; i++) {
		pre_right.push_back(pre[i]);
	}

	reConstructBinaryTree(in_left, pre_left);
	reConstructBinaryTree(in_right, pre_right);
}


//7 用两个栈实现队列
class Solution_7{
public:
	void push(int node)	{
		stackIn.push(node);
	}

	int pop()	{
		int node = -1;
		//  两个栈都是NULL的时候，整个队列为空
		if (this->empty() == true){
			return -1;
		}
		else{
			//  否则队列中有元素
			//  此时分两种情况，
			//  当输出栈不为空的时候, 直接将输出栈中元素弹出即可
			//  当输出栈为NULL, 但是输入栈不为空的时候，需要将输入栈的元素全部倒入输出栈中
			if (stackOut.empty() == true){     //  此时输出栈为空, 输入栈必不为空
				//  此时缓冲栈（输出栈）中没有元素
				//  需要将输入栈中的元素倒入输出栈
				// 看输入栈中有没有元素
				//  否则将元素从输入栈导入输出栈
				while (stackIn.empty() != true)	{
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

	bool empty(){
		return (stackIn.empty() == true && stackOut.empty() == true);
	}
private:
	stack<int> stackIn;
	stack<int> stackOut;
};



//8   旋转数组的最小数字
class Solution_8{
public:
	int minNumberInRotateArray(vector<int> rotateArray){
		if (rotateArray.size() == 0){
			return 0;
		}
		int min = INT_MAX;
		for (int i = 0; i < rotateArray.size(); i++){
			if (rotateArray[i] < min){
				min = rotateArray[i];
			}
		}
		return min;
	}
};



//9 斐波那契数列


//10
//输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示
// bitse()
int Bits(int n) {
	int res = 0;
	while (n) {
		if (n & 1 ==1) {
			res++;
		}
		n >>= 1;
	}
	return res;

}




//11数值的整数次方
//写出指数的二进制表达，例如13表达为二进制1101。
/*
举例 : 10 ^ 1101 = 10 ^ 000110 ^ 010010 ^ 1000。
通过 & 1和 >> 1来逐位读取1101，为1时将该位代表的乘数累乘到最终结果。
简单明了，看来结果根指数中1的个数和位置有关系，那么就简单了，还记得剑指Offer--010 - 二进制中1的个数
*/


double PowerNormal(double base, int exponent){
	if (exponent == 0)	{
		return 1;
	}
	else if (exponent == 1)	{
		return base;
	}

	int res = 1, temp = base;
	while (exponent != 0)	{
		if ((exponent & 1) == 1){ //  当前指数为不为0
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

void sort_even_odd(int arr[],int lower, int upper) {
	for (int i = lower; i <= upper; i++) {
		for (int j = i + 1; j <= upper; j++) {
			if (arr[j] % 2 == 1) {
				swap(arr[j], arr[i]);
			}
		}
	}
}






//15
//树的子结构
//  第一步在树A中找到和B的根节点的值一样的结点R,
//  第二步再判断树A中以R为根结点的子树是不是包含和树B一样的结构。 这个过程其实就是要要判断两棵树对应的节点数据是否相同。这个是一个递归的过程。

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

	bool result = false;
	if (parent->value == child->value) {
		result = DoesParentHasChild(parent, child);
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
		swap(root->left, root->right);
	}
	Mirror_Tree(root->left);
	Mirror_Tree(root->right);
}


//20-顺时针打印矩阵






//21-包含min函数的栈




//22-栈的压入弹出序列
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


//23-从上往下打印二叉树,BFS
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



//24-二叉搜索树的后序遍历序列
//输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。

bool Judge(vector<int> &a, int left, int right) {
	if (left <= right) {
		return true;
	}
	int i = left;
	while (a[i] < a[right]) {
		i++;
    }
	for (int j = i; i <right; j++) {
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




//25-二叉树中和为某一值的路径

//26复杂链表的复制



//27-二叉搜索树与双向链表









int main() {



	return 0;
}