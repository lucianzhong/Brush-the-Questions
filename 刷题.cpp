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



// ��2��
//��ת����
ListNode * ReverseList(ListNode *head) {
	if (head == NULL || head->next == NULL) {  //����Ϊ��ֱ�ӷ��أ���H->nextΪ���ǵݹ��
		return head;
	}

	ListNode* new_ListNode = ReverseList(head->next);//һֱѭ������β 
	
	head->next->next = head;  //��ת�����ָ��
	head->next = NULL;  //�ǵø�ֵNULL����ֹ�������
	return new_ListNode;  //������ͷ��Զָ�����ԭ�������β
}


//��3���ϲ�����
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


// ��4�� �����ĸ߶�
int Height_tree(TreeNode * root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int height = Height_tree(root->left) > Height_tree(root->right) ? Height_tree(root->left) + 1 : Height_tree(root->right) + 1;
		return height;
	}
}


// ��5�� ���ľ��� 
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



// ��6�� �����е�k���ڵ�
ListNode * Kth_Node(ListNode *root, int k) {
	ListNode *fast_node = root + k;
	ListNode *slow_node = root;

	while (fast_node != NULL) {
		slow_node = slow_node->next;
	}
	return slow_node;
}


// ��7�� Fibonacii����
int Fibonacci(int n) {
	if (n == 1 || n == 2) {
		return n;
	}
	else {
		return (Fibonacci(n - 1) + Fibonacci(n - 2));
	}
}

// ��8�� �������к�Ϊһֵ��������
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


// ��9�� ���ľ���
TreeNode * Mirror_TreeNode(TreeNode *root) {
	if (root != NULL) {
		swap(root->left, root->right);
		Mirror_TreeNode(root->left);
		Mirror_TreeNode(root->right);
	}
	return root;
}



// ��10�� ������ȱ���
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


// ��11�� �ַ����е�һ�����ظ����ַ�
// ��ϣ��
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



//��12�� �������򣨷�ת����ʹ��stack
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
		head->next = reverse_list.top();//��ͷ�ڵ�ָ��ջ��Ԫ��������ĵ�һ���ڵ�ĵ�ַ��
		head = reverse_list.top();//����ָ�����
		reverse_list.pop();
	}
	head->next = NULL; // ������ĩβָ��NULL
}


//��13�� ���ַ������ҳ�����������ִ�������������ĳ��ȷ��أ�
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


//��14�� ����ת�ַ������ַ�����
string LeftRotateString(string str, int n) {
	int len = str.size();
	if (len == 0) {
		return " ";
	}
	n = n%len;
	str += str;
	return (str.substr(n, len));
}


// ��15�� һ�����ֶ�������1�ĸ���
int NumberOfOne(int n) {
	int i = 0;
	while (n) {
		if (n && 1 == 1) {
			i++;
		}
		n >>=1; //����һλ
	}
	return i;
}


// ��16�����������������С�����һ�����б�ʾջ��push˳���ж���һ��������û�п����Ƕ�Ӧ��pop˳��
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


//��17���ڴ�1��n��������1���ֵĴ��������飩
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


// ��18��
//��һ�����������Ķ�ά����(Ԫ�غ����)
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

	for (k = 0; k<n; k++){//��ʼ��b[]
		b[k] = 0;
	}
	for (i = 0; i<n; i++){

		for (j = i; j<n; j++){//�ѵ�i�е���j�����,��ÿһ�����������ֵ
		  for (k = 0; k<n; k++){
				b[k] += array[j][k];//j�е�������
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
�����飩
2010������������
�����⣺
������������ n �� m��������1��2��3.......n �� ����ȡ������,
ʹ��͵��� m, Ҫ���������еĿ�������г���.
���������������һ�㶼��ʹ�õݹ�Ĳ��ԣ����ǵ�n������Ϊm,����Ҫ����ĺ���Ϊf(n,m), ��������ѡ���˵�n��������ô����ͱ����f(n-1,m-n)��
����Ļ��������f(n-1,m), �ٿ����±߽������� ���n<1 ���� m<1��Ȼ�����н���� ���n==m����ô��Ȼ�������һ�������,Ȼ������ͱ����f(m-1,m)
*/
void BagProblem(int n, int m) {
	vector<int> res;
	if (n == 1 || m == 1) {
		return;
	}
	if (m>n) {
		res.push_back(n);
		BagProblem(n - 1, m - n);//ѡ��n
		res.pop_back();
		BagProblem(n - 1, m);//not choose n
	}
	else {
		vector<int>::iterator it;
		for (it = res.begin(); it < res.end(); it++) {
			cout << *it << endl;
		}
		cout << m << endl; //��m<nʱ��һ���������m��Ȼ���ڵݹ�
		BagProblem(m - 1, m);
	}
}





// (20)
int sum(int n) {
	int res = n;
	res && (res += sum(n - 1));
	return res;
}


// (21) ���ֲ���
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
// ��Ŀ����:����һ���ǿ��������飬����ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�
// ��� ��ͬΪ�٣���ͬΪ�� 

int singleNumber(vector<int>& nums) {
	int ret = 0;
	for (auto i : nums)
		ret ^= i; //��λ���
	return ret;
}



// (23)
// atoi() ���ַ���ת��Ϊ����
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

	return res > 0 ? res : 1 / res;
}



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





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��ָoffer

//3
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


//4
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
	list[2].value= 3;
	list[2].next = &list[3];
	list[3].value = 4;
	list[3].next = NULL;
	

	printListFromTailToHead( list );
}
*/


//6
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

	for (int i = 1; i < root_index_in+1; i++) {
		pre_left.push_back(pre[i]);
	}


	for (int i = root_index_in + 1; i < pre_length; i++) {
		pre_right.push_back(pre[i]);
	}

	reConstructBinaryTree(in_left, pre_left);
	reConstructBinaryTree(in_right, pre_right);
}


//7 ������ջʵ�ֶ���
class Solution_7{
public:
	void push(int node)	{
		stackIn.push(node);
	}

	int pop()	{
		int node = -1;
		//  ����ջ����NULL��ʱ����������Ϊ��
		if (this->empty() == true){
			return -1;
		}
		else{
			//  �����������Ԫ��
			//  ��ʱ�����������
			//  �����ջ��Ϊ�յ�ʱ��, ֱ�ӽ����ջ��Ԫ�ص�������
			//  �����ջΪNULL, ��������ջ��Ϊ�յ�ʱ����Ҫ������ջ��Ԫ��ȫ���������ջ��
			if (stackOut.empty() == true){     //  ��ʱ���ջΪ��, ����ջ�ز�Ϊ��
				//  ��ʱ����ջ�����ջ����û��Ԫ��
				//  ��Ҫ������ջ�е�Ԫ�ص������ջ
				// ������ջ����û��Ԫ��
				//  ����Ԫ�ش�����ջ�������ջ
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



//8   ��ת�������С����
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



//9 쳲���������


//10
//����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ
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




//11��ֵ�������η�
//д��ָ���Ķ����Ʊ�����13���Ϊ������1101��
/*
���� : 10 ^ 1101 = 10 ^ 000110 ^ 010010 ^ 1000��
ͨ�� & 1�� >> 1����λ��ȡ1101��Ϊ1ʱ����λ����ĳ����۳˵����ս����
�����ˣ����������ָ����1�ĸ�����λ���й�ϵ����ô�ͼ��ˣ����ǵý�ָOffer--010 - ��������1�ĸ���
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
		if ((exponent & 1) == 1){ //  ��ǰָ��Ϊ��Ϊ0
			res *= temp;        //  �ͼ���һ���˻�
		}
		//  ��λ��, curr��Ҫ����, �������¸�
		temp *= temp;           // ����
		exponent >>= 1;         // ����һλ
	}
	return res;
}


//12 ��ӡ1������Nλ��






//13


//14
//����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣�
//���е�ż��λ��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣//�����ⷨ�Լ�ð�ݽⷨ

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
//�����ӽṹ
//  ��һ������A���ҵ���B�ĸ��ڵ��ֵһ���Ľ��R,
//  �ڶ������ж���A����RΪ�����������ǲ��ǰ�������Bһ���Ľṹ�� ���������ʵ����ҪҪ�ж���������Ӧ�Ľڵ������Ƿ���ͬ�������һ���ݹ�Ĺ��̡�

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




//16  ��ת����



// 17



// 18


//19-�������ľ���
void Mirror_Tree(TreeNode *root) {
	if (root != NULL) {
		swap(root->left, root->right);
	}
	Mirror_Tree(root->left);
	Mirror_Tree(root->right);
}


//20-˳ʱ���ӡ����






//21-����min������ջ




//22-ջ��ѹ�뵯������
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


//23-�������´�ӡ������,BFS
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



//24-�����������ĺ����������
//����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����

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




//25-�������к�Ϊĳһֵ��·��

//26��������ĸ���



//27-������������˫������









int main() {



	return 0;
}