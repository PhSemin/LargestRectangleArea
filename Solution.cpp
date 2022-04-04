#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights)
    {
        std::stack<int> topIndices;
        
        auto greaterThanTop = [&](int index)
        {
            return topIndices.empty() or heights[topIndices.top()] <= heights[index];
        };
        
        auto getTopAreaUntil = [&](int current)
        {
            int topHeight = heights[topIndices.top()];
            topIndices.pop();
            
            int from = topIndices.empty() ? 0 : topIndices.top() + 1;
            
            int length = current - from + 1;
            
            return topHeight * length;
        };
        
        int i, maxArea = -1;
        
        for (i = 0; i < heights.size(); i++)
        {
            while (not greaterThanTop(i))
            {
                maxArea = std::max(getTopAreaUntil(i - 1), maxArea);
            }
            
            if (greaterThanTop(i)) { topIndices.push(i); }
        }
        
        while (not topIndices.empty())
        {
            maxArea = std::max(getTopAreaUntil(i - 1), maxArea);
        }
        
        return maxArea;
    }
};

int main()
{
	std::vector<int> heights = {2, 1, 5, 6, 2, 3};
	
	std::string success = Solution().largestRectangleArea(heights) == 10 ? "GOOD" : "BAD";
	
	std::cout << success << std::endl;
}
