#ifndef CPPJNI_DETAIL_STATIC_STRING_HPP_
#define CPPJNI_DETAIL_STATIC_STRING_HPP_

#include <cassert>
#include <type_traits>

namespace cppjni {
namespace detail {

template<std::size_t Length>
class static_string {
public:
    constexpr static_string() {}

    constexpr static_string(const char (&c_str)[Length + 1]) {
        assert(c_str[Length] == '\0');

        for (size_t i = 0; i < Length; i++) {
            data_[i] = c_str[i];
        }
        data_[Length] = '\0';
    }

    template<size_t L1, typename = std::enable_if_t<L1 <= Length>>
    constexpr static_string(const static_string<L1> &s1, const static_string<Length - L1> &s2) {
      for (size_t i = 0; i < L1; ++i) {
          data_[i] = s1[i];
      }
      for (size_t i = 0; i < Length - L1; ++i) {
          data_[L1 + i] = s2[i];
      }
      data_[Length] = '\0';
    }

    constexpr std::size_t size() const noexcept {
        return Length;
    }

    constexpr const char *data() const noexcept {
        return &data_[0];
    }

    constexpr char &operator[](size_t i) {
        assert(i < Length);

        return data_[i];
    }

    constexpr char operator[](size_t i) const {
        assert(i < Length);

        return data_[i];
    }

private:
    char data_[Length + 1] = {}; 
};

template<std::size_t L>
constexpr static_string<L - 1> static_str(const char (&s)[L]) {
    return static_string<L - 1>{s};
}

template<std::size_t L1, std::size_t L2>
constexpr static_string<L1 + L2> static_strcat(const static_string<L1> &s1,
                                               const static_string<L2> &s2) {
    return static_string<L1 + L2>{s1, s2};
}

}  // namespace detail
}  // namespace cppjni

#endif  // CPPJNI_SIGNATURE_HPP_
