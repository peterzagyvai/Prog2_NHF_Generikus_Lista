#include "Tests.h"

#include <iostream>

#include "List.hpp"

#include "gtest_lite.h"
#include "memtrace.h"


namespace ZaPe
{

    #ifdef TEST_CASES
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
        }
    }

    #endif // TEST_CASES
} 