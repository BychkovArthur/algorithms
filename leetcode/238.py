class Solution(object):
    def productExceptSelf(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        prefix = [0] * len(nums)
        suffix = [0] * len(nums)
        current_product = 1
        for i in range(len(nums)):
            current_product *= nums[i]
            prefix[i] = current_product

        current_product = 1
        for i in range(len(nums) - 1, -1, -1):
            current_product *= nums[i]
            suffix[i] = current_product
        
        print(prefix, suffix, sep='\n')
        
assert Solution().productExceptSelf([1,2,3,4]) == [24,12,8,6]