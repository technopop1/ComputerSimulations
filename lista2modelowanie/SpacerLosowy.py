
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
    N = 5000

kid = [ 0 , 0 , 0 ]

print(N)
while N >= 0:
    bpy.ops.mesh.primitive_ico_sphere_add(location=(kid[0], kid[1], kid[2]))
    los = randint(1,26)
    kid[0], kid[1], kid[2] = kid[0] + randint(-1,1), kid[1]  + randint(-1,1), kid[2]  + randint(-1,1)      
    N -= 1    