// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_SITUATIONAL_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_SITUATIONAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/mouldivore/situational.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestSituational {




/******************************************************************************************************/
template<typename A, typename B>
struct Predicate 
{ 
    static constexpr bool value 
    {static_cast<bool>(A::value)}; 
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::true_type

SAME_TYPE(Situational<Predicate>::Mold_t<std::true_type, std::false_type>);
SAME_TYPE(Situational<Predicate>::Mold_t<std::false_type, std::true_type>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif