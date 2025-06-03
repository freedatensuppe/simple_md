#ifndef LINKEDCELLLIST_HPP
#define LINKEDCELLLIST_HPP

#include <list>

#include "box.hpp"

using CellList = std::vector<std::vector<std::vector<std::vector<int>>>>;
using AtomPair = std::pair<int, int>;

CellList createLinkedCellList(Box& box, double cutoff);
void     printLinkedCellList(CellList& cellList, Box& box);

std::vector<std::tuple<int, int, int>> getNeighboringCells(
    int ix,
    int iy,
    int iz,
    int nCellsX,
    int nCellsY,
    int nCellsZ
);

std::list<std::tuple<int, int, int>> getCells(
    int nCellsX,
    int nCellsY,
    int nCellsZ
);
std::vector<AtomPair> createNeighborAtomPairs(const CellList& cellList);

#endif
