/*
    1) Если m + n - нечётное, то ответ - одно число.
    2) Если m + n - чётно, то ответ - среднее между двумя числами.

                                                
*/

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // nums1 всегда больше или равен размеру nums2
        if (nums1.size() < nums2.size()) {
            swap(nums1, nums2);
        }
        long long int n = nums1.size();
        long long int m = nums2.size();
        bool is_even = (n + m + 1) % 2;
        long long int median_index = (m + n - 1) / 2;

        if (m == 0) {
            return is_even ? (nums1[median_index] + nums1[median_index + 1]) / 2.0 : nums1[median_index];
        }

        // Теперь у меня оба списка не пустые.
        // Надо обработать случай, когда у меня один из списков "полностью выше" другого.
        long long int l = 0;
        long long int r = m;
        while (l < r - 1) {
            // Сколько я возьму из nums2
            long long int mid = (l + r) / 2;
            // cout << "HERE " << mid << endl;
            // Сколько надо взять из nums1
            long long int k = median_index + 1 - mid;
            if (k != 0 && mid < m && nums1[k - 1] > nums2[mid]) {
                // cout << "HERE 123" << endl;
                l = mid;
            } else if (mid != 0 && k < n && nums2[mid - 1] > nums1[k]) {
                // cout << "HERE 345" << endl;
                r = mid;
            } else {
                l = mid;
                r = mid;
                break;
            }
        }
        // cout << l << ' ' << r << endl;
        nums1.push_back(1e9);
        nums2.push_back(1e9);
        long long int take_from_nums1 = median_index + 1 - l;
        long long int take_from_nums2 = l;
        // cout << take_from_nums1 << ' ' << take_from_nums2 << endl;

        if (
            (take_from_nums1 == 0 && nums2[take_from_nums2 - 1] <= nums1[0]) ||
            (take_from_nums1 > 0 && take_from_nums2 == 0 && nums1[take_from_nums1 - 1] <= nums2[0]) ||
            (take_from_nums1 > 0 && take_from_nums2 > 0 && nums1[take_from_nums1 - 1] <= nums2[take_from_nums2] && nums2[take_from_nums2 - 1] <= nums1[take_from_nums1])
            ) {
            int mx = 0;
            if (take_from_nums1 > 0 && take_from_nums2 > 0) {
                mx = max(nums1[take_from_nums1 - 1], nums2[take_from_nums2 - 1]);
            } else if (take_from_nums1 > 0) {
                mx = nums1[take_from_nums1 - 1];
            } else {
                mx = nums2[take_from_nums2 - 1];
            }
            int mn = min(nums1[take_from_nums1], nums2[take_from_nums2]);
            return !is_even ? mx : (mx + mn) / 2.0;
        }

        // cout << "HERE" << endl;

        take_from_nums1 = median_index + 1 - r;
        take_from_nums2 = r;

        // cout << take_from_nums1 << ' ' << take_from_nums2;

        int mx = 0;
        if (take_from_nums1 > 0 && take_from_nums2 > 0) {
            mx = max(nums1[take_from_nums1 - 1], nums2[take_from_nums2 - 1]);
        } else if (take_from_nums1 > 0) {
            mx = nums1[take_from_nums1 - 1];
        } else {
            mx = nums2[take_from_nums2 - 1];
        }
        int mn = min(nums1[take_from_nums1], nums2[take_from_nums2]);
        return !is_even ? mx : (mx + mn) / 2.0;

    }
};