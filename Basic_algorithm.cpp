
#include <iostream>
#include <vector>
#include <stack>

using namespace std;



// 排序： 冒泡排序，快速排序，堆排序

/* (1) 快速排序
分治问题
快速排序的思想、时间复杂度、实现以及优化方法
答：快速排序的三个步骤：
(1)选择基准：在待排序列中，按照某种方式挑出一个元素，作为 "基准"（pivot）
(2)分割操作：以该基准在序列中的实际位置，把序列分成两个子序列。此时，在基准左边的元素都比该基准小，在基准右边的元素都比基准大
(3)递归地对两个序列进行快速排序，直到序列为空或者只有一个元素
复杂度分析
在最好的情况下，每次 partition 都会把数组一分为二，所以时间复杂度 T(n) = 2T(n/2) + O(n),解为 T(n) = O(nlog(n))
在最坏的情况下，数组刚好和想要的结果顺序相同，每次 partition 到的都是当前无序区中最小(或最大)的记录，因此只得到一个比上一次划分少一个记录的子序列。T(n) = O(n) + T(n-1),解为 T(n) = O(n²)
在平均的情况下，快排的时间复杂度是 O(nlog(n))
*/

void quicksort(vector<int> &v, int left, int right) {
	if (left >= right) {
		return;
	}
	int lower = left;
	int upper = right;
	while (lower < upper) {
		while (lower < upper && v[upper] >= v[lower]) {    //从后向前搜索
			upper--; // 找到第 1 个比基准数小的值，让它与基准值交换
		}
		swap(v[lower], v[upper]);
		while (lower < upper && v[lower] <= v[upper]) {			//从前向后搜索
			lower++; // 找到第 1 个比基准数大的值，让它与基准值交换
		}
		swap(v[lower], v[upper]);
        // 然后继续寻找，直到 i 与 j 相遇时结束，最后基准值所在的位置即 k 的位置，
        // 也就是说 k 左边的值均比 k 上的值小，而 k 右边的值都比 k 上的值大
	}
    	quicksort(v, left, lower - 1);		//左段
		quicksort(v, upper + 1, right);     //右段
}


// (2) 冒泡排序
// 冒泡排序的复杂度，在最好情况下，即正序有序，则只需要比较n次。故，为O(n) ，最坏情况下，即逆序有序，则需要比较(n-1)+(n-2)+……+1，故，为O(n²)。
// void BubbleSort(int[] array)
// {
//     for (var i = 0; i < array.Length - 1; i++)  // 若最小元素在序列末尾，需要 n-1 次交换，才能交换到序列开头
//     {
//         for (var j = 0; j < array.Length - 1; j++)
//         {
//             if (array[j] > array[j + 1])   // 若这里的条件是 >=，则变成不稳定排序
//             {
//                 Swap(array, j, j+1);
//             }
//         }
//     }
// }


//（3）  堆排序：堆排序是不稳定排序
// 堆的性质：每个节点的值小于等于其父节点 或 大于等于父节点；前者称为“最大堆”，用于升序，后者为“最小堆”，用于降序， 堆是一棵完全二叉树，因此常用数组进行模拟
//完全二叉树：假设一个二叉树有n层，那么如果第1到n-1层的每个节点都达到最大的个数：2，且第n层的排列是从左往右依次排开的，那么就称其为完全二叉树
//注意：此排序方法不适用于个数少的序列，因为初始构建堆需要时间；
//平均时间复杂度O(n log n)， 最差空间复杂度O(n)

// 1）利用给定数组创建一个堆H[0..n-1]（我们这里使用最小堆），输出堆顶元素
// 2）以最后一个元素代替堆顶，调整成堆，输出堆顶元素
// 3）把堆的尺寸缩小1
// 4） 重复步骤2，直到堆的尺寸为1

//例1：编写算法，从10亿个浮点数当中，选出其中最大的10000个
//辅助交换函数
//辅助交换函数
void Swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
 
//堆排序的核心是建堆,传入参数为数组，根节点位置，数组长度
void Heap_build(int a[],int root,int length) {
	int lchild = root*2+1;//根节点的左子结点下标
	if (lchild < length) {//左子结点下标不能超出数组的长度
		int flag = lchild;//flag保存左右节点中最大值的下标
		int rchild = lchild+1;//根节点的右子结点下标
		if (rchild < length) {//右子结点下标不能超出数组的长度(如果有的话)
		    if (a[rchild] > a[flag]) {//找出左右子结点中的最大值
				flag = rchild;
			}
		}
		if (a[root] < a[flag]) {
			//交换父结点和比父结点大的最大子节点
			Swap(a[root],a[flag]);
			//从此次最大子节点的那个位置开始递归建堆
			Heap_build(a,flag,length);
		}
	}
}
 
void Heap_sort(int a[],int len) {
	for (int i = len/2; i >= 0; --i) {//从最后一个非叶子节点的父结点开始建堆
		Heap_build(a,i,len); // 建立最大堆，堆顶为最大的元素，剩余部分仍然无序
	}
 
	for (int j = len-1; j > 0; --j) {//j表示数组此时的长度，因为len长度已经建过了，从len-1开始
		Swap(a[0],a[j]);// 交换首尾元素,将最大值交换到数组的最后位置保存
		Heap_build(a,0,j);//去除最后位置的元素重新建堆，此处j表示数组的长度，最后一个位置下标变为len-2
	} 
}


// 链表
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x),next(NULL){ }
};

void printListFromTailToHead(ListNode* head){
    stack<ListNode *> reverse_list;
    while(head!=NULL){
        reverse_list.push(head);
        head = head->next;
    }
while ( !reverse_list.empty() ) {
    reverse_list.pop();
    }
}


/*
单链表判断是否有环 LeetCode 141
最容易想到的思路是存一个所有 Node 地址的 Hash 表，从头开始遍历，将 Node 存到 Hash 表中，如果出现了重复，则说明链表有环。

一个经典的方法是双指针（也叫快慢指针），使用两个指针遍历链表，一个指针一次走一步，另一个一次走两步，如果链表有环，两个指针必然相遇
*/


// 单链表找环入口 LeetCode 141
// 作为上一题的扩展，为了找到环所在的位置，在快慢指针相遇的时候，此时慢指针没有遍历完链表，再设置一个指针从链表头部开始遍历，这两个指针相遇的点，就是链表环的入口


// 单链表找交点 LeetCode 160
// 和找环的方法类似，同样可以使用 Hash 表存储所有节点，发现重复的节点即交点。

// 一个容易想到的方法是，先得到两个链表的长度，然后得到长度的差值 distance，两个指针分别从两个链表头部遍历，其中较长链表指针先走 distance 步，然后同时向后走，当两个指针相遇的时候，即链表的交点


// 单链表找中间节点 LeetCode 876
// 用快慢指针法，当快指针走到链表结尾时，慢指针刚好走到链表的中间



// 单链表合并 LeetCode 21
// 两个链表本身都是排序过的，把两个链表从头节点开始，逐个节点开始进行比较，最后剩下的节点接到尾部：



// 树
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL) {}
};


// 翻转二叉树 LeetCode 226
// 交互树的左右儿子节点，使用递归实现：
TreeNode* invertTree(TreeNode* root){
    if(root == NULL){
        return NULL;
    }
    TreeNode* tmp;;
    tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    
    while(root->left){
        invertTree(root->left);
    }
    while(root->right){
        invertTree(root->right);
    }
}


// 二叉树子树 LeetCode 572
// 判断二叉树是否是另一棵二叉树的子树，使用递归实现
bool sameTree(TreeNode* s, TreeNode* t) {
    if (!s && !t) return true;
    if (!s || !t) return false;
    if (s->val != t->val) return false;
    return sameTree(s->left, t->left) && sameTree(s->right, t->right);
}

bool isSubtree(TreeNode* s, TreeNode* t) {
    if (!s) return false;
    if (sameTree(s, t)) return true;
    return isSubtree(s->left, t) || isSubtree(s->right, t);
}




// 二叉树的遍历

// 二叉树前中后序遍历
// 二叉树层序遍历有两种方法，分别是深度优先和广度优先



int main() {
    vector<int> a;
    a.push_back(7);
    a.push_back(3);
    a.push_back(1);
    a.push_back(2);
    a.push_back(5);
    a.push_back(4);
    a.push_back(6);
  
  int b[] = {7,3,1,2,5,4,6};
	//quicksort(a, 0, 6);
Heap_sort(b,7);

     
	for (int i = 0; i <= 6; i++) {
		cout << b[i]<<"  ";
	}
	cout << endl;


    cout<<"learning "<<endl;
	return 0;
}






