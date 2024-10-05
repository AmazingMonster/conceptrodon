#ifndef CONCEPTRODON_MOULDIVORE_TEST_FOLD_RIGHT_H
#define CONCEPTRODON_MOULDIVORE_TEST_FOLD_RIGHT_H

#include <concepts>
#include <type_traits>
#include "conceptrodon/mouldivore/fold_right.hpp"
#include "conceptrodon/capsule.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestFoldRight {




/******************************************************************************************************/
template<typename Left, typename Right>
struct BinaryOperation
{ using type = std::integral_constant<int, Left::value + Right::value>; };

template<typename Left, typename Right>
requires (Left::value < Right::value)
struct BinaryOperation<Left, Right>
{ using type = std::integral_constant<int, 1>; };

template<typename Left, typename Right>
using BinaryOperation_t = BinaryOperation<Left, Right>::type;
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 2>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(FoldRight<BinaryOperation>::Mold<std::integral_constant<int, 239>>::Mold_t<std::integral_constant<int, 1>, SHEEP_SPROUT(239)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 2>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(FoldRight<BinaryOperation>::Mold<std::integral_constant<int, 7>>::Mold_t<std::integral_constant<int, 1>, SHEEP_SPROUT(7)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    std::integral_constant<int, 1>

#include "macaron/fragmental/amenity/instances/define_integral_constant_sheep.hpp"
SAME_TYPE(FoldRight<BinaryOperation>::Mold<std::integral_constant<int, 1>>::Mold_t<SHEEP_SPROUT(1)>);
#include "macaron/fragmental/amenity/instances/undef_integral_constant_sheep.hpp"

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif