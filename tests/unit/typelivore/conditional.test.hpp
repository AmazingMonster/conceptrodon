// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_TYPELIVORE_CONDITIONAL_H
#define CONCEPTRODON_TESTS_UNIT_TYPELIVORE_CONDITIONAL_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/typelivore/conditional.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Typelivore {
namespace UnitTests {
namespace TestConditional {




/******************************************************************************************************/
template<typename...>
using MoldT = std::true_type;

template<typename...>
using MoldF = std::false_type;

template<auto...>
using PageT = std::true_type;

template<auto...>
using PageF = std::false_type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::true_type

SAME_TYPE(Conditional<std::true_type, std::false_type>::Road<MoldT, MoldT, MoldT, MoldT>::Mold_t<int>);
SAME_TYPE(Conditional<std::true_type, std::false_type>::Rail<PageT, PageT, PageT, PageT>::Page_t<1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::false_type

SAME_TYPE(Conditional<std::true_type, std::false_type>::Road<MoldF, MoldT, MoldT, MoldT>::Mold_t<int>);
SAME_TYPE(Conditional<std::true_type, std::false_type>::Rail<PageF, PageT, PageT, PageT>::Page_t<1>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif