#ifndef CONCEPTRODON_PAGELIVORE_TEST_TRIP_H
#define CONCEPTRODON_PAGELIVORE_TEST_TRIP_H

#include <type_traits>
#include <utility>
#include "conceptrodon/pagelivore/trip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace TestTrip {




/******************************************************************************************************/
template<auto V>
struct TesterA
{ 
    using type = TesterA; 
    static constexpr auto value {V * 10};
};

template<auto V>
struct TesterB
{
    using type = TesterB;
    static constexpr auto value {V + 1};
};

template<typename T>
struct TesterC
{
    static constexpr auto value {T::value + 1};
};
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    TesterC<TesterB<11>>
#define SUPPOSED_VALUE  \
    13

SAME_TYPE(Trip<TesterA>::Rail<TesterB>::Rail<TesterB>::Road<TesterC>::Page<1>);
EQUAL_VALUE(Trip<TesterA>::Rail<TesterB>::Rail<TesterB>::Road<TesterC>::Page<1>::value);

#undef SUPPOSED_TYPE
#undef SUPPOSED_VALUE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif