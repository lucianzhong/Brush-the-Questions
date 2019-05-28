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

// Ԥ�ȶ������ֵ�������������ȣ�
vector<int> a = {2,0,1,5,2,4,6};


// (1) ��������
/*
���������˼�롢ʱ�临�Ӷȡ�ʵ���Լ��Ż�����
�𣺿���������������裺
(1)ѡ���׼���ڴ��������У�����ĳ�ַ�ʽ����һ��Ԫ�أ���Ϊ "��׼"��pivot����
(2)�ָ�������Ըû�׼�������е�ʵ��λ�ã������зֳ����������С���ʱ���ڻ�׼��ߵ�Ԫ�ض��ȸû�׼С���ڻ�׼�ұߵ�Ԫ�ض��Ȼ�׼��
(3)�ݹ�ض��������н��п�������ֱ������Ϊ�ջ���ֻ��һ��Ԫ�ء�
*/

void quicksort(vector<int> &v, int left, int right) {
	if (left >= right) {
		return;
	}
	int key = v[left];
	int lower = left;
	int upper = right;
	while (lower < upper) {
		while (lower < upper && v[upper] >= v[lower]) {    //�Ӻ���ǰ����
			upper--;
		}
		swap(v[lower], v[upper]);

		while (lower < upper && v[lower] <= v[upper]) {			//��ǰ�������
			lower++;
		}
		swap(v[lower], v[upper]);

		quicksort(v, left, lower - 1);		//���
		quicksort(v, upper + 1, right);     //�Ҷ�
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


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ָoffer 66




// 003-��ά�����еĲ���
//��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳�����������һ������������������һ����ά�����һ��������
//�ж��������Ƿ��и�������
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


// 004-�滻�ո�
//��ʵ��һ����������һ���ַ����еĿո��滻�ɡ�%20���� ���磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy
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


// 005-��β��ͷ��ӡ����
//����һ��������β��ͷ��ӡ����ÿ���ڵ��ֵ��(stack)

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

// 006-�ؽ�������
//����ĳ��������ǰ���������������Ľ�������ؽ����ö����������������ǰ���������������Ľ���ж������ظ�������

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


// 007-������ջʵ�ֶ���
class Solution_7 {
public:
	void push(int node) {
		stackIn.push(node);
	}

	int pop() {
		int node = -1;
		//  ����ջ����NULL��ʱ����������Ϊ��
		if (this->empty() == true) {
			return -1;
		}
		else {
			//  �����������Ԫ��
			//  ��ʱ�����������
			//  �����ջ��Ϊ�յ�ʱ��, ֱ�ӽ����ջ��Ԫ�ص�������
			//  �����ջΪNULL, ��������ջ��Ϊ�յ�ʱ����Ҫ������ջ��Ԫ��ȫ���������ջ��
			if (stackOut.empty() == true) {     //  ��ʱ���ջΪ��, ����ջ�ز�Ϊ��
												//  ��ʱ����ջ�����ջ����û��Ԫ��
												//  ��Ҫ������ջ�е�Ԫ�ص������ջ
												// ������ջ����û��Ԫ��
												//  ����Ԫ�ش�����ջ�������ջ
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




// 008-��ת�������С����
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



// 009-쳲���������


// 010-��������1�ĸ���
//����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ
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


// 011-��ֵ�������η�
//д��ָ���Ķ����Ʊ�����13���Ϊ������1101��
/*
���� : 10 ^ 1101 = 10 ^ 000110 ^ 010010 ^ 1000��
ͨ�� & 1�� >> 1����λ��ȡ1101��Ϊ1ʱ����λ����ĳ����۳˵����ս����
�����ˣ����������ָ����1�ĸ�����λ���й�ϵ����ô�ͼ��ˣ����ǵý�ָOffer--010 - ��������1�ĸ���
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
		if ((exponent & 1) == 1) { //  ��ǰָ��Ϊ��Ϊ0
			res *= temp;        //  �ͼ���һ���˻�
		}
		//  ��λ��, curr��Ҫ����, �������¸�
		temp *= temp;           // ����
		exponent >>= 1;         // ����һλ
	}
	return res;
}


// 012-��ӡ1������Nλ��





// 014-��������˳��ʹ����λ��ż��ǰ��
//����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣�
//���е�ż��λ��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣//�����ⷨ�Լ�ð�ݽⷨ

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


// 015 - �����е�����k�����
// ˫ָ�뷨

// 016-��ת����
// ˼·һ�� ����ԭ������ÿ��Ԫ�ز��뵽һ���µ������е�ͷ��
// ˼·���� ��ָ�뻬��pPrev -> pNode -> pNext


// 017-�ϲ��������������
// ������ָ��ͬ��������������ÿ���ҵ�С���Ǹ����뵽�µ�������


// 018-�����ӽṹ
// �ڶ������ж���A����RΪ�����������ǲ��ǰ�������Bһ���Ľṹ�� ���������ʵ����ҪҪ�ж���������Ӧ�Ľڵ������Ƿ���ͬ�������һ���ݹ�Ĺ���
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

// ��һ������A���ҵ���B�ĸ��ڵ��ֵһ���Ľ��R�� ��ʵ���Ͼ������ı����������õݹ�ʵ��
bool has_tree(TreeNode* parent, TreeNode* child) {
	if (child == NULL || parent == NULL) {
		return false;
	}
	bool result;
	if (parent->value == child->value) {
		result = DoesParentHasChild(parent->left, child) || DoesParentHasChild(parent->right, child);//  ������������ ���������в���
	}
	else {
		return true;
	}

}



// 019-�������ľ���
void Mirror_Tree(TreeNode *root) {
	if (root != NULL) {
		swap(root->left, root->right);
	}
	Mirror_Tree(root->left);
	Mirror_Tree(root->right);
}


// 020-˳ʱ���ӡ���� 


// 021-����min������ջ




// 022-ջ��ѹ�뵯������
//�����һ�����������ָպ���ջ�����֣���ôֱ�ӵ�����
//�����һ�����������ֲ���ջ�������ǰ�ѹջ�����л�û����ջ������ѹ�븨��ջ��ֱ������һ����Ҫ����������ѹ��ջ��Ϊֹ��
//������е����ֶ�ѹ��ջ����Ȼû���ҵ���һ�����������֣���ô�����в�������һ����������

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


// 023-�������´�ӡ������
// �������´�ӡ����������ÿ���ڵ㣬ͬ��ڵ�������Ҵ�ӡ
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

// 024-�����������ĺ����������
//����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ�������Һ�

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


// 025-�������к�Ϊĳһֵ��·��
// ����һ�Ŷ�������һ����������ӡ���������н��ֵ�ĺ�Ϊ��������������·����·������Ϊ�����ĸ���㿪ʼ����һֱ��Ҷ����������Ľ���γ�һ��·��



// 026-��������ĸ���



// 027-������������˫������



// 028-�ַ���������
//�Ӽ���������ѡ��ÿһ��Ԫ�أ���Ϊ���еĵ�һ��Ԫ�أ�Ȼ���ʣ���Ԫ�ؽ���ȫ���У���˵ݹ鴦���Ӷ��õ�����Ԫ�ص�ȫ���С�
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





// 029-�����г��ִ�������һ�������

//�ⷨһ
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



//�ⷨ��
class Solution_29{
public:
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{
		map<int, int> hmap;  //  �������ֵ����ִ�����ӳ��

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



		//  ���ҵ����ִ��������Ǹ�Ԫ��
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


// 030-��С��K����
// ����һ ����

// 031-��������������� DP
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


// 032-��1��n������1���ֵĴ���




// 033-�������ų���С����
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

// 034-����
//��һ���������ж�һ�����ǲ��ǳ����ĺ���
//�ڶ�����ѭ������




// 035-��һ��ֻ����һ�ε��ַ�λ��
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


// 036-�����е������
// �������е��������֣����ǰ��һ�����ִ��ں�������֣����������������һ������ԡ� ����һ�����飬�����������е�����Ե�����
// ð�ݵķ�����ÿ��һ�Σ�������һ



//37-��������ĵ�һ���������
//������������й����ڵ㣬�����ǵ���״��Ȼ��һ��Y���Ρ����������ߣ�ʵ���Ҷ���



//38-���������������г��ֵĴ���
//a[a[i]]


//39-�����������
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

//39-ƽ�������
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



// 040 ������ֻ����һ�ε�����
// ���⿼��������������ص㣺��������ͬ���������Ϊ0


// 041 ��ΪS����������
// ����һ����������������һ������s���������в����������������ǵĺ�������s������ж�����ֵĺ͵���s������˻���С�ļ���
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



// 042-����ת�ַ��� 
//string.substr()
string LeftRotateString_1(string str, int n) {
	string New_string = str + str;
	string res = "";
	res = New_string.substr(n, str.size());
	return res;
}


// 044-�˿���˳��
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


// 045-�����ǵ���Ϸ(ԲȦ�����ʣ�µ���)
//Լɪ��




// 046-��1+2+3+...+n
// ��·���� n && (sum(n-1))



// 047-���üӼ��˳����ӷ�



// 049-���ַ���ת��������

// 050


// 051-�������ظ�������
// a[a[i]]





// 055-�ַ����е�һ�����ظ����ַ� 
// hash table


// 056-�����л�����ڽ��

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
	//      �ƶ�p1��p2
	ListNode *p2 = head;
	while (p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}


// 057-ɾ���������ظ��Ľ��






// 058-����������һ�����
//���������



// 059-�ԳƵĶ�����

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



// 060-�Ѷ�������ӡ�ɶ���  BFS

// 061-��֮����˳���ӡ������



// 062 - ���л�������
// ������������, ����, ������߲�ζ�����
 
// 063-�����������ĵ�K�����
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


//64-������֮�е���λ��
//������


//65-�������ڵ����ֵ
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