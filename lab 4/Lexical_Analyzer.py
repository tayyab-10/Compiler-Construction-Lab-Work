import threading
import time
import re

# ===============================
# Global Buffers and Flags
# ===============================
BUFFER_SIZE = 100
buffer_a = ""
buffer_b = ""
active_buffer = 'A'
buffer_lock = threading.Lock()
buffer_filled = {'A': False, 'B': False}
stop_flag = False


# ===============================
# Function: Lexical Analyzer
# ===============================
def lexical_analyzer(code):
    """
    Simple lexical analyzer using regex patterns.
    Detects keywords, identifiers, numbers, and operators.
    """
    tokens = []
    token_specification = [
        ('KEYWORD',   r'\b(if|else|int|float|bool|return|while|for|class|program|void|print|read|final|new)\b'),
        ('IDENTIFIER', r'\b[A-Za-z_]\w*\b'),
        ('NUMBER',     r'\b\d+(\.\d+)?\b'),
        ('OPERATOR',   r'[+\-*/=<>!%]+'),
        ('SEPARATOR',  r'[;,\(\)\{\}\[\]]'),
        ('CHAR_CONST', r"'.'"),
        ('WHITESPACE', r'\s+'),
        ('UNKNOWN',    r'.')
    ]
    combined = '|'.join(f'(?P<{name}>{pattern})' for name, pattern in token_specification)

    for match in re.finditer(combined, code):
        kind = match.lastgroup
        value = match.group()
        if kind != 'WHITESPACE':  # ignore spaces
            tokens.append((kind, value))
    return tokens


# ===============================
# Producer Thread: Reads Source File
# ===============================
def producer():
    global buffer_a, buffer_b, active_buffer, stop_flag

    try:
        with open("source.mj", "r") as f:  # updated filename
            while not stop_flag:
                chunk = f.read(BUFFER_SIZE)
                if not chunk:  # EOF
                    stop_flag = True
                    break

                with buffer_lock:
                    if active_buffer == 'A':
                        buffer_a = chunk
                        buffer_filled['A'] = True
                        active_buffer = 'B'
                    else:
                        buffer_b = chunk
                        buffer_filled['B'] = True
                        active_buffer = 'A'

                # Allow consumer to catch up
                time.sleep(0.3)

    except FileNotFoundError:
        print("Error: source.mj file not found.")
        stop_flag = True


# ===============================
# Consumer Thread: Processes Tokens
# ===============================
def consumer():
    global buffer_a, buffer_b, stop_flag

    with open("tokens.txt", "w") as out:
        while not stop_flag or buffer_filled['A'] or buffer_filled['B']:
            with buffer_lock:
                if buffer_filled['A']:
                    data = buffer_a
                    buffer_filled['A'] = False
                elif buffer_filled['B']:
                    data = buffer_b
                    buffer_filled['B'] = False
                else:
                    data = ""

            if data:
                tokens = lexical_analyzer(data)
                for ttype, val in tokens:
                    out.write(f"{ttype}: {val}\n")
                    print(f"{ttype}: {val}")
            else:
                time.sleep(0.2)  # brief wait if no data to process


# ===============================
# Main Program
# ===============================
if __name__ == "__main__":  # fixed correct Python syntax
    print("Lexical Analyzer with Double Buffering (source.mj)")

    # Start threads
    t1 = threading.Thread(target=producer)
    t2 = threading.Thread(target=consumer)

    t1.start()
    t2.start()

    # Wait for threads to finish
    t1.join()
    t2.join()

    print("\n=== Tokenization Completed! Check tokens.txt ===")
