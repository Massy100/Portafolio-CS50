def get_height():
    while True:
        try:
            height = int(input("Enter the height (number between 1 and 8): "))
            if 1 <= height <= 8:
                return height
            else:
                print("Please enter a number between 1 and 8")
        except ValueError:
            print("Unvalid digit")


def main():
    height = get_height()

    for i in range(1, height + 1):
        # Print spaces
        for j in range(1, height - i + 1):
            print(" ", end="")

        # Print hashes
        for k in range(1, i + 1):
            print("#", end="")

        # Move to the next line after each row
        print()


if __name__ == "__main__":
    main()
