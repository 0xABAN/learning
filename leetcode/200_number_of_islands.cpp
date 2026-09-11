#include <vector>

using namespace std;

class Solution {
public:
 	int numIslands(vector<vector<char>>& grid) {
		/*
 		 * this is a bfs / dfs problem (either works)
		 * the constraint is that i start when i first identify a "1" 
		 * must flip all "1"s to "0"s globally. when all in one region are flipped, inc by 1
		 * */

		int ans = 0; 
		int m = grid.size(), n = grid[0].size(); 
		vector<pair<int, int>> dir{{0, 1}, {0, -1}, {1, 0}, {-1, 0}}; 

		auto dfs = [&grid, dir, m, n](auto&& self, int i, int j) -> int {
			// base case 
			if(i >= m || i < 0 || j >= n || j < 0 || grid[i][j] == '0') return 0; 
			
			grid[i][j] = '0'; 
			for(const auto& [x, y] : dir) {
				self(self, i+x, j+y); 	
			}
			
			return 1; 	 	
		}; 
		
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				if(grid[i][j] == '1') ans += dfs(dfs, i, j); 
			}
		}
		return ans;
	}
};
