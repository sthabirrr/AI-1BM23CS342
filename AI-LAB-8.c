def FOL_FC_ASK(KB, alpha):
    # Initialize the new sentences to be inferred in this iteration
    new = set()

    while new:  # Repeat until new is empty
        new = set()  # Clear new sentences on each iteration

        # For each rule in KB
        for rule in KB:
            # Standardize the rule variables to avoid conflicts
            standardized_rule = standardize_variables(rule)
            p1_to_pn, q = standardized_rule  # Premises (p1, ..., pn) and conclusion (q)

            # For each substitution θ such that Subst(θ, p1, ..., pn) matches the premises
            for theta in get_matching_substitutions(p1_to_pn, KB):
                q_prime = apply_substitution(theta, q)

                # If q_prime does not unify with some sentence already in KB or new
                if not any(unify(q_prime, sentence) != 'FAILURE' for sentence in KB.union(new)):
                    new.add(q_prime)  # Add q_prime to new

                    # Unify q_prime with the query (alpha)
                    phi = unify(q_prime, alpha)
                    if phi != 'FAILURE':
                        return phi  # Return the substitution if it unifies

        # Add newly inferred sentences to the knowledge base
        KB.update(new)

    return False  # Return false if no substitution is found


def standardize_variables(rule):
    """
    Standardize variables in the rule to avoid variable conflicts.
    Rule is assumed to be a tuple (premises, conclusion).
    """
    premises, conclusion = rule
    # Apply standardization logic here (for simplicity, assume no conflict in this case)
    return (premises, conclusion)


def get_matching_substitutions(premises, KB):
    """
    Get matching substitutions for the premises in the KB.
    This is a placeholder to represent how substitutions would be found.
    """
    # Implement substitution matching here
    return []  # This should return a list of valid substitutions


def apply_substitution(theta, expression):
    """
    Apply a substitution θ to an expression.
    This function will replace variables in expression with their corresponding terms from θ.
    """
    if isinstance(expression, str) and expression.startswith('?'):
        return theta.get(expression, expression)  # Apply substitution to variable
    elif isinstance(expression, tuple):
        return tuple(apply_substitution(theta, arg) for arg in expression)
    return expression


def unify(psi1, psi2, subst=None):
    """Unification algorithm (simplified)"""
    if subst is None:
        subst = {}

    def apply_subst(s_map, expr):
        if isinstance(expr, str) and expr.startswith('?'):
            return s_map.get(expr, expr)
        elif isinstance(expr, tuple):
            return tuple(apply_subst(s_map, arg) for arg in expr)
        return expr

    def is_variable(expr):
        return isinstance(expr, str) and expr.startswith('?')

    _psi1 = apply_subst(subst, psi1)
    _psi2 = apply_subst(subst, psi2)

    if is_variable(_psi1) or is_variable(_psi2) or not isinstance(_psi1, tuple) or not isinstance(_psi2, tuple):
        if _psi1 == _psi2:
            return subst
        elif is_variable(_psi1):
            if _psi1 in str(_psi2):
                return 'FAILURE'
            return {**subst, _psi1: _psi2}
        elif is_variable(_psi2):
            if _psi2 in str(_psi1):
                return 'FAILURE'
            return {**subst, _psi2: _psi1}
        else:
            return 'FAILURE'

    if _psi1[0] != _psi2[0] or len(_psi1) != len(_psi2):
        return 'FAILURE'

    for arg1, arg2 in zip(_psi1[1:], _psi2[1:]):
        s = unify(arg1, arg2, subst)
        if s == 'FAILURE':
            return 'FAILURE'
        subst = s

    return subst

# Knowledge Base (KB)
KB = set()

# Adding facts to KB:
KB.add(('american', 'Robert'))  # Robert is an American
KB.add(('hostile_nation', 'Country_A'))  # Country A is a hostile nation
KB.add(('sell_weapons', 'Robert', 'Country_A'))  # Robert sold weapons to Country A

# Adding the rule (the law):
KB.add((('american(x)', 'hostile_nation(y)', 'sell_weapons(x, y)'),
         'criminal(x)'))

# Goal: Prove that Robert is a criminal
goal = 'criminal(Robert)'

# Calling FOL_FC_ASK to prove the goal
result = FOL_FC_ASK(KB, goal)

if result != 'FAILURE':
    print("Robert is a criminal!")
else:
    print("Robert is not a criminal.")
