// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_STATIC_CASTABLE_TO_BOOL_H
#define CONCEPTRODON_TYPELIVORE_UNIT_TESTS_TEST_STATIC_CASTABLE_TO_BOOL_H

#define CONCEPTRODON_CHECK_VIABILITY 0
#if CONCEPTRODON_CHECK_VIABILITY
#define CONCEPTRODON_BLANKET(...) __VA_ARGS__
#else
#define CONCEPTRODON_BLANKET(...)
#endif

#include "conceptrodon/concepts/typelivore/static_castable_to_bool.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestStaticCastableToBool {




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
static_assert(StaticCastableToBool<int>);
static_assert(StaticCastableToBool<int&>);
static_assert(StaticCastableToBool<int&&>);
static_assert(StaticCastableToBool<int const &&>);
static_assert(not StaticCastableToBool<void>);
static_assert(not StaticCastableToBool<Dummy>);
static_assert(StaticCastableToBool<Tester>);
static_assert(StaticCastableToBool<Tester&>);
static_assert(StaticCastableToBool<Tester&&>);
CONCEPTRODON_BLANKET(StaticCastableToBool<Tester const>)
static_assert(StaticCastableToBool<Tester_1 const>);
/******************************************************************************************************/




}}}}

#undef CONCEPTRODON_BLANKET
#undef CONCEPTRODON_CHECK_VIABILITY

#endif