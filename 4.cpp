//4. Median of Two Sorted Array
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int middle = (n1 + n2) / 2;
        if(n1 ==0){
            if(n2%2==0) return (nums2[middle]+nums2[middle-1])/2.0 ;
            else return nums2[middle];
        }
        if(n2 ==0){
            if(n1%2==0) return (nums1[middle]+nums1[middle-1])/2.0 ;
            else return nums1[middle];
        }
        int i = 0, j = 0, m1, m2;
        for (int cont=0; cont<= middle; cont++) {
            m2 = m1; 
            if (i<n1 && (j >= n2 || nums1[i] <= nums2[j])) {
                m1 = nums1[i];
                i++;
            } else {
                m1 = nums2[j];
                j++;
            }
        }
        if ((n1 + n2) % 2 == 0)  return (m1 + m2) / 2.0;
        else return m1; 
    }
};
