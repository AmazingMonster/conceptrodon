#ifndef CONCEPTRODON_MOULDIVORE_TEST_TRAVEL_H
#define CONCEPTRODON_MOULDIVORE_TEST_TRAVEL_H

#include <type_traits>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/mouldivore/travel.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace TestTravel {




/******************************************************************************************************/
template<typename...Elements>
struct TesterA
{ 
    using type = Capsule<Elements*...>; 
};

template<typename...>
struct TesterB 
{
    using type = Shuttle<0, 0, 0>;
};

template<auto...Variables>
struct TesterC
{ 
    using type = Shuttle<Variables + 1 ...>; 
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<int***, int***, int***>

SAME_TYPE(Travel<TesterA>::Road<TesterA>::Road<TesterA>::Mold<int, int, int>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<2, 2, 2>

SAME_TYPE(Travel<TesterB>::Rail<TesterC>::Rail<TesterC>::Mold<int>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif