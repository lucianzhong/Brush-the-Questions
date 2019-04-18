#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

// 容器
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
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x),left(NULL),right(NULL){}
};

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


//必背算法
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <1> 快排
//快速排序(Quick Sort)是对冒泡排序的一种改进，基本思想是选取一个记录作为枢轴，经过一趟排序，将整段序列分为两个部分，其中一部分的值都小于枢轴，
//另一部分都大于枢轴。然后继续对这两部分继续进行排序，从而使整个序列达到有序。
//排序n^2个项目要 O(nlogn)（大O符号）次比较。在最坏状况下则需要O(n2)次比较
//不稳定排序
int PartSort(int* array, int left, int right)
{
	int& key = array[right];
	while (left < right)
	{
		while (left < right && array[left] <= key)
		{
			++left;
		}
		while (left < right && array[right] >= key)
		{
			--right;
		}
		swap(array[left], array[right]);
	}
	swap(array[left], key);
	return left;
}

void QuickSort(int* array, int left, int right)
{
	assert(array);
	if (left >= right)//表示已经完成一个组
	{
		return;
	}
	int index = PartSort(array, left, right);//枢轴的位置
	QuickSort(array, left, index - 1);
	QuickSort(array, index + 1, right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <3> 二分查找
int binary_search(vector<int> nums, int v) {
	if (nums.size() < 1) {
		return -1;
	}

	int left = 0;
	int right = nums.size()-1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (nums[mid] == v) {
			return mid;
		}
		else if (nums[mid] > v){
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return -1;
}


////////////////////////////////////////////////////////////////////////////////////////////
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

	return res > 0 ? res : 1 / res;}


//////////////////////////////////////////////////////////////////////////////////////////////////
//  <5> atoi() 将字符串转换为整数
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
		sign = 1;
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



//////////////////////////////////////////////////////////////////////////////////////////////////
// <6> 二进制中1的个数
int Number_of_one(int number) {
	int count = 0;
	while (number!=0) {
		if (number & 1) {
			count++;
		}
			number >>= 1;	
	}
	return count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// <7>  题目描述:给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
// 异或： 相同为假，不同为真 

int singleNumber(vector<int>& nums) {
	int ret = 0;
	for (auto i : nums)
		ret ^= i; //按位异或
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// <8> 统计一个数字在排序数组中出现的次数
// 二分查找搜上下界
int Get_Numberof_K(vector<int> data, int k) {
	return upper_bound(data.begin(), data.end(), k) - lower_bound(data.begin(), data.end(), k);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////














/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main() {


	int arr[]{ 10,6,1,2,2,7,9,3,4,5,8,8 };
	int n = sizeof(arr) / sizeof(int);

	QuickSort(arr, 0, n - 1);

	for (int i = 0; i < n; i++) {
		cout << arr[i] << "  ";
	}

	cout << endl;
	
	vector<int> arr_1{ 1,2,3,4,5,6,7 };
	
	cout << binary_search(arr_1, 6) << endl;

	cout << endl;
	cout << Number_of_one(5) << endl;


	vector<int> arr_2{ 1,1,2,2,3,3,7 };

	cout << singleNumber(arr_2) << endl;

	cout << Print_min_number(arr_2) << endl;
	return 0;
}