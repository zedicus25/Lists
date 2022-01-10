#include <iostream>

template<typename T>
struct Node {
	T value;
	Node* next;
	Node* prev;
};

template<typename T>
class List {
private:
	Node<T>* head;
	unsigned long size;
public:
	explicit List(){
		this->head = NULL;
		this->size = 0;
	}
	void addToList(T value) {
		Node<T>* tmp = this->head;
		if (tmp == NULL) {
			tmp = new Node<T>;
			tmp->value = value;
			tmp->next = nullptr;
			tmp->prev = nullptr;
			this->head = tmp;
		}
		else {
			while (tmp->next != nullptr) {
				tmp = tmp->next;
			}
			tmp->next = new Node<T>;
			tmp->next->value = value;
			tmp->next->next = nullptr;
			tmp->next->prev = tmp;
		}
		this->size++;
	}

	void showList() {
		Node<T>* tmp = this->head;
		while (tmp != nullptr) {
			std::cout << tmp->prev << "\t" << tmp << "\t" << tmp->value << "\t" << tmp->next << "\n";
			tmp = tmp->next;
		}
		delete tmp;
	}
};

int main()
{
	List<int> num;
	num.addToList(1);
	num.addToList(2);
	num.addToList(3);
	num.addToList(4);
	num.addToList(5);
	num.showList();
}