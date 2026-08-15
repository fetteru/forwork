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
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
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
//快速排序
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
    shellSort(arr);
    for(int x : arr)
    {
        cout<<x<<" ";
    }
    cout<<endl;
    cout<<(check(arr)? "OK":"Wrong")<<endl;







}