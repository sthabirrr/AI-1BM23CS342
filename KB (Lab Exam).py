import itertools

def pl_true(expr, model):
    if isinstance(expr, str):
        return model[expr]
    elif isinstance(expr, tuple):
        op = expr[0]
        if op == "not":
            return not pl_true(expr[1], model)
        elif op == "and":
            return pl_true(expr[1], model) and pl_true(expr[2], model)
        elif op == "or":
            return pl_true(expr[1], model) or pl_true(expr[2], model)
        elif op == "implies":
            return (not pl_true(expr[1], model)) or pl_true(expr[2], model)
    return False

def get_symbols(expr):
    if isinstance(expr, str):
        return {expr}
    elif isinstance(expr, tuple):
        return get_symbols(expr[1]) | (get_symbols(expr[2]) if len(expr) > 2 else set())
    return set()

def tt_entails_print(KB, query):
    symbols = list(get_symbols(KB) | get_symbols(query))
    all_models = list(itertools.product([True, False], repeat=len(symbols)))

    entailment = True
    print("\nTruth Table Evaluation:")
    print("-" * 50)
    print("Model".ljust(20), "KB".ljust(10), "Query".ljust(10))
    print("-" * 50)

    for values in all_models:
        model = dict(zip(symbols, values))
        kb_val = pl_true(KB, model)
        q_val = pl_true(query, model)

        print(str(model).ljust(20), str(kb_val).ljust(10), str(q_val).ljust(10))

        if kb_val and not q_val:
            entailment = False

    print("-" * 50)
    return entailment

KB = ("and", ("implies", "P", "Q"), "P")
query = "Q"

result = tt_entails_print(KB, query)

print("\nName: Sthavir K")
print("USN : 1BM23CS342")
print("\nKnowledge Base: (P → Q) and (P)")
print("Query: Q")
print("Does KB entail Query? :", "YES " if result else "NO ")
