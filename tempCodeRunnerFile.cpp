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
void printPostorder(BSTNode *root)
{
	if (root)
	{
		printPostorder(root->left);
		cout << root->result << " ";
		printPostorder(root->right);
	}
}
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
	else if (result > root->result)
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
void delete_full_BST(BSTNode *&root)
{
	if (root)
	{
		// Delete left and right subtrees
		delete_full_BST(root->left);
		delete_full_BST(root->right);

		// Delete current node
		delete root;
		root = nullptr;
	}
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
	else
	{
		return 1;
	}
}
void xoa_cay_bst(int vitri, int count, int size)
{
	if (count >= size)
	{
		delete_full_BST(hash_table[vitri]->root);
		return;
	}
	while (count >= 0)
	{
		int val = (hash_table[vitri]->hash_table_queue).front();
		hash_table[vitri]->root = deleteNode(hash_table[vitri]->root, val);
		(hash_table[vitri]->hash_table_queue).pop();
		count--;
	}
}