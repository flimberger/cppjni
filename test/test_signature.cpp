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
    REQUIRE(signature<::jint>::value == "I");
    REQUIRE(signature<::jlong>::value == "J");
    REQUIRE(signature<::jfloat>::value == "F");
}

TEST_CASE("Automatic signature creation for arrays", "[signatures][arrays]") {
    REQUIRE(signature<java_array<::jint>>::value == "[I");
}

struct string_class_tag {
    constexpr static const auto class_name = detail::static_strdup("java/lang/String");
};
using string_class = java_class<string_class_tag>;

TEST_CASE("Automatic signature creation for class names", "[signatures][classes]") {
    REQUIRE(signature<string_class>::value == "Ljava/lang/String;");
}

TEST_CASE("Automatic signature creation for object arrays", "[signatures][arrays][classes]") {
    REQUIRE(signature<java_array<string_class>>::value == "[Ljava/lang/String;");
}

TEST_CASE("Automatic signature creation for methods", "[signatures][methods]") {
  REQUIRE(signature<::jint(::jlong, ::jfloat)>::value.data() == std::string_view{"(JF)I"});
  REQUIRE(signature<::jint(java_array<::jlong>)>::value.data() == std::string_view{"([J)I"});
  REQUIRE(signature<string_class(string_class, string_class)>::value.data() == std::string_view{"(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;"});
  REQUIRE(signature<::jint(java_array<string_class>)>::value.data() == std::string_view{"([Ljava/lang/String;)I"});
}
