#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

#include "memtrace.h"


namespace ZaPe
{
    /// @brief Generikus lista, adatok rendezett tárolására
    /// @attention CSAK OLYAN ADATOKAT KÉPES TÁROLNI, AMIKRE MEGVANNAK VALÓSÍTVA A KÖVETKEZŐ OPERÁTOROK: 
    /// @attention operator==()
    /// @attention operator<()
    /// @attention ezalól kivétel a char* típusú stringek
    template<typename T>
    class List
    {
    ///NOTE: Pre-defined subclass:
    private:
        struct ListElement
        {
            T data;
            ListElement* next;
            ListElement* prev;

            ListElement(T nData) : data(nData), prev(NULL), next(NULL) {}
        };


    public:
        ///NOTE: Iterator:
        class Iterator;
        Iterator begin() const { return Iterator(*this); }
        Iterator end() const { return Iterator(); }

        class Iterator 
        {
        public: 
            /// @brief Beállítja az iterátor listaelemét NULL-ra
            Iterator();

            /// @brief Beállítja az iterátor listaelemét a paraméterként kapott lista első elemének értékére
            /// @param l 
            Iterator(const List& l);
            
            /// @brief Pre-increment: Beállítja az iterátor listaelemét a soron következő listaelemre, majd visszatér magával
            /// @return Az increment utáni önmagával tér vissza
            /// @throws std::out_of_range kivételt dob, ha az iterátor már NULL elemre mutat
            Iterator& operator++();

            /// @brief Post-increment: Beállítja az iterator listaelemét a soron következő listaelemre, majd visszatér az increment előtti értékkel
            /// @return Az increment előtti iterátor másolatával tér vissza
            /// @throws std::out_of_range kivételt dob, ha az iterátor már NULL elemre mutat
            Iterator operator++(int);


            /// @brief Pre-decrement: Beállítja az iterator listaelemét a sorban előtte levő listaelemre, majd visszatér magával
            /// @return A decrement utáni iterátor önmagával tér vissza
            /// @throws std::out_of_range kivételt dob, ha az iterátor már NULL elemre mutat
            Iterator& operator--();

            /// @brief Post-decrement: Beállítja az iterator listaelemét a sorban előtte levő listaelemre, majd visszatér az decrement előtti értékkel
            /// @return A decrement előtti iterátor másolatával tér vissza
            /// @throws std::out_of_range kivételt dob, ha az iterátor már NULL elemre mutat
            Iterator operator--(int);


            /// @brief Összehasonlitja az iterátorok listaelemei pointereit
            /// @param i Az iterátor aminek az értékét össze szeretnénk hasonlítani
            /// @return true-val tér vissza ha az iterátorok nem egyeznek meg
            bool operator!=(const Iterator& i) const;

            /// @brief Visszaadja az iterátor álatl tárolt adat értékét (NEM POINTER)
            /// @throws std::out_of_range kivételt dob, ha az iterátor NULL elemre mutat
            T& operator*();

            /// @brief Elérést nyújt a tárolt adat publikus funkcióihoz és tárolt adataihoz
            /// @return A tárolt listaelem pointere
            /// @throws std::out_of_range kivételt dob, ha az iterátor NULL elemre mutat
            T* operator->();
        private:
            ListElement* current;            
        };

    ///NOTE: Public interface of the list:
    public:

        /// @brief Default konstruktor, létrehoz egy üres listát
        List();

        /// @brief Másoló konstruktor, lemásolja a paraméterként kapott listát
        List(const List& list);

        /// @brief Felszabadítja a lista elemeit
        ~List();


        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        T& at(int idx);

        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        T& at(int idx) const;


        /// @brief A sor végére fűzi a paraméterként kapott adatot
        void push_back(const T& data);
        
        /// @brief Adds a new item to the start of the list;
        void push_front(const T& data);

        /// @brief A tömb egy adott index helyére illeszt be egy ój elemet
        /// @param idx 0 <= idx, get_length() > idx 
        /// @throw std::out_of_range kivételt dob, ha idx a tömb tartományán kívülre esik
        void push_at(const T& newItem, size_t idx);


        /// @brief Töröl minden elemet a listából
        void clear();


        /// @brief Törli a duplikációkat a tömbből
        /// @param cmp: fv, ami cmp(cosnt T& t1, const T& t2) paraméterkre egy bool ad vissza, az alapján hogy t1 és t2 mikor egyenlő
        /// @tparam fv., ami bool paraméterrel tér vissza
        template<typename C>
        void delete_duplicates(C cmp);

        /// @brief Törli a duplikációkat a tömbből
        /// @attention Csak azokra az osztályokra hívhatók, amikre értelmezve van a következő operátor overload:
        /// @attention operator==(const T&, const T&)
        void delete_duplicates();

        /// @brief Rendezi a tömb elemeit egy cmp funktoron keresztül
        /// @param cmp: fv, ami cmp(cosnt T& t1, const T& t2) paraméterkre egy bool ad vissza, az alapján hogy t1 és t2 milyen viszonyban van egymással
        /// @tparam fv., ami bool paraméterrel tér vissza
        template<typename C>
        void sort(C cmp);

        /// @brief Rendezi a tömb elemeit növekvő sorrendbe
        /// @attention Csak azokra az osztályokra hívhatók, amikre értelmezve van a következő operátor overload:
        /// @attention operator<(const T&, const T&)
        void sort();

        /// @brief Visszaadja a listában tárolt elemek számát;
        inline int get_length() const { return length; }


        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        inline T& operator[](int idx) {return at(idx); } 

        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        inline T& operator[](int idx) const {return at(idx); } 

    private:
        ListElement* first;
        ListElement* last;

        int length;
        int iterAtIdx;
    };

    //Definitions:
    /// CONSTRUCTORS: =====================================================================

    template<typename T>
    List<T>::List()
    : first(NULL), last(NULL), length(0) {}

    template<typename T>
    List<T>::~List() { clear(); }

    /// PUSH: ============================================================================= 

    template<typename T>
    void List<T>::push_back(const T& newItem)
    {
        ListElement* newElem = new ListElement(newItem);

        //if first item
        if (first == NULL)
        {
            first = newElem;
            last = first;
        }
        //if not first item
        else
        {
            last->next = newElem;
            newElem->prev = last;

            last = newElem;
        }

        length++;
    }

    template<typename T>
    void List<T>::push_front(const T& newItem)
    {

        if (first == NULL)
        {
            push_back(newItem);
            return;
        }

        ListElement* newElem = new ListElement(newItem);
        newElem->next = first;
        first->prev = newElem;

        first = newElem;
        length++;
    }

    template<typename T>
    void List<T>::push_at(const T& newItem , size_t idx)
    {
        if(idx < 0 || idx > length) throw std::out_of_range("index can not be less than 0 or greater than the current length");


        if(first == NULL || idx == length)
        {
            push_back(newItem);
            return;
        }

        if(idx == 0)
        {
            push_front(newItem);
            return;
        }

        ListElement* newElem = new ListElement(newItem);
        ListElement* prevNewElemIter = first;
        for (size_t i = 0; i < (idx - 1); i++)
        {
            prevNewElemIter = prevNewElemIter->next;
        }
        
        //Új elem beállítása
        newElem->prev = prevNewElemIter;
        newElem->next = prevNewElemIter->next;

        //Szomszédok beállítása:
        prevNewElemIter->next->prev = newElem;
        prevNewElemIter->next = newElem;

        length++;
    }

    /// CLEAR: ============================================================================

    template<typename T>
    void List<T>::clear()
    {
        ListElement* iter = first;

        while (iter != NULL)
        {
            ListElement* tmp = iter;

            iter = iter->next;
            delete tmp;
        }

        first = NULL;
        last = NULL;
        length = 0;
    }
    /// SORT: =============================================================================

    //TODO:

    template<typename T>
    template<typename C>
    void List<T>::delete_duplicates(C cmp)
    {

    }

    template<typename T>
    void List<T>::delete_duplicates()
    {

    }


    template<typename T>
    template<typename C>
    void List<T>::sort(C cmp)
    {
        
    }

    template<typename T>
    void List<T>::sort()
    {

    }

    /// ACCESSORS: ========================================================================

    template<typename T>
    T& List<T>::at(int index)
    {
        if(index < 0 || index >= length) throw std::out_of_range("index can not be less than 0 or greater or equal to the current length");

        ListElement* iter = first;
        for (int i = 0; i < index; i++)
        {
            iter = iter->next;
        }

        return iter->data;
    }

    template<typename T>
    T& List<T>::at(int index) const
    {
        if(index < 0 || index >= length) throw std::out_of_range("index can not be less than 0 or greater or equal to the current length");

        ListElement* iter = first;
        for (int i = 0; i < index; i++)
        {
            iter = iter->next;
        }

        return iter->data;
    }
    
    ///FIXME: Iterator drops last item in list

    template<typename T>
    List<T>::Iterator::Iterator() : current(NULL) {}
    
    template<typename T>
    List<T>::Iterator::Iterator(const List& l) : current(l.first) {}

    template<typename T>
    typename List<T>::Iterator& List<T>::Iterator::operator++() 
    {
        if(current == NULL) throw std::out_of_range("Iter run out of range");

        current = current->next;
        return *this;
    }
    
    template<typename T>
    typename List<T>::Iterator List<T>::Iterator::operator++(int) 
    {
        Iterator tmp = *this;
        operator++();
        return tmp;
    }
    
    template<typename T>
    typename List<T>::Iterator& List<T>::Iterator::operator--() 
    {
        if(current == NULL) throw std::out_of_range("Iter run out of range");

        current = current->prev;
        return *this;
    }
    
    template<typename T>
    typename List<T>::Iterator List<T>::Iterator::operator--(int) 
    {
        Iterator tmp = *this;
        operator--();
        return tmp;
    } 

    template<typename T>
    bool List<T>::Iterator::operator!=(const Iterator& i) const 
    {
        return (current != i.current);
    }
    
    template<typename T>
    T& List<T>::Iterator::operator*() 
    {
        if (current != NULL) return current->data;

        throw std::out_of_range("Iter pointing to NULL");
    }
    
    template<typename T>
    T* List<T>::Iterator::operator->() 
    {
        if (current != NULL) return &(current->data);

        throw std::out_of_range("Iter pointing to NULL");
    }
}

#endif