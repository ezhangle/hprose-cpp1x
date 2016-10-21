/**********************************************************\
|                                                          |
|                          hprose                          |
|                                                          |
| Official WebSite: http://www.hprose.com/                 |
|                   http://www.hprose.org/                 |
|                                                          |
\**********************************************************/

/**********************************************************\
 *                                                        *
 * hprose/io/Reader.h                                     *
 *                                                        *
 * hprose reader header for cpp.                          *
 *                                                        *
 * LastModified: Oct 21, 2016                             *
 * Author: Chen fei <cf@hprose.com>                       *
 *                                                        *
\**********************************************************/

#pragma once

#include <hprose/io/Tags.h>
#include <hprose/io/decoders/BoolDecoder.h>

#include <istream>
#include <numeric>
#include <limits>

namespace hprose {
namespace io {

namespace internal {

class ReaderRefer {
};

} // hprose::io::internal

template<class T>
struct Decoder;

class Reader {
public:
    Reader(std::istream &stream, bool simple = false)
        : stream(stream), refer(simple ? nullptr : new internal::ReaderRefer()) {
    }

    template<class T>
    inline T unserialize() {
        T v;
        readValue(v);
        return std::move(v);
    }

    template<class T>
    inline Reader &unserialize(T &v) {
        readValue(v);
        return *this;
    }

    template<class T>
    inline void readValue(T &v) {
        return decode(v, *this);
    }

    inline bool readBool() {
        return decoders::BoolDecode(*this, stream.get());
    }

    template<class T>
    typename std::enable_if<
        std::is_floating_point<T>::value,
        T
    >::type
    readInfinity() {
        return stream.get() == tags::TagPos ? std::numeric_limits<T>::infinity() : -std::numeric_limits<T>::infinity();
    }

    std::string readUntil(char tag) {
        std::string s;
        std::getline(stream, s, tag);
        return std::move(s);
    }

    std::istream &stream;

private:
    std::unique_ptr<internal::ReaderRefer> refer;
};

}
} // hprose::io

#include <hprose/io/Reader-inl.h>
