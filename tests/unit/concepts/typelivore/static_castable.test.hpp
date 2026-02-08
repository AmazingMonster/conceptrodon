// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_STATIC_CASTABLE_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_STATIC_CASTABLE_H

#define CONCEPTRODON_CHECK_VIABILITY 0
#if CONCEPTRODON_CHECK_VIABILITY
#define CONCEPTRODON_BLANKET(...) __VA_ARGS__
#else
#define CONCEPTRODON_BLANKET(...)
#endif

#include "conceptrodon/concepts/typelivore/static_castable.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestStaticCastable {




/******************************************************************************************************/
/**** Dummy ****/
struct Dummy {};

/**** Tester ****/
struct Tester
{
    operator bool();
};

/**** Tester ****/
struct Tester_1
{
    operator bool() const;
};
/******************************************************************************************************/




/******************************************************************************************************/
static_assert(StaticCastable<int, bool>);
static_assert(StaticCastable<int&, bool>);
static_assert(StaticCastable<int&&, bool>);
static_assert(StaticCastable<int const &&, bool>);
static_assert(not StaticCastable<void, bool>);
static_assert(not StaticCastable<Dummy, bool>);
static_assert(StaticCastable<Tester, bool>);
static_assert(StaticCastable<Tester&, bool>);
static_assert(StaticCastable<Tester&&, bool>);
CONCEPTRODON_BLANKET(StaticCastable<Tester const, bool>)
static_assert(StaticCastable<Tester_1 const, bool>);
/******************************************************************************************************/




}}}}

#undef CONCEPTRODON_BLANKET
#undef CONCEPTRODON_CHECK_VIABILITY

#endif