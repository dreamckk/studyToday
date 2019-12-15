class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        for(int i=0;i<k;++i) {
            int last=nums[nums.size()-1];
            for(int j=0;j<nums.size();++j) {
                int temp=nums[j];
                nums[j]=last;
                last=temp;
            }
        }
        
    }
};