#include <iostream>
#include <vector>

class solution {
  public:
    int wiggleMaxLength(const std::vector<int> & nums) {
        std::vector<int>::const_iterator it;
        for (it = nums.begin(); it != nums.end(); ++it)
            if (!isWiggle(nums.begin(), it))
                break;
        return std::distance(nums.begin(), it);
    }

  private:
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
    // std::vector<int> nums{1,7,4,9,2,5};
    std::vector<int> nums{1,17,5,10,13,15,10,5,16,8};
    
    solution soln;
    int res = soln.wiggleMaxLength(nums);
    std::cout << res << std::endl;
}
