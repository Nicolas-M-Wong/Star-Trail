import os
import numpy as np
import cv2
import time as t
import copy

#%%

path = 'C:/Users/Nicolas/Pictures/Circum-polaire-13-08-2021'

files = []
picture_list = []

# r=root, d=directories, f = files
for r, d, f in os.walk(path):
    for file in f:
        if '.JPG' in file:
            print(file)
            picture = cv2.imread(path+'/'+file)
            picture_list.append(picture)

picture_array = np.array(picture_list) 
#%%

picture_stack = np.zeros_like(picture_array[0])
ref_picture = picture_array[0]
picture_stack = ref_picture

axis_1,axis_2,axis_3,axis_4 = np.shape(picture_array)

    
#%% Ici on essaie avec le carré d'étude 2x2

start = t.time()
picture_stack = np.zeros_like(picture_array[0])
ref_picture = picture_array[0]
picture_stack = copy.deepcopy(ref_picture)


for i in range (1,axis_1):
    print(i)
    for j in range (0,axis_4):
        print("    ",j)
        for k in range (0,axis_2-2,2):
            for l in range (0,axis_3-2,2):
                #Approximation pour réduire le temps de calcul
                #On se déplace de deux en deux sur les lignes et les colonnes
                #4 pixel analysées à chaque itération si la somme des 4 est
                #différente de plus d'une marge prédéfini alors on change tous
                #les pixels du carré sur la nouvelle image
                #L'utilisation des int(pixel[i,j,k]) permet d'eviter l'erreur :
                #RuntimeWarning: overflow encountered in ubyte_scalars
                
                square_study = int(picture_array[i,k,l,j])+int(picture_array[i,k,l+1,j])
                square_study += int(picture_array[i,k+1,l,j])+int(picture_array[i,k+1,l+1,j])
                square_ref = int(picture_stack[k,l,j])+int(picture_stack[k,l+1,j])
                square_ref += int(picture_stack[k+1,l,j])+int(picture_stack[k+1,l+1,j])
                  
                if square_study >= 75+ square_ref:
                    picture_stack[k,l,j] = picture_array [i,k,l,j]
                    picture_stack[k,l+1,j] = picture_array [i,k,l+1,j]
                    picture_stack[k+1,l,j] = picture_array [i,k+1,l,j]
                    picture_stack[k+1,l+1,j] = picture_array [i,k+1,l+1,j]
                    
stop = t.time()
print("Temps total (min) :",round((stop-start)/60,2))

cv2.imwrite("circum_polaire_fast2x2.jpg",picture_stack)
                    
#%% Ici on étudie pixel par pixel


start = t.time()
picture_stack = np.zeros_like(picture_array[0])
ref_picture = picture_array[0]
picture_stack = copy.deepcopy(ref_picture)


for i in range (1,axis_1):
    print(i)
    for j in range (0,axis_4):
        print("    ",j)
        for k in range (0,axis_2):
            for l in range (0,axis_3):

                if picture_stack[k,l,j] <= 12+picture_array [i,k,l,j]:
                    picture_stack[k,l,j] = picture_array [i,k,l,j]
                    
stop = t.time()
print("Temps total (min) :",round((stop-start)/60,2))

cv2.imwrite("circum_polaire_1x1.jpg",picture_stack)
