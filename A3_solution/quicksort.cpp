using namespace std;

void quicksort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int pivot = a[l + rand() % (r - l + 1)];
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
    if (l < j) quicksort(a, l, j);
    if (i < r) quicksort(a, i, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    srand(1);
    quicksort(a, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        cout << a[i];
        if (i + 1 < n) cout << ' ';
    }
    cout << '\n';
}
