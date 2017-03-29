#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath>
#include <unordered_map>

template <typename T, typename Compare = std::less<T>>
class Heap {
public:
    typedef T value_type;
    typedef Compare compare_type;
    
    Heap() {}
    Heap(const std::vector<value_type>& data) : elements_(data) {}
    
    void Heapity() {
        for (int i = int(elements_.size()-1); i >= 0; --i) {
//            std::cout << " sift down : " << elements_[i] << std::endl;
            SiftDown(i);
//            Print();
        }
        Print();
    }
    void Print() const {
        std::cout << "---- Heap elements ----" << std::endl;
        for (const auto& i : elements_) {
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }
    // sift down the element at index 'i'
    void SiftDown(size_t i) {
        size_t swap_with = i;
        // Compare with left child
        size_t lc_indx = 2*i+1;
        if (lc_indx < int(elements_.size()) && CompareElements(lc_indx, swap_with))
            swap_with = lc_indx;
        // Compare with right child
        size_t rc_indx = 2*i+2;
        if (rc_indx < int(elements_.size()) && CompareElements(rc_indx, swap_with))
            swap_with = rc_indx;
        if (swap_with != i) {
            std::swap(elements_[i], elements_[swap_with]);
            SiftDown(swap_with);
        }
    }
    // sift up the element at index 'i'
    void SiftUp(size_t i) {
        if (elements_.size() == 1 || i == 0) {
            return;
        }
        // Compare with parent
        int parent_indx = int((i-1)/2);
        if (!CompareElements(parent_indx, i)) {
            // swap with parent
            std::swap(elements_[parent_indx], elements_[i]);
            // sift up the parent
            SiftUp(parent_indx);
        }
    }
    
    const value_type& GetTop() const { return elements_[0]; }
    value_type ExtractTop() {
        value_type top = elements_[0];
        if (elements_.size() != 0) {
            std::swap(elements_[0], elements_[elements_.size()-1]);
            elements_.pop_back();
            SiftDown(0);
        }
        return top;
    }
    
    void Insert(const T& new_elem) {
        elements_.emplace_back(new_elem);
        SiftUp(elements_.size()-1);
    }

    const std::vector<value_type>& GetElements() const { return elements_; }
    const typename std::vector<value_type>::size_type Size() const { return elements_.size(); }
    
private:
    virtual bool CompareElements(size_t indx1, size_t indx2) const {
        return comparator_(elements_[indx1], elements_[indx2]);
    }
    std::vector<value_type> elements_;
    compare_type comparator_;
};


class MedianFinder {
public:
    using MinHeap = Heap<int, std::less<int>>;
    using MaxHeap = Heap<int, std::greater<int>>;
    
    // Adds a number into the data structure.
    void addNum(int num) {
        if (max_heap_.Size() == 0) {
            max_heap_.Insert(num);
        }
        else if (min_heap_.Size() == 0 || max_heap_.Size() == min_heap_.Size()){
            // both have same size
            // if max heap's top/ max is greater than num then move the top to min heap
            if (max_heap_.GetTop() > num) { // if num should go to max heap
                // extract from max and push to min then add num to max heap
                min_heap_.Insert(max_heap_.ExtractTop());
                max_heap_.Insert(num);
            }
            else
                min_heap_.Insert(num);
        }
        else { // both heaps are not empty and not equal sized
            if (max_heap_.Size() > min_heap_.Size()) {   // an element should go to min heap
                if (max_heap_.GetTop() > num) {  // if the max heap has top greater then it should go to min heap
                    // extract from max and push to min then add num to max heap
                    min_heap_.Insert(max_heap_.ExtractTop());
                    max_heap_.Insert(num);
                }
                else
                    min_heap_.Insert(num);
            }
            else { // an element should go to max heap
                if (min_heap_.GetTop() < num) { // if min heap's top is lesser then it should go to max heap
                    max_heap_.Insert(min_heap_.ExtractTop());
                    min_heap_.Insert(num);
                }
                else
                    max_heap_.Insert(num);
            }
        }
    }
    
    // Returns the median of current data stream
    double findMedian() {
        return min_heap_.Size()==max_heap_.Size() ? (double(min_heap_.GetTop())+double(max_heap_.GetTop()))/2.0f :
        (min_heap_.Size()<max_heap_.Size() ? max_heap_.GetTop() : min_heap_.GetTop());
    }
private:
    MinHeap min_heap_;
    MaxHeap max_heap_;
};


// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
// Driver code
int main()
{
    MedianFinder mf;
    std::vector<int> els = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};
    for (auto& e : els) {
        mf.addNum(e);
        std::cout << mf.findMedian() << std::endl;;
    }
    return 0;
}
