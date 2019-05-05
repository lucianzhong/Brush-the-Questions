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
/*
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
*/




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



//28-�ַ���������
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
			swap(str[j],str[start]);
			Permutation(str, j+1, end);
			swap(str[j], str[start]);
		}
	}
}





//29-�����г��ִ�������һ�������





//30-��С��K����


//31-��������������� DP
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



//32-��1��n������1���ֵĴ���


//33-�������ų���С����
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



//34-����
//��һ���������ж�һ�����ǲ��ǳ����ĺ���
//�ڶ�����ѭ������




//35-��һ��ֻ����һ�ε��ַ�λ��
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


//36-�����е������
//ð�ݵķ�����ÿ��һ�Σ�������һ



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



//40 ������ֻ����һ�ε�����



//41 ��ΪS����������
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



//42-����ת�ַ��� 
//string.substr()
string LeftRotateString_1(string str, int n) {
	string New_string = str + str;
	string res = "";
	res = New_string.substr(n, str.size());
	return res;
}


//44-�˿���˳��
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


//45-�����ǵ���Ϸ(ԲȦ�����ʣ�µ���)
//Լɪ��




//46-��1+2+3+...+n
//��·���� n && (sum(n-1))



//47-���üӼ��˳����ӷ�



//49-���ַ���ת��������

//50


//51-�������ظ�������
//a[a[i]]


//55-�ַ����е�һ�����ظ����ַ� 
//hash table


//56-�����л�����ڽ��

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


//57-ɾ���������ظ��Ľ��






//58-����������һ�����
//���������



//59-�ԳƵĶ�����

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



//60-�Ѷ�������ӡ�ɶ���  BFS

//61-��֮����˳���ӡ������



//62 - ���л�������


//63-�����������ĵ�K�����
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



//////////////////////////////////////////////////////////////////////////////
// LeetCode 100


//01 Two Sum(E)
//��ʹ������Ȼ��ȡ��ֵ��ͷ��β����ӣ��������sum�Ͱ�β��ǰ�ƣ����С��sum����ͷ��ǰ�ƶ���ֱ������sum



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
//����������ϲ���������Ȼ��ȥ�ϲ����������λ��




//05 longest palindromic substring(M)
//�������Ӵ�������������������Ӵ�����Ϊż���������������Ļ�ֱ��������������ż���Ļ�����һ����һ������������
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
//������ʽƥ�䣺�ݹ�&���������

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
//���ǿ���������ָ�룬һ��ָ��leftָ��ʼ����һ��rightָ���β�����leftľ���rightľ�尫���Ǿ���leftָ�����ƣ�
//���leftľ���rightľ��ߣ���ôrightָ�����ơ�Ϊʲô����leftľ���rightľ��߾�����left�أ���ΪľͰЧӦ��ʢˮ�����٣�ȡ�����ǿ���̵İ�
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
//������
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
//�����ֵ䣺ÿ�����ִ�����ַ�����Ȼ��ݹ飺DFS
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
//���ҵ���N��������������ָ��
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



//11 valid parenthese ��֤����(E)
//ʹ��ջ�����Ϊ�����ţ��ͽ�����ջ��������������ţ����ó�ջ��Ԫ�رȽ�

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
//�ݹ�
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
//����
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
//Ѱ������Ӵ����⣺ջ��DP
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
//����������left,mid,right
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
//������ֲ��� binary search
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
//���ֲ���
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
//�������ٵݹ�
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
//1. ��������ɨ��һ�飬����ÿһ�����꣬��ȡ������ֵ��
//2. ��������ɨ��һ�飬����ÿһ�����꣬�������ֵ��
//3. ��ɨ��һ�飬��ȡ�ݻ����Ӻ͡�volume[i] = [min(left[i], right[i]) - A[i]] * 1�������1�ǿ�ȣ����the width of each bar is 2, �Ǿ�Ҫ����2��
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
//ȫ����

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
//���ضԽ�����ת������x����ת
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
//��λ�ʾ��������ַ�������ĸ���ֵĴ�����һ����ֻ��λ�ò�ͬ������abc��bac, cba�����Ǿͻ�Ϊ��λ��
//�Ѵ�λ�ʣ��������һ���ģ�ʹ��map
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
//��������ת��������
//�����Ҫ��Ѷ�����չ������������չ�����γɵ������˳���������ʹ�������������ôֻҪ�����ı������еݹ�ͷǵݹ�����ַ�������⣬��������Ҳ�����ַ�������⡣���������ݹ�汾�ģ�˼·��������DFS��˼·�ҵ������ӽڵ㣬Ȼ��ص��丸�ڵ㣬���丸�ڵ�����ӽڵ�Ͽ�����ԭ���ӽ�����ϸ��ڵ�����ӽڵ��ϣ�Ȼ���ٰ�ԭ���ӽڵ����������ӽڵ�����ӽڵ��ϣ�Ȼ���ٻص���һ���ڵ�����ͬ����
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
//�����Ǿ���Ĳ�������

//-�����ʼ��ɨ��һ��T���Ѷ�Ӧ���ַ�������ֵĴ����浽HashMap�С�

//- Ȼ��ʼ����S���Ͱѱ���������ĸ��Ӧ��HashMap�е�value��һ�������1���Դ��ڵ���0��cnt����1��

//- ���cnt����T������ʱ����ʼѭ������¼һ���ִ���������С�ִ�ֵ��Ȼ���Ӵ��ڵ���߽������ƣ����ĳ���Ƴ�������ĸ��T���в���ȱ�ٵ���ĸ����ôcnt�Լ�1����ʾ��ʱT����û����ȫƥ�䡣
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
//�Ӽ���
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
//�����ά����board�ĵ�ǰ�ַ���Ŀ���ַ���word��Ӧ���ַ���ȣ���������������ĸ����ַ��ֱ����DFS�ĵݹ麯����ֻҪ��һ������true��
//��ô�ͱ�ʾ�����ҵ���Ӧ���ַ���������Ͳ����ҵ�
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
//���Եó�Count�ĵ��ƹ�ʽΪ,Count[i] = �� Count[0...k] * [k + 1....i]     0 <= k<i - 1,�������˻���Ϊһά��̬�滮��

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
// �ⷨ1���ݹ��ж���ֵ�Ĵ�С�����ҡ��� 
//�ⷨ2�����������Ȼ���ж���ֵ�ĵ���
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
//�ڵݹ麯���У������ǰ��㲻���ڣ���ôֱ�ӷ���0������ͷֱ���������ӽڵ���õݹ麯��������·�����п���Ϊ������
//�����ǵ�Ȼ��ϣ�����ϸ���·���ͣ��������Ǻ�0��ȣ�ȡ�ϴ���Ǹ�������Ҫô���ӣ��Ӿ�Ҫ��������Ȼ������������ȫ�����ֵ���res��
//���������ӽ��Ϊ�յ�����path֮�ͼ��������ӽ��Ϊ�յ�����path֮�ͣ���Ҫ���ϵ�ǰ���ֵ�������������һ����������·����
//�����Ƿ���ֵ��ȡleft��right�еĽϴ�ֵ���ϵ�ǰ���ֵ����Ϊ���Ƿ���ֵ�Ķ������Ե�ǰ���Ϊ�յ��path֮�ͣ�
//����ֻ��ȡleft��right�нϴ���Ǹ�ֵ��������������Ҫ

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
//�������е�ÿһ��Ԫ�ؽ��У���set�в��Ҹ�value,Ȼ��ɾ��value,ȥ������ǰһ����pre=value-1,�ͺ�һ����behind=value+1;
//�������в��ң�Ȼ��res=behind-pre+1;��ȡÿ��res�е����res;
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
//���
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
//���������ж�һ�������Ƿ���ڻ�
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
//DP:������ֵ��һ���������ֵ��һ�����棬��Сֵ

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
//�������ȼ����ж�һ������ͼ���Ƿ���ڻ���������ڻ����Ͳ�����������Ҳ���ǲ������������еĿγ�
//Topological Sort via DFS ��������������������������ʵ�֡�
// Topological sort could also be done via BFS ������������ù������������ʵ�֡�
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
//��������
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
//����������С��ͬ���ڵ�
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
//ǰ�����������Ժ���������
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
		if (!q.empty() && q.front() == i - k)         //���������ƶ��ˣ���Ҫpop����ߵ�Ԫ���±�
			q.pop_front();
		while (!q.empty() && nums[q.back()] < nums[i]) //�����ֵ��ǰ�ƶ���˫����еĶ�ͷ
			q.pop_back();
		q.push_back(i);                             //����±�ֵi
		if (i >= k - 1)
			res.push_back(nums[q.front()]);         //��i=k-1��ʼ����Ҫ�������ֵ����ʱ��ʼ�����ͷ��res
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
// ÿ����������ʱ��������ֶ���ͷ���������±꣬�Ǵ�������������±꣬���ӵ�
if (!deque.isEmpty() && deque.peekFirst() == i - k) deque.poll();
// �Ѷ���β�����б�����С�Ķ��ӵ�����֤�����ǽ����
while (!deque.isEmpty() && nums[deque.peekLast()] < nums[i]) deque.removeLast();
// ��������
deque.offerLast(i);
// ����ͷ�����Ǹô����ڵ�һ���
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



//75 Find the Duplicate Number Ѱ���ظ���(M)
// ��������
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