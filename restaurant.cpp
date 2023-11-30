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
///////////Huffman-tree//////////
class AVLNode
{
public:
	char data;
	int freq;
	AVLNode *left;
	AVLNode *right;
	int vitri;
	string mahoa;

	AVLNode(char data, int freq, int vitri)
	{
		left = right = NULL;
		this->data = data;
		this->freq = freq;
		this->vitri = vitri;
		this->mahoa = "";
	}
};
int treeLevel(AVLNode *t)
{
	if (t == NULL)
		return -1;
	return 1 + max(treeLevel(t->left), treeLevel(t->right));
}
AVLNode *turnRight(AVLNode *a)
{
	AVLNode *b = a->left;
	AVLNode *d = b->right;
	a->left = d;
	b->right = a;
	return b;
}
AVLNode *turnLeft(AVLNode *a)
{
	AVLNode *b = a->right;
	AVLNode *c = b->left;
	a->right = c;
	b->left = a;
	return b;
}
AVLNode *updateTreeAvl(AVLNode *t)
{
	if (abs(treeLevel(t->left) - treeLevel(t->right)) > 1)
	{
		if (treeLevel(t->left) > treeLevel(t->right))
		{
			AVLNode *p = t->left;
			if (treeLevel(p->left) >= treeLevel(p->right))
			{
				t = turnRight(t);
			}
			else
			{
				t->left = turnLeft(t->left);
				t = turnRight(t);
			}
		}
		else
		{
			AVLNode *p = t->right;
			if (treeLevel(p->right) >= treeLevel(p->left))
			{
				t = turnLeft(t);
			}
			else
			{
				t->right = turnRight(t->right);
				t = turnLeft(t);
			}
		}
	}
	if (t->left != NULL)
		t->left = updateTreeAvl(t->left);
	if (t->right != NULL)
		t->right = updateTreeAvl(t->right);
	return t;
}

struct compare
{
	bool operator()(AVLNode *l, AVLNode *r)
	{
		if (l->freq == r->freq)
		{
			return l->vitri > r->vitri;
		}
		return (l->freq > r->freq);
	}
};

void encode(AVLNode *root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (root->data != '$')
	{
		huffmanCode[root->data] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

int binaryToDecimal(int binaryNumber)
{
	int decimalNumber = 0;
	int base = 1;
	while (binaryNumber > 0)
	{
		int lastDigit = binaryNumber % 10;
		binaryNumber = binaryNumber / 10;
		decimalNumber += lastDigit * base;
		base = base * 2;
	}
	return decimalNumber;
}

int result_to_int(string result)
{
	int n = (int)result.size();
	string a = "";

	if (n <= 0)
	{
		return 0;
	}
	else if (n < 10)
	{
		for (int i = n - 1; i >= 0; i--)
		{
			a += result[i];
		}
	}
	else if (n >= 10)
	{
		for (int i = n - 1; i >= (n - 10); i--)
		{
			a += result[i];
		}
	}
	int ketqua = stoi(a);
	return binaryToDecimal(ketqua);
}

int HuffmanCodes(node *head)
{
	AVLNode *left, *right, *top;
	priority_queue<AVLNode *, vector<AVLNode *>, compare> minHeap;
	node *temp = head;
	int i = 0;
	while (temp != nullptr)
	{
		minHeap.push(new AVLNode(temp->data, temp->freq, i));
		temp = temp->next;
	}
	while (minHeap.size() != 1)
	{
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();
		top = new AVLNode('$', left->freq + right->freq, i);
		i++;
		top->left = left;
		top->right = right;
		top = updateTreeAvl(top);
		minHeap.push(top);
	}
	AVLNode *root = minHeap.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);
	string result = "";
	while (head != nullptr)
	{
		char ch = head->data;
		result += huffmanCode[ch];
		head = head->next;
	}
	return result_to_int(result);
	;
}
/////////End-Huffman-tree/////////
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
//////NHA-HANG-S/////
void nha_hang_s(int result)
{
	cout << "nha hang s" << endl;
}
/////END-NHA-HANG-S//////

//////NHA-HANG-G/////
void nha_hang_g(int result)
{
	cout << "nha hang g" << endl;
}
/////END-NHA-HANG-G//////

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

	LAPSE_sort(*arr);
	node *head = arr->Linklist_gethead();
	int result = HuffmanCodes(head);
	(result % 2 == 0) ? nha_hang_s(result) : nha_hang_g(result);
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