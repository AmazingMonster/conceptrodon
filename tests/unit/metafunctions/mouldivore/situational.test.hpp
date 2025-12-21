// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_SITUATIONAL_H
#define CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_SITUATIONAL_H

#include <utility>

#include "conceptrodon/utilities/vay.hpp"
#include "conceptrodon/metafunctions/mouldivore/situational.hpp"

#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestSituational {




/******************************************************************************************************/
template<typename A, typename B, typename C>
struct PredA
{ 
    static constexpr bool value 
    {static_cast<bool>(A::value)}; 
};

template<typename A, typename B, typename C>
struct PredB
{ 
    static constexpr bool value 
    {static_cast<bool>(B::value)}; 
};

template<typename A, typename B, typename C>
struct PredC
{ 
    static constexpr bool value 
    {static_cast<bool>(C::value)}; 
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::true_type

SAME_TYPE(Situational<PredA>::Mold<std::true_type, std::false_type, Vay<true>>);
SAME_TYPE(Situational<PredA>::Mold<std::false_type, std::true_type, Vay<true>>);
SAME_TYPE(Situational<PredA, PredC>::Mold<std::true_type, std::false_type, Vay<true>>);
SAME_TYPE(Situational<PredA, PredB>::Mold<std::false_type, std::true_type, Vay<true>>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::false_type

SAME_TYPE(Situational<PredA>::Mold<std::false_type, std::false_type, Vay<true>>);
SAME_TYPE(Situational<PredA, PredC>::Mold<std::true_type, std::false_type, Vay<false>>);
SAME_TYPE(Situational<PredA, PredB>::Mold<std::true_type, std::false_type, Vay<true>>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif