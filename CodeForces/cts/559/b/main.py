caller = (lambda f:lambda x:f(f,x))
#define caller (lambda f:lambda x:f(f,x))

connect = (lambda a,b:a+b if a<b else b+a)
#define connect (lambda a,b:a+b if a<b else b+a)

transfer = caller(lambda f,x:x if len(x)%2==1 else connect(f(f,x[:len(x)>>1]),f(f,x[len(x)>>1:])))
#define transfer caller(lambda f,x:x if len(x)%2==1 else connect(f(f,x[:len(x)>>1]),f(f,x[len(x)>>1:])))

main = (lambda a,b:"YES"if(transfer(a)==transfer(b))else"NO")
#define main (lambda a,b:"YES"if(transfer(a)==transfer(b))else"NO")

print(main(input(),input()))
