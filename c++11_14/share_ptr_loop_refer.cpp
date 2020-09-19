#include <iostream>
#include <memory>

using namespace std;
 
struct Node
{	
	// 虚引用，不增加引用次数
	weak_ptr<Node> _pre;
	weak_ptr<Node> _next;
 
	~Node()
	{
		cout << "~Node():" << this << endl;
	}
	int data;
};

struct Node_
{
	shared_ptr<Node_> _pre;
	shared_ptr<Node_> _next;
 
	~Node_()
	{
		cout << "~Node():" << this << endl;
	}
	int data;
};
 
void FunTest()
{
	shared_ptr<Node> Node1(new Node);
	shared_ptr<Node> Node2(new Node);
	Node1->_next = Node2;
	Node2->_pre = Node1;
 
	cout << "Node1.use_count:"<<Node1.use_count() << endl;
	cout << "Node2.use_count:"<< Node2.use_count() << endl ;

}
 

void FunTest2()
{
	shared_ptr<Node_> Node1(new Node_);
	shared_ptr<Node_> Node2(new Node_);
	Node1->_next = Node2;
	Node2->_pre = Node1;
 
	cout << "Node1.use_count:"<<Node1.use_count() << endl;
	cout << "Node2.use_count:"<< Node2.use_count() << endl;

	// 自定义删除引用
    Node1->_next.reset();
    Node2->_pre.reset();
}

int main()
{
	FunTest();
	FunTest2();
	return 0;
}