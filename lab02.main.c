//ALGO2 IS1 LAB02
#include <iostream>
#include <sstream>
#include <time.h>
#include <math.h>
struct M {
    int field1;
    char field2;
    M(int f1 = 1, char f2 = 'a');

};

std::ostream& operator<<(std::ostream& is, M& t);

template <typename Type>
class table
{
private:
    typedef   std::stringstream& (*tprint_to_string)(std::stringstream& ss, const Type& t);
    Type* array; // wskaźnikami na dane
    long size;
    long max_size;
    int factor; // współczynnik rozszerzania    //bool dynamic_mode
    void assign_memory();
    void delete_memory();
public:

    table();
    ~table();
    void new_array();
    void add_end(Type& object);
    Type& operator[](int i);
    std::string to_string(int number, tprint_to_string print_to_string);
    void clear_table();
    int size_A(){return size;}
};

template <typename Type>
void clear_pointers(Type& table);

template <typename Type>
std::stringstream& print_to_ss(std::stringstream& ss, const Type& t);

int main()
{
    // stale
    const int MAX_ORDER = 7; // maksymalny rzad wielkosci rozmiaru dodawanych danych
    const int n = std::pow(10, 7);
    
    //tabela
    table<M*>* pTable = new table<M*>();
    // dodawnie do ablicy
    clock_t t1 = clock();
    double sum_max_czas{ 0 };
    int liczba_max_czas{ 0 };
    double max_time_per_element = 0.0; // najgorszy czas operacji dodawania
    for (int i = 0; i < n; i++) {
        M* pom = new M(std::rand() % 1000, 'a' + std::rand() % 26);
        clock_t t1_element = clock();
        pTable->add_end(pom);
        clock_t t2_element = clock();
        double time_per_element = t2_element - t1_element;
        if (time_per_element > max_time_per_element)
            // najgorszy czas i informacja o indeksie na ekranie
        {
            liczba_max_czas++;
            sum_max_czas += max_time_per_element;
            max_time_per_element = time_per_element;
            std::cout << "Najgorszy czas: " << max_time_per_element << '\n';

        }
    }
    clock_t t2 = clock();
    std::cout << "\nDodawanie do tabeli \n";
    std::cout << pTable->to_string(2, print_to_ss)
        << "Pomiary czasowe \n"
        << "\tCalkowity czas: " << (((double)t2 - t1)) / CLOCKS_PER_SEC << "[s] " << '\n'
        << "\tZamortyzowany czas: " << ((double)sum_max_czas / liczba_max_czas)
        << "[ns] " << '\n';
    std::cout << '\n';
    
    clear_pointers<table<M*>*>(pTable);
    delete pTable;
    

}

template <typename Type>
void table<Type>::add_end(Type& object)
{

    if (size == max_size) {
        size++;
        new_array(); // size ++ in methode
        array[size - 1] = object;     // [0:size-1]
    }
    else if (size < max_size) {
        size++;
        array[size - 1] = object;   // [0:size-1]
    }
}

template<typename Type>
void table<Type>::new_array()
{
    Type* temp_array = array;
    max_size *= factor;
    assign_memory();
    for (int i = 0; i < size; i++)
    {
        array[i] = temp_array[i]; // *(array+i)
    }
    delete[] temp_array;

}

template <typename Type>
std::string table<Type>::to_string(int number, tprint_to_string print_to_string) //std::stringstream&(*)(std::stringstream& ss,const Type& t))
{
    std::stringstream ss;
    ss << "Adres pamieci tabeli: " << this << '\n';
    ss << "Rozmiar: " << size << "\n"
        << "Dane: ";
    for (int i = 0; ((i < size) && (i < number)); i++) {
        print_to_string(ss, array[i]);
    }
    ss << '\n';
    return ss.str();

}

template <typename Type>
std::stringstream& print_to_ss(std::stringstream& ss, const Type& t)
{
    ss << t->field1 << " " << t->field2 << ", ";
    return ss;
}

template <typename Type>
void table<Type>::clear_table()
{
    delete_memory();
    size = 0;
    max_size = 1;
    assign_memory();
}

template<typename Type>
Type& table<Type>::operator[](int i)
{
    return array[i];
}

M::M(int f1, char f2)
    : field1(f1), field2(f2) {}


std::ostream& operator<<(std::ostream& os, M& t)
{
    os << t.field1 << " " << t.field2 << '\n';
    return os;
}

template <typename Type>
void clear_pointers<Type>(Type& table)
{
    for (int i = 0; i < table->size_A(); i++)
    {
        delete (*table)[i];
        
    }
    table->clear_table();
}

template <typename Type>
void table<Type>::assign_memory()
{
    array = new Type[max_size];
}

template<typename Type>
void table<Type>::delete_memory()
{
    delete[] array;
}

template <typename Type>
table<Type>::table()
    : size(0), max_size(1), factor(2)
{
    assign_memory();
}

template <typename Type>
table<Type>::~table()
{
    delete_memory();
}




