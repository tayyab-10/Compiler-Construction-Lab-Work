#AVL TREE

class AVLNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left = None
        self.right = None
        self.height = 1


class AVLTreeSymbolTable:
    def __init__(self):
        self.root = None

    def height(self, node):
        return node.height if node else 0

    def balance(self, node):
        return self.height(node.left) - self.height(node.right)

    def right_rotate(self, y):
        x = y.left
        T2 = x.right

        x.right = y
        y.left = T2

        y.height = max(self.height(y.left), self.height(y.right)) + 1
        x.height = max(self.height(x.left), self.height(x.right)) + 1

        return x

    def left_rotate(self, x):
        y = x.right
        T2 = y.left

        y.left = x
        x.right = T2

        x.height = max(self.height(x.left), self.height(x.right)) + 1
        y.height = max(self.height(y.left), self.height(y.right)) + 1

        return y

    def _insert(self, node, key, value):
        if not node:
            return AVLNode(key, value)

        if key < node.key:
            node.left = self._insert(node.left, key, value)
        elif key > node.key:
            node.right = self._insert(node.right, key, value)
        else:
            node.value = value
            return node

        node.height = 1 + max(self.height(node.left), self.height(node.right))
        balance = self.balance(node)

        if balance > 1 and key < node.left.key:
            return self.right_rotate(node)
        if balance < -1 and key > node.right.key:
            return self.left_rotate(node)
        if balance > 1 and key > node.left.key:
            node.left = self.left_rotate(node.left)
            return self.right_rotate(node)
        if balance < -1 and key < node.right.key:
            node.right = self.right_rotate(node.right)
            return self.left_rotate(node)

        return node

    def put(self, key, value):
        self.root = self._insert(self.root, key, value)

    def get(self, key):
        curr = self.root
        while curr:
            if key == curr.key:
                return curr.value
            curr = curr.left if key < curr.key else curr.right   
        return None

    def _inorder(self, node, result):
        if node:
            self._inorder(node.left, result)
            result.append((node.key, node.value))
            self._inorder(node.right, result)

    def print_table(self):
        result = []
        self._inorder(self.root, result)
        if not result:
            print("Symbol table is empty")
        else:
            print("\n{:<20} {:<20}".format("Identifier", "Type"))
            print("-" * 40)
            for key, value in result:
                print("{:<20} {:<20}".format(key, value))


#RED-BLACK TREE

RED = True
BLACK = False


class RBNode:
    def __init__(self, key, value, color=RED):
        self.key = key
        self.value = value
        self.color = color
        self.left = None
        self.right = None


class RedBlackTreeSymbolTable:
    def __init__(self):
        self.root = None

    def is_red(self, node):
        return node.color == RED if node else False

    def left_rotate(self, h):
        x = h.right
        h.right = x.left
        x.left = h
        x.color = h.color
        h.color = RED
        return x

    def right_rotate(self, h):
        x = h.left
        h.left = x.right
        x.right = h
        x.color = h.color
        h.color = RED
        return x

    def flip_colors(self, h):
        h.color = RED
        h.left.color = BLACK
        h.right.color = BLACK

    def _insert(self, h, key, value):
        if not h:
            return RBNode(key, value)

        if key < h.key:
            h.left = self._insert(h.left, key, value)
        elif key > h.key:
            h.right = self._insert(h.right, key, value)
        else:
            h.value = value

        if self.is_red(h.right) and not self.is_red(h.left):
            h = self.left_rotate(h)
        if self.is_red(h.left) and self.is_red(h.left.left):
            h = self.right_rotate(h)
        if self.is_red(h.left) and self.is_red(h.right):
            self.flip_colors(h)

        return h

    def put(self, key, value):
        self.root = self._insert(self.root, key, value)
        self.root.color = BLACK

    def get(self, key):
        curr = self.root
        while curr:
            if key == curr.key:
                return curr.value
            curr = curr.left if key < curr.key else curr.right
        return None

    def _inorder(self, node, result):
        if node:
            self._inorder(node.left, result)
            result.append((node.key, node.value))
            self._inorder(node.right, result)

    def print_table(self):
        result = []
        self._inorder(self.root, result)
        if not result:
            print("Symbol table is empty")
        else:
            print("\n{:<20} {:<20}".format("Identifier", "Type"))
            print("-" * 40)
            for key, value in result:
                print("{:<20} {:<20}".format(key, value))


#SPLAY TREE

class SplayNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left = None
        self.right = None


class SplayTreeSymbolTable:
    def __init__(self):
        self.root = None

    def right_rotate(self, x):
        y = x.left
        x.left = y.right
        y.right = x
        return y

    def left_rotate(self, x):
        y = x.right
        x.right = y.left
        y.left = x
        return y

    def splay(self, root, key):
        if not root or root.key == key:
            return root

        if key < root.key:
            if not root.left:
                return root
            if key < root.left.key:
                root.left.left = self.splay(root.left.left, key)
                root = self.right_rotate(root)
            elif key > root.left.key:
                root.left.right = self.splay(root.left.right, key)
                if root.left.right:
                    root.left = self.left_rotate(root.left)
            return self.right_rotate(root) if root.left else root

        else:
            if not root.right:
                return root
            if key > root.right.key:
                root.right.right = self.splay(root.right.right, key)
                root = self.left_rotate(root)
            elif key < root.right.key:
                root.right.left = self.splay(root.right.left, key)
                if root.right.left:
                    root.right = self.right_rotate(root.right)
            return self.left_rotate(root) if root.right else root

    def put(self, key, value):
        if not self.root:
            self.root = SplayNode(key, value)
            return

        self.root = self.splay(self.root, key)

        if key == self.root.key:
            self.root.value = value
            return

        new_node = SplayNode(key, value)
        if key < self.root.key:
            new_node.right = self.root
            new_node.left = self.root.left
            self.root.left = None
        else:
            new_node.left = self.root
            new_node.right = self.root.right
            self.root.right = None

        self.root = new_node

    def get(self, key):
        self.root = self.splay(self.root, key)
        return self.root.value if self.root and self.root.key == key else None

    def _inorder(self, node, result):
        if node:
            self._inorder(node.left, result)
            result.append((node.key, node.value))
            self._inorder(node.right, result)

    def print_table(self):
        result = []
        self._inorder(self.root, result)
        if not result:
            print("Symbol table is empty")
        else:
            print("\n{:<20} {:<20}".format("Identifier", "Type"))
            print("-" * 40)
            for key, value in result:
                print("{:<20} {:<20}".format(key, value))


#MAIN DRIVER CODE

def main():
    print("=" * 50)
    print("SYMBOL TABLE IMPLEMENTATION")
    print("=" * 50)
    
    print("\nChoose Symbol Table Implementation:")
    print("1. AVL Tree")
    print("2. Red-Black Tree")
    print("3. Splay Tree")
    
    choice = input("\nEnter your choice (1-3): ")
    
    if choice == '1':
        print("\n--- AVL TREE SYMBOL TABLE ---")
        st = AVLTreeSymbolTable()
    elif choice == '2':
        print("\n--- RED-BLACK TREE SYMBOL TABLE ---")
        st = RedBlackTreeSymbolTable()
    elif choice == '3':
        print("\n--- SPLAY TREE SYMBOL TABLE ---")
        st = SplayTreeSymbolTable()
    else:
        print("Invalid choice! Defaulting to AVL Tree.")
        st = AVLTreeSymbolTable()
    
    while True:
        print("\n" + "=" * 50)
        print("Operations:")
        print("1. Insert identifier")
        print("2. Search identifier")
        print("3. Print symbol table")
        print("4. Exit")
        
        op = input("\nEnter operation (1-4): ")
        
        if op == '1':
            identifier = input("Enter identifier name: ")
            data_type = input("Enter data type: ")
            st.put(identifier, data_type)
            print(f"✓ Inserted '{identifier}' with type '{data_type}'")
            
        elif op == '2':
            identifier = input("Enter identifier to search: ")
            result = st.get(identifier)
            if result:
                print(f"✓ Found: '{identifier}' -> Type: '{result}'")
            else:
                print(f"✗ Identifier '{identifier}' not found")
                
        elif op == '3':
            st.print_table()
            
        elif op == '4':
            print("\nExiting... Goodbye!")
            break
            
        else:
            print("Invalid operation! Please try again.")


if __name__ == "__main__":
    main()
