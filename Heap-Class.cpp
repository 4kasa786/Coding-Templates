// Implementation of Max Heap
// This is a max-Heap implementation in c++ using an array.
class MaxHeap
{
    int *arr;
    int size;       // total elements in the heap
    int total_size; // total size of the heap

public:
    MaxHeap(int n)
    {
        arr = new int[n];
        size = 0;
        total_size = n;
    }

    // insert into the heap
    void insert(int val)
    {
        // if heap size is available or not
        if (size == total_size)
        {
            cout << "Heap is full, cannot insert " << val << endl;
            return;
        }
        arr[size] = val;  // insert the value at the end of the heap
        int index = size; // index of the newly inserted element
        size++;

        // compare with parent and swap if necessary

        int parent = (index - 1) / 2;
        while (index > 0 && arr[parent] < arr[index])
        {
            swap(arr[parent], arr[index]);
            index = parent;           // move to the parent index
            parent = (index - 1) / 2; // update the parent index
        }

        cout << "Inserted " << val << " into the heap." << endl;
    }

    void printHeap()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }

    void Heapify(int index)
    {
        int largest = index;
        int leftChild = 2 * index + 1;  // left child index
        int rightChild = 2 * index + 2; // right child index

        // largest will store the index of the largest element
        // which is greater between the parent , left child and right child

        if (leftChild < size && arr[leftChild] > arr[largest])
        {
            largest = leftChild; // update largest if left child is greater
        }
        if (rightChild < size && arr[rightChild] > arr[largest])
        {
            largest = rightChild; // update largest if right child is greater
        }

        if (largest != index)
        {
            swap(arr[index], arr[largest]); // swap the parent with the largest child
            Heapify(largest);               // recursively heapify the affected subtree
        }
    }

    void Delete()
    {
        if (size == 0)
        {
            cout << "heap underflow, cannot delete" << endl;
            return;
        }
        cout << "Deleted " << arr[0] << " from the heap." << endl;
        arr[0] = arr[size - 1];
        size--; // remove the last element

        if (size == 0)
            return;

        // heapify the root element
        Heapify(0); // start heapifying from the root element
    }

    ~MaxHeap()
    {
        delete[] arr; // free the allocated memory
    }
};

// Implementation of Min-Heap
// This is a min-Heap implementation in c++ using an array.
class MinHeap
{
public:
    int *arr;
    int size;       // total elements in the heap
    int total_size; // total size of the heap

    MinHeap(int n)
    {
        // n is the total size of the heap
        arr = new int[n];
        // initialize the heap with size 0
        size = 0;
        total_size = n;
    }

    void insert(int val)
    {
        size++;
        if (size > total_size)
        {
            cout << "Heap is full, cannot insert" << "\n";
            return;
        }

        arr[size - 1] = val;          // insert the value at the end of the heap
        int index = size - 1;         // index of the newly inserted element
        int parent = (index - 1) / 2; // parent index of the newly inserted element
        while (index > 0 && arr[parent] > arr[index])
        {
            swap(arr[parent], arr[index]); // swap the parent with the newly inserted element
            index = parent;                // move to the parent index
            parent = (index - 1) / 2;      // update the parent index
        }

        // after the loop ends , the newly inserted element will be at the correct position
    }

    void Heapify(int index)
    {
        int smallest = index;           // index of the smallest element
        int leftChild = 2 * index + 1;  // left child index
        int rightChild = 2 * index + 2; // right child index

        // smallest will store the index of the smallest element
        if (leftChild < size && arr[leftChild] < arr[smallest])
        {
            smallest = leftChild; // update smallest if left child is smaller
        }
        if (rightChild < size && arr[rightChild] < arr[smallest])
        {
            smallest = rightChild; // update smallest if right child is smaller
        }
        // after this we will have the index of the smallest element
        if (smallest != index) // this means that the smallest element is not the parent
        {
            swap(arr[index], arr[smallest]); // swap the parent with the smallest child
            index = smallest;                // move to the smallest index
            Heapify(index);                  // recursively heapify the affected subtree
        }
    }

    void Delete()
    {
        // here delete means deleting the root element of the heap
        // or top element

        if (size == 0)
        {
            cout << "Heap underflow, cannot delete" << "\n";
            return;
        }

        arr[0] = arr[size - 1]; // replace the root element with the last element
        size--;                 // remove the last element
        if (size == 0)
            return; // if the heap is empty, return
        Heapify(0); // heapify the root element
    };

    void printHeap()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
};

void Heapify(vector<int> &arr, int index, int n)
{
    int largest = index;            // index of the largest element
    int leftChild = 2 * index + 1;  // left child index
    int rightChild = 2 * index + 2; // right child index

    if (leftChild < n && arr[leftChild] > arr[largest])
    {
        largest = leftChild; // update largest if left child is greater
    }
    if (rightChild < n && arr[rightChild] > arr[largest])
    {
        largest = rightChild; // update largest if right child is greater
    }

    if (largest != index) // means that the largest element is not the parent
    {
        swap(arr[index], arr[largest]); // swap the parent with the largest child
        // largest now contains the index of the largest element
        Heapify(arr, largest, n); // recursively heapify the affected subtree
    }
}

void BuildMaxHeap(vector<int> &arr, int n)
{
    // step down approach
    // start with the n/2 - 1 index and go to 0 index
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        Heapify(arr, i, n); // heapify the subtree rooted at index i
    }
}

void printVector(const vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void sortArray(vector<int> &arr)
{
    int n = arr.size();

    for (int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]); // swap the root element with the last element
        Heapify(arr, 0, i);   // heapify the root element
    }
}
