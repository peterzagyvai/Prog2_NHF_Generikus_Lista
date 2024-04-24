#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <cstring>
#include <string>

#include "memtrace.h"

namespace ZaPe
{
    namespace Compare 
    {
        template<typename T>
        struct DefaultBigger
        {
            bool operator()(const T& t1, const T& t2);
        };

        template<>
        struct DefaultBigger<const char*>
        {
            bool operator()(const char* c1, const char* c2);
        };

        template<>
        struct DefaultBigger<char*>
        {
            bool operator()(char* c1, char* c2);
        };

        template<typename T>
        struct DefaultEqual
        {
            bool operator()(const T& t1, const T& t2);
        };



    }

    /// @brief Generikus lista, adatok rendezett tárolására
    /// @attention CSAK OLYAN ADATOKAT KÉPES TÁROLNI, AMIKRE MEGVANNAK VALÓSÍTVA A KÖVETKEZŐ OPERÁTOROK: 
    /// @attention operator==(const T&)
    /// @attention operator>(const T&)
    /// @attention operator=(const T&)
    /// @attention ezalól kivétel a char* típusú stringek
    template<typename T>
    class List
    {
    ///NOTE: Pre-defined subclass:
    private:
        struct ListElement
        {
            ListElement(const T& nData) : data(nData)
            {
                prev = NULL;
                next = NULL;
            }
            
            T data;
            ListElement* next;
            ListElement* prev;
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
        List() : first(NULL), last(NULL), length(0) {}

        /// @brief Másoló konstruktor, lemásolja a paraméterként kapott listát
        List(const List& list);

        /// @brief Létrehoz egy listát a paraméerben megadott tömb és méret alapján
        List(T* dataArray, size_t sizeOfArray);

        /// @brief Felszabadítja a lista elemeit
        ~List();


        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        T& at(size_t idx);

        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        const T& at(size_t idx) const;


        /// @brief A sor végére fűzi a paraméterként kapott adatot
        void push_back(const T& data);
        
        /// @brief Adds a new item to the start of the list;
        void push_front(const T& data);

        /// @brief A tömb egy adott index helyére illeszt be egy ój elemet
        /// @param idx 0 <= idx, get_length() > idx 
        /// @throw std::out_of_range kivételt dob, ha idx a tömb tartományán kívülre esik
        void push_at(const T& newItem, size_t idx);

        void delete_at(size_t idx);

        /// @brief Töröl minden elemet a listából
        void clear();


        /// @brief Törli a duplikációkat a tömbből
        /// @param cmp: fv, ami cmp(cosnt T& t1, const T& t2) paraméterkre egy bool ad vissza, az alapján hogy t1 és t2 mikor egyenlő
        /// @tparam fv., ami bool paraméterrel tér vissza
        template<typename Cmp = Compare::DefaultEqual<T> >
        void delete_duplicates(Cmp cmp = Compare::DefaultEqual<T>());

        /// @brief Rendezi a tömb elemeit egy cmp funktoron keresztül
        /// @param cmp: fv, ami cmp(cosnt T& t1, const T& t2) paraméterkre egy bool ad vissza, az alapján hogy t1 és t2 milyen viszonyban van egymással
        /// @tparam fv., ami bool paraméterrel tér vissza
        template<typename Cmp = Compare::DefaultBigger<T> >
        void sort(Cmp cmp = Compare::DefaultBigger<T>());

        /// @brief Visszaadja a listában tárolt elemek számát;
        inline size_t get_length() const { return length; }


        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        inline T& operator[](size_t idx) {return at(idx); } 

        /// @brief Visszaadja az "idx" helyen szereplő tárolt adatot
        /// @throws std:out_of_range kivételt dob, ha "idx" kissebb mint 0, vagy nagyobb/egyenlő mint a listában tárolt elemek száma
        inline const T& operator[](size_t idx) const {return at(idx); } 

    private:
        ListElement* first;
        ListElement* last;

        size_t length;

        static void swap(T& t1, T& t2);
    };

    //Definitions:

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
        if(idx < 0 || idx > length)
            throw std::out_of_range("index can not be less than 0 or greater than the current length");


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

    template<typename T>
    void List<T>::swap(T& t1, T& t2)
    {
        T tmp = t1;
        t1 = t2;
        t2 = tmp;
    }

    template<typename T>
    template<typename Cmp>
    void List<T>::delete_duplicates(Cmp cmp)
    {
        if (length <= 1) return; // Nem  lehet benne duplikáció

        ListElement* outer_iter = first;
        size_t outIndex = 0;

        while (outer_iter != NULL)
        {
            size_t deleteIdex = outIndex + 1;
            ListElement* inner_iter = outer_iter->next;

            while (inner_iter != NULL)
            {
                ListElement* tmp = inner_iter;
                inner_iter = inner_iter->next;

                if (cmp(tmp->data, outer_iter->data))
                {
                    delete_at(deleteIdex);
                }

                deleteIdex++;
            }

            outIndex++;
            outer_iter = outer_iter->next;
        }
    }

    template<typename T>
    template<typename Cmp>
    void List<T>::sort(Cmp cmp)
    {
        for (size_t i = 0; i < length-1; i++)
        {
            bool swapped = false;
            for (size_t j = 0; j < length - i -1; j++)
            {
                if(cmp(at(j), at(j+1)))
                {
                    swap(at(j), at(j+1));
                    swapped = true;
                }                
            }

            if (!swapped) break;
        }
    }


    template<typename T>
    void List<T>::delete_at(size_t idx)
    {
        if (idx < 0 || idx >= length) throw std::out_of_range("DELETE_AT, index out of range");

        ListElement* iter = first;

        for (size_t i = 0; i < idx; i++)
        {
            if (iter == NULL) throw std::out_of_range("DELETE_AT, trying to iter a NULL");

            iter = iter->next;
        }

        if (iter == NULL) throw std::out_of_range("DELETE_AT, trying to delete a NULL Element");

        if (iter->prev != NULL) iter->prev->next = iter->next;
        else first = iter->next;

        if (iter->next != NULL) iter->next->prev = iter->prev;
        else last = iter->prev;

        delete iter;

        length--;

        if (length == 0)
        {
            first = last = NULL;
        }
    }

    /// ACCESSORS: ========================================================================

    template<typename T>
    T& List<T>::at(size_t index)
    {
        if(first == NULL || length == 0)
            throw std::out_of_range("list has no members yet");
        if(index < 0 || index >= length)
            throw std::out_of_range("index can not be less than 0 or greater or equal to the current length");

        ListElement* iter = first;
        for (size_t i = 0; i < index; i++)
        {
            iter = iter->next;
        }

        return iter->data;
    }

    template<typename T>
    const T& List<T>::at(size_t index) const
    {
        if(first == NULL || length == 0) throw std::out_of_range("list has no members yet");
        if(index < 0 || index >= length) throw std::out_of_range("index can not be less than 0 or greater or equal to the current length");

        ListElement* iter = first;
        for (int i = 0; i < index; i++)
        {
            iter = iter->next;
        }

        return iter->data;
    }
    
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

    /// COMPARE:

    template<typename T>
    bool Compare::DefaultBigger<T>::operator()(const T& t1, const T& t2)
    {
        return t1 > t2;
    }

    inline bool Compare::DefaultBigger<const char*>::operator()(const char* c1, const char* c2)
    {
        return strcmp(c1, c2) > 0;
    }

    template<typename T>
    bool Compare::DefaultEqual<T>::operator()(const T& t1, const T& t2)
    {
        return t1 == t2;
    }

    inline bool Compare::DefaultBigger<char*>::operator()(char* c1, char* c2)
    {
        return strcmp(c1, c2) > 0;
    }
    

}

#endif