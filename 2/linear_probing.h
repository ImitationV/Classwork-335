#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <string>
#include <functional>

template <typename HashedObj>
class LinearProbing {
public:
    explicit LinearProbing(int size = 101) : array_(NextPrime(size)), current_size_(0), collisions_(0) { }

    bool Contains(const HashedObj &x, int &probes) const {
        int current_pos = FindPos(x, probes);
        return IsActive(current_pos);
    }

    void MakeEmpty() {
        current_size_ = 0;
        for (auto &entry : array_)
            entry.info_ = EMPTY;
    }

    bool Insert(const HashedObj &x) {
        int current_pos = FindPos(x);
        if (IsActive(current_pos))
            return false;

        array_[current_pos].element_ = x;
        array_[current_pos].info_ = ACTIVE;

        if (++current_size_ > array_.size() / 2)
            Rehash();
        return true;
    }

    int getNumberOfElements() const { return current_size_; }
    int getSize() const { return array_.size(); }
    double getLoadFactor() const { return static_cast<double>(current_size_) / array_.size(); }
    int getCollisions() const { return collisions_; }
    double getAvgCollisions() const { return static_cast<double>(collisions_) / current_size_; }

private:
    struct HashEntry {
        HashedObj element_;
        enum EntryType { ACTIVE, EMPTY, DELETED } info_;
        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY) : element_{e}, info_{i} { }
    };

    std::vector<HashEntry> array_;
    int current_size_;
    mutable int collisions_;

    bool IsActive(int current_pos) const { return array_[current_pos].info_ == ACTIVE; }

    int FindPos(const HashedObj &x, int &probes) const {
        int offset = 1;
        int current_pos = InternalHash(x);

        while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
            current_pos += offset;
            if (current_pos >= array_.size())
                current_pos -= array_.size();
            probes++;
            collisions_++;
        }
        return current_pos;
    }

    void Rehash() {
        std::vector<HashEntry> old_array = array_;

        array_.resize(NextPrime(2 * old_array.size()));
        for (auto &entry : array_)
            entry.info_ = EMPTY;

        current_size_ = 0;
        for (auto &entry : old_array)
            if (entry.info_ == ACTIVE)
                Insert(std::move(entry.element_));
    }

    size_t InternalHash(const HashedObj &x) const {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size();
    }

    int NextPrime(int n) {
        while (!IsPrime(n)) ++n;
        return n;
    }

    bool IsPrime(int n) {
        if (n == 2 || n == 3)
            return true;
        if (n == 1 || n % 2 == 0)
            return false;
        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;
        return true;
    }
};

#endif
