
def gcd(x,y):
    while(y!=0):
        x,y=y,x%y
    return x
def trans(num):
    L=len(num)
    X=0
    Y=1
    flag=0
    for i in range(L):
        if(num[i]=='.'):
            flag=1
            continue
        X=X*10+int(num[i])
        if(flag):Y*=10
    d=gcd(X,Y)
    X/=d
    Y/=d
    return (X,Y)
def calc(a,A,b,B):
    #find k,that satisfies ceil(k*(a/A))<=floor(k*(b/B))

    if(a%A==0):
        return 1
    if(b%B==0):
        return 1
    X1=a/A
    X2=b/B
    if(X1<X2):
        return 1
    if(X1>0):
        a-=A*X1
        b-=B*X2
    T=calc(B,b,A,a)
    return (B*T+b-1)/b
def solve(A,B):
    return calc(A[0],A[1],B[0],B[1])
tmp=raw_input().split();
print solve(trans(tmp[0]),trans(tmp[1]))
