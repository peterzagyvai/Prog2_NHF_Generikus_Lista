#include "memtrace.h"


#define OPERATORS_DEFINED
#define RENDEZ


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

    private:
        int number;
        bool boolean;
    };

#ifndef OPERATORS_DEFINED
        bool TestClassEq(const TestClass& tc1, const TestClass& tc2); 
        bool TestClassBigger(const TestClass& tc1, const TestClass& tc2);
#endif

    void Tests();
}