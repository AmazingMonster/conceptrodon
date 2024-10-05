#ifndef CONCEPTRODON_PAGELIVORE_TEST_TRAVEL_H
#define CONCEPTRODON_PAGELIVORE_TEST_TRAVEL_H

#include <type_traits>
#include <utility>
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/pagelivore/travel.hpp"
#include "conceptrodon/shuttle.hpp"
#include "macaron/judgmental/same_type.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"

namespace Conceptrodon {
namespace Pagelivore {
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

template<auto...Variables>
struct TesterD
{ 
    using type = Shuttle<Variables * 10 ...>; 
};

template<auto...>
struct TesterE
{ 
    using type = Capsule<int, int, int>; 
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Shuttle<11, 11, 11>

SAME_TYPE(Travel<TesterC>::Rail<TesterD>::Rail<TesterC>::Page<0, 0, 0>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    Capsule<int**, int**, int**>

SAME_TYPE(Travel<TesterE>::Road<TesterA>::Road<TesterA>::Page<>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif