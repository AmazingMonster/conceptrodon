// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_SITUATIONAL_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_COGNATE_SITUATIONAL_H

#include <type_traits>
#include "conceptrodon/pagelivore/cognate_situational.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestCognateSituational {




/******************************************************************************************************/
template<auto A, auto B, auto C>
struct PredA
{ 
    static constexpr bool value 
    {static_cast<bool>(A)}; 
};

template<auto A, auto B, auto C>
struct PredB
{ 
    static constexpr bool value 
    {static_cast<bool>(B)}; 
};

template<auto A, auto B, auto C>
struct PredC
{ 
    static constexpr bool value 
    {static_cast<bool>(C)}; 
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_VALUE   \
    std::true_type{}

EQUAL_VALUE(CognateSituational<PredA>::Page_v<std::true_type{}, std::false_type{}, 0>);
EQUAL_VALUE(! CognateSituational<PredA, PredC>::Page_v<std::true_type{}, std::false_type{}, 0>);
EQUAL_VALUE(CognateSituational<PredA, PredC>::Page_v<std::true_type{}, std::false_type{}, 1>);
EQUAL_VALUE(CognateSituational<PredA>::Page_v<std::false_type{}, std::true_type{}, 0>);
EQUAL_VALUE(CognateSituational<PredA, PredB>::Page_v<std::false_type{}, std::true_type{}, 0>);

#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif