class FileSystem:
  def __init__(self):
    self.root = {
      "children": {},
      "isFile": False,
      "content": None,
    }

  def get_path_parts(self, path: str):
    parts = path.split("/")
    return [part for part in parts if part]
  
  def create(self, path: str, isFile: bool, content: str = ""):
    parts = self.get_path_parts(path)
    if not parts:
      raise ValueError("Path cannot be empty")
    
    node = self.root

    for i, part in enumerate(parts):
      if part not in node['children']:
        node['children'][part] = {
          "children": {},
          "isFile": False,
          "content": None,
        }
      
      node = node['children'][part]

      if isFile and i == len(parts) - 1:
        node['isFile'] = True
        node['content'] = content
    
  
  def list_folder(self, path: str):
    parts = self.get_path_parts(path)
    node = self.root

    for part in parts:
      if part not in node['children']:
        return []
      node = node['children'][part]

    if node['isFile']:
      return []
    
    return sorted(node['children'].keys())
  

fs = FileSystem()
fs.create("/a/b/c", isFile=False)
fs.create("/a/b/d.txt", isFile=True, content="Hello, World!")
print(fs.list_folder("/a/b"))  # Output: ['c', 'd.txt']