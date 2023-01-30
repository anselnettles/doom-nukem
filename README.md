# WIP-Doom-Nukem

My current project, which is still a work in progress.

The goal of this project is to create a mix of Doom and Duke Nukem


# Controls:

W/S to move forward and backward

A/D to strife

Mouse to rotate camera

0 to toggle multithreading

# updatelog:

16/1/22
i have converted wolf3d into SDL, discarded some utilities and added mouse movement.

18/1/22
Added multithreading, though i still need to optimize each threads workload, program is much faster without multithreading.
You can toggle multithreading with '0'(zero).
I also added strife

19/1/22
I fixed multithreading, though it doesnt really improve my programs performance from non-multithread version. It will be more useful
later on when i change my drawing from rect-based drawing to individual pixel-based drawing (which is required by school).
I also added some basic shading.

20/1/22
Changed rect-based drawing to individual pixel-based drawing. Next up wall-textures from bmp.
