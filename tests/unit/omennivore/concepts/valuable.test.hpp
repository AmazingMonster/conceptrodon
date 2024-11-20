// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_OMENNIVORE_VALUABLE_H
#define CONCEPTRODON_TESTS_UNIT_OMENNIVORE_VALUABLE_H

#include "conceptrodon/descend/omennivore/concepts/valuable.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"
#include <type_traits>

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestValuable {




/******************************************************************************************************/
struct Tester
{
    static constexpr bool value = true;
};

VALID(Valuable<Tester>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_1
{
    static constexpr bool value() {return true;};
};

INVALID(Valuable<Tester_1>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_2
{
    using value = int;
};

INVALID(Valuable<Tester_2>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_3
{
    bool value;
};

INVALID(Valuable<Tester_3>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_4
{
    bool const value;
};

INVALID(Valuable<Tester_4>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_5
{
    static bool const value;
};

bool const Tester_5::value {true};

}

VALID(Valuable<Tester_5>);
/******************************************************************************************************/




/******************************************************************************************************/
namespace {

struct Tester_6
{
    static float const value;
};

float const Tester_6::value {1.11};

}

INVALID(Valuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
struct Tester_7
{
    static bool const value;
};

INVALID(Valuable<Tester_6>);
/******************************************************************************************************/




/******************************************************************************************************/
template<typename...>
struct Tester_8 {};

template<typename Element>
requires Varybivore::Divulge
<
    Ominuci::isValueImmediate<decltype(Element::value)>,
    Element::value
>
struct Tester_8<Element>
{
    static constexpr int value {-1};
};

template<typename Element>
requires Typelivore::Clarify<std::is_const, const decltype(Element::value)>
struct Tester_8<Element>
{
    static constexpr int value {0};
};

template<typename Element>
requires Valuable<Element>
struct Tester_8<Element>
{
    static constexpr int value {1};
};

static_assert(Tester_8<std::integral_constant<int, 1>>::value == 1);
/******************************************************************************************************/

}}}}

#endif