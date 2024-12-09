from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day6.txt'
file = parse_input(filePath)

rows = len(file)
cols = len(file[0])


# Define movement and directions
directions = ["up", "right", "down", "left"]
movement = {
    "up": (-1, 0),
    "right": (0, 1),
    "down": (1, 0),
    "left": (0, -1),
}

# Simulate the guard's movement to check for a loop
def simulate_with_obstruction(map_with_obstruction, start_row, start_col, start_direction):
    spt_row, spt_col, direction = start_row, start_col, start_direction
    visited = set()  # To track visited positions with directions

    while True:
        # Check the current state (position and direction)
        state = (spt_row, spt_col, direction)
        if state in visited:
            return True  # Loop detected
        visited.add(state)

        # Get the movement delta for the current direction
        delta_row, delta_col = movement[direction]
        next_row, next_col = spt_row + delta_row, spt_col + delta_col

        # Check if the next position is within bounds
        if 0 <= next_row < rows and 0 <= next_col < cols:
            if map_with_obstruction[next_row][next_col] == "#":
                # Obstacle: Turn 90 degrees to the right
                direction = directions[(directions.index(direction) + 1) % 4]
            else:
                # Move forward
                spt_row, spt_col = next_row, next_col
        else:
            # Out of bounds: no loop
            return False

# Main logic to test all possible obstruction positions
def find_guard_position(grid):
    direction_map = {
        "^": "up",
        ">": "right",
        "v": "down",
        "<": "left"
    }
    for row in range(len(grid)):
        for col in range(len(grid[0])):
            if grid[row][col] in direction_map:
                return row, col, direction_map[grid[row][col]]
    return None

# Function to test all possible obstruction placements
def count_obstruction_positions(grid):
    start = find_guard_position(grid)
    if not start:
        raise ValueError("No starting position found")
    start_row, start_col, start_direction = start

    valid_positions = 0

    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == ".":
                # Place obstruction and simulate
                grid_with_obstruction = [list(row) for row in grid]
                grid_with_obstruction[i][j] = "#"
                if simulate_with_obstruction(grid_with_obstruction, start_row, start_col, start_direction):
                    valid_positions += 1

    return valid_positions

# Output the result
print(count_obstruction_positions(file))
# Output the result
