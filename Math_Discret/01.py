import itertools

#(p -> q) ^ (p -> r) === p-> (q ^ r)
print("Equivalência 1:")
print("(p -> q) ^ (p -> r) === p-> (q ^ r)")
equivalencia1_valida = True
for p, q, r in itertools.product([True, False], repeat=3):
    lado_esquerdo = ((not p) or q) and ((not p) or r)
    lado_direito = (not p) or (q and r) 
    if lado_esquerdo != lado_direito:
        equivalencia1_valida = False

print(f"Resultado: {equivalencia1_valida}")

#(p ∧ ¬q) → r ≡ (p → q) ∨ (p → r)
print("Equivalência 2:")
print("(p ∧ ¬q) → r ≡ (p → q) ∨ (p → r)")
equivalencia2_valida = True
for p, q, r in itertools.product([True, False], repeat=3):
    lado_esquerdo = (not(p and (not q))) or r 
    lado_direito = ((not p) or q) or ((not p) or r)
    if lado_esquerdo != lado_direito:
        equivalencia2_valida = False
print(f"Resultado: {equivalencia2_valida}")

#(p ∨ q) ∧ ¬(r → s) ≡ ¬((¬p ∧ ¬q) ∨ (¬r ∨ s))
print("Equivalência 3:")
print("(p ∨ q) ∧ ¬(r → s) ≡ ¬((¬p ∧ ¬q) ∨ (¬r ∨ s))")
equivalencia3_valida = True
for p, q, r, s in itertools.product([True, False], repeat=4):
    lado_esquerdo = (p or q) and (not((not r) or s))
    lado_direito = not(((not p) and (not q)) or ((not r) or s))
    if lado_esquerdo != lado_direito:
        equivalencia3_valida = False
print(f"Resultado: {equivalencia3_valida}")
