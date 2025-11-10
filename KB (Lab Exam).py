import itertools
import re

def logic_to_python(expr):
    
    clauses = expr.split(',')
    python_clauses = []
    for clause in clauses:
        clause = clause.strip()
        
        clause = clause.replace(' ', '')
        clause = re.sub(r'(\([^()]+\)|[A-Za-z0-9_]+)=>(\([^()]+\)|[A-Za-z0-9_]+)',
                          lambda m: f"(not {m.group(1)} or {m.group(2)})", clause)
        clause = clause.replace('<=>', '==')
        clause = clause.replace('∧', ' and ').replace('∨', ' or ').replace('¬', ' not ')
        python_clauses.append(f"({clause})") 
    
    
    return " and ".join(python_clauses)

def evaluate(expr, model):
    temp = expr
    for sym, val in model.items():
        temp = re.sub(r'\b' + re.escape(sym) + r'\b', str(val), temp)
    try:
        return eval(temp)
    except Exception as e:
        print("Error evaluating:", temp)
        return False

def entails(KB, query, symbols):
    python_KB = logic_to_python(KB)
    python_query = logic_to_python(query)
    result = True
    print(f"{' | '.join(symbols)} | KB | Query")
    print('-' * (4 * len(symbols) + 15))
    for values in itertools.product([True, False], repeat=len(symbols)):
        model = dict(zip(symbols, values))
        kb_val = evaluate(python_KB, model)
        q_val = evaluate(python_query, model)
        row = ' | '.join(['T' if model[s] else 'F' for s in symbols])
        row += f" | {'T' if kb_val else 'F'}  | {'T' if q_val else 'F'}"
        print(row)
        if kb_val and not q_val:
            result = False
    return result


KB = input("Enter Knowledge Base (use ∧, ∨, ¬, =>): ")
query = input("Enter Query (use ∧, ∨, ¬, =>): ")
symbol_input = input("Enter symbols separated by spaces: ")
symbols = symbol_input.split()

if entails(KB, query, symbols):
    print("KB entails Query.")
else:
    print("KB does NOT entail Query.")
