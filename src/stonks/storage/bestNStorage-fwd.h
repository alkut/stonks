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

#ifndef STONKS_BEST_N_STORAGE_FWD_H
#define STONKS_BEST_N_STORAGE_FWD_H

#include "stonks/utils/defines.h"
#include <concepts>
#include <map>

namespace STONKS_NAMESPACE {

    template<typename TOutputIterator, typename Key, typename Value>
    concept KeyValueOutputIterator = requires(TOutputIterator iterator, const std::pair<const Key, Value> &pair) {
        { *iterator++ = pair };
    };

    template<typename Key, typename Value, typename Compare, typename Allocator>
    class BestNStorage;

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    class BestNStorageBuffered;

    /**
     * Generic class similar to std::map. Allows get lowest N element
     * @tparam Key must be copy-assignable
     * @tparam Value must be copy-assignable
     * @tparam Compare defines compare of two keys. must produce strong order
     * @tparam Allocator allocator for std::pair<const Key, Value>
     */
    template<typename Key, typename Value, typename Compare, typename Allocator>
    class STONKS_API BestNStorage final {
    public:
        using Super = std::map<Key, Value, Compare, Allocator>;
        using key_type = typename Super::key_type;
        using value_type = typename Super::value_type;
        using size_type = typename Super::size_type;
        using difference_type = typename Super::difference_type;
        using key_compare = typename Super::key_compare;
        using value_compare = typename Super::value_compare;
        using allocator_type = typename Super::allocator_type;
        using reference = typename Super::reference;
        using const_reference = typename Super::const_reference;
        using pointer = typename Super::pointer;
        using const_pointer = typename Super::const_pointer;
        using iterator = typename Super::iterator;
        using const_iterator = typename Super::const_iterator;
        using reverse_iterator = typename Super::reverse_iterator;
        using const_reverse_iterator = typename Super::const_reverse_iterator;
        // TODO fix
        using insert_return_type = std::pair<iterator, bool>;
#if __cplusplus >= 201703L
        using node_type = typename Super::node_type;
#endif

        /**
         *
         * @param n GetBest will return n lowest elements
         */
        constexpr explicit BestNStorage(size_t n);
        /**
         * Get n lowest by key pair and write it via first output iterator
         * @tparam OutputIterator output iterator fow writing lowest pairs. @see KeyValueOutputIterator concept
         * @param first output iterator fow writing lowest pairs
         * @return iterator right after last written element
         */
        template<KeyValueOutputIterator<Key, Value> OutputIterator>
        constexpr OutputIterator GetBest(OutputIterator first) const;
        /**
         * If there is pair with equal key, values would be added up
         * @param value key-value pair
         * @return pair of iterator of inserted element and flag if pair was added
         */
        constexpr insert_return_type Insert(std::pair<const Key, Value> value);
        /**
         * If there is pair with equal key, values would be added up
         * @tparam UKey Universal reference to the key
         * @tparam UValue Universal reference to the value
         * @param key Universal reference to the key
         * @param value Universal reference to the value
         * @return pair of iterator of inserted element and flag if pair was added
         */
        template<typename UKey, typename UValue>
        constexpr insert_return_type Emplace(UKey &&key, UValue &&value);
        /**
         * Remove key-value pair if exists pair with following key
         * @param key key to remove
         * @return 0 if there is no pair with following key. 1 otherwise
         */
        constexpr size_type Erase(const Key &key);
        /**
         * Remove key-value pair by iterator. if iterator == end(), do nothing
         * @param it iterator to remove
         * @return iterator following removed element
         */
        constexpr iterator Erase(iterator it);
        /**
         * If there is pair with equal key, values would be overwritten. Otherwise, pair would be inserted
         * @param value key-value pair
         * @return pair of iterator of inserted element and flag if pair was added
         */
        constexpr insert_return_type Change(std::pair<const Key, Value> value);
        /**
         * If there is pair with equal key, values would be overwritten. Otherwise, pair would be inserted
         * @tparam UKey Universal reference to the key
         * @tparam UValue Universal reference to the value
         * @param key Universal reference to the key
         * @param value Universal reference to the value
         * @return pair of iterator of inserted element and flag if pair was added
         */
        template<typename UKey, typename UValue>
        constexpr insert_return_type Change(UKey &&key, UValue &&value);

    private:
        std::map<Key, Value, Compare, Allocator> m_map;
        size_t m_n;

        template<typename UKey, typename UValue, typename UCompare, typename UAllocator, size_t maxSSOBufferSize>
        friend class BestNStorageBuffered;
    };

    template<typename Key, typename Value, typename Compare, typename Allocator, size_t maxSSOBufferSize>
    class STONKS_API BestNStorageBuffered final {
    public:
        using Super = BestNStorage<Key, Value, Compare, Allocator>;
        using key_type = typename Super::key_type;
        using value_type = typename Super::value_type;
        using size_type = typename Super::size_type;
        using difference_type = typename Super::difference_type;
        using key_compare = typename Super::key_compare;
        using value_compare = typename Super::value_compare;
        using allocator_type = typename Super::allocator_type;
        using reference = typename Super::reference;
        using const_reference = typename Super::const_reference;
        using pointer = typename Super::pointer;
        using const_pointer = typename Super::const_pointer;
        using iterator = typename Super::iterator;
        using const_iterator = typename Super::const_iterator;
        using reverse_iterator = typename Super::reverse_iterator;
        using const_reverse_iterator = typename Super::const_reverse_iterator;
        // TODO fix
        using insert_return_type = std::pair<iterator, bool>;
#if __cplusplus >= 201703L
        using node_type = typename Super::node_type;
#endif

        /**
         *
         * @param n GetBest will return n lowest elements
         */
        constexpr explicit BestNStorageBuffered(size_t n);
        constexpr ~BestNStorageBuffered() noexcept;
        /**
         * Get n lowest by key pair and write it via first output iterator
         * @tparam OutputIterator output iterator fow writing lowest pairs. @see KeyValueOutputIterator concept
         * @param first output iterator fow writing lowest pairs
         * @return iterator right after last written element
         */
        template<typename OutputIterator>
        constexpr OutputIterator GetBest(OutputIterator first) const;
        /**
         * If there is pair with equal key, values would be added up
         * @param value key-value pair
         * @return pair of iterator of inserted element and flag if pair was added
         */
        constexpr insert_return_type Insert(std::pair<const Key, Value> value);
        /**
         * If there is pair with equal key, values would be added up
         * @tparam UKey Universal reference to the key
         * @tparam UValue Universal reference to the value
         * @param key Universal reference to the key
         * @param value Universal reference to the value
         * @return pair of iterator of inserted element and flag if pair was added
         */
        template<typename UKey, typename UValue>
        constexpr insert_return_type Emplace(UKey &&key, UValue &&value);
        /**
         * Remove key-value pair if exists pair with following key
         * @param key key to remove
         * @return 0 if there is no pair with following key. 1 otherwise
         */
        constexpr size_type Erase(const Key &key);
        /**
         * If there is pair with equal key, values would be overwritten. Otherwise, pair would be inserted
         * @param value key-value pair
         * @return pair of iterator of inserted element and flag if pair was added
         */
        constexpr insert_return_type Change(std::pair<const Key, Value> value);
        /**
         * If there is pair with equal key, values would be overwritten. Otherwise, pair would be inserted
         * @tparam UKey Universal reference to the key
         * @tparam UValue Universal reference to the value
         * @param key Universal reference to the key
         * @param value Universal reference to the value
         * @return pair of iterator of inserted element and flag if pair was added
         */
        template<typename UKey, typename UValue>
        constexpr insert_return_type Change(UKey &&key, UValue &&value);

    private:
        BestNStorage<Key, Value, Compare, Allocator> m_baseStorage;
        std::pair<Key, Value> *m_bufferBest;
        std::pair<Key, Value> m_ssoBuffer[maxSSOBufferSize / sizeof(std::pair<Key, Value>)];
        size_t m_bufferSize = 0;
    };

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_BEST_N_STORAGE_FWD_H
