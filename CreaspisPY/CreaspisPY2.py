f = open('SolUSliC.lst','w');
for i in range(224,291): 
    for k in range(1,17):
       f.writelines('W'+ str(k)+'0'+str(i)+'.tga \n')
    