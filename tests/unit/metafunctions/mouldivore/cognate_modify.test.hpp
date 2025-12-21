// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_COGNATE_MODIFY_H
#define CONCEPTRODON_MOULDVORE_UNIT_TESTS_TEST_COGNATE_MODIFY_H

#include "conceptrodon/metafunctions/mouldivore/cognate_modify.hpp"

#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"
#include "macaron/fragmental/double_sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestCognateModify {




/******************************************************************************************************/
template<typename...Args>
using PlusOne = std::integral_constant<int, (Args::value + 1)...>;

template<typename...Elements>
requires (sizeof...(Elements) == 240)
struct Operation {};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    std::integral_constant<int,
#define DOUBLE_SHEEP_MIDDLE \
    * 2 + 1>, std::integral_constant<int, 
#define DOUBLE_SHEEP_SUFFIX \
    * 2 + 1>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Operation<DOUBLE_SHEEP_SPROUT(120)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(CognateModify<Operation>::Road<PlusOne>::Page<SHEEP_SPROUT(120, *2)>::Mold<LLAMA_SPROUT(240)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_llama.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif