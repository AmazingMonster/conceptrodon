// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDIVORE_TEST_POP_H
#define CONCEPTRODON_MOULDIVORE_TEST_POP_H

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
namespace TestPop {




/******************************************************************************************************/
using SupposedResult = Capsule<>;
/******************************************************************************************************/




/******************************************************************************************************/
template<typename T>
struct Predicate
{ static constexpr bool value {T::size()==0}; };
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(Recur<Agent<Typelivore::Pop>::Mold>::Road<Predicate>::Mold_t<Capsule<SHEEP_SPROUT(240)>>::type);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif