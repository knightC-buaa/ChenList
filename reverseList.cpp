#include<iostream>
using namespace std;

//节点结构体
struct Node {
	int data;
	Node* next;
};

//带头尾指针的单链表，缺点：查找上一项困难，删除尾节点困难
class List {
private:
	Node* head;
	Node* tail;
	int size;
public:
	List();
	//~List();
	int getsize() { return size; }
	bool isEmpty();
	void insertLast(int elemnt);
	int popLast();//及其低效
	int reverse();
	void show();
};

//构造
List::List() {
	head = NULL;
	tail = NULL;
	size = 0;
}

//List::~List() {
	//怎么样析构掉这个链表呢？，先实现insert再说吧
	//把insert里面new的那些玩意儿都给delete掉
//}

//判空
bool List::isEmpty() {
	return head == NULL;
}

//尾插
void List::insertLast(int elemnt) {
	Node* node = new Node;
	node->data = elemnt;
	node->next = NULL;

	if (this->isEmpty()) {//当node以第一个元素插入的时候
		//等效写法：this->isEmpty()  <==>  NULL == tail
		head = node;
		tail = node;
	}
	else {//当node以非第一个元素插入的时候
		Node* temp = tail;
		tail = node;
		temp->next = node;
	}
	size++;
}

//尾删。极其低效O(n)，强烈建议用少量空间换取时间，加上一个指针域，变成双向链表
int List::popLast() {
	//原本一个节点都没有
	if (this->isEmpty())
		return -1;//删除失败，已经没节点了
	//如果只有一个节点了
	else if (NULL == head->next) {
		Node* temp = tail;
		head = NULL;
		tail = NULL;
		delete temp;
		return 0;
	}
	//否则，有一个以及以上的节点
	else {
		//靠，单向链表删除最后一个节点，尾指针怎么样指向倒数第二额个指针，是个问题呀
		//不用想了，从头开始遍历，至结尾，低效，所以最好还是写成双向链表
		//如果poplast是一个高频操作，重构整个链表势在必行
		Node* last = tail;
		Node* temp = head, *tempnext = head->next;
		while (true) {
			if (tempnext->next == NULL)
				break;//此刻的temp就是倒数第二个节点
			temp = tempnext;
			tempnext = tempnext->next;
		}
		tail = temp;
		temp->next = NULL;
		delete last;
		return 0;
	}
}

//逆转链表
int List::reverse() {
	//当没有节点的情况
	if (isEmpty())
		return 0;
	//有一个节点的情况
	Node* p1 = head;
	if (NULL == p1->next)
		return 0;
	//当有两个节点或者以上的情况
	Node* p2 = p1->next;
	Node* p3 = p2->next;
	p1->next = NULL;
	tail = p1;//这一句差点漏了，一个容易修补的小bug，20190316
	while (true) {
		p2->next = p1;
		if (NULL == p3) {
			head = p2;
			break;
		}
		p1 = p2; p2 = p3; p3 = p3->next;
	}
	return 0;
}

//打印链表
void List::show() {
	Node* temp = head;
	if (this->isEmpty()) {
		cout << "链表为空" << endl;
		return;
	}
	while (true) {
		if (temp->next == NULL) {
			cout << temp->data << ' ' << "链表结束" << endl;
			break;
		}
		cout << temp->data << ' ';
		temp = temp->next;
	}
	cout << "head=" << head->data << ' '
		<< "tail=" << tail->data << endl;
	return;
}

//这是一个测试函数
void test1() {
	List li;
	cout << li.getsize() << endl;
	li.insertLast(1);
	li.insertLast(2);
	li.insertLast(3);
	li.insertLast(4);
	cout << li.getsize() << endl;
	li.show();
	li.reverse();
	li.show();
}

int main()
{
	test1();
	system("pause");
	return 0;
}