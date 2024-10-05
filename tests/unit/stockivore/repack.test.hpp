#ifndef CONCEPTRODON_STOCKIVORE_TEST_REPACK_H
#define CONCEPTRODON_STOCKIVORE_TEST_REPACK_H

#include <concepts>
#include "conceptrodon/stockivore/repack.hpp"
#include "conceptrodon/phantom.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"

#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/judgmental/amenity/define_same_type.hpp"


namespace Conceptrodon {
namespace Stockivore {
namespace TestRepack {




/******************************************************************************************************/
template<size_t>
struct Tester
{
    template<auto...>
    struct ProtoPage {};

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

template<template<auto...> class...>
struct Transport {};
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX    \
    Tester<
#define SHEEP_SUFFIX    \
    >::Page
#define SHEEP_SEPARATOR \
    ,

using SupposedResult = Transport<SHEEP_SPROUT(240)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    SupposedResult

#define SHEEP_PREFIX    \
    Phantom<Tester<
#define SHEEP_SUFFIX    \
    >::Page>
#define SHEEP_SEPARATOR \
    ,

SAME_TYPE(Repack<SHEEP_SPROUT(240)>::UniSail<Transport>);

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR

#undef SUPPOSED_TYPE
/**************************************************************************************************/


}}}


#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/judgmental/amenity/undef_same_type.hpp"

#endif