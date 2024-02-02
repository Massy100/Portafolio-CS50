import csv
import sys


def read_csv(file_path):
    with open(file_path, "r") as file:
        reader = csv.DictReader(file)
        return list(reader)


def read_dna(file_path):
    with open(file_path, "r") as file:
        return file.read()


def find_match(csv_data, dna_sequence):
    for row in csv_data:
        name = row["name"]
        match = all(
            longest_match(dna_sequence, str_sequence) == int(row[str_sequence])
            for str_sequence in row.keys()
            if str_sequence != "name"
        )
        if match:
            return name

    return "No match"


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


def main():
    # Check for correct number of command-line arguments
    if len(sys.argv) != 3:
        print("Usage: python dna.py <CSV file> <DNA sequence file>")
        sys.exit(1)

    # Read CSV file into memory
    csv_file_path = sys.argv[1]
    csv_data = read_csv(csv_file_path)

    # Read DNA sequence into memory
    dna_file_path = sys.argv[2]
    dna_sequence = read_dna(dna_file_path)

    # Find a match in the CSV data
    result = find_match(csv_data, dna_sequence)

    # Print the result
    print(result)


if __name__ == "__main__":
    main()
