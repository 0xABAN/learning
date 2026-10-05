"""743. Network Delay Time (Medium).

https://leetcode.com/problems/network-delay-time/

You are given a network of ``n`` nodes, labeled from 1 to n. You are also
given a list of travel times ``times``, where ``times[i] = (u_i, v_i, w_i)``
means that a signal takes ``w_i`` time units to travel from node ``u_i`` to
node ``v_i``.

A signal is sent from a given node ``k``. Return the minimum time it takes for
all the n nodes to receive the signal. If it is impossible for all nodes to
receive the signal, return -1.

Examples:

Example 1:
Input: times = [[2, 1, 1], [2, 3, 1], [3, 4, 1]], n = 4, k = 2
Output: 2

Example 2:
Input: times = [[1, 2, 1]], n = 2, k = 1
Output: 1

Example 3:
Input: times = [[1, 2, 1]], n = 2, k = 2
Output: -1

Constraints:

- 1 <= k <= n <= 100
- 1 <= times.length <= 6000
- ``times[i].length == 3``
- 1 <= u_i, v_i <= n
- u_i != v_i
- 0 <= w_i <= 100
- All the pairs ``(u_i, v_i)`` are unique. (The pairs are not necessarily
  given in sorted order.)

graph = {
    1: []
    2: [(1, 1), (1, 3)]
    3: [(1, 4)]
    4: []
}
q = [(0, 2)]
arrivals = [inf] * n 

(store the best known arrival at each point in time)

next -> [(1, 1), (1, 3)]

"""

from collections import defaultdict
from heapq import * 

class Solution:
    def networkDelayTime(
        self, times: list[list[int]], n: int, k: int
    ) -> int:
    
        graph = defaultdict(list)
        for u, v, w in times: 
            graph[u].append((w, v))
            
        arrivals = [float('inf')] * (n + 1) 
        arrivals[k] = 0
        q = [(0, k)]
        
        while q: 
            curr_w, node = heappop(q)
            
            if curr_w > arrivals[node]: 
                continue 
            
            for new_w, new_node in graph[node]: 
                total_w = curr_w + new_w 
                
                if total_w < arrivals[neighbor]: 
                    arrivals[neighbor] = total_w 
                    heappush(q, (total_w, new_node))
            
        for node in range(1, n+1): 
            if arrivals[node] == float('inf'): 
                return -1

        return max(arrivals)
             

def main() -> None:
    solution = Solution()

    assert solution.networkDelayTime(
        [[2, 1, 1], [2, 3, 1], [3, 4, 1]], 4, 2
    ) == 2
    assert solution.networkDelayTime([[1, 2, 1]], 2, 1) == 1
    assert solution.networkDelayTime([[1, 2, 1]], 2, 2) == -1
    assert solution.networkDelayTime([[1, 2, 0]], 2, 1) == 0
    assert solution.networkDelayTime([[1, 2, 1], [2, 3, 1]], 3, 1) == 2


if __name__ == "__main__":
    main()
