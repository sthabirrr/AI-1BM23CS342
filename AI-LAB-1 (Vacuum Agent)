import random

NAME = "Sthavir K"
USN = "1BM23CS342"

def reflex_vacuum_agent(location, status):
    if status == "Dirty":
        return "Suck"
    elif location == "A":
        return "Right"
    elif location == "B":
        return "Left"

def vacuum_world():
    locations = {"A": random.choice(["Clean", "Dirty"]),
                 "B": random.choice(["Clean", "Dirty"])}
    location = random.choice(["A", "B"])

    print("Initial State:", locations, "| Vacuum at:", location)

    steps = 5
    for _ in range(steps):
        status = locations[location]
        action = reflex_vacuum_agent(location, status)
        print(f"Vacuum at {location} | Status: {status} -> Action: {action}")

        if action == "Suck":
            locations[location] = "Clean"
        elif action == "Right":
            location = "B"
        elif action == "Left":

        print("World State:", locations)

    print("\nFinal State:", locations)
    print(f"\nSubmitted by: {NAME}, USN: {USN}")

vacuum_world()
