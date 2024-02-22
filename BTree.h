#pragma once



template<class TKey, class TVal>
struct BTreeNode
{
	TKey key;
	TVal value;
	BTreeNode* left  = nullptr;
	BTreeNode* right = nullptr;

	BTreeNode(const TKey& key, const TVal& val): key(key), value(val){ }

	void print()
	{
		if (left != nullptr) left->print();
		cout << value << " ";
		if (right != nullptr) right->print();
	}

	void del()
	{
		if (left != nullptr) left->del();
		if (right != nullptr) right->del();
		delete this;
	}


	TVal* getValue(const TKey& key)
	{
		if (key == this->key) return &value;
		if (key < this->key && left != nullptr) return left->getValue(key);
		if (key > this->key && right != nullptr) return right->getValue(key);
		return nullptr;
	}
};


template<class TKey, class TVal>
class BTree
{
	BTreeNode<TKey, TVal>* root = nullptr;

	BTreeNode<TKey, TVal>* push_r(const TKey& key, const TVal& value, BTreeNode<TKey, TVal>*& node);
	void printToFile(BTreeNode<TKey, TVal>* node, ofstream& file) const {
			if (node) {
				printToFile(node->left, file);
				file << node->key << ":\n";
				node->value.printToFile(file);
				printToFile(node->right, file);
			}
		}
public:
	~BTree();
	bool push(const TKey& key, const TVal& value);
	bool push_r(const TKey& key, const TVal& value);
	TVal* getValue(const TKey& key);
	void print();
	void clear();
	void printToFile(ofstream& file) const {
		printToFile(root, file);
	}
	BTreeNode<TKey, TVal>* getRoot() const {
		return root;
	}
};




template<class TKey, class TVal>
BTreeNode<TKey, TVal>* BTree<TKey, TVal>::push_r(const TKey& key, const TVal& value, BTreeNode<TKey, TVal>*& node)
{
	if (node == nullptr)
	{
		node = new BTreeNode<TKey, TVal>(key, value);
		return node;
	}

	if (key < node->key)
		node->left = push_r(key, value, node->left);
	else if (key > node->key)
		node->right = push_r(key, value, node->right);
	return node;

}

template<class TKey, class TVal>
BTree<TKey, TVal>::~BTree()
{
	this->clear();
}

template<class TKey, class TVal>
bool BTree<TKey, TVal>::push(const TKey& key, const TVal& value)
{
	
	if (!root)
	{
		root = new BTreeNode<TKey, TVal>(key, value);
		return true;
	}

	BTreeNode<TKey, TVal>* current = root;
	do
	{
		if (key < current->key)
		{
			if (current->left != nullptr)
			{
				current = current->left;
			}
			else
			{
				current->left = new BTreeNode<TKey, TVal>(key, value);
				return true;
			}
		}
		else if (key > current->key)
		{
			if (current->right != nullptr)
			{
				current = current->right;
			}
			else
			{
				current->right = new BTreeNode<TKey, TVal>(key, value);
				return true;
			}
		}
		else
		{
			return false;
		}
	} while (true);
}

template<class TKey, class TVal>
bool BTree<TKey, TVal>::push_r(const TKey& key, const TVal& value)
{
	return push_r(key, value, root);
}

template<class TKey, class TVal>
TVal* BTree<TKey, TVal>::getValue(const TKey& key)
{
	if(root)
		return root->getValue(key);
	return nullptr;
}

template<class TKey, class TVal>
void BTree<TKey, TVal>::print()
{
	if (root)
		root->print();
}

template<class TKey, class TVal>
void BTree<TKey, TVal>::clear()
{
	if (root)
		root->del();
}
