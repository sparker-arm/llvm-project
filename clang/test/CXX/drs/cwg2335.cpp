// RUN: %clang_cc1 -std=c++98 %s -verify=expected,cxx98-11 -fexceptions -fcxx-exceptions -pedantic-errors
// RUN: %clang_cc1 -std=c++11 %s -verify=expected,cxx98-11 -fexceptions -fcxx-exceptions -pedantic-errors
// RUN: %clang_cc1 -std=c++14 %s -verify=expected,since-cxx14 -fexceptions -fcxx-exceptions -pedantic-errors
// RUN: %clang_cc1 -std=c++17 %s -verify=expected,since-cxx14 -fexceptions -fcxx-exceptions -pedantic-errors
// RUN: %clang_cc1 -std=c++20 %s -verify=expected,since-cxx14 -fexceptions -fcxx-exceptions -pedantic-errors
// RUN: %clang_cc1 -std=c++23 %s -verify=expected,since-cxx14 -fexceptions -fcxx-exceptions -pedantic-errors
// RUN: %clang_cc1 -std=c++2c %s -verify=expected,since-cxx14 -fexceptions -fcxx-exceptions -pedantic-errors

// cxx98-11-no-diagnostics

namespace cwg2335 { // cwg2335: no drafting 2018-06
// FIXME: current consensus is that the examples are well-formed.
#if __cplusplus >= 201402L
namespace ex1 {
template <class...> struct partition_indices {
  static auto compute_right() {}
  static constexpr auto right = compute_right;
};
template struct partition_indices<int>;
} // namespace ex1

namespace ex2 {
template <int> struct X {};
template <class T> struct partition_indices {
  static auto compute_right() { return X<I>(); }
  // since-cxx14-error@-1 {{no member 'I' in 'cwg2335::ex2::partition_indices<int>'; it has not yet been instantiated}}
  //   since-cxx14-note@#cwg2335-ex2-right {{in instantiation of member function 'cwg2335::ex2::partition_indices<int>::compute_right' requested here}}
  //   since-cxx14-note@#cwg2335-ex2-inst {{in instantiation of template class 'cwg2335::ex2::partition_indices<int>' requested here}}
  //   since-cxx14-note@#cwg2335-ex2-I {{not-yet-instantiated member is declared here}}
  static constexpr auto right = compute_right; // #cwg2335-ex2-right
  static constexpr int I = sizeof(T); // #cwg2335-ex2-I
};
template struct partition_indices<int>; // #cwg2335-ex2-inst
} // namespace ex2

namespace ex3 {
struct partition_indices {
  static auto compute_right() {} // #cwg2335-compute_right
  static constexpr auto right = compute_right; // #cwg2335-ex3-right
  // since-cxx14-error@-1 {{function 'compute_right' with deduced return type cannot be used before it is defined}}
  //   since-cxx14-note@#cwg2335-compute_right {{'compute_right' declared here}}
  // since-cxx14-error@#cwg2335-ex3-right {{declaration of variable 'right' with deduced type 'const auto' requires an initializer}}
};
} // namespace ex3
#endif
} // namespace cwg2335
