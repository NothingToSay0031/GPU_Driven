# Vulkan Render Engine with Real-Time Rendering Techniques

This repository contains two modern real-time rendering systems. Each technique is designed to improve GPU efficiency and reduce rendering overhead, with implementation in compute shaders for high performance.

## Visibility Culling System

Based on [SIGGRAPH 2015: GPU-Driven Rendering Pipelines](https://advances.realtimerendering.com/s2015/aaltonenhaar_siggraph2015_combined_final_footer_220dpi.pdf).

This system combines depth-based culling, indirect draw generation, and iterative refinement:

### Pipeline Overview

1. **Initial Culling**
   Use the *previous frame's* depth buffer to perform mesh and meshlet **frustum** and **occlusion culling**.
   A list of potentially visible objects is built via a **compute shader**, though false negatives may occur.

2. **Draw List Generation**
   The visible meshlets from Step 1 are encoded into **indirect draw commands**.

3. **Depth Update**
   These draw calls produce an **updated depth buffer**, which is also used to build a **depth pyramid**.

4. **False Positive Recheck**
   Previously culled meshlets are re-tested using the new depth. A second draw list corrects false positives.

5. **Final Draw & Feedback Loop**
   The corrected list is drawn, generating the **final depth buffer** for use in the next frame.


## Light Clustering System

Based on [SIGGRAPH 2017: Improved Culling for Tiled and Clustered Rendering](https://www.activision.com/cdn/research/2017_Sig_Improved_Culling_final.pdf).

This hybrid technique leverages both **depth-based clustering** and **screen-space tiling** to efficiently determine per-fragment light lists.

### Algorithm Steps

1. **Light Sorting**
   Sort all lights by depth in **camera space**.

2. **Z-Binning**
   Divide depth into uniform or **logarithmic bins**, assigning lights to bins based on their bounding volume.

3. **Bin Indexing**
   For each bin, store the **min/max light indices**, requiring just 16 bits per bin unless >65K lights.

4. **Tile Division**
   Screen is split into **8×8 pixel tiles**. Each tile stores a **bitfield** indicating which lights overlap it.

5. **Fragment Shading Prep**
   For a given fragment, determine its **depth**, map it to a **Z-bin**, and use that to fetch light index range.

6. **Final Light Lookup**
   Iterate through lights in the bin and check against the tile’s bitmask to find **visible lights**.

This method balances spatial granularity (tiles) with depth-aware light assignment (bins), providing a performant way to evaluate light lists at fragment level.

# Usage

1. Install CMake
2. `python3 .\bootstrap.py`
3. Install Vulkan SDK
4. `cmake -B build -DCMAKE_BUILD_TYPE=Debug`
