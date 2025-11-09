from itertools import combinations

def unify(x, y, theta=None):
    if theta is None:
        theta = {}
    if x == y:
        return theta
    elif isinstance(x, str) and x.islower():
        return unify_var(x, y, theta)
    elif isinstance(y, str) and y.islower():
        return unify_var(y, x, theta)
    elif isinstance(x, tuple) and isinstance(y, tuple) and len(x) == len(y):
        return unify(x[1:], y[1:], unify(x[0], y[0], theta))
    else:
        return None

def unify_var(var, x, theta):
    if var in theta:
        return unify(theta[var], x, theta)
    elif x in theta:
        return unify(var, theta[x], theta)
    else:
        theta[var] = x
        return theta

def negate(predicate):
    if isinstance(predicate, tuple) and predicate[0] == 'not':
        return predicate[1]
    else:
        return ('not', predicate)

def substitute_predicate(predicate, theta):
    if isinstance(predicate, str):
        return theta.get(predicate, predicate)
    elif isinstance(predicate, tuple):
        return (predicate[0],) + tuple(theta.get(arg, arg) for arg in predicate[1:])
    return predicate

def substitute(clause, theta):
    return {substitute_predicate(p, theta) for p in clause}

def resolve(clause1, clause2):
    resolvents = []
    for p1 in clause1:
        for p2 in clause2:
            theta = unify(p1, negate(p2))
            if theta is not None:
                new_clause = (substitute(clause1, theta) | substitute(clause2, theta)) - {p1, p2}
                resolvents.append(frozenset(new_clause))
    return resolvents

def resolution(kb, query):
    negated_query = frozenset({negate(query)})
    clauses = kb | {negated_query}
    new = set()

    while True:
        pairs = list(combinations(clauses, 2))
        for (ci, cj) in pairs:
            resolvents = resolve(ci, cj)
            if frozenset() in resolvents:
                return True
            new |= set(resolvents)
        if new.issubset(clauses):
            return False
        clauses |= new

# Knowledge Base
kb = {
    frozenset({('not', ('Food', 'x')), ('Likes', 'John', 'x')}),  # a
    frozenset({('Food', 'Apple')}),  # b
    frozenset({('Food', 'Vegetables')}),  # b
    frozenset({('not', ('Eats', 'x', 'y')), ('Killed', 'x'), ('Food', 'y')}),  # c
    frozenset({('Eats', 'Anil', 'Peanuts')}),  # d
    frozenset({('Alive', 'Anil')}),  # d
    frozenset({('not', ('Eats', 'Anil', 'x')), ('Eats', 'Harry', 'x')}),  # e
    frozenset({('not', ('Alive', 'x')), ('not', ('Killed', 'x'))}),  # f
    frozenset({('Killed', 'x'), ('Alive', 'x')}),  # g
}
query = ('Likes', 'John', 'Peanuts')

# Run resolution
result = resolution(kb, query)

if result:
    print("Proved by resolution: John likes peanuts.")
else:
    print("Cannot prove that John likes peanuts.")
