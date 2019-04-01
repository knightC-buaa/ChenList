#include<iostream>
using namespace std;

//�ڵ�ṹ��
struct Node {
	int data;
	Node* next;
};

//��ͷβָ��ĵ�����ȱ�㣺������һ�����ѣ�ɾ��β�ڵ�����
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
	int popLast();//�����Ч
	int reverse();
	void show();
};

//����
List::List() {
	head = NULL;
	tail = NULL;
	size = 0;
}

//List::~List() {
	//��ô����������������أ�����ʵ��insert��˵��
	//��insert����new����Щ���������delete��
//}

//�п�
bool List::isEmpty() {
	return head == NULL;
}

//β��
void List::insertLast(int elemnt) {
	Node* node = new Node;
	node->data = elemnt;
	node->next = NULL;

	if (this->isEmpty()) {//��node�Ե�һ��Ԫ�ز����ʱ��
		//��Чд����this->isEmpty()  <==>  NULL == tail
		head = node;
		tail = node;
	}
	else {//��node�Էǵ�һ��Ԫ�ز����ʱ��
		Node* temp = tail;
		tail = node;
		temp->next = node;
	}
	size++;
}

//βɾ�������ЧO(n)��ǿ�ҽ����������ռ任ȡʱ�䣬����һ��ָ���򣬱��˫������
int List::popLast() {
	//ԭ��һ���ڵ㶼û��
	if (this->isEmpty())
		return -1;//ɾ��ʧ�ܣ��Ѿ�û�ڵ���
	//���ֻ��һ���ڵ���
	else if (NULL == head->next) {
		Node* temp = tail;
		head = NULL;
		tail = NULL;
		delete temp;
		return 0;
	}
	//������һ���Լ����ϵĽڵ�
	else {
		//������������ɾ�����һ���ڵ㣬βָ����ô��ָ�����ڶ����ָ�룬�Ǹ�����ѽ
		//�������ˣ���ͷ��ʼ����������β����Ч��������û���д��˫������
		//���poplast��һ����Ƶ�������ع������������ڱ���
		Node* last = tail;
		Node* temp = head, *tempnext = head->next;
		while (true) {
			if (tempnext->next == NULL)
				break;//�˿̵�temp���ǵ����ڶ����ڵ�
			temp = tempnext;
			tempnext = tempnext->next;
		}
		tail = temp;
		temp->next = NULL;
		delete last;
		return 0;
	}
}

//��ת����
int List::reverse() {
	//��û�нڵ�����
	if (isEmpty())
		return 0;
	//��һ���ڵ�����
	Node* p1 = head;
	if (NULL == p1->next)
		return 0;
	//���������ڵ�������ϵ����
	Node* p2 = p1->next;
	Node* p3 = p2->next;
	p1->next = NULL;
	tail = p1;//��һ����©�ˣ�һ�������޲���Сbug��20190316
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

//��ӡ����
void List::show() {
	Node* temp = head;
	if (this->isEmpty()) {
		cout << "����Ϊ��" << endl;
		return;
	}
	while (true) {
		if (temp->next == NULL) {
			cout << temp->data << ' ' << "�������" << endl;
			break;
		}
		cout << temp->data << ' ';
		temp = temp->next;
	}
	cout << "head=" << head->data << ' '
		<< "tail=" << tail->data << endl;
	return;
}

//����һ�����Ժ���
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