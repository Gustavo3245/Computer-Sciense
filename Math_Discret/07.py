MARCADO = 1
DESMARCADO = 0

def criar_lista(n):
    lista = []
    for idx in range(n-1):
        lista.append(DESMARCADO)
    return lista

def marcar(primo,n,lista):
    for numero in range(primo+1,n+1):
        if numero % primo == 0:
            lista[numero-2] = MARCADO
            
def proximo(primo,n,lista):
    for proximo in range(primo+1,n+1):
        if lista[proximo - 2] == DESMARCADO:
            return proximo

    return n

def imprime(n,lista):
    print(f"Os primos menores que {n}: ")
    for numero in range(n-1):
        if lista[numero] == DESMARCADO:
            print(numero+2,end=" -> ")
    print("FIM")

def primos_ate_n(valor,lista):
    primo = 2
    while(primo <= valor):
        marcar(primo, valor, lista)
        if primo == valor:
            break
        primo = proximo(primo, valor, lista)
    return lista  

def mmc(a, b):
    lista_a = criar_lista(a)
    lista_b = criar_lista(b)

    primos_ate_n(a,lista_a)
    primos_ate_n(b,lista_b)
    dicio_a = {}
    dicio_b = {}
    for i in range(a-1):
        if lista_a[i] == DESMARCADO:
            count = 0
            while (a % (i+2) == 0):
                a = a / (i+2)
                count+=1
            dicio_a[i+2] = count
    for i in range(b-1):
        if lista_a[i] == DESMARCADO:
            count = 0
            while (b % (i+2) == 0):
                b = b / (i+2)
                count+=1
            dicio_b[i+2] = count
    
    
def main():
    a = int(input("Digite um a: "))
    b = int(input("Digite um b: "))
    mmc(a,b)
    



main()
        
    