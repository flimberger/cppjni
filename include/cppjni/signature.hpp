#ifndef CPPJNI_SIGNATURE_HPP_
#define CPPJNI_SIGNATURE_HPP_

#include <jni.h>

#include <cppjni/detail/static_string.hpp>

namespace cppjni {

template<typename>
struct signature;

template<>
struct signature<jboolean> {
    constexpr static const auto value = detail::static_strdup("Z");
};

template<>
struct signature<jbyte> {
    constexpr static const auto value = detail::static_strdup("B");
};

template<>
struct signature<jshort> {
    constexpr static const auto value = detail::static_strdup("S");
};

template<>
struct signature<jint> {
    constexpr static const auto value = detail::static_strdup("I");
};

template<>
struct signature<jlong> {
    constexpr static const auto value = detail::static_strdup("J");
};

template<>
struct signature<jfloat> {
    constexpr static const auto value = detail::static_strdup("F");
};

template<>
struct signature<jdouble> {
    constexpr static const auto value = detail::static_strdup("D");
};

template<typename T>
struct java_array {};

/** Signature for arrays
 */
template<typename T>
struct signature<java_array<T>> {
    constexpr static const auto value =
      detail::static_strcat(detail::static_strdup("["), signature<T>::value);
};

// tag uses the following structure
// struct string_class_tag {
//     constexpr static const char class_name[] = "java/lang/String";
// };
template<typename Tag>
struct java_class {
    using tag = Tag;
};

/** Signature for classes
 */
template<typename Tag>
struct signature<java_class<Tag>> {
    constexpr static const auto value =
      detail::static_strcat(detail::static_strdup("L"),
                            detail::static_strcat(
                              detail::static_strdup(Tag::class_name),
                              detail::static_strdup(";")));
};

namespace detail {

template<typename A0, typename... Args>
struct signature_list {
    constexpr static const auto value = static_strcat(signature_list<A0>::value,
                                                      signature_list<Args...>::value);
};

template<typename A>
struct signature_list<A> {
    constexpr static const auto value = signature<A>::value;
};

}  // namespace detail

/** Signature for methods
 */
template<typename R, typename... Args>
struct signature<R(Args...)> {
    constexpr static const auto value = 
      detail::static_strcat(
        detail::static_strdup("("),
        detail::static_strcat(
          detail::signature_list<Args...>::value,
          detail::static_strcat(
            detail::static_strdup(")"),
            signature<R>::value
          )
        )
      );
};

}  // namespace cppjni

#endif  // CPPJNI_SIGNATURE_HPP_
