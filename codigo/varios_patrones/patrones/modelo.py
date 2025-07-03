f=open('modelo.dat','w')

str2="patron"
cont=""

for i in range(8):

	a=open(str2+str(i+1)+".dat",'r')

	cont=a.readlines()

	a.close()

	for j in cont:
		f.write(j.rstrip()+" ")

	f.write('\n')
	cont=""



f.close()