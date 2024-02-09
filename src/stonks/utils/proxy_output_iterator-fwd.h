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

#ifndef STONKS_UTILS_PROXY_OUTPUT_ITERATOR_FWD
#define STONKS_UTILS_PROXY_OUTPUT_ITERATOR_FWD

#include "stonks/utils/defines.h"

namespace STONKS_NAMESPACE {

    template<typename ProxyValue, typename OutputIterator, typename Transform>
    concept ProxyValueFor = requires(ProxyValue value, OutputIterator iterator, Transform transform) {
        { *iterator++ = transform(value) };
    };

    /**
     * Class Transform one output iterator to another.
     * When user write to proxy iterator, it applies transform function and write result to obtained iterator.
     * So proxy iterator has interface of output iterator for proxy value type
     * @tparam OutputIterator iterator you would like to transform
     * @tparam Transform transform function
     * @tparam ProxyValue value to read
     */
    template<typename OutputIterator, typename Transform, ProxyValueFor<OutputIterator, Transform> ProxyValue>
    class STONKS_API OutputIteratorProxy {
    public:
        /**
         * Obtain iterator to write to
         * @param first iterator to the begin
         * @param transform transform function
         */
        constexpr explicit OutputIteratorProxy(OutputIterator first, Transform transform = {});
        /**
         * does nothing, required only the consistency of interface
         * @return reference to itself
         */
        constexpr OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &operator++(int);
        /**
         * does nothing, required only the consistency of interface
         * @return reference to itself
         */
        constexpr OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &operator++();
        /**
         * does nothing, required only the consistency of interface
         * @return reference to itself
         */
        constexpr OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &&operator*();
        /**
         * transform value and write result
         * @return r-value reference to itself
         */
        constexpr OutputIteratorProxy<OutputIterator, Transform, ProxyValue> &operator=(const ProxyValue &value) &&;
        /**
         * implicit cast to obtained iterator
         * @return iterator to following of last written position
         */
        constexpr operator OutputIterator() const;

    private:
        OutputIterator m_iterator;
        Transform m_transform;
    };

}// end namespace STONKS_NAMESPACE

#endif// #ifndef STONKS_UTILS_PROXY_OUTPUT_ITERATOR_FWD