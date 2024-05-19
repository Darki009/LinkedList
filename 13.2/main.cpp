#include <iostream>
#include <Windows.h>

using namespace std;

struct Node
{
	int value;
	Node* next = NULL;
	Node* prev = NULL;

	Node(int value)
	{
		this->value = value;
	}
};

struct LinkedList
{
	Node* root = NULL;
	Node* end = NULL;
	int lenght = 0;
};

void AddNodeEnd(LinkedList* list, int value)
{
	Node* element = new Node(value);
	Node* save = list->end;

	if (list->lenght == 0)
	{
		list->root = element;
		list->end = element;
		list->lenght = 1;
		return;
	}

	list->end = element;
	save->next = list->end;
	element->prev = save;

	list->lenght++;
}

void AddNodeBegin(LinkedList* list, int value)
{
	Node* element = new Node(value);
	Node* save = list->root;

	if (list->lenght == 0)
	{
		list->root = element;
		list->end = element;
		list->lenght++;
		return;
	}

	list->root = element;
	save->prev = list->root;
	element->next = save;

	list->lenght++;

}

void AddNode(LinkedList* list, int value, int index)
{
	if (index == 0)
		AddNodeBegin(list, value);
	else if (index >= list->lenght)
		AddNodeEnd(list, value);
	else if (index > 0)
	{
		Node* pl = list->root;

		for (int i = 0; i < index - 1; i++)
			pl = pl->next;

		Node* element = new Node(value);
		Node* saved_left = pl;
		Node* saved_right = pl->next;

		saved_left->next = element;
		saved_right->prev = element;
		element->prev = saved_left;
		element->next = saved_right;

		list->lenght++;
	}
	else
		cout << "Элемент " << value <<" не добавлен!У списка не может быть отрицательных индексов!\n";
}

void DeleteNode(LinkedList* list, int index)
{
	Node* pl = list->root;
	if (list->lenght == 1)
	{
		list->end = NULL;
		list->root = NULL;
		delete(pl);
		return;
	}

	if (pl == NULL || index >= list->lenght || index < 0)
	{
		cout << "Вы не можете удалить этот элемент, его не существует\n";
		return;
	}
	else if (index == 0)
	{
		list->root = pl->next;
		pl->next->prev = NULL;
	}
	else if (index == list->lenght - 1)
	{
		list->end = list->end->prev;
		list->end->prev->next = NULL;
	}
	else if (index > 0)
	{
		for (int i = 0; i < index; i++)
			pl = pl->next;

		pl->prev->next = pl->next;
		pl->next->prev = pl->prev;
	}
	
	delete(pl);
	list->lenght--;
}

void print(LinkedList* list)
{
	Node* pl = list->root;
	/*for (int i = 0; i < list->lenght; i++)
	{
		cout << pl->value << " ";
		pl = pl->next;
	}*/

	for (Node* pl = list->root; pl != NULL; pl = pl->next)
		cout << pl->value << " ";
	cout << endl;
}

int search(LinkedList* list, int value)
{
	int index = 0;
	for (Node* pl = list->root; pl != NULL; pl = pl->next)
	{
		if (pl->value == value)
		{
			cout << "Номер элемента: " << index + 1 << endl;
			return index;
		}
		index++;
	}
	cout << "Элемент не найден\n";
	return -1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	LinkedList* list = new LinkedList();
	int number = 0;
	int val, num;

	for (int i = 0; i < 10; i++)
	{
		cout << "Введите\n 1 - Добавить элемент\n 2 - Удалить элемент\n 3 - Поиск элемента\n";
		cin >> number;

		switch (number)
		{
		case 1:

			cout << "Введите значение элемента и его номер\n";
			cin >> val >> num;
			AddNode(list, val, num - 1);
			print(list); break;
		case 2:
			cout << "Введите номер удаляемого элемента\n";
			cin >> num;
			DeleteNode(list, num - 1);
			print(list); break;
		case 3:
			cout << "Введите значение элемента\n";
			cin >> val;
			search(list, val); break;
		default:
			cout << "Введено неверное значение\n";
		}
	}

	return 0;
}