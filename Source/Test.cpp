#include "Tests.h"

#include <iostream>
#include <cstring>

#include "List.hpp"

#include "gtest_lite.h"
#include "memtrace.h"

namespace ZaPe
{

    void Tests()
    {
        GTINIT(std::cin);

        TEST(Lista, Inic){
            List<int> numbers;
            EXPECT_EQ(0, numbers.get_length());
            EXPECT_THROW(numbers.at(0), std::out_of_range);
        } END
        
        {
            List<int> numbers;
            TEST(Lista, Feltolt_Elore){
                numbers.push_front(1);
                numbers.push_front(2);
                numbers.push_front(3);

                EXPECT_EQ(3, numbers[0]);
                EXPECT_EQ(2, numbers[1]);
                EXPECT_EQ(1, numbers[2]);

                EXPECT_THROW(numbers[-1], std::out_of_range);
                EXPECT_THROW(numbers[3], std::out_of_range);
            } END

            TEST (Lista, Torol) {
                numbers.clear();
                EXPECT_EQ(0, numbers.get_length());
                EXPECT_THROW(numbers[0], std::out_of_range);
            } END

            TEST(Lista, Feltolt_Hatulra) {
                numbers.push_back(1);
                numbers.push_back(2);
                numbers.push_back(3);

                EXPECT_EQ(1, numbers[0]);
                EXPECT_EQ(2, numbers[1]);
                EXPECT_EQ(3, numbers[2]);

                EXPECT_THROW(numbers[-1], std::out_of_range);
                EXPECT_THROW(numbers[3], std::out_of_range);
            } END

            TEST (Lista, Iter) {
                List<int>::Iterator iter = numbers.begin();
                EXPECT_EQ(1,*(iter++));        
                EXPECT_EQ(2,*iter);        
                EXPECT_EQ(3,*(++iter));

                EXPECT_EQ(3, *iter--);
                EXPECT_EQ(2, *iter);
                EXPECT_EQ(1, *--iter);
            } END

            TEST (Lista, Iter_Exception){
                numbers.clear();
                numbers.push_back(10);
                List<int>::Iterator iter = numbers.begin();

                EXPECT_THROW(*++iter, std::out_of_range);
                EXPECT_THROW(iter++, std::out_of_range);

                iter = numbers.begin();
                EXPECT_THROW(*--iter, std::out_of_range);
                EXPECT_THROW(iter--, std::out_of_range);
            } END

            TEST (Lista, FeltoltesBele){
                numbers.clear();

                EXPECT_THROW(numbers.push_at(10, -1), std::out_of_range);
                EXPECT_THROW(numbers.push_at(10,  1), std::out_of_range);

                EXPECT_NO_THROW(numbers.push_at(10, 0));
                EXPECT_NO_THROW(numbers.push_at(12, 1));
                EXPECT_NO_THROW(numbers.push_at(11, 1));

                EXPECT_EQ(3, numbers.get_length());
                EXPECT_EQ(10, numbers[0]);
                EXPECT_EQ(11, numbers[1]);
                EXPECT_EQ(12, numbers[2]);
            } END

#ifdef RENDEZ
            TEST (Lista, Rendez){
                numbers.clear();

                EXPECT_NO_THROW(numbers.push_back(12));
                EXPECT_NO_THROW(numbers.push_back(11));
                EXPECT_NO_THROW(numbers.push_back(15));
                EXPECT_NO_THROW(numbers.push_back(12));
                EXPECT_NO_THROW(numbers.push_back( 9));

                EXPECT_NO_THROW(numbers.sort());

                EXPECT_EQ( 5, numbers.get_length());

                EXPECT_EQ( 9, numbers[0]);
                EXPECT_EQ(11, numbers[1]);
                EXPECT_EQ(12, numbers[2]);
                EXPECT_EQ(12, numbers[3]);
                EXPECT_EQ(15, numbers[4]);

            } END


            TEST(Lista, Torol) {
                List<int> szamok;
                szamok.push_back(1);

                EXPECT_NO_THROW(szamok.delete_at(0));
                EXPECT_THROW(szamok[0], std::out_of_range);
                EXPECT_EQ(0, szamok.get_length());

                EXPECT_NO_THROW(numbers.delete_at(0));
                EXPECT_EQ(11, numbers[0]);
            } END

            TEST (Lista, char_string_rendez) {
                List<const char*> strings;

                const char* c1 = "Hello Wolrd";
                const char* c2 = "Szia Uram";
                const char* c3 = "Hello Prog2";

                EXPECT_NO_THROW(strings.push_back(c1));
                EXPECT_NO_THROW(strings.push_back(c2));
                EXPECT_NO_THROW(strings.push_back(c3));

                EXPECT_NO_THROW(strings.sort());

                EXPECT_STREQ(c3, strings[0]);
                EXPECT_STREQ(c1, strings[1]);
                EXPECT_STREQ(c2, strings[2]);

            }END


#endif
#ifdef DUPLIK
            TEST (Lista, Duplikacio){
                List<int> szamok;

                szamok.push_back(1);
                szamok.push_back(2);
                szamok.push_back(2);
                szamok.push_back(1);
                szamok.push_back(3);

                EXPECT_NO_THROW(szamok.delete_duplicates());

                EXPECT_EQ(3, szamok.get_length());
                EXPECT_EQ(1, szamok[0]);
                EXPECT_EQ(2, szamok[1]);
                EXPECT_EQ(3, szamok[2]);
            } END
#endif
            /// NOTE: <int> test vége 
        }


        TEST (Lista, OnClass_Init){
            EXPECT_NO_THROW(List<TestClass> tcs);
            EXPECT_NO_THROW(List<TestClass>::Iterator iter);
        } END

        List<TestClass> tcs;
        TEST(Lista, OnClass_push_and_accesors){

            EXPECT_NO_THROW(tcs.push_back(TestClass(1, false)));
            EXPECT_NO_THROW(tcs.push_front(TestClass()));
            EXPECT_NO_THROW(tcs.push_at(TestClass(2), 1));

            EXPECT_EQ(0, tcs[0].get_number());
            EXPECT_EQ(true, tcs[0].get_boolean());

            EXPECT_EQ(2, tcs[1].get_number());
            EXPECT_EQ(true, tcs[1].get_boolean());
            
            EXPECT_EQ(1, tcs[2].get_number());
            EXPECT_EQ(false, tcs[2].get_boolean());
            
            EXPECT_NO_THROW(tcs[0].set_number(10));
            EXPECT_NO_THROW(tcs[0].set_boolean(false));

            EXPECT_EQ(10, tcs[0].get_number());
            EXPECT_EQ(false, tcs[0].get_boolean());
        } END

        List<TestClass>::Iterator tcIter;
        TEST (Lista, OnClass_Iter){
            EXPECT_NO_THROW(tcIter = tcs.begin());

            TestClass tc;
            EXPECT_NO_THROW(tc = *tcIter);
            EXPECT_EQ(10, tc.get_number());
            EXPECT_EQ(false, tc.get_boolean());

            EXPECT_THROW(*--tcIter, std::out_of_range);
            tcIter = tcs.begin();

            EXPECT_NO_THROW(tc = *tcIter++);
            EXPECT_EQ(10, tc.get_number());
            EXPECT_EQ(false, tc.get_boolean());

            EXPECT_EQ(2, tcIter->get_number());
            EXPECT_EQ(true, tcIter->get_boolean());

            EXPECT_NO_THROW(tcIter++);
            EXPECT_NO_THROW(tcIter++);
            EXPECT_THROW(tcIter++, std::out_of_range);
        }END



#ifdef RENDEZ

    #ifdef OPERATORS_DEFINED
        TEST (Lista, OnClass_Rendez_Operatorok) {
            EXPECT_NO_THROW(tcs.sort());
            EXPECT_EQ( 1, tcs[0].get_number());
            EXPECT_EQ( 2, tcs[1].get_number());
            EXPECT_EQ(10, tcs[2].get_number());
        } END
    #endif
    #ifndef OPERATORS_DEFINED
        TEST (Lista, OnClass_Renez_No_Operators) {
            List<TestClass> tcs2;
            tcs2.push_back(TestClass(3));
            tcs2.push_back(TestClass(1));
            tcs2.push_back(TestClass(2));

            EXPECT_NO_THROW(tcs2.sort(Compare::TestSortFunctor()));

            EXPECT_EQ(3, tcs2[0].get_number());
            EXPECT_EQ(2, tcs2[1].get_number());
            EXPECT_EQ(1, tcs2[2].get_number());
        } END
    #endif
#endif

        TEST(Lista, Clear){
            EXPECT_NO_THROW(tcs.clear());
            EXPECT_THROW(tcs[0], std::out_of_range);
            EXPECT_EQ(0, tcs.get_length());
        }END
    }
} 



void ZaPe::TestClass::write(const char* filePath) const
{
    size_t size = 0;
    TestClass* tcArray = NULL;
    bool fileExists = true;
    try
    {
        size = TestClass::read(filePath);
        tcArray = new TestClass[size];
        TestClass::read(filePath, tcArray);
    }
    catch (std::out_of_range e)
    {
        delete[] tcArray;
        if (strcmp(e.what(), "Unable to open file") != 0) // Létezik a fájl, de mégis hibát dob
        {
            std::cout << e.what() << std::endl;
        }
        else // Ha nem létezik a fájl
        {
            fileExists = false;
        }
    }

    if (fileExists)
    {
        if (std::remove(filePath) != 0);
    }

    size++;
    std::ofstream file(filePath);

    if (file.is_open())
    {
        file << size << "\n";
        for (size_t i = 0; i < size - 1; i++)
        {
            file << tcArray[i].get_number() << " " << (tcArray[i].get_boolean() ? "true" : "false") << "\n";
        }
        file << number << " " << (boolean ? "true" : "false") << "\n";
    }

    if (tcArray != NULL) delete[] tcArray;
}

size_t ZaPe::TestClass::read(const char* filePath, TestClass* tcArray)
{
    std::ifstream file(filePath);    
    size_t counter = 0;

    if (file.is_open())
    {
        file >> counter;

        if (counter < 1) 
        {
            file.close();
            throw std::out_of_range("File is not in the correct format or counter is smaller than 0");
        }

        if (tcArray == NULL)
        {
            file.close();
            return counter;
        }

        for (size_t i = 0; i < counter; i++)
        {
            int number;
            bool boolean;

            file >> number >> std::boolalpha >> boolean;

            tcArray[i].set_number(number);
            tcArray[i].set_boolean(boolean);
        }
    }
    else throw std::out_of_range("Unable to open file");


    return counter;
}


#ifdef OPERATORS_DEFINED
namespace ZaPe
{
    bool TestClass::operator>(const TestClass& t1) const
    {
        return number > t1.get_number();
    }

    bool TestClass::operator==(const TestClass& t1) const
    {
        return (t1.get_number() == number && t1.get_boolean() == boolean);
    }
}
#endif
#ifndef OPERATORS_DEFINED
namespace ZaPe
{
    bool Compare::TestSortFunctor::operator()(const TestClass& tc1, const TestClass& tc2)
    {
        return tc1.get_number() < tc2.get_number();
    }

    bool Compare::TestEqualFunctor::operator()(const TestClass& tc1, const TestClass& tc2)
    {
        return (tc1.get_number() == tc2.get_number() && tc1.get_boolean() == tc2.get_boolean());
    }
}
#endif