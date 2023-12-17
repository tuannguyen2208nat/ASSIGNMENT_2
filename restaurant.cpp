#include "main.h"

int MAXSIZE;

class node
{
public:
	char data;
	int freq;
	node *next;
	node *prev;
	node(char data, node *temp) : data(data), freq(1), next(nullptr), prev(temp){};
	node(char data) : data(data), freq(1), next(nullptr), prev(nullptr){};
};

class Linklist
{
public:
	node *head;
	node *tail;
	/////////////////
	void addElement(char data)
	{
		node *temp = head;
		while (temp != nullptr)
		{
			if (temp->data == data)
			{
				temp->freq++;
				return;
			}
			temp = temp->next;
		}
		node *p = new node(data, tail);
		tail->next = p;
		tail = p;
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
	/////////////////
	void LAPSE_swap(node *a, node *b)
	{
		char temp_data = a->data;
		int temp_freq = a->freq;
		a->data = b->data;
		a->freq = b->freq;
		b->data = temp_data;
		b->freq = temp_freq;
	}
	/////////////////
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
	void LAPSE_sort()
	{
		if (head == nullptr || head->next == nullptr)
		{
			return;
		}
		bool swapped;
		node *ptr1;
		node *lptr = nullptr;
		do
		{
			swapped = false;
			ptr1 = head;

			while (ptr1->next != lptr)
			{
				if (ptr1->freq > ptr1->next->freq || (ptr1->freq == ptr1->next->freq && int(ptr1->data) > int(ptr1->next->data)))
				{
					LAPSE_swap(ptr1, ptr1->next);
					swapped = true;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (swapped);
	}
};

Linklist *newlist(char data)
{
	Linklist *arr = new Linklist;
	arr->head = new node(data);
	arr->tail = arr->head;
	return arr;
}

template <typename E>
class HuffNode
{
public:
	HuffNode<E> *left;				 // left child
	HuffNode<E> *right;				 // right child
	virtual ~HuffNode() {}			 // Base destructor
	virtual int weight() const = 0;	 // Return frequency
	virtual bool isLeaf() const = 0; // Determine type
	HuffNode<E> *getleft() const { return left; }
	HuffNode<E> *getright() const { return right; }
};
template <typename E>
class LeafNode : public HuffNode<E>
{
private:
	E it;	 // Value
	int wgt; // Weight
public:
	LeafNode(const E &val, int freq) // Constructor
	{
		this->it = val;
		this->wgt = freq;
		this->left = nullptr;
		this->right = nullptr;
	}
	int weight() const override { return wgt; }
	E val() const { return it; }
	bool isLeaf() const override { return true; }
};
template <typename E>
class IntlNode : public HuffNode<E>
{
private:
	int wgt; // Subtree weight
public:
	IntlNode(HuffNode<E> *l, HuffNode<E> *r)
	{
		this->left = l;
		this->right = r;
		this->wgt = l->weight() + r->weight();
	}
	int weight() const override { return wgt; }
	bool isLeaf() const override { return false; }
};
template <typename E>
class HuffTree
{
public:
	HuffNode<E> *Root; // Tree root
protected:
	int getHeightRec(const HuffNode<E> *node)
	{
		if (node)
		{
			int lh = getHeightRec(node->getleft());
			int rh = getHeightRec(node->getright());
			return 1 + max(lh, rh);
		}
		return 0;
	}

public:
	// Leaf constructor
	HuffTree(E &val, int freq)
		: Root(new LeafNode<E>(val, freq)) {}

	// Internal node constructor
	HuffTree(HuffTree<E> *l, HuffTree<E> *r)
		: Root(new IntlNode<E>(l->root(), r->root())) {}

	~HuffTree()
	{
		delete Root; // Recursively delete nodes}
	}

	HuffNode<E> *root() const { return Root; }
	int weight() const { return Root->weight(); }

	int BalanceFactor(const HuffNode<E> *node)
	{
		if (node)
		{
			return getHeightRec(node->getright()) - getHeightRec(node->getleft());
		}
		return 0;
	}

	bool check_avl(const HuffNode<E> *node)
	{
		if (abs(BalanceFactor(node)) > 1)
		{
			return false;
		}
		return true;
	}

	HuffNode<E> *rotateLeft(HuffNode<E> *node)
	{
		HuffNode<E> *newRoot = node->right;
		node->right = newRoot->left;
		newRoot->left = node;
		return newRoot;
	}

	HuffNode<E> *rotateRight(HuffNode<E> *node)
	{
		HuffNode<E> *newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;
		return newRoot;
	}

	HuffNode<E> *rebalance(HuffNode<E> *root)
	{
		if (root == nullptr)
		{
			return root;
		}
		if (BalanceFactor(root) >= -1 && BalanceFactor(root) <= 1)
		{
			return root;
		}

		HuffNode<E> *newRoot = root;
		if (BalanceFactor(root) <= -1)
		{
			HuffNode<E> *leftTree = root->getleft();
			if (BalanceFactor(leftTree) >= 1)
			{
				root->left = rotateLeft(root->getleft());
				newRoot = rotateRight(root);
			}
			else
				newRoot = rotateRight(root);
		}
		else if (BalanceFactor(root) >= 1)
		{
			HuffNode<E> *rightTree = root->getright();
			if (BalanceFactor(rightTree) <= -1)
			{
				root->right = rotateRight(root->right);
				newRoot = rotateLeft(root);
			}
			else
				newRoot = rotateLeft(root);
		}
		return newRoot;
	}

	void duyetcay(HuffNode<E> *&node)
	{
		if (!node)
		{
			return;
		}

		for (int i = 0; i < 3; i++)
		{
			if (!check_avl(node))
			{
				node = rebalance(node);
			}
			else
			{
				break;
			}
		}
		duyetcay(node->left);
		duyetcay(node->right);
	}

	void encode(const HuffNode<E> *node, string str, unordered_map<char, string> &huffmanCode)
	{
		if (node == nullptr)
		{
			return;
		}
		if (node->isLeaf())
		{
			const LeafNode<E> *leafNode = dynamic_cast<const LeafNode<E> *>(node);
			huffmanCode[leafNode->val()] = str;
		}
		encode(node->getleft(), str + "0", huffmanCode);
		encode(node->getright(), str + "1", huffmanCode);
	}

	int HUFFMAN_CODE(node *head)
	{
		node *temp = head;
		unordered_map<char, string> huffmanCode;
		encode(Root, "", huffmanCode);
		string result = "";
		while (temp != nullptr)
		{
			char ch = temp->data;
			result += huffmanCode[ch];
			temp = temp->next;
		}
		return result_to_int(result);
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
};
template <typename E>
struct minTreeComp
{
	bool operator()(const HuffTree<E> *tree1, const HuffTree<E> *tree2) const
	{
		return tree1->weight() < tree2->weight();
	}
};
template <typename E, typename C>
class heap
{
private:
	vector<E> heapdata;
	C comparator;

public:
	heap(E arr[], int n, int maxsize)
	{
		heapdata.reserve(maxsize);
		for (int i = 0; i < n; ++i)
		{
			heapdata.push_back(arr[i]);
		}
		buildHeap();
	}

	void buildHeap()
	{
		int n = heapdata.size();
		for (int i = n / 2 - 1; i >= 0; --i)
		{
			heapify(i);
		}
	}

	void heapify(int i)
	{
		int n = heapdata.size();
		int smallest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < n && comparator(heapdata[left], heapdata[smallest]))
		{
			smallest = left;
		}

		if (right < n && comparator(heapdata[right], heapdata[smallest]))
		{
			smallest = right;
		}

		if (smallest != i)
		{
			std::swap(heapdata[i], heapdata[smallest]);
			heapify(smallest);
		}
	}

	void insert(const E &item)
	{
		heapdata.push_back(item);
		int i = heapdata.size() - 1;

		while (i > 0 && comparator(heapdata[i], heapdata[(i - 1) / 2]))
		{
			std::swap(heapdata[i], heapdata[(i - 1) / 2]);
			i = (i - 1) / 2;
		}
	}

	E removeFirst()
	{
		if (heapdata.empty())
		{
			throw std::out_of_range("Heap is empty");
		}

		E first = heapdata[0];
		heapdata[0] = heapdata.back();
		heapdata.pop_back();
		heapify(0);

		return first;
	}

	int size() const
	{
		return heapdata.size();
	}
};
template <typename E>
HuffTree<E> *buildHuff(HuffTree<E> **TreeArray, int count)
{
	heap<HuffTree<E> *, minTreeComp<E>> *forest =
		new heap<HuffTree<E> *, minTreeComp<E>>(TreeArray, count, count);

	HuffTree<E> *temp1, *temp2, *temp3 = nullptr;
	while (forest->size() > 1)
	{
		temp1 = forest->removeFirst();
		temp2 = forest->removeFirst();
		temp3 = new HuffTree<E>(temp1, temp2);
		temp3->duyetcay(temp3->Root);
		if (temp3->root()->isLeaf())
		{
			delete forest;
			return nullptr;
		}
		forest->insert(temp3);
	}
	delete forest;
	return temp3;
}
template <typename E>
void HUFFMANTREE_Inorder(const HuffNode<E> *node)
{
	if (node)
	{
		HUFFMANTREE_Inorder(node->getleft());
		if (!node->isLeaf())
		{
			cout << node->weight() << endl;
		}
		else
		{
			const LeafNode<E> *leafNode = dynamic_cast<const LeafNode<E> *>(node);
			cout << leafNode->val() << endl;
		}
		HUFFMANTREE_Inorder(node->getright());
	}
}
template <typename E>
bool check_number_node(const HuffNode<E> *node)
{
	if (node->getleft() == nullptr && node->getright() == nullptr)
	{
		return false;
	}
	return true;
}
/////////////////

//////NHA-HANG-S/////
class minheap_node
{
public:
	int id;
	int freq;
	vector<int> minheap_node_result;

	minheap_node(int id, int result)
	{
		this->id = id;
		this->freq = 1;
		minheap_node_result.push_back(result);
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
				int size = thutuid.size();
				int i = 0;
				for (i = 0; i < size; i++)
				{
					if (thutuid[i] == heap[vitri].id)
					{
						break;
					}
				}
				thutuid.erase(thutuid.begin() + i);
				cout << heap[vitri].minheap_node_result.front() << "-" << heap[vitri].id << endl;
				heap[vitri].minheap_node_result.erase(heap[vitri].minheap_node_result.begin());
			}
			heap.erase(heap.begin() + vitri);
		}
		else
		{
			int count = 0;
			while (count != num)
			{
				int size = thutuid.size();
				int i = 0;
				for (i = 0; i < size; i++)
				{
					if (thutuid[i] == heap[vitri].id)
					{
						break;
					}
				}
				thutuid.erase(thutuid.begin() + i);
				cout << heap[vitri].minheap_node_result.front() << "-" << heap[vitri].id << endl;
				heap[vitri].minheap_node_result.erase(heap[vitri].minheap_node_result.begin());
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

	hash_table_node(BSTNode *root, int result)
	{
		this->root = root;
		hash_table_queue.push(result);
	}
};

hash_table_node *hash_table[10000] = {nullptr};

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

HuffTree<char> *hand = nullptr;

class myarray
{
public:
	int id;
	int freq;
	myarray(int id, int freq) : id(id), freq(freq) {}
};

void LAPSE_main(string name)
{
	hand = nullptr;
	delete hand;

	if ((int)name.size() <= 0)
	{
		return;
	}
	Linklist *arr = newlist(name[0]);
	for (int i = 1; i < (int)name.size(); i++)
	{
		arr->addElement(name[i]);
	}
	if ((arr->Linklist_size()) < 3)
	{
		return;
	}
	arr->LAPSE_caesar();
	arr->delete_samenode();
	arr->LAPSE_sort();

	node *head = arr->Linklist_gethead();
	const int size = arr->Linklist_size();
	HuffTree<char> *treeArray[size];
	for (int i = 0; i < size; ++i)
	{
		treeArray[i] = new HuffTree<char>(head->data, head->freq);
		head = head->next;
	}
	hand = buildHuff(treeArray, size);
	if (!hand)
	{
		hand = nullptr;
		return;
	}
	int result = hand->HUFFMAN_CODE(arr->Linklist_gethead());
	if (!check_number_node(hand->root()))
	{
		result = 0;
	}
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
void KEITEIKEN_main(int num)
{
	int NUM = num;
	int n = HEAP.minheap_size();
	if (num > n)
	{
		NUM = n;
	}
	vector<myarray> khuvuc;
	for (int i = 0; i < n; i++)
	{
		myarray a(HEAP.heap[i].id, HEAP.heap[i].freq);
		khuvuc.push_back(a);
	}
	sort(khuvuc.begin(), khuvuc.end(), [](const myarray &a, const myarray &b)
		 { return a.freq < b.freq; });

	int num1 = NUM;
	for (int i = 0; i < NUM; i++)
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
			while (vector2.size() > 1 && dem < (int)vector2.size())
			{
				if (HEAP.thutuid[j] == vector2[dem].id)
				{
					vector2.erase(vector2.begin() + dem);
					break;
				}
				dem++;
			}
		}
		for (int j = 0; j < (int)khuvuc.size(); j++)
		{
			if (khuvuc[j].id == vector2[0].id)
			{
				khuvuc.erase(khuvuc.begin() + j);
				break;
			}
		}
		int ID = vector2[0].id;
		HEAP.thutuid.push_back(ID);
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
	if (!hand)
	{
		return;
	}
	HUFFMANTREE_Inorder(hand->root());
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
	if (num < 1 || num > MAXSIZE)
	{
		return;
	}
	KEITEIKEN_main(num);
}
void HAND()
{
	HAND_main();
}
void LIMITLESS(int num)
{
	if (num < 1 || num > MAXSIZE)
	{
		return;
	}
	LIMITLESS_main(num);
}
void CLEAVE(int num)
{
	if (num < 0)
	{
		return;
	}
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