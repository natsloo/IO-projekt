#include "pch.h"
#include "Data.h"

TEST(data, data_na_str)
{
	Data d(12, 5, 2025);
	EXPECT_EQ(Data::data_na_string(d), "12.05.2025");
}