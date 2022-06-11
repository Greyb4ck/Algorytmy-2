//ALGO2 IS1 LAB04

#include <iostream>
template<typename Type>
void clear_key(Type del);

template<typename Type>
class RedBlack_Tree
{
public:
	struct Node
	{
		Node(Type& k, Node* p, int i);
		Node* parent;
		Node* left;
		Node* right;
		int index;
		Type key;
		bool color;
	};
	enum { black, red};

    RedBlack_Tree();
    ~RedBlack_Tree();
	Node* search_Node(const Type& key, int (*compareT)(const Type& obj1, const Type& obj2));
	void inorder(Node* inin);
	void preorder(Node* jojo);
	void print(Node* tencoma);
	void clear_tree();
	void clear_tree(void (*clear_key)(Type del));
	int hight_tree();
	Node* add_Node(Type& key, int (*compareT)(const Type& obj1, const Type& obj2));
	void print();
	void rotation_L (Node* x, Node* y);
	void rotation_R (Node* x, Node* y);
	void fixup(Node* nowy);
	void delete_LNode(Node* branch_cut);
	void delete_LNode(Node* branch_cut, void (*clear_key)(Type del));

private:
	Node* root;
	int size;
	int hight_Node(Node* hight);
	void clear_Nodes(Node* cut);
	void clear_Nodes(Node* cut, void (*clear_key)(Type del));
};

template <typename Type>
RedBlack_Tree<Type>::Node::Node(Type& k, Node* p, int i)
	: parent{ p }, key{ k }, left{ nullptr }, right{ nullptr }, index{ i }, color{red}
{

}


template <typename T>
int compareT(const T& obj1, const T& obj2);

struct test
{
	test(int f1, char f2)
		:field1{ f1 }, field2{ f2 }
	{}

	int field1;
	char field2;
};


template <typename Type>
typename RedBlack_Tree<Type>::Node* RedBlack_Tree<Type>::search_Node(const Type& key, int (*compareT)(const Type& obj1, const Type& obj2))
{
	if (size == 0) {

		return nullptr;
	}
	else
	{
		Node* actual_node = root;
		while (compareT(actual_node->key,key))
		{
			if (compareT(actual_node->key,key)<0)
			{
				actual_node = actual_node->right;
			}
			else if (compareT(actual_node->key,key)>0)
			{
				actual_node = actual_node->left;
			}
			if (actual_node == nullptr)
			{
				return nullptr;
			}

		}
		if (compareT(actual_node->key,key) == 0)
		{
			return actual_node;
		}
	}
}


template <typename Type>
void RedBlack_Tree<Type>::print(Node* tencoma)
{
	if (tencoma == nullptr)
	{
		std::cout << "Node* nullptr\n";
		return;
	}

	if (tencoma->parent == nullptr)
		std::cout << " parent null   ";
	if (tencoma->left == nullptr)
		std::cout << " left null  ";
	if (tencoma->right == nullptr)
		std::cout << " right null";
	std::cout << "\n";
	std::cout << tencoma->key->field1 << " key\t"
		<< tencoma->index << " index  \t";
	if (tencoma->parent != nullptr)
		std::cout << tencoma->parent->key->field1 << " parent key   ";
	if (tencoma->left != nullptr)
		std::cout << tencoma->left->key->field1 << " left key   ";
	if (tencoma->right != nullptr)
		std::cout << tencoma->right->key->field1 << " right key   ";
		std::cout << tencoma->color << " color   ";
	std::cout << "\n";
}

template <typename Type>
void RedBlack_Tree<Type>::preorder(Node* jojo)
{
	if (jojo != nullptr)
	{
		print(jojo);
		preorder(jojo->left);
		preorder(jojo->right);

	}
	return;
}


template <typename Type>
void RedBlack_Tree<Type>::inorder(Node* inin)
{
	if (inin != nullptr)
	{
		inorder(inin->left);
		print(inin);
		inorder(inin->right);
	}
	return;
}

template <typename Type>
void RedBlack_Tree<Type>::clear_Nodes(Node* cut)
{
	if (cut->left != nullptr)
		clear_Nodes(cut->left);

	if (cut->right != nullptr)
		clear_Nodes(cut->right);

	if (cut->left == nullptr && cut->right == nullptr)
	{
		Node* parent = cut->parent;
		if (cut == root)
		{
			delete cut;
			return;
		}

		if (parent->right == cut)
			parent->right = nullptr;
		if (parent->left == cut)
			parent->left = nullptr;
		delete cut;
		return;
	}
}

template <typename Type>
void RedBlack_Tree<Type>::clear_Nodes(Node* cut, void (*clear_key)(Type del))
{
	if (cut->left != nullptr)
		clear_Nodes(cut->left);

	if (cut->right != nullptr)
		clear_Nodes(cut->right);

	if (cut->left == nullptr && cut->right == nullptr)
	{
		Node* parent = cut->parent;
		if (cut == root)
		{
			clear_key(cut->key);
			delete cut;

			return;
		}

		if (parent->right == cut)
			parent->right = nullptr;
		if (parent->left == cut)
			parent->left = nullptr;
		clear_key(cut->key);
		delete cut;
		return;
	}
}

template <typename Type>
void RedBlack_Tree<Type>::clear_tree()
{
	if (root != nullptr)
	{
		clear_Nodes(root);
	}
}

template <typename Type>
void RedBlack_Tree<Type>::clear_tree(void (*clear_key)(Type del))
{
	if (root != nullptr)
	{
		clear_Nodes(root, clear_key);
	}
}



template <typename Type>
int RedBlack_Tree<Type>::hight_tree()
{
	if (root == nullptr)
	{
		return -1;
	}
	else
	{
		return hight_Node(root);
	}
}

template <typename Type>
int RedBlack_Tree<Type>::hight_Node(Node* hight)
{
	if (hight == nullptr)
	{
		return -1;
	}
	int left_hight = hight_Node(hight->left);
	int right_hight = hight_Node(hight->right);

	if (left_hight > right_hight)
	{
		return left_hight + 1;
	}
	else
	{
		return right_hight + 1;
	}

}

template <typename Type>
typename RedBlack_Tree<Type>::Node* RedBlack_Tree<Type>::add_Node(Type& key, int (*compareT)(const Type& obj1, const Type& obj2))
{
	if (root != nullptr)
	{
		Node* actual_node;
		Node* actual_parent{ nullptr };
		actual_node = root;
		while (actual_node != nullptr)
		{
			actual_parent = actual_node;

			if (compareT(actual_node->key, key) == 0)
			{
				return nullptr;
			}

			if (compareT(actual_node->key, key) < 0)
			{
				actual_node = actual_node->right;
			}
			else if (compareT(actual_node->key, key) > 0)
			{
				actual_node = actual_node->left;
			}
		}

		actual_node = new Node(key, actual_parent, size);
		if (compareT(actual_parent->key, actual_node->key) > 0) {
			actual_parent->left = actual_node;
		}
		if (compareT(actual_parent->key, actual_node->key) < 0) {
			actual_parent->right = actual_node;
		}
		size++;
		/*
		if (size > 1) {
		std::cout << actual_node->key.field1 << " key\t"
			<< actual_node->index << " index  \t"
			<< actual_node->parent->key.field1 << " parent key   "
			<< actual_node->parent->index<< " parent index" << '\n';
		}
		*/
		fixup(actual_node);
		return actual_node;
	}
	else
	{
		root = new Node(key, nullptr, 0);
		size++;
		fixup(root);
		return root;
	}


}



template <typename Type>
void RedBlack_Tree<Type>::rotation_L(Node* x, Node* y)
{
	Node* z;
	if (x->parent != nullptr) 
	{
		z = x->parent;
		if (z->right == x)
			z->right = y;
		else
			z->left = y;
		x->parent = y;
		y->parent = z;
	}
	else
	{
		y->parent = nullptr;
		x->parent = y;
		root = y;
	}
	
	if (y->left != nullptr)
	{
		x->right = y->left;
		z = y->left;
		z->parent = x;
		
	}
	else
	{
		x->right = nullptr;
	}
	y->left = x;

}

template <typename Type>
void RedBlack_Tree<Type>::rotation_R(Node* x, Node* y)
{
	Node* z;
	if (x->parent != nullptr)
	{
		z = x->parent;
		if (z->right == x)
			z->right = y;
		else
			z->left = y;
		x->parent = y;
		y->parent = z;
	}
	else
	{
		y->parent = nullptr;
		x->parent = y;
		root = y;
	}

	if (y->right != nullptr)
	{
		x->left = y->right;
		z = y->right;
		z->parent = x;
	}
	else
	{
		x->left = nullptr;
	}
	y->right = x;

}


template <typename Type>
void RedBlack_Tree<Type>::fixup(Node* x)
{
	Node* parent = nullptr;
	Node* grandpa = nullptr;
	
	/*
	if (z->parent != nullptr)
	{
		parent = z->parent;

		if (z->parent->parent != nullptr)
		{
			grandpa = z->parent->parent;
			while ((z != root) && (parent->color == red))
			{

				if (parent == grandpa->left)
				{
					y = grandpa->right;
					
					if (y!=nullptr && y->color == red)     
						// 1
					{
						parent->color = black;          
						y->color = black;                  
						grandpa->color = red;
						z = grandpa;
						parent = grandpa->parent;
						grandpa = grandpa->parent->parent;
					}
					else
					{
						if (z == parent->right)
						{
							rotation_L(grandpa, parent);
							z = parent;
						}
						parent->color = black;
						grandpa->color = red;
						rotation_L(grandpa, parent);
					}
				}
				else
				{
					y = grandpa->left;
					if (y->color == red)
					{
						parent->color = black;
						y->color = black;
						grandpa->color = red;
						z = parent;
						parent = grandpa;
						if (parent == root)
						{
							break;
						}
						if (grandpa->parent != nullptr)
						{
							grandpa = grandpa->parent;
						}
					}
					else
					{
						if (z == parent->left)
						{
							rotation_R(grandpa, parent);
							z = parent;
							parent = grandpa;
							if (parent == root)
							{
								break;
							}
							if (grandpa->parent != nullptr)
							{
								grandpa = grandpa->parent;
							}
						}
						parent->color = black;
						grandpa->color = red;                          
						rotation_L(grandpa, parent);
					}
				}
			}
		}
	}
	root->color = black;
	*/
	while ((x != root) && (x->color != black) && (x->parent->color == red))
	{
		parent = x->parent;
		grandpa = x->parent->parent;
		if (parent == grandpa->left)
		{
			Node* uncle = grandpa->right;
			if ((uncle != nullptr) && (uncle->color == red))
			{
				grandpa->color = red;
				parent->color = black;
				uncle->color = black;
				x = grandpa;
			}
			else
			{
				if (x == parent->right)
				{
					rotation_L(parent, x);

					x  = parent;
					parent = x->parent;
					//grandpa = parent->parent;
				}
				rotation_R(grandpa, parent);
				//std::swap(parent->color, (bool)grandpa->color);
				bool temp_c = parent->color;
				parent->color = grandpa->color;
				grandpa->color = temp_c;
				//Node
				x = parent;
			}
		}
		else
		{
			Node* uncle = grandpa->left;
			if ((uncle != nullptr) && (uncle->color == red)) 
			{
				grandpa->color = red;
				parent->color = black;
				uncle->color = black;
				x = grandpa;
			}
			else
			{
				if (x == parent->left)
				{
					rotation_R(parent, x);
					x = parent;
					parent = x->parent;
					//grandpa = parent->parent;
				}
				rotation_L(grandpa, parent);
				//std::swap((bool)parent->color, (bool)grandpa->color);
				bool temp_c = parent->color;
				parent->color = grandpa->color;
				grandpa->color = temp_c;
				x = parent;
			}
		}
	}
	root->color = black;
}

template <typename Type>
void RedBlack_Tree<Type>::delete_LNode(Node* branch_cut)
{

	Node* parent = branch_cut->parent;
	//Node* &parent_side;
	//if (parent->right == branch_cut)

	if ((branch_cut->left == nullptr) && (branch_cut->right == nullptr))
	{
		if (compareT(parent->key, branch_cut->key) < 0)
		{
			parent->right = nullptr;
		}
		else if (compareT(parent->key, branch_cut->key) > 0)
		{
			parent->left = nullptr;
		}

	}
	if ((branch_cut->left != nullptr) || (branch_cut->right != nullptr))
	{
		if (branch_cut->left == nullptr)
		{

			if (parent->right == branch_cut) {
				parent->right = branch_cut->right;
				parent->right->parent = parent;
			}
			else {
				parent->left = branch_cut->right;
				parent->left->parent = parent;
			}

		}
		else if (branch_cut->right == nullptr)
		{
			if (parent->left == branch_cut) {
				parent->left = branch_cut->left;
				parent->left->parent = parent;
			}
			else {
				parent->right = branch_cut->left;
				parent->right->parent = parent;
			}
		}
	}
	if ((branch_cut->left != nullptr) && (branch_cut->right != nullptr))
	{


		Node* search_node = branch_cut->right;
		while (search_node->left != nullptr)
		{
			search_node = search_node->left;
		}
		if (parent->left == branch_cut)
		{
			parent->left = search_node;
			search_node->left = branch_cut->left;
			if (search_node != branch_cut->right)
				search_node->right = branch_cut->right;
		}
		else if (parent->right == branch_cut)
		{
			parent->right = search_node;
			search_node->left = branch_cut->left;
			if (search_node != branch_cut->right)
				search_node->right = branch_cut->right;
		}
	}
	delete branch_cut;
	size--;
}

template <typename Type>
void RedBlack_Tree<Type>::delete_LNode(Node* branch_cut, void (*clear_key)(Type del))
{

	Node* parent = branch_cut->parent;
	Node* fix = nullptr;
	//Node* &parent_side;
	//if (parent->right == branch_cut)
	if (branch_cut)
	{

	}
	
	if ((branch_cut->left == nullptr) && (branch_cut->right == nullptr))
	{
		if (compareT(parent->key, branch_cut->key) < 0)
		{
			parent->right = nullptr;
		}
		else if (compareT(parent->key, branch_cut->key) > 0)
		{
			parent->left = nullptr;
		}

	}
	else if ((branch_cut->left != nullptr) || (branch_cut->right != nullptr))
	{
		if (branch_cut->left == nullptr)
		{

			if (parent->right == branch_cut) {
				parent->right = branch_cut->right;
				parent->right->parent = parent;
			}
			else {
				parent->left = branch_cut->right;
				parent->left->parent = parent;
			}

		}
		else if (branch_cut->right == nullptr)
		{
			if (parent->left == branch_cut) {
				parent->left = branch_cut->left;
				parent->left->parent = parent;
			}
			else {
				parent->right = branch_cut->left;
				parent->right->parent = parent;
			}
		}
	}
	if ((branch_cut->left != nullptr) && (branch_cut->right != nullptr))
	{

		Node* search_node = branch_cut->right;
		while (search_node->left != nullptr)
		{
			search_node = search_node->left;
		}
		if (parent->left == branch_cut)
		{
			parent->left = search_node;
			search_node->left = branch_cut->left;
			if (search_node != branch_cut->right)
				search_node->right = branch_cut->right;
		}
		else if (parent->right == branch_cut)
		{
			parent->right = search_node;
			search_node->left = branch_cut->left;
			if (search_node != branch_cut->right)
				search_node->right = branch_cut->right;
		}
		while (fix->right != nullptr) 
		{
			fix = fix->right;
		}

	}
	

	clear_key(branch_cut->key);
	delete branch_cut;
	size--;
	fixup(fix);
}


int main()
{
	test* pierw = new test(5, 'a');
	test* dru = new test(2, 'b');
	test* trz = new test(4, 'c');
	test* czw = new test(8, 'd');
	test* pia = new test(1, 'e');
	test* szes = new test(9, 'e');
	test* sied = new test(7, 'e');
	RedBlack_Tree<test*> M;
	/*
	M.add_Node(trz, compareT);
	M.print(M.search_Node(trz, compareT));
	M.add_Node(pierw, compareT);
	M.print(M.search_Node(pierw, compareT));
	M.add_Node(dru, compareT);
	M.print(M.search_Node(dru, compareT));
	
	std::cout << "*************************\n";
	M.print(M.search_Node(trz, compareT));
	M.print(M.search_Node(pierw, compareT));
	M.print(M.search_Node(dru, compareT));
	*/
	/*M.add_Node(pierw, compareT);
	M.print(M.search_Node(pierw, compareT));
	M.add_Node(dru, compareT);
	std::cout << "*************************\n";
	M.print(M.search_Node(pierw, compareT));
	M.print(M.search_Node(dru, compareT));
	M.add_Node(trz, compareT);
	std::cout << "*************************\n";
	M.add_Node(czw, compareT);*/
	
	M.add_Node(pierw, compareT);
	M.add_Node(dru, compareT);
	M.add_Node(trz, compareT);
	M.add_Node(czw, compareT);
	M.add_Node(pia, compareT);
	M.add_Node(szes, compareT);
	M.add_Node(sied, compareT);
	M.print(M.search_Node(pierw, compareT));
	M.print(M.search_Node(dru, compareT));
	M.print(M.search_Node(trz, compareT));
	M.print(M.search_Node(czw, compareT));
	M.print(M.search_Node(pia, compareT));
	M.print(M.search_Node(szes, compareT));
	M.print(M.search_Node(sied, compareT));

	}


template <typename Type>
RedBlack_Tree<Type>::RedBlack_Tree()
	:size{ 0 }, root{ nullptr }
{

}

template <typename Type>
RedBlack_Tree<Type>::~RedBlack_Tree()
{

}

template <typename T>
int compareT(const T& obj1, const T& obj2) //
{

	return(obj1->field1 - obj2->field1);
}

template<typename Type>
void clear_key(Type del)
{
	delete del;
}