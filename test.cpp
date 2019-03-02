#include <iostream>

using namespace std;

void findMax(float arr[], int out_index[], const size_t &size)
{
    // Returns maximum number index in the array of doubles
    for (size_t i = 0; i < size; i++)
    {
        int max_index = 0;
        for (size_t j = i + 1; j < size; j++)
            if (arr[max_index] <= arr[j] && arr[max_index] != -1)
                max_index = j;
        out_index[i] = max_index;
        arr[max_index] = -1;    
    }
}

int main()
{
    float arr[20] = {0.67, 0.38, 0.75, 0.92, 0, 0.02, 0.79, 0.44, 0.47, 0.02,
                     0.55, 0.63, 0.77, 0.95, 0.52, 0.37, 0.81, 0.73, 0.59};
    float tar[20];
    for (int i = 0; i < 20; i++)
        tar[i] = arr[i];
    int output[20];
    findMax(arr, output, 20);
    for (int i = 0; i < 20; i++)
        cout << tar[output[i]] << " ";
}