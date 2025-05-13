#include "pch.h"
#include "Data.h"

TEST(data, data_na_str)
{
	Data d(12, 5, 2025);
	EXPECT_EQ(Data::data_na_string(d), "12.05.2025");
    EXPECT_EQ(d.string(), "12.05.2025");
}

TEST(data, operatory_porownania)
{
    Data d1(12, 5, 2025);
    Data d2(15, 6, 2025);
    EXPECT_TRUE(d1 < d2);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_FALSE(d2 == d1 + 3);
    EXPECT_TRUE(d2 == d1 + 34);
    d1 += 5;
    EXPECT_TRUE(d1 >= d1);
    EXPECT_TRUE(Data::data_na_string(d1) == "17.05.2025");
}

TEST(data, operatory_przypisania)
{
    Data d1(12, 5, 2025);
    Data d2(15, 6, 2025);
    d1++;
    EXPECT_EQ(d1.string(), "13.05.2025");
    d2--;
    EXPECT_EQ(d2.string(), "14.06.2025");
    d1-=1;
    EXPECT_EQ(d1.string(), "12.05.2025");
    d2+=1;
    EXPECT_EQ(d2.string(), "15.06.2025");
}

TEST(data, poprawnosc_dat) {
    Data d1(32, 5, 8);
    EXPECT_EQ(d1.string(), "00.00.0");
    Data d2(31, 5, 2028);
    EXPECT_EQ(d2.string(), "31.05.2028");
    Data d3(10, -1, 2025);
    EXPECT_EQ(d3.string(), "00.00.0");
    Data d4(2, 3, -4);
    EXPECT_EQ(d4.string(), "00.00.0");
}