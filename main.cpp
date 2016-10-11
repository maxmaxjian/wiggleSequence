#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class solution {
  public:
    int wiggleMaxLength(const std::vector<int> & nums) {
        // std::vector<int>::const_iterator it;
        // for (it = nums.begin(); it != nums.end(); ++it)
        //     if (!isWiggle(nums.begin(), it))
        //         break;
        // return std::distance(nums.begin(), it);
        vector<vector<int>> paths_incr = getSeq(nums, 0, true);
        std::cout << "first increasing:" << std::endl;
        for (auto path : paths_incr)
            std::for_each(path.begin(), path.end(), [](int i){std::cout << i << " ";});
        std::cout << std::endl;
        std::cout << "first decreasing:" << std::endl;
        vector<vector<int>> paths_decr = getSeq(nums, 0, false);
        for (auto path : paths_decr)
            std::for_each(path.begin(), path.end(), [](int i){std::cout << i << " ";});
        std::cout << std::endl;
        return std::max(paths_incr.front().size(), paths_decr.front().size());
    }

  private:
    vector<vector<int>> getSeq(const vector<int> & nums, size_t curr, bool increasing) {
        vector<vector<int>> result;
        if (curr == nums.size()-1)
            result.push_back(vector<int>{nums[curr]});
        else {
            auto next = getNext(nums, curr, increasing);
            if (next.empty())
                result.push_back(vector<int>{nums[curr]});
            else {
                vector<vector<int>> cands;
                for (auto nx : next) {
                    auto temp = getSeq(nums, nx, !increasing);
                    for (auto tmp : temp) {
                        tmp.insert(tmp.begin(), nums[curr]);
                        cands.push_back(tmp);
                    }
                }
                size_t idx = 0;
                for (size_t i = idx+1; i < cands.size(); ++i)
                    if (cands[i].size() > cands[idx].size())
                        idx = i;
                result.push_back(cands[idx]);
            }
        }
        return result;
    }

    vector<size_t> getNext(const vector<int> & nums, size_t curr, bool increasing) {
        vector<size_t> next;
        if (increasing) {
            for (size_t i = curr+1; i < nums.size(); ++i)
                if (nums[i] > nums[curr])
                    next.push_back(i);
        }
        else {
            for (size_t i = curr+1; i < nums.size(); ++i)
                if (nums[i] < nums[curr])
                    next.push_back(i);
        }
        return next;
    }
    
    
    template<typename InputIterator>
    bool isWiggle(InputIterator first, InputIterator last) {
        if (first == last)
            return true;
        else {
            bool incrs =  *first < *(first+1) ? true : false;
            first++;
            if (first == last)
                return true;
            else {
                while (first+1 != last) {
                    if (incrs && *first > *(first+1)) {
                        incrs = false;
                        first++;
                    }
                    else if (!incrs && *first < *(first+1)) {
                        incrs = true;
                        first++;
                    }
                    else
                        break;
                }
                if (first+1 == last)
                    return true;
                return false;
            }
        }
    }
};

int main() {
    std::vector<int> nums{1,7,4,9,2,5};
    // std::vector<int> nums{1,17,5,10,13,15,10,5,16,8};
    // std::vector<int> nums{1,2,3,4,5,6,7,8,9};
    
    solution soln;
    int res = soln.wiggleMaxLength(nums);
    std::cout << "The maximum length of wiggle sequence is:\n";
    std::cout << res << std::endl;
}
