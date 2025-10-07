def input_positivo_nulo(msg):
    n = int(input(msg))
    if n >= 0:
        return n
    while n < 0:
        n = int(input("Não são aceitos numeros negativos. Tente novamente: "))
        
def input_positivo(msg):
    n = int(input(msg))
    if n > 0:
        return n
    while n <= 0:
        n = int(input("Não são aceitos numeros negativos ou 0. Tente novamente: "))

def input_maior_que(msg,numero):
    n = int(input(msg))
    if n > numero:
        return n
    while n < numero:
        n = int(input(f"Não são aceitos numeros menores que {numero}. Tente novamente: "))