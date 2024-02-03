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

#ifndef STONKS_UTILS_PROXY_OUTPUT_ITERATOR
#define STONKS_UTILS_PROXY_OUTPUT_ITERATOR

#include "proxy_output_iterator-fwd.h"

STONKS_DIAGNOSTIC_PUSH

namespace STONKS_NAMESPACE {

    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    constexpr STONKS_ALWAYS_INLINE OutputIteratorProxy<OutputIterator, Transform, ProxyValue>::OutputIteratorProxy(OutputIterator first, Transform transform) : m_iterator(first), m_transform(transform) {}

    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    constexpr STONKS_ALWAYS_INLINE OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &OutputIteratorProxy<OutputIterator, Transform, ProxyValue>::operator++(int) {
        return *this;
    }

    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    constexpr STONKS_ALWAYS_INLINE OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &OutputIteratorProxy<OutputIterator, Transform, ProxyValue>::operator++() {
        return *this;
    }

    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    constexpr STONKS_ALWAYS_INLINE OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &OutputIteratorProxy<OutputIterator, Transform, ProxyValue>::operator*() {
        return *this;
    }

    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    constexpr STONKS_ALWAYS_INLINE OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &OutputIteratorProxy<OutputIterator, Transform, ProxyValue>::operator=(const ProxyValue &value) {
        *m_iterator++ = m_transform(value);
        return *this;
    }

    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    constexpr STONKS_ALWAYS_INLINE OutputIteratorProxy<OutputIterator, Transform, ProxyValue>::operator OutputIterator() const {
        return m_iterator;
    }

}// end namespace STONKS_NAMESPACE

STONKS_DIAGNOSTIC_ATTRIBUTE
STONKS_DIAGNOSTIC_POP

#endif// #ifndef STONKS_UTILS_PROXY_OUTPUT_ITERATOR
