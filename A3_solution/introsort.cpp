using namespace std;

void insertionSort(vector<int>& a, int l, int r) {
    for (int i = l + 1; i <= r; ++i) {
        int x = a[i];
        int j = i - 1;
        while (j >= l && a[j] > x) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = x;
    }
}

void heapSort(vector<int>& a, int l, int r) {
    make_heap(a.begin() + l, a.begin() + r + 1);
    sort_heap(a.begin() + l, a.begin() + r + 1);
}

void introsortUtil(vector<int>& a, int l, int r, int depth) {
    int size = r - l + 1;
    if (size <= 16) {
        insertionSort(a, l, r);
        return;
    }
    if (depth == 0) {
        heapSort(a, l, r);
        return;
    }
    int pivot = a[l + size / 2];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < pivot) ++i;
        while (a[j] > pivot) --j;
        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    if (l < j) introsortUtil(a, l, j, depth - 1);
    if (i < r) introsortUtil(a, i, r, depth - 1);
}

void introsort(vector<int>& a) {
    int depth = 2 * log2(a.size());
    introsortUtil(a, 0, (int)a.size() - 1, depth);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    introsort(a);
    for (int i = 0; i < n; ++i) {
        cout << a[i];
        if (i + 1 < n) cout << ' ';
    }
    cout << '\n';
}
