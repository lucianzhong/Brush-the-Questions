#include <iostream>
#include <vector>
#include <stack>
#include<queue>
#include <string>
#include<map>

using namespace std;


//https://github.com/gatieme/CodingInterviews




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
		Permutation(str, j + 1, end);
		swap(str[j], str[start]);
	}
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