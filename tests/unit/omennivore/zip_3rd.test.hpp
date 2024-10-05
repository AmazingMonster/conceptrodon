#ifndef CONCEPTRODON_OMENNIVORE_TEST_ZIP_3RD_H
#define CONCEPTRODON_OMENNIVORE_TEST_ZIP_3RD_H

#include "conceptrodon/capsule.hpp"
#include "conceptrodon/descend/omennivore/zip.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/fragmental/sheep.hpp"
#include "macaron/fragmental/double_sheep.hpp"
#include <utility>

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/fragmental/amenity/define_sheep.hpp"
#include "macaron/fragmental/amenity/define_double_sheep.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace TestZip3rd {




/******************************************************************************************************/
template<size_t>
struct TesterA 
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};


template<size_t>
struct TesterB 
{
    template<typename...>
    struct ProtoMold {};

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};


template<typename>
struct TesterC {};

template<template<template<typename...> class...> class Warehouse, template<typename...> class A, template<typename...> class B>
struct TesterC<Warehouse<A, B>>
{ using type = Capsule<A<int>, B<int>>; };

template<typename>
struct TesterD {};

template<template<typename...> class Container, typename...Elements>
struct TesterD<Container<Elements...>>
{
    using type = Capsule<typename TesterC<Elements>::type...>;
};
/******************************************************************************************************/




/******************************************************************************************************/
#define DOUBLE_SHEEP_PREFIX \
    Capsule<TesterA<
#define DOUBLE_SHEEP_MIDDLE \
    >::Mold<int>, TesterB<
#define DOUBLE_SHEEP_SUFFIX \
    >::Mold<int>>
#define DOUBLE_SHEEP_SEPARATOR  \
    ,

using SupposedResult = Capsule<DOUBLE_SHEEP_SPROUT(120)>;

#undef DOUBLE_SHEEP_PREFIX
#undef DOUBLE_SHEEP_MIDDLE
#undef DOUBLE_SHEEP_SUFFIX
#undef DOUBLE_SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterA<
#define SHEEP_SUFFIX \
    >::Mold
#define SHEEP_SEPARATOR  \
    ,

using ArgA = Reverie<SHEEP_SPROUT(120)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SHEEP_PREFIX \
    TesterB<
#define SHEEP_SUFFIX \
    >::Mold
#define SHEEP_SEPARATOR  \
    ,

using ArgB = Reverie<SHEEP_SPROUT(150)>;

#undef SHEEP_PREFIX
#undef SHEEP_SUFFIX
#undef SHEEP_SEPARATOR
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE \
    SupposedResult

SAME_TYPE(TesterD<Zip<ArgA, ArgB>::type>::type);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/fragmental/amenity/undef_sheep.hpp"
#include "macaron/fragmental/amenity/undef_double_sheep.hpp"

#endif