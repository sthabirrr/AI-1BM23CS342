import copy
import heapq


NAME = "Sthavir K"
USN = "1BM23CS342"

print(f"Name: {NAME}")
print(f"USN : {USN}\n")


goal_state = [[1, 2, 3],
              [8, 0, 4],
              [7, 6, 5]]

def heuristic_misplaced(current_state):
    misplaced = 0
    for i in range(3):
        for j in range(3):
            if current_state[i][j] != 0 and current_state[i][j] != goal_state[i][j]:
                misplaced += 1
    return misplaced

def is_goal(state):
    return state == goal_state

def find_blank(state):
    for i in range(3):
        for j in range(3):
            if state[i][j] == 0:
                return i, j

def get_neighbors(state):
    neighbors = []
    x, y = find_blank(state)
    directions = [(-1,0), (1,0), (0,-1), (0,1)]
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx < 3 and 0 <= ny <3:
            new_state = copy.deepcopy(state)
            new_state[x][y], new_state[nx][ny] = new_state[nx][ny], new_state[x][y]
            neighbors.append(new_state)
    return neighbors

def a_star_misplaced(initial_state):
    open_list = []
    heapq.heappush(open_list, (heuristic_misplaced(initial_state), 0, initial_state, []))
    visited = set()

    while open_list:
        heuristic, g, current_state, path = heapq.heappop(open_list)
        state_id = str(current_state)
        if state_id in visited:
            continue
        visited.add(state_id)

        if is_goal(current_state):
            return path + [current_state]

        for neighbor in get_neighbors(current_state):
            heapq.heappush(open_list, (heuristic_misplaced(neighbor) + g + 1, g + 1, neighbor, path + [current_state]))
    return None

initial_state = [[2, 8, 3],
                 [1, 6, 4],
                 [7, 0, 5]]

solution = a_star_misplaced(initial_state)

print("\nSolution Steps:\n")
for step in solution:
    for row in step:
        print(row)
    print()
