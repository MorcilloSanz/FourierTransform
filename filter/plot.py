import numpy as np
import matplotlib.pyplot as plt


def read_data(file):
    with open(file, 'r') as file:
        linea = file.readline().strip()
        data = [float(valor) for valor in linea.split()]
    return np.array(data)


if __name__ == "__main__":
    
    # Read signals
    signal = read_data("sampled_signal.txt")
    filtered_signal = read_data("filtered_signal.txt")
    residues = signal - filtered_signal
    t = range(1, len(signal) + 1)

    # Plot
    fig, ax = plt.subplots()

    ax.plot(t, signal, label='signal')
    ax.plot(t, filtered_signal, label='filtered_signal')
    ax.plot(t, residues, label='residues')

    ax.set_title('signal = filtered_signal + residues')
    ax.set_xlabel('t')
    ax.set_ylabel('A')

    ax.legend()
    plt.show()
