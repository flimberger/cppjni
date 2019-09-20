#include <cppjni/signature.hpp>

#include <algorithm>
#include <string>

#include "catch.hpp"

namespace cppjni {
namespace detail {

template<size_t L>
constexpr bool operator==(const static_string<L> &s1, const char *s2) {
    using Traits = std::char_traits<char>;

    return Traits::compare(s1.data(), s2, std::max(L, Traits::length(s2))) == 0;
}

}  // namespace detail
}  // namespace cppjni

using namespace cppjni;

TEST_CASE("Automatic signature creation for primitives", "[signatures]") {
    REQUIRE(signature<::jboolean>::value == "Z");
    REQUIRE(signature<::jbyte>::value == "B");
    REQUIRE(signature<::jchar>::value == "C");
    REQUIRE(signature<::jshort>::value == "S");
    REQUIRE(signature<::jint>::value == "I");
    REQUIRE(signature<::jlong>::value == "J");
    REQUIRE(signature<::jfloat>::value == "F");
    REQUIRE(signature<::jdouble>::value == "D");
}

TEST_CASE("Automatic signature creation for primitive arrays", "[signatures][arrays]") {
    REQUIRE(signature<::jbooleanArray>::value == "[Z");
    REQUIRE(signature<::jbyteArray>::value == "[B");
    REQUIRE(signature<::jcharArray>::value == "[C");
    REQUIRE(signature<::jshortArray>::value == "[S");
    REQUIRE(signature<::jintArray>::value == "[I");
    REQUIRE(signature<::jlongArray>::value == "[J");
    REQUIRE(signature<::jfloatArray>::value == "[F");
    REQUIRE(signature<::jdoubleArray>::value == "[D");
}

struct string_class_tag {
    constexpr static const char class_name[] = "java/lang/String";
};
using string_class = java_class<string_class_tag>;

TEST_CASE("Automatic signature creation for class names", "[signatures][classes]") {
    REQUIRE(signature<string_class>::value == "Ljava/lang/String;");
}

/*
TEST_CASE("Automatic signature creation for object arrays", "[signatures][arrays][classes]") {
    REQUIRE(signature<java_array<string_class>>::value == "[Ljava/lang/String;");
}
*/

TEST_CASE("Automatic signature creation for methods", "[signatures][methods]") {
  REQUIRE(signature<::jint(::jlong, ::jfloat)>::value.data() == std::string_view{"(JF)I"});
  REQUIRE(signature<::jint(::jlongArray)>::value.data() == std::string_view{"([J)I"});
  REQUIRE(signature<string_class(string_class, string_class)>::value.data() == std::string_view{"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"});
  // REQUIRE(signature<::jint(java_array<string_class>)>::value.data() == std::string_view{"([Ljava/lang/String;)I"});
  REQUIRE(signature<void(::jint)>::value.data() == std::string_view{"(I)V"});
}
