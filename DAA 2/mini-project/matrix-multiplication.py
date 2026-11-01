import numpy as np
import threading
import time
from concurrent.futures import ThreadPoolExecutor

def generate_matrix(rows, cols):
    return np.random.rand(rows, cols)

def standard_matrix_multiply(A, B):
    return np.dot(A, B)

def multiply_row(A, B, result, row):
    result[row] = np.dot(A[row], B)

def thread_per_row_matrix_multiply(A, B):
    result = np.zeros((A.shape[0], B.shape[1]))
    threads = []
    for i in range(A.shape[0]):
        thread = threading.Thread(target=multiply_row, args=(A, B, result, i))
        threads.append(thread)
        thread.start()
    for thread in threads:
        thread.join()
    return result

def multiply_cell(A, B, result, row, col):
    result[row, col] = np.dot(A[row], B[:, col])

def thread_per_cell_matrix_multiply(A, B):
    result = np.zeros((A.shape[0], B.shape[1]))
    with ThreadPoolExecutor(max_workers=A.shape[0] * B.shape[1]) as executor:
        for i in range(A.shape[0]):
            for j in range(B.shape[1]):
                executor.submit(multiply_cell, A, B, result, i, j)
    return result

def time_function(func, *args):
    start_time = time.time()
    result = func(*args)
    end_time = time.time()
    return result, end_time - start_time

def run_comparison(sizes):
    print(f"{'Size':>10} {'Standard':>15} {'Thread/Row':>15} {'Thread/Cell':>15}")
    print("-" * 60)
    
    for size in sizes:
        A = generate_matrix(size, size)
        B = generate_matrix(size, size)
        
        _, standard_time = time_function(standard_matrix_multiply, A, B)
        _, row_time = time_function(thread_per_row_matrix_multiply, A, B)
        _, cell_time = time_function(thread_per_cell_matrix_multiply, A, B)
        
        print(f"{size:10d} {standard_time:15.6f} {row_time:15.6f} {cell_time:15.6f}")

if __name__ == "__main__":
    sizes = [10, 50, 100, 200]
    run_comparison(sizes)