#include "linkedCellList.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

#include "box.hpp"

CellList createLinkedCellList(Box& box, double cutoff)
{
    int    numCells = std::floor(box.getDimensions().min() / cutoff);
    double cellSize = box.getDimensions().min() / numCells;

    int nCellsX = static_cast<int>(box.getDimensions().x / cellSize);
    int nCellsY = static_cast<int>(box.getDimensions().y / cellSize);
    int nCellsZ = static_cast<int>(box.getDimensions().z / cellSize);

    CellList cellList(
        nCellsX,
        std::vector<std::vector<std::vector<int>>>(
            nCellsY,
            std::vector<std::vector<int>>(nCellsZ)
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

        ix = std::min(std::max(ix, 0), nCellsX - 1);
        iy = std::min(std::max(iy, 0), nCellsY - 1);
        iz = std::min(std::max(iz, 0), nCellsZ - 1);

        cellList[ix][iy][iz].push_back(i);
    }

    return cellList;
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

// Returns a vector of unique atom index pairs (i, j) with i < j
std::vector<AtomPair> createNeighborAtomPairs(const CellList& cellList)
{
    int                   nCellsX = cellList.size();
    int                   nCellsY = cellList[0].size();
    int                   nCellsZ = cellList[0][0].size();
    std::vector<AtomPair> atomPairs;

    for (int ix = 0; ix < nCellsX; ++ix)
    {
        for (int iy = 0; iy < nCellsY; ++iy)
        {
            for (int iz = 0; iz < nCellsZ; ++iz)
            {
                const auto& atomsInCell = cellList[ix][iy][iz];

                // Pairs within the same cell
                for (size_t i = 0; i < atomsInCell.size(); ++i)
                {
                    for (size_t j = i + 1; j < atomsInCell.size(); ++j)
                    {
                        atomPairs.emplace_back(atomsInCell[i], atomsInCell[j]);
                    }
                }

                // Pairs with neighboring cells
                auto neighbors =
                    getNeighboringCells(ix, iy, iz, nCellsX, nCellsY, nCellsZ);
                for (const auto& neighborCell : neighbors)
                {
                    int nix, niy, niz;
                    std::tie(nix, niy, niz) = neighborCell;

                    // To avoid double counting, only consider neighbor cells
                    // that are "after" the current cell in lexicographical
                    // order
                    if ((nix > ix) || (nix == ix && niy > iy) ||
                        (nix == ix && niy == iy && niz > iz))
                    {
                        const auto& atomsInNeighbor = cellList[nix][niy][niz];
                        for (size_t i : atomsInCell)
                        {
                            for (size_t j : atomsInNeighbor)
                            {
                                atomPairs.emplace_back(i, j);
                            }
                        }
                    }
                }
            }
        }
    }
    return atomPairs;
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
