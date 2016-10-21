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
 * ReaderTest.cpp                                         *
 *                                                        *
 * hprose reader test for cpp.                            *
 *                                                        *
 * LastModified: Oct 21, 2016                             *
 * Author: Chen fei <cf@hprose.com>                       *
 *                                                        *
\**********************************************************/

#include <hprose/io/Writer.h>
#include <hprose/io/Reader.h>

#include <gtest/gtest.h>

#define T(Type, value, expected) { \
    std::stringstream stream; \
    hprose::io::Writer writer(stream, false); \
    writer.serialize(value); \
    hprose::io::Reader reader(stream, false); \
    EXPECT_EQ(reader.unserialize<Type>(), expected); \
}

TEST(Reader, UnserializeBool) {
    T(bool, true, true);
    T(bool, 0, false);
    T(bool, 99, true);
    T(bool, std::string("true"), true);
    T(bool, std::string("false"), false);
}