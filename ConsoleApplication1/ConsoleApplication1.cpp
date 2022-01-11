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
	void removeFromList(T value) {
		if (this->isInList(value)) {
			Node<T>* forDelete = NULL;
			if (this->head->value == value) {
				forDelete = this->head;
				this->head = this->head->next;
				this->head->prev = NULL;
			}
			else {
				Node<T>* tmp = this->head;
				forDelete = tmp;
				while (tmp->next != nullptr) {
					if (tmp->next->value == value && tmp->next != nullptr) {
						forDelete = tmp->next;
						break;
					}
				    tmp = tmp->next;
				}
				if (tmp->next->next == NULL) {
					tmp->next = NULL;
					tmp->prev = tmp;
				}
				else {
					tmp->next = tmp->next->next;
					tmp->next->prev = tmp;
				}
			}
			delete forDelete;
			this->size--;
		}
	}

	void showList() {
		Node<T>* tmp = this->head;
		while (tmp != nullptr) {
			std::cout << tmp->prev << "\t" << tmp << "\t" << tmp->value << "\t" << tmp->next << "\n";
			tmp = tmp->next;
		}
		delete tmp;
	}

	bool isInList(T value) {
		bool isIn = false;
		Node<T>* tmp = this->head;
		while (tmp != nullptr) {
			if (tmp->value == value) {
				isIn = true;
				break;
			}
			tmp = tmp->next;
		}
		tmp = nullptr;

		return isIn;
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
	std::cout << "\n";
	num.removeFromList(1);
	num.showList();

}