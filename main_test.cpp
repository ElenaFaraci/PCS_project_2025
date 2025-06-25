#include <gtest/gtest.h>

#include "test_baricentro.hpp"
#include "test_esiste_gia_1D.hpp"
#include "test_Esiste_gia.hpp"
#include "test_trova_facce_per_vertice.hpp"
#include "test_Nuovo_Vertice.hpp"
#include "test_Triangolazione.hpp"
#include "test_Triangolazione_2.hpp"
#include "test_tri_vertici_facce.hpp"
#include "test_tri_lati_facce.hpp"
#include "test_giro_attorno_vertice.hpp"
#include "test_CostruisciDualeMesh.hpp"

#include "test_trova_cammino.hpp"
#include "test_proiezione_sfera.hpp"
#include "test_costruisci_grafo.hpp"
#include "test_dijkstra.hpp"
#include "test_salvataggio_Cell0D.hpp"
#include "test_salvataggio_Cell1D.hpp"
#include "test_salvataggio_Cell2D.hpp"
#include "test_salvataggio_Cell3D.hpp"
#include "test_controllo_lati_vertici.hpp"
#include "test_converti_uns_int.hpp"



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