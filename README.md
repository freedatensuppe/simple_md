# Simple MD - Molecular Dynamics Simulation in C++

A molecular dynamics simulation code for the treatment of Lennard-Jones systems written in modern C++ for educational purposes.

## Features

### Core Simulation Capabilities

The simulation engine implements a complete **Lennard-Jones potential**, including cutoff and force shifting for computational efficiency. Time integration uses the stable and accurate **Velocity Verlet algorithm** with a two-step scheme that provides superior energy conservation. For performance optimization, the code employs a **linked cell list algorithm** that reduces neighbor searching complexity from O(N²) to O(N) for large systems. The simulation supports **periodic boundary conditions** with cubic simulation boxes and proper minimum image convention to eliminate finite-size effects.

Temperature control is achieved through a **Berendsen thermostat** enabling NVT ensemble simulations with smooth coupling to a thermal reservoir. The implementation of pressure control via a Berendsen manostat is planned.

### Input/Output

The simulation uses modern [**TOML configuration files**](https://github.com/marzer/tomlplusplus) , that provide human-readable and easily modifiable simulation parameters. Output includes **XYZ trajectory files** in standard format compatible with VMD, PyMOL, and other visualization tools for molecular graphics and analysis. Real-time **energy monitoring** tracks kinetic, potential, and total energy throughout the simulation with output to both console and data files.

The code supports **restart capabilities** allowing simulations to continue from previous runs using restart files containing atomic positions, velocities, and forces. Built-in **analysis tools** provide support for radial distribution function (RDF) calculations and other structural analysis methods directly from trajectory data.

## Building the Project

### Prerequisites
- CMake 3.18 or higher
- GCC with C++ support (GCC 11+ recommended)

### Compilation
```bash
mkdir build
cd build
cmake ..
make
```

The executable `simple_md` will be created in the build directory.

## Usage

### Basic Simulation
```bash
./simple_md <config_file.toml>
```

### Configuration File Format
Create a TOML configuration file with the following structure:

```toml
[MDSettings]
nsteps      = 25000      # Number of simulation steps
timestep    = 2.0        # Time step in femtoseconds
temperature = 87.15      # Target temperature in Kelvin
restart_file = "ar_1000_md.rst"  # Restart file with initial coordinates

[FF]  # Force Field Parameters
epsilon = 0.23806458033  # LJ epsilon parameter (kcal/mol)
sigma = 3.4              # LJ sigma parameter (Angstrom)
```

### Example Simulation
A complete example with 1000 Argon atoms is provided in the `example/` directory:

```bash
cd example
../build/simple_md ar_1000_md.toml
```

This simulation demonstrates:
- Liquid Argon at 87.15 K
- 25,000 time steps (50 ps simulation time)
- Automatic energy and trajectory output
- Temperature equilibration

## Input Files

### Restart File Format
The restart file (`.rst`) contains initial atomic coordinates, velocities, and forces:
```
Box    38.88371978008842688723    38.88371978008842688723    38.88371978008842688723
ar   1   1    x   y   z   vx   vy   vz   fx   fy   fz
...
```

Fields:
- **Box**: Simulation box dimensions (cubic)
- **Atom entries**: element, ID, type, position (x,y,z), velocity (vx,vy,vz), force (fx,fy,fz)

## Output Files

### Trajectory Files
- `output_trajectory.xyz`: Atomic positions for each output step in XYZ format
- Compatible with most molecular visualization tools

### Energy and Analysis Data
- `output_energy.dat`: Time series of kinetic, potential, and total energy
- `out.dat`: Detailed simulation log with step, temperature, and energy data
- Console output shows real-time simulation progress

### Visualization and Analysis
- `plot_t_e.gnu`: GNUplot script for energy vs. time plots
- `vmd.vmd`: VMD visualization script, can be loaded with `vmd -e vmd.vmd`

## Code Architecture

### Core Classes

#### Simulation Engine
- **`Box`**: Manages simulation cell, atomic data, and system properties
- **`Atom`**: Individual atom properties (position, velocity, force, mass, type)
- **`Integrator`**: Velocity Verlet time integration with two-step algorithm
- **`Setup`**: System initialization and configuration management

#### Force Field and Thermodynamics
- **`Potential`**: Lennard-Jones force field with cutoff, energy, and force calculations
- **`Thermostat`**: Temperature control with Berendsen algorithm
- **`Manostat`**: Pressure control with Berendsen barostat
- **`Kinetics`**: Kinetic energy calculations and temperature monitoring

#### Performance and I/O
- **`LinkedCellList`**: Efficient O(N) neighbor searching algorithm
- **`Input`**: TOML configuration file parser with validation
- **`Output`**: Trajectory and energy data output management
- **`Utils`**: Utility functions for vector operations and conversions

### Key Algorithms

1. Linked Cell Algorithm
   - Divides simulation box into cells
   - Only checks neighboring cells for interactions
   - Reduces computational complexity from O(N²) to O(N)

2. Velocity Verlet Integration:
   - First step: Update positions using current velocities and forces
   - Force calculation: Compute new forces at updated positions
   - Second step: Update velocities using averaged forces
   - Superior energy conservation compared to basic Verlet

3. Berendsen Thermostat
   - Smoothly couples system to thermal reservoir
   - Exponential approach to target temperature
   - Configurable coupling time constant (τ = 250 fs default)

## Units and Physical Constants

### Simulation Units
- Energy: kJ/mol and kcal/mol 
- Force: kcal/mol/Å
- Length: Angstroms (Å)
- Mass: Atomic mass units (u)
- Temperature*: Kelvin (K)
- Time: Femtoseconds (s)
- Velocity: Femtoseconds (Å/s)

## License

See LICENSE file for details.
