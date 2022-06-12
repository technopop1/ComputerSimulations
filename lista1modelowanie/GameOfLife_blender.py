
###
### kod do blendera 
###

import bpy
import numpy as np
from random import randint

a = bpy.data.collections['Collection'].all_objects
if (len(a) != 0):
    N = int(np.sqrt(len(a)))
else:
    N = 15

cubes = np.full((N, N), False)
selection_names = [ [ [] for _ in range(0, N) ] for _ in range(0, N)]

p0 = 0.4

for i in range(0, N):
    for j in range(0, N):
        los = randint(0,1)
        if los < p0:
            cubes[i, j] = 1

for i in range(0, N):
    for j in range(0, N):
        
        # set anim property if cubes exists on scene
        if (len(a) != 0):
            a[i*N + j].data.animation_data_create()
            a[i*N + j].data.animation_data.action = bpy.data.actions.new('Visibility Action')
            
            selection_names[i][j] = a[i*N + j].name
            if cubes[i, j] == 1:
                a[i*N + j].hide_viewport = False
            else:
                a[i*N + j].hide_viewport = True
        else: # set anim property if cubes don't exists on scene
            bpy.ops.mesh.primitive_cube_add(location=(i*2,j*2,0.0))
            obj = bpy.context.selected_objects[0]
            obj.data.animation_data_create()
            obj.data.animation_data.action = bpy.data.actions.new('Visibility Action')
            
            selection_names[i][j] = obj.name
            if cubes[i, j] == 1:
                obj.hide_viewport = False
            else:
                obj.hide_viewport = True


cubesNext = cubes.copy()

time = 0
neighborPos = [ [-1,-1], [0,-1], [1,-1], [-1,0], [1,0], [-1,1], [0,1], [1,1] ]

# dla time < 100 i 10k kostek kompiluje się 1.2h XD
# dla time < 500 i 10k kostek kompiluje się 4,5h XDDDD
while time < 500:
    
    cubes = cubesNext.copy()
    for x in range(0, N):
        for y in range(0, N):
            AliveCounter = 0
            for i in neighborPos:
                AliveCounter += cubes[(x + i[0] + N) % N][(y + i[1] + N) % N]
            
                    
            bo = bpy.data.objects[ selection_names[x][y] ]
            if (cubesNext[x][y] == 1):
                bo.hide_viewport = False
                bo.hide_render = False
            else:
                bo.hide_viewport = True
                bo.hide_render = True
            
            if (((AliveCounter == 2 or AliveCounter == 3) and cubes[x][y] == 1) or (AliveCounter == 3 and cubes[x][y] == 0)):
                cubesNext[x][y] = 1
            else:
                cubesNext[x][y] = 0
                
            bo.keyframe_insert(data_path = "hide_viewport", frame = time)
            bo.keyframe_insert(data_path = "hide_render", frame = time)
            
    
    time += 1