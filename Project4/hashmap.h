#if 1
#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <string>
#include <algorithm>
#include <functional>

template <typename ValueType>
class HashMap {
public:
    explicit HashMap(double maxLoadFactor = 0.75) : m_size(0), m_maxLoadFactor(maxLoadFactor) {
        m_buckets.resize(10); // Start with 10 buckets
    }

    void insert(const std::string& key, const ValueType& value) {
        ensureLoadFactor();
        size_t index = getBucketIndex(key, m_buckets.size());
        for (auto& entry : m_buckets[index]) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        m_buckets[index].emplace_back(key, value);
        ++m_size;
    }

    int size() const {
        return m_size;
    }

    ValueType* find(const std::string& key) {
        size_t index = getBucketIndex(key, m_buckets.size());
        for (auto& entry : m_buckets[index]) {
            if (entry.first == key) {
                return &entry.second;
            }
        }
        return nullptr;
    }

    const ValueType* find(const std::string& key) const {
        return const_cast<HashMap*>(this)->find(key);
    }

    ValueType& operator[](const std::string& key) {
        ValueType* found = find(key);
        if (found) {
            return *found;
        }
        else {
            insert(key, ValueType());
            return *find(key);
        }
    }

private:
    std::vector<std::vector<std::pair<std::string, ValueType>>> m_buckets;
    int m_size;
    double m_maxLoadFactor;

    size_t getBucketIndex(const std::string& key, size_t bucketCount) const {
        return std::hash<std::string>{}(key) % bucketCount;
    }

    void ensureLoadFactor() {
        double currentLoadFactor = static_cast<double>(m_size) / static_cast<double>(m_buckets.size());
        if (currentLoadFactor > m_maxLoadFactor) {
            rehash(m_buckets.size() * 2);
        }
    }

    void rehash(size_t newBucketCount) {
        std::vector<std::vector<std::pair<std::string, ValueType>>> newBuckets(newBucketCount);
        for (const auto& bucket : m_buckets) {
            for (const auto& entry : bucket) {
                size_t newIndex = getBucketIndex(entry.first, newBucketCount);
                newBuckets[newIndex].push_back(entry);
            }
        }
        m_buckets.swap(newBuckets);
    }
};

#endif // HASHMAP_H

#endif // 
 
#if 0

#ifndef HASHMAP_H
#define HASHMAP_H

// ***** DO NOT TURN IN THIS FILE *****
//
// This file is an implementation of HashMap that has correct visible
// behavior.  If you cannot get your HashMap class to work well enough to
// make progress on the other classes that use HashMaps, you can use this
// one temporarily, switch your attention to implementing the other
// classes, and go back to working on *your* HashMap implementation later.
//
// DO NOT TURN IN THIS FILE AS YOUR IMPLEMENTATION -- it uses unordered_map,
// which the spec forbids.

#include <string>
#include <unordered_map>

template <class T>
class HashMap {
public:
    HashMap(double = 0.75) {}
    void insert(const std::string& key, const T& value) { m_map[key] = value; }
    int size() const { return m_map.size(); }
    T* find(const std::string& key) { const auto& hm = *this; return const_cast<T*>(hm.find(key)); }
    const T* find(const std::string& key) const { auto it = m_map.find(key); return it == m_map.end() ? nullptr : &it->second; }
    T& operator[](const std::string& key) { return m_map[key]; }
private:
    std::unordered_map<std::string, T> m_map;
};

#endif // HASHMAP_H

#endif // 0

