// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_RECUR_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_RECUR_H

#include <utility>

#include "conceptrodon/descend/typelivore/pop.hpp"
#include "conceptrodon/descend/mouldivore/recur.hpp"
#include "conceptrodon/mouldivore/agent.hpp"
#include "conceptrodon/capsule.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestRecur {




/******************************************************************************************************/
template<typename T>
struct Pred_0
{ static constexpr bool value {T::size() <= 1}; };

template<typename T>
struct Pred_1
{ static constexpr bool value {T::size() >= 1}; };
/******************************************************************************************************/




/******************************************************************************************************/
using SupposedResult = Capsule<std::integral_constant<int, 0>>;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE
(
    Recur<Agent<Typelivore::Pop>::Mold>
    ::Road<Pred_0, Pred_1>
    ::Mold<Capsule<SHEEP_SPROUT(240)>>
);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif