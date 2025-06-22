#include <gtest/gtest.h>

#include "test_baricentro.hpp"
#include "test_esiste_gia_1D.hpp"
#include "test_Esiste_gia.hpp"
#include "test_trova_facce_per_vertice.hpp"
#include "test_Nuovo_Vertice.hpp"
#include "test_tri_vertici_facce.hpp"
#include "test_tri_lati_facce.hpp"
#include "test_trova_cammino.hpp"
#include "test_proiezione_sfera.hpp"




/*TO DO: 
salvataggi celle 0D, 1D, 2D, 3D - enri
proiezione sfera unitaria - enri
trova cammino minimo - enri
valorizza poliedro - enri
contollo lati vertici
nuovo vertice - fede
dijkstra - enri
grafo pesato- enri
triangolazione - fede
costruisci duale - fede
tri_vertici_facce - fede

*/




int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}