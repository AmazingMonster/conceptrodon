// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_MOULDIVORE_INSERT_H
#define CONCEPTRODON_TESTS_UNIT_MOULDIVORE_INSERT_H

#include <concepts>
#include "conceptrodon/descend/descend/mouldivore/insert.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/llama.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_llama.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace UnitTests {
namespace TestInsert {




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
using SupposedResult = Capsule<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/define_integral_constant_llama.hpp"
SAME_TYPE(Insert<Capsule>::Mold<LLAMA_SPROUT(120, *2+1)>::Page<SHEEP_SPROUT(120, *2)>::Mold<LLAMA_SPROUT(120, *2)>);
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
#include "macaron/fragmental/amenity/instances/undef_integral_constant_llama.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_llama.hpp"

#endif