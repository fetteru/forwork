#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void swap(int& a,int& b)
{
    int t = a;
    a = b;
    b = t;
}
//冒泡排序,升序
void bubbleSort(vector<int>& arr)
{
    int len = arr.size();
    for(int i=0;i<len-1;i++)
    {   bool swapped = false;//设置提前结束标志
        for(int j=0;j<len-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr[j],arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped)break;//本轮无交换，已经有序
    }
}
//选择排序，每轮找最小
void selectSort(vector<int>& arr)
{
   int len = arr.size();
   for(int i = 0;i<len-1;i++)
   {
    for(int j = i+1;j<len;j++)
    {
        if(arr[i]>arr[j])
        {
            swap(arr[i],arr[j]);
        }
    }
   }
}
//插入排序，类比整理扑克牌
void insertSort(vector<int>& arr)
{
    int len = arr.size();
    for(int i=1;i<len;i++)
    {   
        int key = arr[i];
        int j = i-1;
        while(j>=0&&arr[j]>key)
        {
            arr[j+1] = arr[j];//向右移动一位
            j--;//向前面检查
        }
        arr[j+1]=key;
    }
}
//希尔排序,设置gap，进化版插入
void shellSort(vector<int>& arr)
{
    int len = arr.size();
    int gap = len/2;
    while(gap!=0)
    {
       for(int i=gap;i<len;i++)
        {
        int key = arr[i];
        int j = i-gap;
        while(j>=0&&arr[j]>key)
        {
            arr[j+gap] = arr[j];
            j = j-gap;
        }
        arr[j+gap] = key;
        }
        gap=gap/2;
    }
}
//归并排序
int depth = 0;

void merge(vector<int>& arr,int l,int m,int r)//合并
{
    vector<int> B(r-l+1);
    int i=l,j=m+1;
    int k = 0;
    for(;i<=m&&j<=r;k++)
    {
        if(arr[i]<=arr[j])
        {
            B[k]=arr[i++];
        }
        else{
            B[k]=arr[j++];
        }
    }
    while(i<=m)B[k++]=arr[i++];
    while(j<=r)B[k++]=arr[j++];
    for(int s=l;s<=r;s++)
    {
        arr[s] = B[s-l];
    }

 
}
void mergeSort(vector<int>& arr,int l,int r)
{
    cout << string(depth*2,' ') << "进入  sort(" << l << "," << r << ")\n";
    if(l>=r)
    {
        cout << string(depth*2,' ') << "返回  [" << l << "," << r << "] 单元素\n";
        return;
    }
    int m = l+(r-l)/2;
    depth++;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    depth--;
    if(arr[m]<=arr[m+1])
    {
        cout << string(depth*2,' ') << "跳过merge [" << l << "," << r << "]\n";
        return;
    }//两半已各自有序且衔接有序，跳过合并
    merge(arr,l,m,r);
    cout << string(depth*2,' ') << "完成  [" << l << "," << r << "] m=" << m << "\n";
}
void mergeSort(vector<int>& arr)
{
    if(!arr.empty())
       mergeSort(arr,0,(int)arr.size()-1);
}
//快速排序
//划分：partition以arr[r]为基准
int partition(vector<int>& arr,int l,int r)
{
    int pivot = arr[r];
    int i = l-1;//i是“小于区”的右边界
    for(int j=l;j<r;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[r]);//将pivot放到中间
    return i+1;
}
void quickSort(vector<int>& arr,int l,int r)
{
    if(l>=r)return;
    int p = partition(arr,l,r);
    quickSort(arr,l,p-1);
    quickSort(arr,p+1,r);
}
void quickSort(vector<int>& arr)
{
    if(!arr.empty())
    {
        int l=0,r=arr.size()-1;
        quickSort(arr,l,r); 
    }
}

//堆排序




bool check(vector<int> arr)
{
    vector<int> stdAns= arr;
    sort(stdAns.begin(),stdAns.end());//标准库参照
    return arr==stdAns;
}

int main()
{
    vector<int> arr={2,3,6,7,61,34,45,11,85,77,1,9,18};
    selectSort(arr);
    for(int x : arr)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<(check(arr)? "OK":"Wrong")<<endl;







}