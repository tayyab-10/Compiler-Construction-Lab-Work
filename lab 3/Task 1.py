import threading
import time

# --- Step 1: Define buffer settings ---
BUFFER_SIZE = 20
buffer_A = []
buffer_B = []
active_buffer = 'A'  # Start with buffer A

# Lock and condition for synchronization
buffer_lock = threading.Lock()
buffer_filled = threading.Condition(buffer_lock)

# Flag to stop the program gracefully
stop_program = False


# --- Step 2: Producer thread (fills the buffer) ---
def fill_buffer():
    global active_buffer, stop_program

    while not stop_program:
        # Ask user for input source code line
        user_input = input("\nEnter source code line (type 'q' to quit): ")

        if user_input.lower() == 'q':
            stop_program = True
            with buffer_filled:
                buffer_filled.notify_all()
            break

        # Acquire lock before writing to buffer
        with buffer_lock:
            current_buffer = buffer_A if active_buffer == 'A' else buffer_B
            current_buffer.extend(list(user_input + " "))

            # When buffer is full, signal consumer
            if len(current_buffer) >= BUFFER_SIZE:
                print(f"\n[Producer] {active_buffer} is full. Switching buffers...")
                active_buffer = 'B' if active_buffer == 'A' else 'A'
                buffer_filled.notify()  # Wake up consumer
        time.sleep(0.5)  # Simulate slight delay in input


# --- Step 3: Consumer thread (processes the buffer) ---
def process_data():
    global active_buffer

    while not stop_program:
        with buffer_filled:
            buffer_filled.wait(timeout=1)  # Wait until buffer is filled or timeout
            if stop_program:
                break

            inactive_buffer = buffer_B if active_buffer == 'A' else buffer_A

            if inactive_buffer:
                data = "".join(inactive_buffer).strip()
                words = data.split()
                print(f"\n[Consumer] Processing {len(words)} words from buffer...")
                print(f"Words: {words}")

                inactive_buffer.clear()  # Empty the buffer for reuse
        time.sleep(1)  # Simulate processing delay


# --- Step 4: Start threads ---
producer_thread = threading.Thread(target=fill_buffer)
consumer_thread = threading.Thread(target=process_data)

producer_thread.start()
consumer_thread.start()

producer_thread.join()
consumer_thread.join()

print("\nProgram exited gracefully.")
