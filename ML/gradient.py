import seaborn as sns

def func(x):
    return (x + 3)**2
def derivative(x):
    return 2 * (x + 3)

gd = []

def gradient_descent(starting_x, learning_rate, num_iterations):
    x = starting_x
    gd.append(starting_x)

    for i in range(num_iterations):
        grad = derivative(x)
        x = x - learning_rate * grad
        gd.append(x)
        print(f"Iteration {i+1}: x = {x}, f(x) = {func(x)}")
    return x

starting_x = 2
learning_rate = 0.1
num_iterations = 50

min_x = gradient_descent(starting_x, learning_rate, num_iterations)
print(f"Local minimum occurs at x = {min_x}")
sns.scatterplot(x=range(len(gd)), y=gd)