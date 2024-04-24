#include "memtrace.h"


//#define OPERATORS_DEFINED
#define RENDEZ
#define DUPLIK

#ifndef TEST_H
#define TEST_H


namespace ZaPe
{
    class TestClass
    {
    public:
        TestClass(int number = 0, bool boolean = true)
        : number(number), boolean(boolean) {}

        TestClass(const TestClass& tc) : number(tc.get_number()), boolean(tc.get_boolean()) {}
        
        virtual ~TestClass() {}
        
        inline TestClass& operator=(const TestClass& tc)
        {
            if(this == &tc) return *this;

            boolean = tc.get_boolean();
            number = tc.get_number();

            return *this;
        }


#ifdef OPERATORS_DEFINED
        bool operator==(const TestClass& tc) const;
        bool operator>(const TestClass& tc) const;
#endif

        
        inline int get_number() const { return number; } 
        inline bool get_boolean() const { return boolean; }

        inline void set_number(int number) { this->number = number; }
        inline void set_boolean(bool boolean) { this->boolean = boolean; }

        void write(const char* filePath) const;
        static size_t read(const char* filePath, TestClass* tcArray);

    private:
        int number;
        bool boolean;
    };

    namespace Compare
    {
        class TestSortFunctor
        {
        public:
            bool operator()(const TestClass& tc1, const TestClass& tc2);
        };

        class TestEqualFunctor
        {
        public:
            bool operator()(const TestClass& tc1, const TestClass& tc2);
        };
    }

    void Tests();
}

#endif // !TEST_H

