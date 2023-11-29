#include "main.h"
int MAXSIZE;

class node
{
public:
	char data;
	int freq;
	node *next;
	node() : data('\0'), freq(0), next(nullptr){};
	node(char data) : data(data), freq(1), next(nullptr){};
};
node *addElement(node *head, node *temp, char data)
{
	node *p = head;
	while (p != nullptr)
	{
		if (p->data == data)
		{
			p->freq++;
			return temp;
		}
		p = p->next;
	}
	node *l = new node(data);
	temp->next = l;
	return l;
}
void print(node *temp)
{
	while (temp != nullptr)
	{
		cout << temp->data << " " << temp->freq << endl;
		temp = temp->next;
	}
}
void LAPSE_sort(node *temp)
{
}
void LAPSE_main(string name)
{
	node *head = new node(name[0]);
	node *temp = head;
	for (int i = 1; i < (int)name.size(); i++)
	{
		temp = addElement(head, temp, name[i]);
	}
	print(head);
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