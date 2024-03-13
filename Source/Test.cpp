#include "Tests.h"

#include <iostream>

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

            TEST (Lista, Duplikacio){
                EXPECT_NO_THROW(numbers.delete_duplicates());

                EXPECT_EQ( 4, numbers.get_length());

                EXPECT_EQ( 9, numbers[0]);
                EXPECT_EQ(11, numbers[1]);
                EXPECT_EQ(12, numbers[2]);
                EXPECT_EQ(15, numbers[3]);

                EXPECT_THROW(numbers[4], std::out_of_range);
            } END

            /// NOTE: <int> test vége 
        }

        TEST (Lista, Complex){


        } END
    }
} 