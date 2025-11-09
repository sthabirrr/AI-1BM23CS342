from collections import deque


GOAL_STATE = (1, 2, 3,
              8, 0, 4,
              7, 6, 5)  


MOVES = {
    'Up':    (-1, 0),
    'Down':  (1, 0),
    'Left':  (0, -1),
    'Right': (0, 1)
}

def index_to_pos(index):
    return index // 3, index % 3

def pos_to_index(row, col):
    return row * 3 + col

def get_neighbors(state):
    neighbors = []
    zero_index = state.index(0)
    zero_row, zero_col = index_to_pos(zero_index)

    for move, (dr, dc) in MOVES.items():
        new_row, new_col = zero_row + dr, zero_col + dc
        if 0 <= new_row < 3 and 0 <= new_col < 3:
            new_zero_index = pos_to_index(new_row, new_col)
            new_state = list(state)

            new_state[zero_index], new_state[new_zero_index] = new_state[new_zero_index], new_state[zero_index]
            neighbors.append((tuple(new_state), move))
    return neighbors

def bfs(start_state, max_depth=50):
    queue = deque([(start_state, [], [start_state])])
    visited = set([start_state])

    while queue:
        state, path_moves, path_states = queue.popleft()

        if state == GOAL_STATE:
            return path_moves, path_states

        if len(path_moves) < max_depth:
            for neighbor, move in get_neighbors(state):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, path_moves + [move], path_states + [neighbor]))
    return None, None

def print_puzzle(state):
    for i in range(0, 9, 3):
        print(state[i:i+3])
    print()




name = input("Enter your name: ")
usn = input("Enter your USN: ")


start_state = (2, 8, 3,
               1, 6, 4,
               7, 0, 5)

print(f"\nSolver started for {name} (USN: {usn})")
print("\nStart State:")
print_puzzle(start_state)

moves, states = bfs(start_state, max_depth=50)

if moves is not None:
    print(f"Solution found in {len(moves)} moves!\n")

    print("States passed through from start to goal:")
    for i, state in enumerate(states):
        print(f"Step {i}:")
        print_puzzle(state)

    print("Moves to solve the puzzle:")
    print(moves)
else:
    print("No solution found within the depth limit.")

