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
#include <cstdlib>
#include <utility>

STONKS_DIAGNOSTIC_PUSH

namespace STONKS_NAMESPACE {

    template<typename Key, typename Value, typename Compare, typename Allocator>
    constexpr STONKS_ALWAYS_INLINE BestNStorage<Key, Value, Compare, Allocator>::BestNStorage(size_t n) : m_n(n) {}


    template<typename Key, typename Value, typename Compare, typename Allocator>
    template<KeyValueOutputIterator<Key, Value> OutputIterator>
    constexpr STONKS_ALWAYS_INLINE OutputIterator BestNStorage<Key, Value, Compare, Allocator>::GetBest(OutputIterator first) const {
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
    constexpr STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Insert(std::pair<const Key, Value> value) {
        return Emplace(value.first, value.second);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    template<typename UKey, typename UValue>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Emplace(UKey &&key, UValue &&value) {
        if (const auto it = m_map.find(key); it != m_map.end()) {
            it->second += value;
            return {it, false};
        }
        return m_map.emplace(std::forward<UKey>(key), std::forward<UValue>(value));
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::size_type BestNStorage<Key, Value, Compare, Allocator>::Erase(const Key &key) {
        return m_map.erase(key);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::iterator BestNStorage<Key, Value, Compare, Allocator>::Erase(typename BestNStorage<Key, Value, Compare, Allocator>::iterator it) {
        return m_map.erase(it);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Change(std::pair<const Key, Value> value) {
        return Change(value.first, value.second);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator>
    template<typename UKey, typename UValue>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorage<Key, Value, Compare, Allocator>::insert_return_type BestNStorage<Key, Value, Compare, Allocator>::Change(UKey &&key, UValue &&value) {
        if (const auto it = m_map.find(key); it != m_map.end()) {
            it->second = value;
            return {it, false};
        }
        return m_map.emplace(std::forward<UKey>(key), std::forward<UValue>(value));
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    constexpr STONKS_ALWAYS_INLINE BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::BestNStorageBuffered(size_t n) : m_baseStorage(n) {
        const size_t bufferSize = n * sizeof(std::pair<Key, Value>);
        if (bufferSize > maxSSOBufferSize) {
            m_bufferBest = static_cast<std::pair<Key, Value> *>(ALIGNED_MALLOC(bufferSize, alignof(std::pair<Key, Value>)));
        } else {
            m_bufferBest = m_ssoBuffer;
        }
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    constexpr BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::~BestNStorageBuffered() noexcept {
        if (m_bufferBest != m_ssoBuffer) {
            ALIGNED_FREE(m_bufferBest);
        }
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    template<typename OutputIterator>
    constexpr STONKS_ALWAYS_INLINE OutputIterator BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::GetBest(OutputIterator first) const {
        size_t resultSize = 0;
        for (auto *it = m_bufferBest;; ++it) {
            if (resultSize++ == m_baseStorage.m_n) {
                return first;
            }
            *first++ = *it;
        }
        return first;
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::insert_return_type BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::Insert(std::pair<const Key, Value> value) {
        return Emplace(value.first, value.second);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    template<typename UKey, typename UValue>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::insert_return_type BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::Emplace(UKey &&key, UValue &&value) {
        if (m_bufferSize == 0) {
            new (m_bufferBest) std::pair<const Key, Value>{key, value};
            ++m_bufferSize;
            return m_baseStorage.Emplace(std::forward<UKey>(key), std::forward<UValue>(value));
        }
        if (!m_baseStorage.m_map.key_comp()(m_bufferBest[m_bufferSize - 1].first, key)) {
            for (size_t i = 0; i < m_bufferSize; ++i) {
                if (m_bufferBest[i].first == key) {
                    m_bufferBest[i].second += value;
                    return m_baseStorage.Emplace(std::forward<UKey>(key), std::forward<UValue>(value));
                }
                if (m_baseStorage.m_map.key_comp()(key, m_bufferBest[m_bufferSize - 1].first)) {
                    for (size_t j = m_bufferSize - 1; j > i; --j) {
                        m_bufferBest[j] = m_bufferBest[j - 1];
                    }
                    new (m_bufferBest + i) std::pair<const Key, Value>{key, value};
                    ++m_bufferSize;
                    return m_baseStorage.Emplace(std::forward<UKey>(key), std::forward<UValue>(value));
                }
            }
            STONKS_ASSERT(false, "impossible control flow - if key not greater than max inside buffer, either there is equal key or less");
        }
        if (m_bufferSize < m_baseStorage.m_n) {
            new (m_bufferBest + m_bufferSize++) std::pair<const Key, Value>{key, value};
            return m_baseStorage.Emplace(std::forward<UKey>(key), std::forward<UValue>(value));
        }
        return m_baseStorage.Emplace(std::forward<UKey>(key), std::forward<UValue>(value));
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::size_type BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::Erase(const Key &key) {
        if (m_bufferSize == 0) {
            STONKS_ASSERT(m_baseStorage.m_map.empty(), "buffer empty - map must be empty too");
            return 0;
        }
        if (!m_baseStorage.m_map.key_comp()(m_bufferBest[m_bufferSize - 1].first, key)) {
            const Key greatest = m_bufferBest[m_bufferSize - 1].first;
            for (size_t i = 0; i < m_bufferSize; ++i) {
                if (m_bufferBest[i].first == key) {
                    for (size_t j = i + 1; j < m_bufferSize; ++j) {
                        m_bufferBest[j - 1] = std::move_if_noexcept(m_bufferBest[j]);
                    }
                    --m_bufferSize;
                    if (m_baseStorage.m_map.size() > m_baseStorage.m_n) {
                        new (m_bufferBest + m_bufferSize++) std::pair<const Key, Value>{*m_baseStorage.m_map.upper_bound(greatest)};
                    }
                    return m_baseStorage.Erase(key);
                }
            }
            STONKS_ASSERT(m_baseStorage.m_map.find(key) == m_baseStorage.m_map.end(), "since key is not greater than max in buffer, it must be in buffer");
            return 0;
        }
        return m_baseStorage.Erase(key);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::insert_return_type BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::Change(std::pair<const Key, Value> value) {
        return Change(value.first, value.second);
    }

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    template<typename UKey, typename UValue>
    constexpr STONKS_ALWAYS_INLINE typename BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::insert_return_type BestNStorageBuffered<Key, Value, Compare, Allocator, maxSSOBufferSize>::Change(UKey &&key, UValue &&value) {
        if (m_bufferSize == 0) {
            STONKS_ASSERT(m_baseStorage.m_map.empty(), "buffer empty - map must be empty too");
            return {m_baseStorage.m_map.end(), false};
        }
        if (!m_baseStorage.m_map.key_comp()(m_bufferBest[m_bufferSize - 1].first, key)) {
            // TODO binary search?
            for (size_t i = 0; i < m_bufferSize; ++i) {
                if (m_bufferBest[i].first == key) {
                    m_bufferBest[i].second = value;
                    return m_baseStorage.Change(std::forward<UKey>(key), std::forward<UValue>(value));
                }
            }
            return {m_baseStorage.m_map.end(), false};
        }
        return m_baseStorage.Change(std::forward<UKey>(key), std::forward<UValue>(value));
    }

}// end namespace STONKS_NAMESPACE

STONKS_DIAGNOSTIC_ATTRIBUTE
STONKS_DIAGNOSTIC_POP

#endif// #ifndef STONKS_BEST_N_STORAGE_H
