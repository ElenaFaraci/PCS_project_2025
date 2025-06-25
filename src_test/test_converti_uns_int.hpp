#pragma once

#include <iostream>
#include <vector>
#include "Eigen/Eigen"

#include <gtest/gtest.h>
#include "Utils.hpp"
using namespace std;

namespace PolygonalLibrary {
	
	TEST(TestFunzionalità, test_converti_uns_int)
{
    
	
	unsigned int valore_funz;
	
	EXPECT_TRUE(converti_uns_int("2", valore_funz));
    EXPECT_EQ(valore_funz, 2);
	
	EXPECT_FALSE(converti_uns_int("-2", valore_funz));
    
	EXPECT_FALSE(converti_uns_int("a", valore_funz));
	
	char lettera = 'b';
	char* punt_char = &lettera;
	EXPECT_FALSE(converti_uns_int(punt_char, valore_funz));
	
		
}

}