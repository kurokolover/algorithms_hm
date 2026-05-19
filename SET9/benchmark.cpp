#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <stack>

static long long g_charComps = 0;
static std::mt19937 rng(42);

class StringGenerator {
    static constexpr char ALPHABET[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
        "0123456789!@#%:;^&*()-.";
    static constexpr int ALPHA_SIZE = 74;
    static constexpr int MIN_LEN    = 10;
    static constexpr int MAX_LEN    = 200;
    std::mt19937 rng_;
public:
    explicit StringGenerator(unsigned seed = 123) : rng_(seed) {}

    std::string randomString() {
        std::uniform_int_distribution<int> lenD(MIN_LEN, MAX_LEN);
        std::uniform_int_distribution<int> chrD(0, ALPHA_SIZE - 1);
        int len = lenD(rng_);
        std::string s(len, ' ');
        for (char& c : s) c = ALPHABET[chrD(rng_)];
        return s;
    }
    std::vector<std::string> randomArray(int n) {
        std::vector<std::string> arr(n);
        for (auto& s : arr) s = randomString();
        return arr;
    }
    std::vector<std::string> reverseSortedArray(int n) {
        auto arr = randomArray(n);
        std::sort(arr.begin(), arr.end(), std::greater<std::string>());
        return arr;
    }
    std::vector<std::string> nearlySortedArray(int n) {
        auto arr = randomArray(n);
        std::sort(arr.begin(), arr.end());
        int swaps = std::max(1, n / 200);
        std::uniform_int_distribution<int> idx(0, n - 1);
        for (int i = 0; i < swaps; ++i)
            std::swap(arr[idx(rng_)], arr[idx(rng_)]);
        return arr;
    }
};

bool cmpStr(const std::string& a, const std::string& b) {
    int mn = std::min(a.size(), b.size());
    for (int i = 0; i < mn; ++i) {
        ++g_charComps;
        if (a[i] != b[i]) return (unsigned char)a[i] < (unsigned char)b[i];
    }
    ++g_charComps;
    return a.size() < b.size();
}

int medianOf3(std::vector<std::string>& a, int lo, int hi) {
    int mid = (lo + hi) / 2;
    if (cmpStr(a[hi], a[lo])) std::swap(a[lo], a[hi]);
    if (cmpStr(a[mid], a[lo])) std::swap(a[lo], a[mid]);
    if (cmpStr(a[hi], a[mid])) std::swap(a[mid], a[hi]);
    return mid;
}
void qsort_(std::vector<std::string>& a, int lo, int hi) {
    if (lo >= hi) return;
    int pivIdx = medianOf3(a, lo, hi);
    std::swap(a[pivIdx], a[hi]);
    const std::string& piv = a[hi];
    int i = lo - 1, j = hi;
    while (true) {
        while (cmpStr(a[++i], piv));
        while (i < j && cmpStr(piv, a[--j]));
        if (i >= j) break;
        std::swap(a[i], a[j]);
    }
    std::swap(a[i], a[hi]);
    qsort_(a, lo, i - 1);
    qsort_(a, i + 1, hi);
}
void stdQuickSort(std::vector<std::string>& a) {
    if (a.size() > 1) qsort_(a, 0, (int)a.size() - 1);
}

void merge_(std::vector<std::string>& a, int lo, int mid, int hi) {
    std::vector<std::string> L(a.begin()+lo, a.begin()+mid+1);
    std::vector<std::string> R(a.begin()+mid+1, a.begin()+hi+1);
    int i=0, j=0, k=lo;
    while (i<(int)L.size() && j<(int)R.size()) {
        if (!cmpStr(R[j], L[i])) a[k++]=L[i++];
        else a[k++]=R[j++];
    }
    while (i<(int)L.size()) a[k++]=L[i++];
    while (j<(int)R.size()) a[k++]=R[j++];
}
void msort_(std::vector<std::string>& a, int lo, int hi) {
    if (lo>=hi) return;
    int mid=(lo+hi)/2;
    msort_(a,lo,mid); msort_(a,mid+1,hi);
    merge_(a,lo,mid,hi);
}
void stdMergeSort(std::vector<std::string>& a) {
    if (a.size()>1) msort_(a,0,(int)a.size()-1);
}

int computeLcp(const std::string& a, const std::string& b) {
    int len=std::min(a.size(),b.size());
    for (int i=0;i<len;++i) { ++g_charComps; if(a[i]!=b[i]) return i; }
    ++g_charComps; return len;
}
int lcpCompare(const std::string& a, const std::string& b, int lcp) {
    int mn=std::min((int)a.size(),(int)b.size());
    for (int i=lcp;i<mn;++i) {
        ++g_charComps;
        if ((unsigned char)a[i]!=(unsigned char)b[i])
            return (unsigned char)a[i]<(unsigned char)b[i]?-1:1;
    }
    if (a.size()==b.size()) return 0;
    return a.size()<b.size()?-1:1;
}
void lcpMerge(std::vector<std::string>& arr, int lo, int mid, int hi) {
    std::vector<std::string> L(arr.begin()+lo,arr.begin()+mid);
    std::vector<std::string> R(arr.begin()+mid,arr.begin()+hi);
    int i=0,j=0,k=lo,lcpL=0,lcpR=0;
    while (i<(int)L.size()&&j<(int)R.size()) {
        int lcp=std::min(lcpL,lcpR);
        if (lcpCompare(L[i],R[j],lcp)<=0) {
            if (j<(int)R.size()) lcpR=computeLcp(L[i],R[j]);
            arr[k++]=L[i++];
        } else {
            if (i<(int)L.size()) lcpL=computeLcp(R[j],L[i]);
            arr[k++]=R[j++];
        }
    }
    while (i<(int)L.size()) arr[k++]=L[i++];
    while (j<(int)R.size()) arr[k++]=R[j++];
}
void lcpMSort(std::vector<std::string>& arr,int lo,int hi) {
    if (hi-lo<=1) return;
    int mid=(lo+hi)/2;
    lcpMSort(arr,lo,mid); lcpMSort(arr,mid,hi);
    lcpMerge(arr,lo,mid,hi);
}
void stringMergeSort(std::vector<std::string>& a) { lcpMSort(a,0,(int)a.size()); }

static int charAtInt(const std::string& s, int d) {
    if (d<(int)s.size()) { ++g_charComps; return (unsigned char)s[d]; }
    return -1;
}
void stringQuickSort(std::vector<std::string>& arr, int lo, int hi, int d0) {
    struct Fr{int lo,hi,d;};
    std::stack<Fr> st;
    if(lo<hi) st.push({lo,hi,d0});
    while(!st.empty()) {
        auto f=st.top(); st.pop();
        int lo=f.lo,hi=f.hi,d=f.d;
        if(lo>=hi) continue;
        int pivIdx=lo+(int)(rng()%(unsigned)(hi-lo+1));
        std::swap(arr[lo],arr[pivIdx]);
        int lt=lo,gt=hi,i=lo+1;
        int pivot=charAtInt(arr[lo],d);
        while(i<=gt){
            int c=charAtInt(arr[i],d);
            if(c<pivot)      {std::swap(arr[lt++],arr[i++]);}
            else if(c>pivot) {std::swap(arr[i],arr[gt--]);}
            else             {++i;}
        }
        if(gt+1<=hi)        st.push({gt+1,hi,d});
        if(pivot>=0&&lt<=gt) st.push({lt,gt,d+1});
        if(lo<=lt-1)        st.push({lo,lt-1,d});
    }
}
void stringQuickSortWrap(std::vector<std::string>& a) {
    if(a.size()>1) stringQuickSort(a,0,(int)a.size()-1,0);
}

static const int RADIX=256;
void msdSort(std::vector<std::string>& arr, bool hybrid) {
    int n=(int)arr.size(); if(n<=1) return;
    std::vector<std::string> aux(n);
    struct Fr{int lo,hi,d;};
    std::stack<Fr> st; st.push({0,n-1,0});
    while(!st.empty()){
        auto f=st.top(); st.pop();
        int lo=f.lo,hi=f.hi,d=f.d;
        if(lo>=hi) continue;
        if(hybrid && hi-lo+1<74){ stringQuickSort(arr,lo,hi,d); continue; }
        std::vector<int> count(RADIX+2,0);
        for(int i=lo;i<=hi;++i){ ++g_charComps; int c=(d<(int)arr[i].size())?(unsigned char)arr[i][d]:0; ++count[c+2]; }
        for(int r=0;r<=RADIX;++r) count[r+1]+=count[r];
        std::vector<int> head(count.begin(),count.end());
        for(int i=lo;i<=hi;++i){ int c=(d<(int)arr[i].size())?(unsigned char)arr[i][d]:0; aux[lo+head[c+1]++]=arr[i]; }
        for(int i=lo;i<=hi;++i) arr[i]=aux[i];
        for(int r=RADIX;r>=1;--r){ int from=lo+count[r],to=lo+count[r+1]-1; if(from<to) st.push({from,to,d+1}); }
    }
}
void msdRadix(std::vector<std::string>& a)  { msdSort(a,false); }
void msdRadixQ(std::vector<std::string>& a) { msdSort(a,true);  }

struct Res { double timeUs; long long comps; };

template<typename F>
Res measure(const std::vector<std::string>& base, F fn, int runs=5) {
    double tsum=0; long long csum=0;
    for(int r=0;r<runs;++r){
        auto tmp=base;
        g_charComps=0;
        auto t0=std::chrono::high_resolution_clock::now();
        fn(tmp);
        auto t1=std::chrono::high_resolution_clock::now();
        tsum+=std::chrono::duration<double,std::micro>(t1-t0).count();
        csum+=g_charComps;
    }
    return {tsum/runs, csum/runs};
}

int main() {
    StringGenerator gen(42);

    auto base_rand   = gen.randomArray(3000);
    auto base_rev    = gen.reverseSortedArray(3000);
    auto base_nearly = gen.nearlySortedArray(3000);

    std::vector<int> sizes;
    for(int n=100;n<=3000;n+=100) sizes.push_back(n);

    struct Algo { std::string name; void(*fn)(std::vector<std::string>&); };
    std::vector<Algo> algos = {
        {"QuickSort",        stdQuickSort},
        {"MergeSort",        stdMergeSort},
        {"StringQuickSort",  stringQuickSortWrap},
        {"StringMergeSort",  stringMergeSort},
        {"MSDRadix",         msdRadix},
        {"MSDRadixQuick",    msdRadixQ},
    };

    struct DataSet { std::string name; const std::vector<std::string>* base; };
    std::vector<DataSet> datasets = {
        {"random",   &base_rand},
        {"reverse",  &base_rev},
        {"nearly",   &base_nearly},
    };

    std::ofstream csv("results.csv");
    csv << "dataset,algorithm,n,time_us,char_comps\n";

    for(auto& ds : datasets) {
        std::cerr << "Dataset: " << ds.name << "\n";
        for(int n : sizes) {
            std::vector<std::string> sub(ds.base->begin(), ds.base->begin()+n);
            for(auto& alg : algos) {
                auto r = measure(sub, alg.fn, 7);
                csv << ds.name << "," << alg.name << "," << n
                    << "," << (long long)r.timeUs << "," << r.comps << "\n";
            }
            std::cerr << "  n=" << n << " done\n";
        }
    }
    csv.close();
    std::cerr << "Done!\n";
    return 0;
}
