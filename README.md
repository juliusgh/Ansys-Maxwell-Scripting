# Ansys-Maxwell-Scripts

This repository contains various Python scripts to facilitate the modeling and simulation in Ansys Maxwell 3D. So far the scripts focus on the simulation of inductive coupling using different coil geometries. The scripts are partly based on the examples which are provided by Ansys, all rights reserved. The full documentation of the Ansys Scripting Python library is available in every Ansys Maxwell installation (Help -> Maxwell Scripting Help) and not included in this repository due to copyright reasons.

Repository structure:
- `UDP`: User Defined Primitives in form of Python scripts that automatically create geometrical objects in Ansys Maxwell, but only by the help of a limited API. UDPs can also be created by compiled C++ code in a more efficient way, but using the same limited API.
- `Geometry`: Python scripts that create advanced geometrical objects, but can't be used directly as UDPs.
- `Sweeps`: Python scripts that automatically perform simulations for different parameters and geometries and thus enable a more advanced parameter sweep than the built-in optimetrics in Ansys Maxwell. For example the built-in optimetrics don't support the generation of UDPs using Python scripts.

The `deploy.bat` Windows batch script can be used to automatically deploy the included `UPD` scripts to the current Ansys Maxwell installation.