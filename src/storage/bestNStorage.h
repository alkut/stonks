// MIT License
//
// Copyright (c) [2024] [Aleksei Kutasov]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef STONKS_BEST_N_STORAGE_H
#define STONKS_BEST_N_STORAGE_H

#include "storage/bestNStorage-fwd.h"
#include <utility>

STONKS_DIAGNOSTIC_PUSH

namespace STONKS_NAMESPACE {

    template<typename Key, typename Value, typename Compare, typename Allocator>
    STONKS_ALWAYS_INLINE BestNStorage<Key, Value, Compare, Allocator>::BestNStorage(size_t n) : m_n(n) {}


    template<typename Key, typename Value, typename Compare, typename Allocator>
    template<typename OutputIterator>
    STONKS_ALWAYS_INLINE OutputIterator BestNStorage<Key, Value, Compare, Allocator>::GetBest(OutputIterator first) const {
        size_t resultSize = 0;
        for (const auto &it: m_map) {
            if (resultSize++ == m_n) {
                return first;
            }
            *first++ = it;
        }
        return first;
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Insert(std::pair<const Key, Value> value) {
        return Emplace(value.first, value.second);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    template<typename UKey, typename UValue>
    STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Emplace(UKey &&key, UValue &&value) {
        if (const auto it = m_map.find(key); it != m_map.end()) {
            it->second += value;
            return {it, false};
        }
        return m_map.emplace(key, value);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::size_type BestNStorage<Key, Value, Compare, Allocator>::Erase(const Key &key) {
        return m_map.erase(key);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::iterator BestNStorage<Key, Value, Compare, Allocator>::Erase(typename BestNStorage<Key, Value, Compare, Allocator>::iterator it) {
        return m_map.erase(it);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Change(std::pair<const Key, Value> value) {
        return Change(value.first, value.second);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    template<typename UKey, typename UValue>
    STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Change(UKey &&key, UValue &&value) {
        if (const auto it = m_map.find(key); it != m_map.end()) {
            it->second = value;
            return {it, false};
        }
        return m_map.emplace(key, value);
    }

}// end namespace STONKS_NAMESPACE

STONKS_DIAGNOSTIC_ATTRIBUTE
STONKS_DIAGNOSTIC_POP

#endif// #ifndef STONKS_BEST_N_STORAGE_H
