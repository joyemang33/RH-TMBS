import numpy as np

from algorithms.subroutines.commons import evaluate_objective_function


def print_input(dataset, algorithm):
    0

def print_end_algorithm(runtime, x, signed_graph, beta=np.nan, threshold=np.nan):
    community_p1 = {node for node, element in enumerate(x) if element == 1}
    community_m1 = {node for node, element in enumerate(x) if element == -1}
    
    print(len(community_p1))
    print(str(str(community_p1).replace('set([', '').replace('])', '').replace(',', '')))
    print(len(community_m1))
    print(str(str(community_m1).replace('set([', '').replace('])', '').replace(',', '')))
