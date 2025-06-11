#include <gtest/gtest.h>

#include "test_baricentro.hpp"
#include "test_esiste_gia_1D.hpp"
#include "test_Esiste_gia.hpp"
#include "test_trova_facce_per_vertice.hpp"
#include "test_tri_lati_facce.hpp"







int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}