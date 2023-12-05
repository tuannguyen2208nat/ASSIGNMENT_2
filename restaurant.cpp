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
bool checkAvl(AVLNode *t)
{
	if (t == NULL)
		return true;
	if (abs(treeLevel(t->left) - treeLevel(t->right)) > 1)
		return false;
	return checkAvl(t->left) && checkAvl(t->right);
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
		while (!checkAvl(top))
		{
			top = updateTreeAvl(top);
		}
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
class minheap_node
{
public:
	int id;
	int freq;
	deque<int> minheap_node_result;

	minheap_node(int id, int result)
	{
		this->id = id;
		this->freq = 1;
		minheap_node_result.push_back(result);
	}

	void print()
	{
		int n = minheap_node_result.size();
		cout << "id : " << id << " "
			 << "freq : " << freq << endl;
		for (int i = 0; i < n; i++)
		{
			cout << minheap_node_result[i] << " ";
		}
		cout << endl;
	}

	void MINHEAP_print(int num)
	{
		int n = minheap_node_result.size();
		if (num <= 0 || n <= 0)
		{
			return;
		}

		if (num >= n)
		{
			for (int i = n - 1; i >= 0; i--)
			{
				cout << id << "-" << minheap_node_result[i] << endl;
			}
		}
		else
		{
			for (int i = n - 1; i >= (n - num); i--)
			{
				cout << id << "-" << minheap_node_result[i] << endl;
			}
		}
	}
};

class minHeap
{
public:
	vector<minheap_node> heap;
	vector<int> thutuid;

	int minheap_parent(int index)
	{
		return (index - 1) / 2;
	}

	int minheap_left(int index)
	{
		return (2 * index + 1);
	}

	int minheap_right(int index)
	{
		return (2 * index + 2);
	}

	int left_right_order(int left, int right)
	{
		int n = thutuid.size();
		int largest = 0;
		for (int i = 0; i < n; i++)
		{
			if (thutuid[i] == heap[left].id)
			{
				largest = left;
				break;
			}
			if (thutuid[i] == heap[right].id)
			{
				largest = right;
				break;
			}
		}
		return largest;
	}

	void reheapup(int index)
	{
		int parentIndex = minheap_parent(index);
		while (index > 0 && heap[index].freq < heap[parentIndex].freq)
		{
			std::swap(heap[index], heap[parentIndex]);
			index = parentIndex;
			parentIndex = (index - 1) / 2;
		}
	}

	void reheapdown(int index)
	{
		int leftChild = minheap_left(index);
		int rightChild = minheap_right(index);
		int smallest = index;

		if (leftChild < (int)heap.size() && heap[leftChild].freq < heap[smallest].freq)
		{
			smallest = leftChild;
		}

		if (rightChild < (int)heap.size())
		{
			if (heap[rightChild].freq < heap[smallest].freq)
			{
				smallest = rightChild;
			}
			else if (heap[rightChild].freq == heap[smallest].freq)
			{
				smallest = left_right_order(smallest, rightChild);
			}
		}

		if (smallest != index)
		{
			swap(heap[index], heap[smallest]);
			reheapdown(smallest);
		}
	}

	void minheap_update()
	{
		for (int i = 0; i < (int)heap.size(); i++)
		{
			int parent = minheap_parent(i);
			if (parent < (int)heap.size())
			{
				if (heap[i].freq < heap[parent].freq)
				{
					reheapup(i);
				}
				else
				{
					reheapdown(i);
				}
			}
		}
	}

	bool check_id(int id, int result)
	{
		for (int i = 0; i < (int)heap.size(); i++)
		{
			if (heap[i].id == id)
			{
				(heap[i].minheap_node_result).push_back(result);
				(heap[i].freq) += 1;
				return true;
			}
		}
		return false;
	}

	void insert(int id, int result)
	{
		thutuid.push_back(id);
		if (!check_id(id, result))
		{
			minheap_node min_heap(id, result);
			heap.push_back(min_heap);
			reheapup(heap.size() - 1);
		}
		minheap_update();
	}

	int minheap_size()
	{
		return (int)heap.size();
	}

	void minheap_delete(int id, int num)
	{
		int vitri = 0;
		int size = heap.size();
		for (int i = 0; i < size; i++)
		{
			if (heap[i].id == id)
			{
				vitri = i;
				break;
			}
		}
		int n = heap[vitri].freq;
		if (num >= n)
		{
			while (!(heap[vitri].minheap_node_result.empty()))
			{
				cout << heap[vitri].minheap_node_result.front() << "-" << heap[vitri].id << endl;
				heap[vitri].minheap_node_result.pop_front();
			}
			heap.erase(heap.begin() + vitri);
		}
		else
		{
			int count = 0;
			while (count != num)
			{
				cout << heap[vitri].minheap_node_result.front() << "-" << heap[vitri].id << endl;
				heap[vitri].minheap_node_result.pop_front();
				heap[vitri].freq -= 1;
				count++;
			}
		}
		minheap_update();
	}

	void MINHEAP_preorder(int index, int num)
	{
		if (index < (int)heap.size())
		{
			heap[index].MINHEAP_print(num);				 // Print the current node
			MINHEAP_preorder(minheap_left(index), num);	 // Recursively print left subtree
			MINHEAP_preorder(minheap_right(index), num); // Recursively print right subtree
		}
	}
};

minHeap HEAP;

void MINHEAP_main(int id, int result)
{
	HEAP.insert(id, result);
}

void nha_hang_s(int result)
{
	int id = (result % MAXSIZE) + 1;
	MINHEAP_main(id, result);
}
/////END-NHA-HANG-S//////

//////NHA-HANG-G/////

/// BST///
class BSTNode
{
public:
	int result;
	BSTNode *left;
	BSTNode *right;

	BSTNode() : result(0), left(nullptr), right(nullptr) {}

	BSTNode(int result) : result(result), left(nullptr), right(nullptr) {}

	BSTNode(int result, BSTNode *&left, BSTNode *&right) : result(result), left(left), right(right) {}
};
BSTNode *BST_insert(BSTNode *root, int result)
{
	if (!root)
	{
		return new BSTNode(result);
	}

	if (result < root->result)
	{
		root->left = BST_insert(root->left, result);
	}
	else if (result >= root->result)
	{
		root->right = BST_insert(root->right, result);
	}
	return root;
}
BSTNode *minValueNode(BSTNode *node)
{
	BSTNode *current = node;
	while (current && current->left)
	{
		current = current->left;
	}
	return current;
}
BSTNode *deleteNode(BSTNode *root, int key)
{
	if (!root)
	{
		return root;
	}
	if (key < root->result)
	{
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->result)
	{
		root->right = deleteNode(root->right, key);
	}
	else
	{
		if (!root->left)
		{
			BSTNode *temp = root->right;
			delete root;
			return temp;
		}
		else if (!root->right)
		{
			BSTNode *temp = root->left;
			delete root;
			return temp;
		}
		BSTNode *temp = minValueNode(root->right);
		root->result = temp->result;
		root->right = deleteNode(root->right, temp->result);
	}
	return root;
}
void delete_full_BST(BSTNode *root)
{
	if (root)
	{
		delete_full_BST(root->left);
		delete_full_BST(root->right);
		delete root;
		root = nullptr;
	}
}
void printInorder_BST(BSTNode *root)
{
	if (root != nullptr)
	{
		printInorder_BST(root->left);
		cout << root->result << endl;
		printInorder_BST(root->right);
	}
}
BSTNode *turnRight(BSTNode *root)
{
	BSTNode *b = root->left;
	BSTNode *d = b->right;
	root->left = d;
	b->right = root;
	return b;
}
BSTNode *turnLeft(BSTNode *root)
{
	BSTNode *b = root->right;
	BSTNode *c = b->left;
	root->right = c;
	b->left = root;
	return b;
}
int treeLevel(BSTNode *root)
{
	if (root == NULL)
		return -1;
	return 1 + max(treeLevel(root->left), treeLevel(root->right));
}
/// END-BST///

class hash_table_node
{
public:
	BSTNode *root;
	queue<int> hash_table_queue;
	hash_table_node *next;

	hash_table_node(BSTNode *root, int result)
	{
		this->root = root;
		hash_table_queue.push(result);
		this->next = nullptr;
	}
};

hash_table_node *hash_table[10000];

void hash_table_insert(int id, int result)
{
	if (!hash_table[id])
	{
		BSTNode *root = new BSTNode(result);
		hash_table[id] = new hash_table_node(root, result);
	}
	else
	{
		BSTNode *root = hash_table[id]->root;
		BST_insert(root, result);
		hash_table[id]->hash_table_queue.push(result);
	}
}
int sumOfSubtrees(BSTNode *root)
{
	if (!root)
	{
		return 0;
	}
	int leftSum = sumOfSubtrees(root->left);
	int rightSum = sumOfSubtrees(root->right);
	return leftSum + rightSum + 1;
}
int fact(int n)
{
	if (n == 0)
		return 1;
	int res = 1;
	for (int i = 2; i <= n; i++)
		res = res * i;
	return res;
}
int nCr(int n, int r)
{
	return fact(n) / (fact(r) * fact(n - r));
}
int countBST(BSTNode *root)
{
	if (root != nullptr)
	{
		int n1 = sumOfSubtrees(root->left);
		int n2 = sumOfSubtrees(root->right);
		int n = n1 + n2;
		return nCr(n, n2) * countBST(root->left) * countBST(root->right);
	}

	return 1;
}
void xoa_cay_bst(int vitri, int count, int size)
{
	if (count >= size)
	{
		delete_full_BST(hash_table[vitri]->root);
		hash_table[vitri] = nullptr;
		return;
	}
	while (count > 0)
	{
		int val = (hash_table[vitri]->hash_table_queue).front();
		hash_table[vitri]->root = deleteNode(hash_table[vitri]->root, val);
		(hash_table[vitri]->hash_table_queue).pop();
		count--;
	}
}
void LIMITLESS_print(int id)
{
	if (hash_table[id] != nullptr)
	{
		printInorder_BST(hash_table[id]->root);
	}
}

void nha_hang_g(int result)
{
	int id = (result % MAXSIZE) + 1;
	hash_table_insert(id, result);
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
	if ((arr->Linklist_size()) < 3)
	{
		return;
	}
	arr->LAPSE_caesar();
	arr->delete_samenode();

	LAPSE_sort(*arr);
	node *head = arr->Linklist_gethead();
	int result = HuffmanCodes(head);
	(result % 2 == 0) ? nha_hang_s(result) : nha_hang_g(result);
}

void KOKUSEN_main()
{
	for (int id = 1; id <= MAXSIZE; id++)
	{
		if (hash_table[id] != nullptr)
		{
			int count = countBST(hash_table[id]->root);
			count %= MAXSIZE;
			int size = (hash_table[id]->hash_table_queue).size();
			xoa_cay_bst(id, count, size);
		}
	}
}

class myarray
{
public:
	int id;
	int freq;
	myarray(int id, int freq) : id(id), freq(freq) {}
};

void KEITEIKEN_main(int num)
{
	int n = HEAP.minheap_size();
	if (num > n)
	{
		num = n;
	}
	vector<myarray> khuvuc;
	for (int i = 0; i < n; i++)
	{
		myarray a(HEAP.heap[i].id, HEAP.heap[i].freq);
		khuvuc.push_back(a);
	}
	sort(khuvuc.begin(), khuvuc.end(), [](const myarray &a, const myarray &b)
		 { return a.freq < b.freq; });

	int num1 = num;
	for (int i = 0; i < num; i++)
	{
		int smallest = 0;
		vector<myarray> vector2;
		for (int j = 0; j < num1; j++)
		{
			if (khuvuc[j].freq == khuvuc[smallest].freq)
			{
				myarray a(khuvuc[j].id, khuvuc[j].freq);
				vector2.push_back(a);
			}
		}

		for (int j = HEAP.thutuid.size() - 1; j >= 0; j--)
		{
			int dem = 0;
			while (vector2.size() > 1 && dem < vector2.size())
			{
				if (HEAP.thutuid[j] == vector2[dem].id)
				{
					vector2.erase(vector2.begin() + dem);
					break;
				}
				dem++;
			}
		}
		for (int j = 0; j < khuvuc.size(); j++)
		{
			if (khuvuc[j].id == vector2[0].id)
			{
				khuvuc.erase(khuvuc.begin() + j);
				break;
			}
		}
		HEAP.minheap_delete(vector2[0].id, num);
		vector2.clear();
		num1--;
		if (num1 == 0)
		{
			break;
		}
	}
	khuvuc.clear();
}

void HAND_main()
{
}

void LIMITLESS_main(int num)
{
	if (!hash_table[num])
	{
		return;
	}
	LIMITLESS_print(num);
}

void CLEAVE_main(int num)
{
	HEAP.MINHEAP_preorder(0, num);
}

////////////////
void LAPSE(string name)
{
	LAPSE_main(name);
}
void KOKUSEN()
{
	KOKUSEN_main();
}
void KEITEIKEN(int num)
{
	KEITEIKEN_main(num);
}
void HAND()
{
	cout << "HAND" << endl;
	HAND_main();
}
void LIMITLESS(int num)
{
	LIMITLESS_main(num);
}
void CLEAVE(int num)
{
	CLEAVE_main(num);
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