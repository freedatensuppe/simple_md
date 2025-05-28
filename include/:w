#ifndef LINKEDCELLLIST_HPP
#define LINKEDCELLLIST_HPP

#include <list>

#include "box.hpp"

using CellList = std::vector<std::vector<std::vector<std::list<size_t>>>>;

CellList createLinkedCellList(Box& box);
void     printLinkedCellList(CellList& cellList, Box& box);

std::vector<std::tuple<int, int, int>> getNeighboringCells(
    int ix,
    int iy,
    int iz,
    int nCellsX,
    int nCellsY,
    int nCellsZ
);

#endif
