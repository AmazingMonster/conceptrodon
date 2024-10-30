// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_RECURSION_H
#define CONCEPTRODON_TESTS_RECURSION_H

namespace Conceptrodon {
namespace DocsTests {
namespace TestRecursion {

#if 1

template<size_t I>
struct Tester
{ static constexpr size_t value {2 * I + Tester<I-1>::value}; };

template<>
struct Tester<0>
{ static constexpr size_t value {0}; };

constexpr size_t Tester_v = Tester<400>::value;

#else

template<size_t I>
struct Tester0
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester1
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester2
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester3
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester4
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester5
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester6
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester7
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester8
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester9
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester10
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester11
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester12
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester13
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester14
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester15
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester16
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester17
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester18
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester19
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester20
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester21
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester22
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester23
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester24
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester25
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester26
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester27
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester28
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester29
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester30
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester31
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester32
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester33
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester34
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester35
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester36
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester37
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester38
{ static constexpr size_t value {I}; };

template<size_t I>
struct Tester39
{ static constexpr size_t value {I}; };

constexpr size_t Tester0_v = Tester0<0>::value;
constexpr size_t Tester1_v = Tester1<0>::value;
constexpr size_t Tester2_v = Tester2<0>::value;
constexpr size_t Tester3_v = Tester3<0>::value;
constexpr size_t Tester4_v = Tester4<0>::value;
constexpr size_t Tester5_v = Tester5<0>::value;
constexpr size_t Tester6_v = Tester6<0>::value;
constexpr size_t Tester7_v = Tester7<0>::value;
constexpr size_t Tester8_v = Tester8<0>::value;
constexpr size_t Tester9_v = Tester9<0>::value;
constexpr size_t Tester10_v = Tester10<0>::value;
constexpr size_t Tester11_v = Tester11<0>::value;
constexpr size_t Tester12_v = Tester12<0>::value;
constexpr size_t Tester13_v = Tester13<0>::value;
constexpr size_t Tester14_v = Tester14<0>::value;
constexpr size_t Tester15_v = Tester15<0>::value;
constexpr size_t Tester16_v = Tester16<0>::value;
constexpr size_t Tester17_v = Tester17<0>::value;
constexpr size_t Tester18_v = Tester18<0>::value;
constexpr size_t Tester19_v = Tester19<0>::value;
constexpr size_t Tester20_v = Tester20<0>::value;
constexpr size_t Tester21_v = Tester21<0>::value;
constexpr size_t Tester22_v = Tester22<0>::value;
constexpr size_t Tester23_v = Tester23<0>::value;
constexpr size_t Tester24_v = Tester24<0>::value;
constexpr size_t Tester25_v = Tester25<0>::value;
constexpr size_t Tester26_v = Tester26<0>::value;
constexpr size_t Tester27_v = Tester27<0>::value;
constexpr size_t Tester28_v = Tester28<0>::value;
constexpr size_t Tester29_v = Tester29<0>::value;
constexpr size_t Tester30_v = Tester30<0>::value;
constexpr size_t Tester31_v = Tester31<0>::value;
constexpr size_t Tester32_v = Tester32<0>::value;
constexpr size_t Tester33_v = Tester33<0>::value;
constexpr size_t Tester34_v = Tester34<0>::value;
constexpr size_t Tester35_v = Tester35<0>::value;
constexpr size_t Tester36_v = Tester36<0>::value;
constexpr size_t Tester37_v = Tester37<0>::value;
constexpr size_t Tester38_v = Tester38<0>::value;
constexpr size_t Tester39_v = Tester39<0>::value;

#endif

}}}

#endif