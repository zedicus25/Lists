#include <iostream>
#include <exception>
#include <string>
namespace Lists
{
template<typename T>
struct Node {
	T value;
	Node* next;
	Node* prev;
	
};
class ListException : public std::exception
{
private:
	std::string error;
	int code;
public:
	ListException(int code) : code(code) {
		if (code == 1) {
			this->error = "Out of bounds list";
		}
	}

	const char* what() const noexcept override {
		return this->error.c_str();
	}
};

	template<typename T>
	class List {
	private:
		Node<T>* head;
		unsigned long size;
	public:
		explicit List() {
			this->head = NULL;
			this->size = 0;
		}

		unsigned long getSize() {
			return this->size;
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

		void editElement(int id, T value) {
			if (id < 0 || id >this->size) {
				throw ListException(1);
			}
			Node<T>* tmp = this->head;
			for (int i = 0; i < id; i++)
			{
				if (tmp->next != nullptr) {
					tmp = tmp->next;
				}
			}
			tmp->value = value;
		}

		T getElement(int id) {
			if (id < 0 || id >this->size) {
				throw ListException(1);
			}
			Node<T>* tmp = this->head;
			for (int i = 0; i < id; i++)
			{
				if (tmp->next != nullptr) {
					tmp = tmp->next;
				}
			}
			return tmp->value;
		}

		void removeFromList(int index) {
			if (index < 0 || index > this->size) {
				throw ListException(1);
			}
			Node<T>* forDelete = NULL;
			if (index == 0) {
				forDelete = this->head;
				this->head = this->head->next;
				this->head->prev = NULL;
			}
			else {
				Node<T>* tmp = this->head;
				forDelete = tmp;
				int i = 1;
				while (tmp->next != nullptr) {
					if (i == index && tmp->next != nullptr) {
						forDelete = tmp->next;
						break;
					}
					i++;
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

		/*void removeFromList(T value) {
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
		}*/

		void showList() {
			Node<T>* tmp = this->head;
			while (tmp != nullptr) {
				std::cout << tmp->value << "\n";
				tmp = tmp->next;
			}
			delete tmp;
		}

		T operator[](const int index) {
			if (index < 0 || index >this->size) {
				throw ListException(1);
			}
			return this->getElement(index);
		}

		List<T>* operator+(List<T> other) {
			Node<T>* tmp = this->head;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			Node<T>* tmp1 = other.head;
			while (tmp1->next != nullptr)
			{
				tmp->next = tmp1;
				tmp1 = tmp1->next;
			}
		}
	};
}

int main()
{
	Lists::List<int> num;
	num.addToList(5);
	num.addToList(3);
	num.addToList(4);


	try
	{
		num.removeFromList(2);
	}
	catch (Lists::ListException error)
	{
		std::cout << error.what() << "\n";
	}
	try
	{
		num.editElement(15, 15);
	}
	catch (Lists::ListException error)
	{
		std::cout << error.what() << "\n";
	}

	try
	{
		std::cout <<"Get element " << num[4] << "\n";
	}
	catch (Lists::ListException error)
	{
		std::cout <<  error.what() << "\n";
	}
	
	num.showList();


}