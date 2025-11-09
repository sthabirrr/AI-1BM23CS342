import random
import math


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


def get_neighbor(state):
    n = len(state)
    neighbor = state[:]
    col = random.randint(0, n-1)
    row = random.randint(0, n-1)
    neighbor[col] = row
    return neighbor


def simulated_annealing(n, max_steps=100000, start_temp=100, cooling_rate=0.99):
    current = random_state(n)
    current_cost = calculate_cost(current)
    T = start_temp

    for step in range(max_steps):
        if current_cost == 0:
            break
        neighbor = get_neighbor(current)
        neighbor_cost = calculate_cost(neighbor)
        delta = neighbor_cost - current_cost

        if delta < 0 or random.uniform(0, 1) < math.exp(-delta / T):
            current, current_cost = neighbor, neighbor_cost

        T = T * cooling_rate
        if T < 1e-5:
            break

    return current, current_cost


solution, cost = simulated_annealing(8)

print("Name: Sthavir K")
print("USN : 1BM23CS342")
print("\nSimulated Annealing for 8-Queens Problem")
print("Final State (row positions per column):", solution)
print("Final Cost (0 means solved):", cost)
if cost == 0:
    print("Solution Found: Queens are safe!")
else:
    print("Stuck in Local Optimum (Not a solution)")
