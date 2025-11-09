import random


def calculate_cost(state):
    cost = 0
    n = len(state)
    for i in range(n):
        for j in range(i+1, n):
            if state[i] == state[j]:
                cost += 1
            if abs(state[i] - state[j]) == abs(i - j):
                cost += 1
    return cost

def random_state(n):
    return [random.randint(0, n-1) for _ in range(n)]


def get_best_neighbor(state):
    n = len(state)
    best_state = state[:]
    best_cost = calculate_cost(state)

    for col in range(n):
        for row in range(n):
            if state[col] != row:
                new_state = state[:]
                new_state[col] = row
                new_cost = calculate_cost(new_state)
                if new_cost < best_cost:
                    best_cost = new_cost
                    best_state = new_state
    return best_state, best_cost


def hill_climbing(n):
    current = random_state(n)
    current_cost = calculate_cost(current)

    while True:
        neighbor, neighbor_cost = get_best_neighbor(current)

        if neighbor_cost < current_cost:
            current, current_cost = neighbor, neighbor_cost
        else:
            break

    return current, current_cost

solution, cost = hill_climbing(4)

print("Name: Sthavir K")
print("USN : 1BM23CS342")
print("\nHill Climbing for 4-Queens Problem")
print("Final State (row positions per column):", solution)
print("Final Cost (0 means solved):", cost)
if cost == 0:
    print("Solution Found: Queens are safe!")
else:
    print(" Stuck in Local Optimum (Not a solution)")

