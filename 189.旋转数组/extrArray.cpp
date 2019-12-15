class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len=nums.size();
        int arr[]={};
        for (int i=0;i<len;++i) {
            arr[(i+k)%len]=nums[i];
        }
        for (int j=0;j<len;++j) {
            nums[j]=arr[j];
        }
 
    }
};