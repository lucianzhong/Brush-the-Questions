#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include <string>
#include<map>

using namespace std;


//https://github.com/gatieme/CodingInterviews





//3
//��һ����ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳�����������һ������������������һ����ά�����һ��������
//�ж��������Ƿ��и�������
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
//��ʵ��һ����������һ���ַ����еĿո��滻�ɡ�%20���� ���磬���ַ���ΪWe Are Happy.�򾭹��滻֮����ַ���ΪWe%20Are%20Happy
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
//����һ��������β��ͷ��ӡ����ÿ���ڵ��ֵ��(stack)
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
//����ĳ��������ǰ���������������Ľ�������ؽ����ö����������������ǰ���������������Ľ���ж������ظ�������
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



//7 ������ջʵ�ֶ���
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

		//  ����ջ����NULL��ʱ����������Ϊ��
		if (this->empty() == true)
		{
			

			return -1;
		}
		else
		{
			//  �����������Ԫ��
			//  ��ʱ�����������
			//  �����ջ��Ϊ�յ�ʱ��, ֱ�ӽ����ջ��Ԫ�ص�������
			//  �����ջΪNULL, ��������ջ��Ϊ�յ�ʱ����Ҫ������ջ��Ԫ��ȫ���������ջ��

			if (stackOut.empty() == true)     //  ��ʱ���ջΪ��, ����ջ�ز�Ϊ��
			{
				//  ��ʱ����ջ�����ջ����û��Ԫ��
				//  ��Ҫ������ջ�е�Ԫ�ص������ջ
				// ������ջ����û��Ԫ��

				//  ����Ԫ�ش�����ջ�������ջ
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





//8   ��ת�������С����
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


//9 쳲���������
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
//����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ
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


//11��ֵ�������η�
//д��ָ���Ķ����Ʊ�����13���Ϊ������1101��
/*
���� : 10 ^ 1101 = 10 ^ 000110 ^ 010010 ^ 1000��
	ͨ�� & 1�� >> 1����λ��ȡ1101��Ϊ1ʱ����λ����ĳ����۳˵����ս����
	�����ˣ����������ָ����1�ĸ�����λ���й�ϵ����ô�ͼ��ˣ����ǵý�ָOffer--010 - ��������1�ĸ���
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
		if ((exponent & 1) == 1) //  ��ǰָ��Ϊ��Ϊ0
		{
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
//�����ӽṹ
//1.��һ������A���ҵ���B�ĸ��ڵ��ֵһ���Ľ��R,2.�ڶ������ж���A����RΪ�����������ǲ��ǰ�������Bһ���Ľṹ�� ���������ʵ����ҪҪ�ж���������Ӧ�Ľڵ������Ƿ���ͬ�������һ���ݹ�Ĺ��̡�

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


//16  ��ת����



// 17



// 18


//19-�������ľ���
void Mirror_Tree(TreeNode *root) {
	if (root != NULL) {
		return;
	}
	swap(root->left, root->right);
	Mirror_Tree(root->left);
	Mirror_Tree(root->right);
}




//20-˳ʱ���ӡ����






//21-����min������ջ





//22-ջ��ѹ�뵯������
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


//23-�������´�ӡ������,BFS
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




//24-�����������ĺ����������
//����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ����
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
	else {}
	for (int j = 0; j < end; j++) {
		swap(str[j],str[start]);
		Permutation(str, j + 1, end);
		swap(str[j], str[start]);
	}
}



//29-�����г��ִ�������һ�������





//30-��С��K����



//31-��������������� DP
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



//32-��1��n������1���ֵĴ���


//33-�������ų���С����
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


//34-����
//��һ���������ж�һ�����ǲ��ǳ����ĺ���
//�ڶ�����ѭ������



//35-��һ��ֻ����һ�ε��ַ�λ��
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
		int depth_left = TreeDepthRecursion(root->left);
		int depth_right = TreeDepthRecursion(root->right);
		return max(depth_left,depth_right)+1;
	}
}

//39-ƽ�������
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



//40 ������ֻ����һ�ε�����


//41 ��ΪS����������
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


//42-����ת�ַ��� 
//string.substr()
string LeftRotateString(string str, int n) {
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




//












//55-�ַ����е�һ�����ظ����ַ� 
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




//56-�����л�����ڽ��

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




//60-�Ѷ�������ӡ�ɶ���  BFS

//61-��֮����˳���ӡ������



//62 - ���л�������


//63-�����������ĵ�K�����
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


//64-������֮�е���λ��
//������


//65-�������ڵ����ֵ
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