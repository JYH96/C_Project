#include <iostream>
#include <vector>
#include <random>
using namespace std;
class node
{
public:
	node() {};
	~node() {};
	int key = NULL;
	node* p = nullptr;
	node *left = nullptr;
	node *right = nullptr;
private:
};
void printnodes(vector<node> nodes);
node* findmax(node& node);
int main() {
	int size = 63;
	vector<node> nodes = vector<node>(size, node());
	vector<int> tape;
	for (int i = 1; i <= size; ++i) {
		tape.push_back(i);
	}
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].key = tape[i];
		if (i * 2 + 2< nodes.size()) {
			nodes[i].left = &nodes[i * 2 + 1];
			nodes[i].right = &nodes[i * 2 + 2];
		}
		if (i > 0) {
			nodes[i].p = &nodes[int((i-1)/2)];
		}
	}
	vector<node> temp = vector<node>(size, node());
	bool action = true;

	int num = 0;
	while (action) {
		action = false;
		temp.assign(nodes.begin(), nodes.end());
		findmax(nodes[0]);
		for (int i = 0; i < nodes.size(); i++) {
			if (temp[i].key!=nodes[i].key) {
				action = true;
			}
		}
		cout << num << " 번째 정렬" << endl;
		num += 1;
	}
	printnodes(nodes);
}

void printnodes(vector<node> nodes) {
	for (auto i : nodes) {
		if (i.p != nullptr) {
			cout << i.p->key << endl;
		}
		else {
			cout << "start" << endl;
		}
		cout << i.key << endl;
		if (i.left != nullptr) {
			cout << i.left->key << " ";
		}
		else {
			cout << "@ ";
		}
		if (i.right != nullptr) {
			cout << i.right->key << endl;
		}
		else {
			cout << "@" << endl;
		}
	}
	cout << "-------------------------------" << endl;
}
node* findmax(node &node) {
	
	if (node.right!=nullptr && node.left != nullptr) {
		int temp;
		

		auto left = findmax(*node.left);
		auto right = findmax(*node.right);

		if (left->key > node.key) {
			temp = node.key;
			node.key = left->key;
			left->key = temp;
		}
		if (right->key > node.key) {
			temp = node.key;
			node.key = right->key;
			right->key = temp;
		}
		if (node.left->key > node.right->key) {
			temp = node.left->key;
			node.left->key = node.right->key;
			node.right->key = temp;
		}
		return &node;
	}
	else {
		return &node;
	}
}