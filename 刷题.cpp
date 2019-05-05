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
/*
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
*/




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
			Permutation(str, j+1, end);
			swap(str[j], str[start]);
		}
	}
}





//29-数组中出现次数超过一半的数字





//30-最小的K个数


//31-连续子数组的最大和 DP
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



//32-从1到n整数中1出现的次数


//33-把数组排成最小的数
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
	for (auto i :numbers) {
		res += to_string(i);
	}
	return res;
}



//34-丑数
//第一步：定义判断一个书是不是丑数的函数
//第二步：循环遍历




//35-第一个只出现一次的字符位置
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
		int left_depth = TreeDepthRecursion(root->left);
		int right_depth = TreeDepthRecursion(root->right);
		return max(left_depth, right_depth) + 1;
	}
	
}


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



//40 数组中只出现一次的数字



//41 和为S的两个数字
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



//42-左旋转字符串 
//string.substr()
string LeftRotateString_1(string str, int n) {
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


//55-字符流中第一个不重复的字符 
//hash table


//56-链表中环的入口结点

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


//57-删除链表中重复的结点






//58-二叉树的下一个结点
//分情况讨论



//59-对称的二叉树

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



//60-把二叉树打印成多行  BFS

//61-按之字形顺序打印二叉树



//62 - 序列化二叉树


//63-二叉搜索树的第K个结点
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



//////////////////////////////////////////////////////////////////////////////
// LeetCode 100


//01 Two Sum(E)
//先使用排序，然后取数值的头和尾，相加，如果大于sum就把尾向前移，如果小于sum，把头向前移动，直到等于sum



//02 Add two numbers(M)


// 03 longest substring without repeating characters(M)
int lengthOfLongestSubstring(string s) {
	int res = 0;
	unordered_map<char, int> mp;
	for (int i = 0; i < s.size(); i++) {
		mp[s[i]]++;
	}
	for (int i = 0; i < s.size(); i++) {
		if (mp[s[i]] == 1) {
			res++;
		}
	}
	return res;
}



//04 median of two sorted arrays(H)
//将两个数组合并，并排序，然后去合并后数组的中位数




//05 longest palindromic substring(M)
//最大回文子串：分两种情况，回文子串长度为偶数和奇数：奇数的话直接向两边搜索，偶数的话和下一个数一起向两边搜索
void search_Palindrome(string s, int left, int right, int &start, int &maxLen) {
	while (left >= 0 && right <= s.size() && (s[left] == s[right])) {
		left--;
		right++;
	}
	if (maxLen < (right - left - 1)) {
		start = left + 1;
		maxLen = right - left - 1;
	}
}

string Longest_Palindrome(string s) {
	if (s.size() < 2) {
		return s;
	}
	int maxLEN = 0;
	int start = 0;
	for (int i = 0; i < s.size() - 1; i++) {
		search_Palindrome(s, i, i, start, maxLEN);
		search_Palindrome(s, i, i + 1, start, maxLEN);
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
		res = max(res, min(height[left], height[right])*(left - right));
		height[left] < height[right] ? left++ : right--;
	}
	return res;
}


// three sum(M)
//two sum
//先排序
vector<int> twoSum(vector<int>& nums, int target, int start, int end) {
	sort(nums.begin(), nums.end());
	vector<int> res;
	int left = start;
	int right = end;
	while (left <= right) {
		if (nums[left] + nums[right] > target) {
			right--;
		}
		else if (nums[left] + nums[right] > target) {
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
		res_two_sum = (twoSum(nums, target - nums[i], start, end));
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

	vector<string> res = { "" };
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
	ListNode * res = NULL;
	if (l1->value > l2->value) {
		res = l1;
		mergeTwoLists(l1->next, l2);
	}
	else {
		res = l2;
		mergeTwoLists(l1, l2->next);
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
			mergeTwoLists(lists[i], lists[i + k]);
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
	sort(candidates.begin(), candidates.end());

	for (int i = 0; i < candidates.size(); i++) {
		if (candidates[i] > target) {
			break;
		}
		else if (candidates[i] == target) {
			res.push_back({ candidates[i] });
			continue;
		}

		vector<int> remaining = vector<int>(candidates.begin() + 1, candidates.end());
		vector<vector<int>> tmp = combinationSum(remaining, target - candidates[i]);
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

	for (i = 0, max = A.front(), left[0] = A.front(); i < A.size(); i++) {
		if (A[i] < max) {
			left[i] = max;
		}
		else {
			left[i] = A[i];
			max = A[i];
		}
	}

	for (j = A.size() - 2, max = A.back(), right.front() = A.back(); j >= 0; j--) {
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
	permutation_DFS(num, 0, res);
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
		sort(sr.begin(), sr.end());
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
			A[j] = i;
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
	for (int i = 2; i <= n; i++) {
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
	vector<int> tmp = Inorder(root);
	for (vector<int>::iterator it = tmp.begin(); it<tmp.end() - 1; it++) {
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
	return IsSymmetric_recursive(root->left, root->right);
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
		buy = min(buy, price);
		res = max(res, (price - buy));
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
		res = 0;
		return res;
	}
	int left = max(Max_PathSum_recursive(root->left, res), 0);
	int right = max(Max_PathSum_recursive(root->right, res), 0);
	res = max((left + right + root->value), res);
	return max(left, right) + root->value;
}


int Max_PathSum(TreeNode *root) {
	int res = INT_MIN;
	Max_PathSum_recursive(root, res);
	return res;
}



//48 Largest consecutive sequence (H)
//对数组中的每一个元素进行：在set中查找该value,然后删除value,去该数的前一个数pre=value-1,和后一个数behind=value+1;
//在数组中查找，然后res=behind-pre+1;再取每个res中的最大res;
int longestConsecutive(vector<int>& nums) {
	int res = 0;
	unordered_set<int> tmp(nums.begin(), nums.end());
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
	if (head && head->next) {
		return false;
	}
	ListNode *fast = head;
	ListNode *slow = head;
	while (fast->next != NULL && fast->next->next != NULL && slow->value != fast->value) {
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

void Qucik_sort(vector<TreeNode *> num, int left, int right) {
	while (left < right) {
		int pivot_index = partition(num, left, right);
		Qucik_sort(num, left, pivot_index - 1);
		Qucik_sort(num, pivot_index + 1, right);
	}
}


//55 Maximum product subarray (M)
//DP:两个数值，一个保存最大值，一个保存，最小值

int maxProduct(vector<int>& nums) {
	int res = nums[0];
	int length = nums.size();
	vector<int> f_max(length, 0);
	vector<int> f_min(length, 0);
	f_max[0] = f_min[0] = nums[0];

	for (int i = 1; i < length; i++) {
		f_max[i] = max(max(f_max[i - 1] * nums[i], f_min[i - 1] * nums[i]), nums[i]);
		f_min[i] = min(min(f_max[i - 1] * nums[i], f_min[i - 1] * nums[i]), nums[i]);
		res = max(res, f_max[i]);
	}
	return res;
}


// 56 Min stack (E)
int Min_stack(stack<int> s) {
	stack<int> s1;
	int res = s.top();
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

	while (headA && headB && headA != headB) {
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
	vector<int> res = { num[0],max(num[0],num[1]) };
	for (int i = 2; i < num.size(); i++) {
		res.push_back(max((num[i] + res[i - 2]), num[i]));
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
	vector<vector<bool>> visited(row, vector<bool>(colume, false));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < colume; j++) {
			if (!visited[i][j] && grid[i][j] == '1') {
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
	ListNode *res = NULL;
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
	ListNode *slow = head;
	ListNode *fast = head;
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
	TreeNode *left = lowestCommonAncestor(root->left, p, q);
	TreeNode *right = lowestCommonAncestor(root->right, p, q);
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
	sort(starts.begin(), starts.end());
	sort(ends.begin(), ends.end());

	int end_index = 0;
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
	vector<int> dp(n + 1, INT_MAX);
	dp[0] = 0;
	for (int a = 0; a <= n; a++) {
		for (int b = 0; a + b*b <= n; b++) {
			dp[a + b*b] = min(dp[a + b*b], dp[a] + 1);
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