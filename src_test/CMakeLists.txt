list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_baricentro.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_esiste_gia_1D.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_Esiste_gia.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_trova_facce_per_vertice.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_Nuovo_Vertice.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_Triangolazione.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_Triangolazione_2.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_tri_vertici_facce.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_tri_lati_facce.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_giro_attorno_vertice.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_CostruisciDualeMesh.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_proiezione_sfera.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_trova_cammino.hpp)
list(APPEND src_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_controllo_lati_vertici.hpp)






list(APPEND src_test_includes ${CMAKE_CURRENT_SOURCE_DIR})

set(src_test_headers ${src_test_headers} PARENT_SCOPE)
set(src_test_sources ${src_test_sources} PARENT_SCOPE)
set(src_test_includes ${src_test_includes} PARENT_SCOPE)
