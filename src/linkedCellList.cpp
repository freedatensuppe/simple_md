#include "linkedCellList.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <tuple>

#include "box.hpp"

CellList createLinkedCellList(Box& box)
{
    double cutoff   = 8.5;
    int    numCells = std::floor(box.getDimensions().minElement() / cutoff);
    double cellSize = box.getDimensions().minElement() / numCells;
    std::cout << "numcells:" << numCells;
    std::cout << std::endl;
    std::cout << "cellsize:" << cellSize;
    std::cout << std::endl;

    int nCellsX = static_cast<int>(box.getDimensions().x / cellSize);
    int nCellsY = static_cast<int>(box.getDimensions().y / cellSize);
    int nCellsZ = static_cast<int>(box.getDimensions().z / cellSize);
    std::cout << "ncellsXYZ:" << nCellsX << " " << nCellsY << "" << nCellsZ;
    std::cout << std::endl;

    CellList cellList(
        nCellsX,
        std::vector<std::vector<std::list<size_t>>>(
            nCellsY,
            std::vector<std::list<size_t>>(nCellsZ)
        )
    );

    for (size_t i = 0; i < box.getAtoms().size(); ++i)
    {
        Vector3D pos = box.getAtom(i).getPosition();

        int ix =
            static_cast<int>((pos.x + box.getDimensions().x / 2) / cellSize);
        int iy =
            static_cast<int>((pos.y + box.getDimensions().y / 2) / cellSize);
        int iz =
            static_cast<int>((pos.z + box.getDimensions().z / 2) / cellSize);

        // Clamp indices to valid range
        ix = std::min(std::max(ix, 0), nCellsX - 1);
        iy = std::min(std::max(iy, 0), nCellsY - 1);
        iz = std::min(std::max(iz, 0), nCellsZ - 1);

        cellList[ix][iy][iz].push_back(i);
    }

    return cellList;
}

void printLinkedCellList(CellList& cellList, Box& box)
{
    int nCellsX = cellList.size();
    int nCellsY = cellList[0].size();
    int nCellsZ = cellList[0][0].size();

    for (int ix = 0; ix < nCellsX; ++ix)
    {
        for (int iy = 0; iy < nCellsY; ++iy)
        {
            for (int iz = 0; iz < nCellsZ; ++iz)
            {
                const auto& atomIndices = cellList[ix][iy][iz];
                if (!atomIndices.empty())
                {
                    std::cout << "Cell (" << ix << ", " << iy << ", " << iz
                              << "): ";
                    for (size_t idx : atomIndices)
                    {
                        std::cout << idx << " ";
                    }
                    std::cout << std::endl;
                }
            }
        }
    }
}

std::vector<std::tuple<int, int, int>> getNeighboringCells(
    int ix,
    int iy,
    int iz,
    int nCellsX,
    int nCellsY,
    int nCellsZ
)
{
    std::vector<std::tuple<int, int, int>> neighbors;

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            for (int dz = -1; dz <= 1; ++dz)
            {
                int nix = (ix + dx + nCellsX) % nCellsX;
                int niy = (iy + dy + nCellsY) % nCellsY;
                int niz = (iz + dz + nCellsZ) % nCellsZ;
                neighbors.emplace_back(nix, niy, niz);
            }
        }
    }
    return neighbors;
}
