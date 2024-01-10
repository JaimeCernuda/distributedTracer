#!/usr/bin/python3

import json
import glob
import os
import argparse

def parse_args():
    parser = argparse.ArgumentParser(description="Merge JSON files from a specified directory.")
    parser.add_argument("-d", "--directory", default=".",
                        help="Directory containing the trace files (default is current directory)")
    return parser.parse_args()

def main():
    args = parse_args()

    file_pattern = os.path.join(args.directory, 'trace_*.json')
    file_names = glob.glob(file_pattern)

    combined_data = []

    for file_name in file_names:
        with open(file_name, 'r') as file:
            data = json.load(file)
            combined_data.extend(data)

    output_file = os.path.join(args.directory, 'combined.json')
    with open(output_file, 'w') as file:
        json.dump(combined_data, file, indent=4)

    print(f"Combined file created at {output_file}")

if __name__ == "__main__":
    main()
