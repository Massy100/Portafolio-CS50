from cs50 import get_float


def main():
    while True:
        # Get user input for change owed
        dollars = get_float("Change owed: ")

        # Check if input is non-negative
        if dollars >= 0:
            break

    # Convert dollars to cents
    cents = round(dollars * 100)

    # Calculate the minimum number of coins
    quarters = cents // 25
    dimes = (cents % 25) // 10
    nickels = ((cents % 25) % 10) // 5
    pennies = ((cents % 25) % 10) % 5

    # Print the minimum number of coins
    print(quarters + dimes + nickels + pennies)


if __name__ == "__main__":
    main()
