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

#include "utils/defines.h"
#include <map>

namespace STONKS_NAMESPACE {

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

        explicit BestNStorage(size_t n);
        template<typename OutputIterator>
        OutputIterator GetBest(OutputIterator first) const;
        insert_return_type Insert(std::pair<const Key, Value> value);
        template<typename UKey, typename UValue>
        insert_return_type Emplace(UKey &&key, UValue &&value);
        size_type Erase(const Key &key);
        iterator Erase(iterator it);
        insert_return_type Change(std::pair<const Key, Value> value);
        template<typename UKey, typename UValue>
        insert_return_type Change(UKey &&key, UValue &&value);

    private:
        std::map<Key, Value, Compare, Allocator> m_map;
        size_t m_n;
    };

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_BEST_N_STORAGE_FWD_H
