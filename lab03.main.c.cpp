//ALGO2 IS1 LAB03


#include <iostream>
template<typename Type>
void clear_key(Type del);

template <typename Type> 
class DrzewoBST
{
public:
	typedef   std::stringstream& (*tprint_to_string)(std::stringstream& ss, const Type& t);
	struct Node
	{
		Node(Type& k, Node* p, int i);
		Node* parent;
		Node* left;
		Node* right;
		int index;
		Type key;
	};
	
	
private:
	Node* root;
	int size;
	void clear_Nodes(Node* cut);
	void clear_Nodes(Node* cut, void (*clear_key)(Type del));
	int hight_Node(Node* hight);
public:

	DrzewoBST();
	~DrzewoBST();
	Node* add_Node(Type& key, int (*compareT)(const Type& obj1,const Type& obj2));
	Node* search_Node(const Type &key, int (*compareT)(const Type& obj1, const Type& obj2));
	void delete_LNode(Node* branch_cut);
	void delete_LNode(Node* branch_cut, void (*clear_key)(Type del));
	void preorder(Node* koko);
	void inorder(Node* inin);
	void clear_tree();
	void clear_tree(void (*clear_key)(Type del));
	int hight_tree();
	void print(Node* tencoma);
};



struct test
{
	test(int f1, char f2)
		:field1{ f1 }, field2{ f2 }
	{}

	int field1;
	char field2;
};

template <typename T>
int compareT(const T& obj1, const T& obj2);


template <typename Type>
std::stringstream& print_to_ss(std::stringstream& ss, const Type& t);




template <typename Type>
DrzewoBST<Type>::Node::Node(Type& k, Node* p, int i)
	: parent{ p }, key{ k }, left{ nullptr }, right{ nullptr }, index{ i }
{

}

template <typename Type>
typename DrzewoBST<Type>::Node* DrzewoBST<Type>::add_Node(Type& key, int (*compareT)(const Type& obj1,const Type& obj2))
{
	if (root != nullptr) 
	{
		Node* actual_node;
		Node* actual_parent{nullptr};
		actual_node = root;
		while (actual_node != nullptr)
		{
			actual_parent = actual_node;
			
			if (compareT(actual_node->key, key)  == 0)
			{
				return nullptr;
			}

			if (compareT(actual_node->key, key)<0)
			{
				actual_node = actual_node->right;
			}
			else if (compareT(actual_node->key, key)>0)
			{
				actual_node = actual_node->left;
			}
		}
		
		actual_node = new Node(key, actual_parent, size);
		if (compareT(actual_parent->key, actual_node->key) > 0) {
			actual_parent->left = actual_node;
		}
		if (compareT(actual_parent->key,actual_node->key) < 0) {
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
		return actual_node;
	}
	else
	{
		root = new Node(key, nullptr, 0);
		size++;
		return root;
	}
	
	
}


template <typename Type>
typename DrzewoBST<Type>::Node* DrzewoBST<Type>::search_Node(const Type& key, int (*compareT)(const Type& obj1, const Type& obj2))
{
	if (size == 0)
	{
		return nullptr;
	}
	else
	{	
		Node* actual_node=root;
		while ( compareT( actual_node->key, key ) )
		{
			
			if (compareT(actual_node->key, key)<0)
			{
				actual_node = actual_node->right;
			}
			else if (compareT(actual_node->key, key)>0)
			{
				actual_node = actual_node->left;
			}
			if (actual_node == nullptr)
			{
				return nullptr;
			}

		}
		if (compareT(actual_node->key, key) == 0)
		{
			
			return actual_node;
			
		}

	}
}

template <typename Type>
void DrzewoBST<Type>::delete_LNode(Node* branch_cut)
{
	
	Node* parent= branch_cut->parent;
	//Node* &parent_side;
	//if (parent->right == branch_cut)

	if ( (branch_cut->left == nullptr) && (branch_cut->right == nullptr) )
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
	else if ((branch_cut->left != nullptr) && (branch_cut->right != nullptr))
	{

	
		Node* search_node = branch_cut->right;
		while (search_node->left !=nullptr)
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
void DrzewoBST<Type>::delete_LNode(Node* branch_cut, void (*clear_key)(Type del))
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
	else if ((branch_cut->left != nullptr) && (branch_cut->right != nullptr))
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
	clear_key(branch_cut->key);
	delete branch_cut;
	size--;
}



template <typename T>
int compareT(const T& obj1,const T& obj2) //
{
	
	return(obj1->field1-obj2->field1);
}

template <typename Type>
void DrzewoBST<Type>::preorder(Node* koko) 
{
	if (koko != nullptr)
	{
		print(koko);
		preorder(koko->left);
		preorder(koko->right);

	}
	return;
}


template <typename Type>
void DrzewoBST<Type>::print(Node* tencoma)
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
	std::cout << "\n";
}


template <typename Type>
void DrzewoBST<Type>::inorder(Node* inin) 
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
void DrzewoBST<Type>::clear_Nodes(Node* cut)
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
void DrzewoBST<Type>::clear_Nodes(Node* cut, void (*clear_key)(Type del))
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
void DrzewoBST<Type>::clear_tree() 
{
	if (root != nullptr)
	{
		clear_Nodes(root);
	}
		

}
template <typename Type>
void DrzewoBST<Type>::clear_tree(void (*clear_key)(Type del))
{
	if (root != nullptr)
	{
		clear_Nodes(root,clear_key);
	}


}

template <typename Type>
int DrzewoBST<Type>::hight_tree()
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
int DrzewoBST<Type>::hight_Node(Node* hight)
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

template<typename Type>
void clear_key(Type del) 
{
	delete del;
}

template <typename Type>
DrzewoBST<Type>::DrzewoBST()
	:size{ 0 }, root{ nullptr }
{

}

template <typename Type>
DrzewoBST<Type>::~DrzewoBST()
{
}

template <typename Type>
std::stringstream& print_to_ss(std::stringstream& ss, const Type& t)
{
	ss << t->field1 << " " << t->field2 << ", ";
	return ss;
}

int main()
{
	test* pierw = new test(2, 'a');
	test* dru = new test(4, 'b');
	test* trz = new test(5, 'c');
	test* czw = new test(6, 'd');
	test* szu = new test(40, 'e');
	DrzewoBST<test*> M;
	M.add_Node(trz, compareT);
	M.add_Node(pierw, compareT);
	M.add_Node(dru, compareT);
	M.add_Node(szu, compareT);
	M.add_Node(czw, compareT);
	M.inorder(M.search_Node(trz, compareT));
	std::cout << "Hight: " << M.hight_tree() << '\n';

	M.clear_tree(clear_key);


}
