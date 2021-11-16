_Un=int(input())
_Umod=1000000007
_Ua1=pow(2,_Un*_Un,_Umod)
_Ua2=pow(2,(_Un*_Un+1)//2,_Umod)
_Ua3=pow(2,(_Un*_Un+3)//4,_Umod)
print(250000002*(_Ua1+_Ua2+_Ua3+_Ua3)%_Umod)
