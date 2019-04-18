#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

// ����
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


//�ر��㷨
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <1> ����
//��������(Quick Sort)�Ƕ�ð�������һ�ָĽ�������˼����ѡȡһ����¼��Ϊ���ᣬ����һ�����򣬽��������з�Ϊ�������֣�����һ���ֵ�ֵ��С�����ᣬ
//��һ���ֶ��������ᡣȻ��������������ּ����������򣬴Ӷ�ʹ�������дﵽ����
//����n^2����ĿҪ O(nlogn)����O���ţ��αȽϡ����״��������ҪO(n2)�αȽ�
//���ȶ�����
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
	if (left >= right)//��ʾ�Ѿ����һ����
	{
		return;
	}
	int index = PartSort(array, left, right);//�����λ��
	QuickSort(array, left, index - 1);
	QuickSort(array, index + 1, right);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <2>  �����򣺶������ǲ��ȶ�����
// �ѵ����ʣ�ÿ���ڵ��ֵС�ڵ����丸�ڵ� �� ���ڵ��ڸ��ڵ㣻ǰ�߳�Ϊ�����ѡ����������򣬺���Ϊ����С�ѡ������ڽ��� ����һ����ȫ����������˳����������ģ��
//��ȫ������������һ����������n�㣬��ô�����1��n-1���ÿ���ڵ㶼�ﵽ���ĸ�����2���ҵ�n��������Ǵ������������ſ��ģ���ô�ͳ���Ϊ��ȫ������
//ע�⣺�����򷽷��������ڸ����ٵ����У���Ϊ��ʼ��������Ҫʱ�䣻
//ƽ��ʱ�临�Ӷ�O(n log n)�� ���ռ临�Ӷ�O(n)
//��1����д�㷨����10�ڸ����������У�ѡ����������10000����
//������������
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//������ĺ����ǽ���,�������Ϊ���飬���ڵ�λ�ã����鳤��
void Heap_build(int a[], int root, int length)
{
	int lchild = root * 2 + 1;//���ڵ�����ӽ���±�
	if (lchild < length)//���ӽ���±겻�ܳ�������ĳ���
	{
		int flag = lchild;//flag�������ҽڵ������ֵ���±�
		int rchild = lchild + 1;//���ڵ�����ӽ���±�
		if (rchild < length)//���ӽ���±겻�ܳ�������ĳ���(����еĻ�)
		{
			if (a[rchild] > a[flag])//�ҳ������ӽ���е����ֵ
			{
				flag = rchild;
			}
		}
		if (a[root] < a[flag])
		{
			//���������ͱȸ����������ӽڵ�
			Swap(a[root], a[flag]);
			//�Ӵ˴�����ӽڵ���Ǹ�λ�ÿ�ʼ�ݹ齨��
			Heap_build(a, flag, length);
		}
	}
}

void Heap_sort(int a[], int len)
{
	for (int i = len / 2; i >= 0; --i)//�����һ����Ҷ�ӽڵ�ĸ���㿪ʼ����
	{
		Heap_build(a, i, len);
	}

	for (int j = len - 1; j > 0; --j)//j��ʾ�����ʱ�ĳ��ȣ���Ϊlen�����Ѿ������ˣ���len-1��ʼ
	{
		Swap(a[0], a[j]);//������βԪ��,�����ֵ��������������λ�ñ���
		Heap_build(a, 0, j);//ȥ�����λ�õ�Ԫ�����½��ѣ��˴�j��ʾ����ĳ��ȣ����һ��λ���±��Ϊlen-2
	}

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <3> ���ֲ���
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
// <4>  �������㷨  
// �� 3^20 = 9^10 = 81^5 (= 81*81^4) = 81*6561^2 = 81*43046721
// �����ⷨ������������ - O(n) �������� - O(logN)

double quickPow(double base, int p) {
	double res = 0;
	int q = abs(p);
	if (q > 0) {
		if (q & 1) {  //���ָ��Ϊ������һ�������ϳ� 2 ������һ�λ���������2/2 = 1
			res *= base;
			base *= base;
			q >>= 1;  //����2������һλ
		}
	}

	return res > 0 ? res : 1 / res;}


//////////////////////////////////////////////////////////////////////////////////////////////////
//  <5> atoi() ���ַ���ת��Ϊ����
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
// <6> ��������1�ĸ���
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
// <7>  ��Ŀ����:����һ���ǿ��������飬����ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�
// ��� ��ͬΪ�٣���ͬΪ�� 

int singleNumber(vector<int>& nums) {
	int ret = 0;
	for (auto i : nums)
		ret ^= i; //��λ���
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// <8> ͳ��һ�����������������г��ֵĴ���
// ���ֲ��������½�
int Get_Numberof_K(vector<int> data, int k) {
	return upper_bound(data.begin(), data.end(), k) - lower_bound(data.begin(), data.end(), k);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// <9>
//����һ�����������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ����������������{3��32��321}�����ӡ���������������ųɵ���С����Ϊ321323
static bool cmp(int &left, int & right) { // ��Ҫ��̬����
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