#ifndef CONCEPTRODON_OMENNIVORE_TEST_HARVEST_VARIABLES_H
#define CONCEPTRODON_OMENNIVORE_TEST_HARVEST_VARIABLES_H

#include <type_traits>
#include "conceptrodon/descend/omennivore/harvest_variables.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace TestHarvestVariables {




/******************************************************************************************************/
template<auto...Variables>
requires (sizeof...(Variables)==240)
struct TesterA {};

template<auto I>
struct TesterB
{ static constexpr auto value {I}; };
/******************************************************************************************************/




/******************************************************************************************************/
#include "macaron/fragmental/amenity/instances/define_integer_sheep.hpp"
using SupposedResult = TesterA<SHEEP_SPROUT(240)>;
#include "macaron/fragmental/amenity/instances/undef_integer_sheep.hpp"
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    TesterB<
#define SHEEP_SUFFIX    \
    >
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(HarvestVariables<SHEEP_SPROUT(240)>::UniRail<TesterA>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"

#endif