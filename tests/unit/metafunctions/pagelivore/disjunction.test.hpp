// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_DISJUNCTION_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_DISJUNCTION_H

#include "conceptrodon/metafunctions/pagelivore/disjunction.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestDisjunction {




/******************************************************************************************************/
/**** Pred_0 ****/
// Returns true if the argument is greater than 10.
template<auto...>
struct Pred_0
{ static constexpr bool value {false}; };

template<auto I>
requires (10 < I)
struct Pred_0<I>
{ static constexpr bool value {true}; };

/**** Pred_1 ****/
// Returns true if the argument is less than 0.
template<auto...>
struct Pred_1
{ static constexpr bool value {false}; };

template<auto I>
requires (I < 0)
struct Pred_1<I>
{ static constexpr bool value {true}; };

/**** Pred_2 ****/
// Returns true if the argument is even.
template<auto...>
struct Pred_2
{ static constexpr bool value {false}; };

template<auto I>
requires (I % 2 == 0)
struct Pred_2<I>
{ static constexpr bool value {true}; };

/**** Example ****/
template<auto...Args>
using Metafunction = Disjunction<Pred_0, Pred_1, Pred_2>
::Page<Args...>;
/******************************************************************************************************/




/******************************************************************************************************/
VALID(Metafunction<-1>::value);
VALID(Metafunction<2>::value);
INVALID(Metafunction<5>::value);
VALID(Metafunction<-2>::value);

// If no predicate is provided,
// the value is always `false`.
INVALID(Disjunction<>::Page<1, 2, 3>::value);
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif