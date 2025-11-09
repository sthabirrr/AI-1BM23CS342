import math

NAME = "Sthavir Kiran Kulkarni"
USN = "1BM23CS342"

# Function to print the board
def print_board(board):
    for row in board:
        print("|".join(row))1
    print()

# Function to check if moves are left
def is_moves_left(board):
    for row in board:
        if " " in row:
            return True
    return False

# Function to evaluate board
def evaluate(board):
    # Check rows
    for row in board:
        if row.count(row[0]) == 3 and row[0] != " ":
            return 10 if row[0] == "O" else -10
    # Check cols
    for col in range(3):
        if board[0][col] == board[1][col] == board[2][col] != " ":
            return 10 if board[0][col] == "O" else -10
    # Check diagonals
    if board[0][0] == board[1][1] == board[2][2] != " ":
        return 10 if board[0][0] == "O" else -10
    if board[0][2] == board[1][1] == board[2][0] != " ":
        return 10 if board[0][2] == "O" else -10
    return 0

# Minimax function
def minimax(board, depth, is_max):
    score = evaluate(board)
    if score == 10: return score - depth
    if score == -10: return score + depth
    if not is_moves_left(board): return 0

    if is_max:
        best = -math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == " ":
                    board[i][j] = "O"
                    best = max(best, minimax(board, depth + 1, False))
                    board[i][j] = " "
        return best
    else:
        best = math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == " ":
                    board[i][j] = "X"
                    best = min(best, minimax(board, depth + 1, True))
                    board[i][j] = " "
        return best

# Find best move for computer
def find_best_move(board):
    best_val = -math.inf
    best_move = (-1, -1)
    for i in range(3):
        for j in range(3):
            if board[i][j] == " ":
                board[i][j] = "O"
                move_val = minimax(board, 0, False)
                board[i][j] = " "
                if move_val > best_val:
                    best_move = (i, j)
                    best_val = move_val
    return best_move

# Play game
def play_game():
    board = [[" "]*3 for _ in range(3)]
    print("Tic-Tac-Toe Game! You are X, Computer is O")
    print_board(board)

    for turn in range(9):
        if turn % 2 == 0:  # Human move
            row = int(input("Enter row (0-2): "))
            col = int(input("Enter col (0-2): "))
            if board[row][col] != " ":
                print("Invalid move, try again.")
                continue
            board[row][col] = "X"
        else:  # Computer move
            move = find_best_move(board)
            board[move[0]][move[1]] = "O"
            print(f"Computer places O at {move}")

        print_board(board)
        score = evaluate(board)
        if score == 10:
            print("Computer Wins!")
            print(f"\nSubmitted by: {NAME}, USN: {USN}")
            return
        elif score == -10:
            print("You Win!")
            print(f"\nSubmitted by: {NAME}, USN: {USN}")
            return

    print("It's a Draw!")
    print(f"\nSubmitted by: {NAME}, USN: {USN}")

play_game()
