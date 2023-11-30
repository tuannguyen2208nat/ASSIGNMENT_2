#include "main.h"
int MAXSIZE;

class node
{
public:
	char data;
	int freq;
	node *next;
	node *prev;
	node() : data('\0'), freq(0), next(nullptr), prev(nullptr){};
	node(char data, node *temp) : data(data), freq(1), next(nullptr), prev(temp){};
	node(char data) : data(data), freq(1), next(nullptr), prev(nullptr){};
};
class Linklist
{
public:
	node *head;
	node *tail;
	/////////////////
	void Linklist_print()
	{
		node *temp = head;
		while (temp != nullptr)
		{
			cout << temp->data << " " << temp->freq << endl;
			temp = temp->next;
		}
	}
	/////////////////
	int Linklist_size()
	{
		int count = 0;
		node *temp = head;
		while (temp != nullptr)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}
	/////////////////
	node *Linklist_gethead()
	{
		return head;
	}
	/////////////////
	void LAPSE_caesar()
	{
		node *temp = head;
		while (temp != nullptr)
		{
			if (isalpha(temp->data))
			{
				char base = isupper(temp->data) ? 'A' : 'a';
				temp->data = (temp->data - base + temp->freq) % 26 + base;
			}
			temp = temp->next;
		}
	}
	/////////////////
	node *search_node(char data)
	{
		node *current = head;
		while (current != nullptr)
		{
			if (current->data == data)
			{
				break;
			}
			current = current->next;
		}
		return current;
	}
	void delete_samenode()
	{
		set<char> seenData;
		node *current = head;

		while (current != nullptr)
		{
			if (seenData.count(current->data) > 0)
			{
				node *p = search_node(current->data);
				int n = current->freq;
				p->freq += n;
				node *temp = current;
				current = current->next;

				if (temp->prev != nullptr)
				{
					temp->prev->next = temp->next;
				}
				else
				{
					head = temp->next;
				}

				if (temp->next != nullptr)
				{
					temp->next->prev = temp->prev;
				}
				else
				{
					tail = temp->prev;
				}

				delete temp;
			}
			else
			{
				seenData.insert(current->data);
				current = current->next;
			}
		}
	}
	/////////////////
};

Linklist *newlist(char data)
{
	Linklist *arr = new Linklist;
	arr->head = new node(data);
	arr->tail = arr->head;
	return arr;
}
Linklist *addElement(Linklist *arr, char data)
{
	node *temp = arr->head;
	while (temp != nullptr)
	{
		if (temp->data == data)
		{
			temp->freq++;
			return arr;
		}
		temp = temp->next;
	}
	node *p = new node(data, arr->tail);
	arr->tail->next = p;
	arr->tail = p;
	return arr;
}
/////////////////
void swap(node *a, node *b)
{
	char temp_data = a->data;
	int temp_freq = a->freq;
	a->data = b->data;
	a->freq = b->freq;
	b->data = temp_data;
	b->freq = temp_freq;
}
void LAPSE_sort(Linklist &list)
{
	if (list.head == nullptr || list.head->next == nullptr)
	{
		return;
	}

	bool swapped;
	node *ptr1;
	node *lptr = nullptr;
	do
	{
		swapped = false;
		ptr1 = list.head;

		while (ptr1->next != lptr)
		{
			if (ptr1->freq > ptr1->next->freq || (ptr1->freq == ptr1->next->freq && int(ptr1->data) > int(ptr1->next->data)))
			{
				swap(ptr1, ptr1->next);
				swapped = true;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}
/////////////////
void LAPSE_main(string name)
{
	if ((int)name.size() <= 0)
	{
		return;
	}
	Linklist *arr = newlist(name[0]);
	for (int i = 1; i < (int)name.size(); i++)
	{
		arr = addElement(arr, name[i]);
	}
	arr->LAPSE_caesar();
	arr->delete_samenode();

	node *head = arr->Linklist_gethead();
	LAPSE_sort(*arr);
	arr->Linklist_print();
}

void LAPSE(string name)
{
	cout << "LAPSE" << endl;
	LAPSE_main(name);
}
void KOKUSEN()
{
	cout << "KOKUSEN" << endl;
}
void KEITEIKEN(int num)
{
	cout << "KEITEIKEN"
		 << " " << num << endl;
}
void HAND()
{
	cout << "HAND" << endl;
}
void LIMITLESS(int num)
{
	cout << "LIMITLESS"
		 << " " << num << endl;
}
void CLEAVE(int num)
{
	cout << "CLEAVE"
		 << " " << num << endl;
}

////////////////////
void simulate(string filename)
{
	ifstream ss(filename);
	string str, maxsize, name, num;
	while (ss >> str)
	{
		if (str == "MAXSIZE")
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize);
		}
		else if (str == "LAPSE")
		{
			ss >> name;
			LAPSE(name);
		}
		else if (str == "KOKUSEN")
		{
			KOKUSEN();
		}
		else if (str == "KEITEIKEN")
		{
			ss >> num;
			KEITEIKEN(stoi(num));
		}
		else if (str == "HAND")
		{
			HAND();
		}
		else if (str == "LIMITLESS")
		{
			ss >> num;
			LIMITLESS(stoi(num));
		}
		else if (str == "CLEAVE")
		{
			ss >> num;
			CLEAVE(stoi(num));
		}
	}
}