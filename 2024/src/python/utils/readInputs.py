
def parse_input(file_path: str) -> list[str]:
  """Reads the input file and returns a list of lines."""
  with open(file_path, "r") as file:
    return file.read().strip().splitlines()