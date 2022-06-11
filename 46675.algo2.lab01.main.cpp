//ALGO2 IS1 LAB01
#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <exception>
#include <string>
#include <sstream>

template <typename Type>
class linked_list
{
private:

	struct Node
	{
		Node* previous;
		Node* next;
        Type object;
        Node(Node* p, Node* n,  Type& obj) 
        :previous(p), next(n), object(obj)
        {}
	};
	Node* first;
	Node* last;
	long size;

public:
    //void print()const;
	linked_list();
	~linked_list();
    void add_end(Type& object);             // a)
    void add_start(Type& object);          // b)
    void delete_last();                     // c)
    void delete_first();                    // d)
    void delete_last(bool p);                     // c)
    void delete_first(bool p);                    // d)
    const Type& give_i(int);                      // e)
    const Type& give_iRev(int);
    void set(int i, const Type& object);          // f)
    void set(int i, const Type& object, bool p);          // f)
    const Type* get(const Type& object,int (*compareT)(const Type&, const Type&)); // g)
    bool remove_if(const Type& object,int (*compareT)(const Type&, const Type&)); // h)
    bool remove_if(const Type& object, int (*compareT)(const Type&, const Type&), bool p); // h)
    bool add_order( Type& object,int (*compareT)(const Type&, const Type&)); // i)
    void clear_list(); // j
    void clear_list(bool p); // j
    std::string to_string(int number, std::stringstream& (*print_to_ss)(std::stringstream& ss,const Type& t));

};

template <typename Type>
linked_list<Type>::~linked_list() 
{
    clear_list();
}

template <typename Type>
std::string linked_list<Type>::to_string(int number,std::stringstream& (*print_to_ss)(std::stringstream& ss,const Type& t))
{
    std::stringstream ss;
    ss << "Adres pamieci listy: " << this << '\n';
    ss << "Rozmiar: " << size << "\n"
       << "Dane: " ;
    for (int i=0; i < size &&  i < number ; i++){   
        print_to_ss(ss, give_i(i));
    }
    ss << '\n';
    return ss.str();
    
}


template <typename Type>
linked_list<Type>::linked_list()
:size{ 0 }, first{ nullptr }, last{nullptr}
{
	
}



template <typename Type> 
void linked_list<Type>::add_end( Type& object)
{
	Node* second = last;
	last = new Node(second,nullptr,object);
	/*last->object = object;
	last->previous = second;
	last->next = nullptr;
    */
	if (second != nullptr)
		second->next = last;
	if (first == nullptr)
		first = last;
	++size;
}

template <typename Type>
void linked_list<Type>::add_start(Type& object)
{
    Node* second = first;
    
    first = new Node(nullptr, second, object);
    /*first->object = object;
    first->previous = nullptr;
    first->next = second;
    */
    if (second != nullptr)
        second->previous = first;
    if (last == nullptr)
        last = first;
    ++size;
}

template <typename Type> 
void linked_list<Type>::delete_last()
{
	// throw exception?

	if (last == nullptr)
		return; 

	Node* temp = last;
	if (size == 1) {
		first = nullptr;
		last = nullptr;
        //delete temp->object;
		delete temp;
		--size;
		return;
	}
	last = temp->previous;
	last->next = nullptr;
    //delete temp->object;
	delete temp;
	--size;

}
template <typename Type>
void linked_list<Type>::delete_last(bool p)
{
    // throw exception?
    
    if (last == nullptr)
        return;

    Node* temp = last;
    if (size == 1) {
        first = nullptr;
        last = nullptr;
        if (p)
            delete temp->object;
        delete temp;
        --size;
        return;
    }
    last = temp->previous;
    last->next = nullptr;
    if (p)
        delete temp->object;
    delete temp;
    --size;

}


template <typename Type> 
void linked_list<Type>::delete_first()
{
	if (first == nullptr)
		return;
	Node* temp = first;
	if (size == 1) {
		first = nullptr;
		last = nullptr;
        //bool
        //delete temp->object;
		delete temp;
		--size;
		return;
	}
	first = temp->next;
	first->previous = nullptr;
    //bool
    //delete temp->object;
	delete temp;
	--size;

}
template <typename Type>
void linked_list<Type>::delete_first(bool p)
{
    if (first == nullptr)
        return;
    Node* temp = first;
    if (size == 1) {
        first = nullptr;
        last = nullptr;
        if(p)
            delete temp->object;
        delete temp;
        --size;
        return;
    }
    first = temp->next;
    first->previous = nullptr;
   
    if (p)
        delete temp->object;
    delete temp;
    --size;

}



template <typename Type>
const Type& linked_list<Type>::give_i(int i)
{
    if (i >= size)
        throw (std::out_of_range{ std::string("Size < i, give_i") });

    Node* m = first;
    for (size_t x = 0; x < i; x++)
    {
        m = m->next;
    }

    return m->object;
}



template <typename Type>
const Type& linked_list<Type>::give_iRev(int i)
{
    if (i >= size)
        throw (std::runtime_error{ std::string("Size < i, give_iRev") });
    Node* m = last;
    for (size_t x = 0; x < i; x++)
    {
        m = m->previous;
    }

    return m->object;

}



template <typename Type>
void linked_list<Type>::set(int i, const Type& object)
{
    if (i >= size)
        throw (std::out_of_range{ std::string("Size < i, give_i") });

    Node* m = first;

    for (size_t x = 0; x < i; x++)
    {
        m = m->next;
    }
    // bool
    //delete m->object;
    
    m->object = object;
}





template <typename Type>
const Type* linked_list<Type>::get(const Type& object, int (*compareT)(const Type&, const Type&))
{
    if (size == 0)
        return nullptr;

    Node* temp = first;
    int diff;
    for (int i = 0; i < size; i++) {
        diff = compareT(temp->object, object);
        if (!diff)
            return &temp->object;
        temp = temp->next;
    }
    return nullptr;
}




template <typename Type>
bool linked_list<Type>::remove_if(const Type& object, int (*compareT)(const Type&, const Type&))
{
    if (size == 0)
        return false;
    Node* temp = first;
    int diff;
    for (int i = 0; i < size; i++) {
        diff = compareT(temp->object, object);
        if (!diff) {
            if (temp == first) {
                // ? delete_first(true)
                delete_first();
                return true;
            }
            if (temp == last) {
                // // ? delete_last(true)
                delete_last();
                return true;
            }
            Node* temp2 = temp->previous;
            temp2->next = temp->next;
            delete temp;
            temp = temp2->next;
            temp->previous = temp2;
            // bool??
            // delete temp->object;

            --size;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <typename Type>
bool linked_list<Type>::remove_if(const Type& object, int (*compareT)(const Type&, const Type&), bool p)
{
    if (size == 0)
        return false;
    Node* temp = first;
    int diff;
    for (int i = 0; i < size; i++) {
        diff = compareT(temp->object, object);
        if (!diff) {
            if (temp == first) {
                delete_first(p);
                return true;
            }
            if (temp == last) {
                delete_last(p);
                return true;
            }
            Node* temp2 = temp->previous;
            temp2->next = temp->next;
            if (p)
                delete temp->object;
            delete temp;
            temp = temp2->next;
            temp->previous = temp2;


            --size;
            return true;
        }
        temp = temp->next;
    }
    return false;
}



template <typename Type>
bool linked_list<Type>::add_order(Type& object, int (*compareT)(const Type&, const Type&))
{
    if (size == 0) {
        add_start(object);
        return true;
    }
    Node* temp = first;
    int diff;
    for (int i = 0; i < size; i++) {
        diff = compareT(temp->object, object);
        if (diff <= 0) {
            if (temp == first) {

                add_start(object);
                return true;
            }
            Node* temp2 = new Node;
            temp2->object = object;
            temp2->next = temp;
            temp2->previous = temp->previous;
            temp->previous = temp2;
            temp = temp2->previous;
            temp->next = temp2;
            ++size;

            return true;
        }
        if (temp == last) {
            add_end(object);
            return true;
        }
        temp = temp->next;
    }

}



template <typename Type>
void linked_list<Type>::clear_list()
{
    while (size != 0)
    {
        delete_last();
    }
    return;
}

template <typename Type>
void linked_list<Type>::clear_list(bool p)
{
    while (size != 0)
    {
        delete_last(p);
    }
    return;
}

//#include "linked_list.tpp"
#endif // LINKED_LIST

struct test
{
    test(int f1,char f2);

    int field1;
    char field2;
};

template <typename T>
int compareT(T obj1, T obj2);

template <typename T>
std::stringstream& print_to_ss(std::stringstream& ss, const T& t);

std::ostream& operator<<(std::ostream& is, test* t);


int main()
{ 
    
    const int MAX_ORDER = 6; // maksymalny rzad wielkosci rozmiaru dodawanych danych 
    linked_list<test*>* ll = new linked_list<test*>();
    
    for (int i = 1; i <= MAX_ORDER; i++)
    {
        const int n = pow(10, i);
        std::cout <<"*******"<< i <<"******* " << '\n';
        clock_t t1 = clock();
        // dodawanie do listy 
        for (int x = 0; x < n; x++) 
        {     
            test* so = new test(std::rand()%100, 'a'+ std::rand()%26);
            ll->add_start(so);
        }
        clock_t t2 = clock();
        std::cout<<"Dodawanie do listy" << '\n';
        std::cout << ll->to_string(2, print_to_ss)
            << "Pomiary czasowe \n" 
            << "\tCalkowity czas: "<< ((double)t2-t1) / CLOCKS_PER_SEC << "[s] " << '\n'
            << "\tSredni czas: "<< ((((double)t2-t1)/n) / CLOCKS_PER_SEC)*1000000000 << "[ns] " << '\n';
        
        // wyszukiwanie i usuwanie z listy 
        const int m = pow(10, 4); // liczba prob wyszukania 
        t1 = clock();
        for (int i = 0; i < m; i++) {
            test* so = new test(std::rand() % 1000, 'a' + std::rand() % 26);
            ll->remove_if(so, compareT,true);
            delete so;
        }
        t2 = clock();

        std::cout << "\nWyszukiwanie i usuwanie z listy \n";
        std::cout << ll->to_string(2, print_to_ss)
            << "Pomiary czasowe \n"
            << "\tCalkowity czas: " << (((double)t2 - t1)) / CLOCKS_PER_SEC << "[s] " <<'\n'
            << "\tSredni czas: " 
            << (((((double)t2 - t1)) / n) / CLOCKS_PER_SEC) *1000000000
            << "[ns] " << '\n';
        std::cout << '\n';
        ll->clear_list(true);
       
    }
    delete ll;
    return 0;
}

test::test(int f1, char f2)
    :field1(f1), field2(f2)
{}

template <typename T>
std::stringstream& print_to_ss(std::stringstream& ss, const T& t)
{
    ss << t->field1 << " " << t->field2 << ", ";
    return ss;
}

template <typename T>
int compareT(T obj1, T obj2)
{/*
    if (!(obj1->field1 - obj2->field1))
        return obj1->field1 - obj2->field1; // inny rodzaj porownania
    if(obj2->field2 - obj1->field2)
        return obj2->field2 - obj1->field2;
   */ 
    
    int diff = obj1->field1 - obj2->field1;
    if (diff != 0)
        return diff;
    return  obj2->field2 - obj1->field2;
}

std::ostream& operator<<(std::ostream& is, test* t)
{
    is << t->field1 << " " << t->field2 << '\n';
    return is;
}

