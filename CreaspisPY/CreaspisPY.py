f = open('AliHKri.lst','w');
for i in range(1,236): 
    for k in range(1,10):
        f.writelines('W'+str(k)+'0'+'0'+'0'+' '+'('+str(i)+')'+'.tga \n')
    