#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__
// common binary_search
template<class T>
int binary_search(const T A[], int n, const T &value)
{
    if (0 == n) return -1;
    int low = 0, high = n-1;
    while(low<=high)
    {
        int mid = low + ((high-low)>>1);
        if (A[mid] == value) 
            return mid;
        else if (A[mid] > value)
            high = mid-1;
        else
            low = mid+1;
    }
    return -1;
}

//find  first occur value
template<class T>
int binary_search_first_occur(const T A[], int n, const T& value)
{
    if (n == 0) return -1;
    int low = 0, high = n-1;
    while(low<high)
    {
        int mid = low + ((high-low)>>1);
        if (A[mid]>=value)high = mid;
        else
            low = mid+1;
    }
    if(A[low] == value) return low;
    return -1;
}

//find last occur value
template<class T>
int binary_search_last_occur(const T A[], int n, const T& value)
{
    if (n == 0) return -1;
    int low = 0, high = n-1;
    while(low<high-1)
    {
        int mid = low + ((high-low)>>1);
        if (A[mid]<=value)
            low = mid;
        else
            high = mid-1;
    }
    if (A[high] == value) return high;
    else if(A[low] == value) return low;
    return -1;
}

// find element less than value which is max
template<class T>
int less_max(const T A[], int n, const T& value)
{
    if (n == 0) return -1;
    int low = 0, high = n-1;
    while(low<=high)
    {
        int mid = low + ((high-low)>>1);
        if (A[mid]>=value)high = mid-1;
        else
            low = mid+1;
    }
    return low-1;
}

// find element large than value which is min
template<class T>
int greater_min(const T A[], int n, const T& value)
{
    if (n == 0) return -1;
    int low = 0, high = n-1;
    while(low<=high)
    {
        int mid = low+((high-low)>>1);
        if (A[mid]<=value)
            low = mid+1;
        else
            high = mid-1;
    }
    if(high<n-1) return high+1;
    return -1;
}



#endif 
