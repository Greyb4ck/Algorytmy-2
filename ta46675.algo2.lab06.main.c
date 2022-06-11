//ALGO2 IS1 LAB06

#include <iostream>
#include <vector>
#include <sstream>
#include <time.h>
#include <math.h>


template<typename Type>
void clear_key(Type& del);

template <typename Type>
struct Node
{
	Node(Type&& k);
	Node();
	Type key;
};

template <typename Type>
class binary_h
{
private:
	typedef   std::stringstream& (*tprint_to_string)(std::stringstream& ss, const Type& t);
	int find_Parent(int index);
	int find_Child(int index, bool left);
	int capacity;

public:
	int size;
	binary_h();
	~binary_h();
	void add_Node(Type &key, int (*compareT)(const Type& obj1, const Type& obj2));
	void reHeap(int index, int (*compareT)(const Type& obj1, const Type& obj2));
	void reHeap_up(int index, int (*compareT)(const Type& obj1, const Type& obj2));
	void delete_elemMax(int (*compareT)(const Type& obj1, const Type& obj2));
	void delete_elemMax(int (*compareT)(const Type& obj1, const Type& obj2), void (*clear_key)(Type& del));
	void delete_all();
	void delete_all(void (*clear_key)(Type& del));
	std::string to_string(int number, tprint_to_string print_to_string);
	std::vector<Type> table_D;
	

	
};

template <typename Type>
std::stringstream& print_to_ss(std::stringstream& ss, const Type& t);

template <typename Type>
binary_h<Type>::binary_h()
	: size{ 0 }, capacity{ 1 }, table_D(0)
{

}

template <typename Type>
binary_h<Type>::~binary_h()
{
}



template <typename Type>
void  binary_h<Type>::add_Node(Type& node, int (*compareT)(const Type& obj1, const Type& obj2))
{
	if (size == capacity)
	{
		table_D.reserve(capacity * 2);
	}


	size++;
	int number = size - 1;
	table_D.push_back(node);
	if (size == 1)
	{

		return;
	}
	reHeap(number, compareT);

}


template <typename Type>
void binary_h<Type>::reHeap(int index, int (*compareT)(const Type& obj1, const Type& obj2))
{
	int int_p = find_Parent(index);
	int actual_numb = index;

	if (compareT(table_D[int_p], table_D[index]) == 0)
	{
		return;
	}

	if (compareT(table_D[int_p], table_D[index]) < 0)
	{
		Type temp = table_D[int_p];
		table_D[int_p] = table_D[actual_numb];
		table_D[actual_numb] = temp;
		actual_numb = int_p;
		reHeap(actual_numb, compareT);

	}

	return;
}


template <typename Type>
void binary_h<Type>::reHeap_up(int index, int (*compareT)(const Type& obj1, const Type& obj2))
{
	if (size > (index * 2) + 2)
	{
		int int_CL = find_Child(index, 1);
		int int_CR = find_Child(index, 0);
		int actual_numb = index;
		if (compareT(table_D[int_CL], table_D[int_CR]) > 0)
		{
			if (compareT(table_D[int_CL], table_D[index]) > 0)
			{
				Type temp = table_D[int_CL];
				table_D[int_CL] = table_D[actual_numb];
				table_D[actual_numb] = temp;
			}
			actual_numb = int_CL;
		}
		else if (compareT(table_D[int_CL], table_D[int_CR]) <= 0)
		{
			if (compareT(table_D[int_CR], table_D[index]) > 0)
			{
				Type temp = table_D[int_CR];
				table_D[int_CR] = table_D[actual_numb];
				table_D[actual_numb] = temp;
			}
			actual_numb = int_CR;
		}
		reHeap_up(actual_numb, compareT);
	}
	else if (size > (index * 2) + 1)
	{
		int int_CL = find_Child(index, 1);
		int actual_numb = index;
		if (compareT(table_D[int_CL], table_D[index]) > 0)
		{
			Type temp = table_D[int_CL];
			table_D[int_CL] = table_D[actual_numb];
			table_D[actual_numb] = temp;
		}
		actual_numb = int_CL;
		reHeap_up(actual_numb, compareT);
	}
	return;
}

template <typename Type>
void binary_h<Type>::delete_elemMax(int (*compareT)(const Type& obj1, const Type& obj2))
{
	if (size == 0)
	{
	
		return;
	}
	Type temp = table_D[0];
	table_D[0] = table_D[size - 1];
	table_D.pop_back();
	size--;
	reHeap_up(0, compareT);


}


template <typename Type>
void binary_h<Type>::delete_elemMax(int (*compareT)(const Type& obj1, const Type& obj2), void (*clear_key)(Type& del))
{
	if (size == 0)
	{
	
		return;
	}
	Type temp = table_D[0];
	table_D[0] = table_D[size - 1];
	clear_key(temp);
	table_D.pop_back();
	size--;
	reHeap_up(0, compareT);


}


template <typename Type>
int binary_h<Type>::find_Parent(int index)
{
	if (size >= 1 && index < size)
	{
		int index_parent = (index - 1) / 2;
		return	index_parent;
	}
}






template <typename Type>
int binary_h<Type>::find_Child(int index , bool left)
{
	if (left == 1) // left
	{
		int index_left = (2 * index) + 1;
		return index_left;
	}
	else if (left == 0) // right
	{
		int	index_right = (2 * index) + 2;
		return index_right;
	}

}



template <typename Type>
int compareT(const Type& obj1, const Type& obj2);



template <typename Type>
void binary_h<Type>::delete_all()
{
	table_D.clear();
	size = 0;
}

template <typename Type>
void binary_h<Type>::delete_all(void (*clear_key)(Type &del))
{
	for (int i = 0; i < size; i++)
	{
		clear_key(table_D[i]);
	}

	table_D.clear();
	size = 0;
}

template <typename Type>
int compareT(const Type& obj1, const Type& obj2) //
{
	return(obj1->key - obj2->key);
}




int main()
{
	//binary_h<Node<int>> M;
	/*
	Node<int> uu(5);
	M.add_Node(uu, compareT);
	Node<int> ue(4);
	M.add_Node(ue, compareT);
	Node<int> uc(3);
	M.add_Node(uc, compareT);
	Node<int> ua(2	);
	M.add_Node(ua, compareT);
	Node<int> ut(8);
	M.add_Node(ut, compareT);
	Node<int> ug(10);
	M.add_Node(ug, compareT);
	M.delete_elemMax(compareT);
	std::cout << M.to_string(3 , print_to_ss);
	//M.table_D[0].key = 1;
	//M.reHeap_up(0, compareT);



	/*std::cout << M.table_D[0].key << "\n";
	std::cout << M.table_D[1].key << "\n";
	std::cout << M.table_D[2].key << "\n";
	std::cout << M.table_D[3].key << "\n";
	std::cout << M.table_D[4].key << "\n";*/
	//std::cout << M.table_D[5].key << "\n";

	/*
	M.table_D.push_back(1);
	M.table_D.push_back(2);
	M.table_D.push_back(3);
	M.table_D.push_back(4);
	M.table_D.push_back(5);
	M.table_D.push_back(6);
	M.table_D.push_back(7);
	M.table_D.push_back(8);
	M.table_D.push_back(9);
	M.table_D.push_back(10);
	M.table_D.push_back(11);
	M.table_D.push_back(12);
	M.size = 12;
	M.find_Child(1,1);
	M.find_Child(1,0);
	M.find_Child(2,1);
	M.find_Child(2,0);
	M.find_Child(3,1);
	M.find_Child(3,0);
	M.find_Child(4,0);
	M.find_Child(4,1);
	M.find_Child(5,0);
	M.find_Child(5,1);
	M.find_Child(6,0);
	M.find_Child(6,1);
	M.find_Child(7,0);
	M.find_Child(7,1);
	M.find_Child(8,0);
	M.find_Child(8,1);

	
	M.find_Parent(0);
	M.find_Parent(1);
	M.find_Parent(2);
	M.find_Parent(3);
	M.find_Parent(4);
	M.find_Parent(5);
	M.find_Parent(6);
	M.find_Parent(7);
	M.find_Parent(8);
	M.find_Parent(9);
	M.find_Parent(10);
	M.find_Parent(11);
    */
	std::cout << "Hello World!\n";
	
	const int MAX_ORDER = 7;
	const int n = std::pow(10, 4);

	binary_h<Node<int>*>* bh = new binary_h<Node<int>*>();
	for (int o = 1; o <= MAX_ORDER; o++) 
	{
	
		clock_t t1 = clock();
		for (int i = 0; i < n; i++) 
		{
			Node<int>* t = new Node<int>(rand()%10000);
			bh->add_Node(t, compareT);
		
		}
		clock_t t2 = clock();
		std::cout << bh->to_string(10, print_to_ss);
		t1 = clock();
		std::cout << "czas t2: " << t2 << "\n";
		for (int i = 0; i < n; i++) 
		{
			bh->delete_elemMax(compareT);
		}
		
		t2 = clock();
		std::cout << "czas t1: "<< t1 << "\n";
		bh->delete_all();

	}
	bh->delete_all(clear_key);

}
//
//size++;
//int number = size - 1;
//table_D.push_back(node);

template<typename Type>
void clear_key(Type& del)
{
	delete del;
}


template <typename Type>
std::string binary_h<Type>::to_string(int number, tprint_to_string print_to_string) //std::stringstream&(*)(std::stringstream& ss,const Type& t))
{
	std::stringstream ss;
	
	for (int i = 0; i < number; i++)
	{
		int los = rand() % size;
		ss << "index: " << los << "  ";
		ss << "klucz: "; 
		print_to_ss(ss, table_D[los]);

	}
	ss << '\n';

	return ss.str();

}

template <typename Type>
std::stringstream& print_to_ss(std::stringstream& ss, const Type& t)
{
	ss << t->key << '\n';
	return ss;
}

template <typename Type>
Node<Type>::Node(Type&& k)
	: key{ k }
{
}
template <typename Type>
Node<Type>::Node()
	: key{ 0 }
{
}