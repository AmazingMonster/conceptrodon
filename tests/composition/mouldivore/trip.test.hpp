// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_COMPOSITION_MOULDIVORE_TRIP_H
#define CONCEPTRODON_TESTS_COMPOSITION_MOULDIVORE_TRIP_H

#include <functional>
#include <map>
#include "conceptrodon/mouldivore/bind_front.hpp"
#include "conceptrodon/mouldivore/trip.hpp"
#include "conceptrodon/descend/mouldivore/tale.hpp" 
#include "conceptrodon/mouldivore/bind_back.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Mouldivore {
namespace CompositionTests {
namespace TestTrip {




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

template<typename...Elements>
using MakeFunctionAlias = void(Elements...);

SAME_TYPE
(
    Tale<BindBack<MakeFunctionAlias>::Mold>
    ::Mold<void*, void**>
    ::Flow<Tale>
    ::Flow<Trip>
    ::Road<Tale<std::function>::Mold>
    ::Road<BindBack<std::map>::Mold>
    ::Mold<int, int*>
    ::Mold<size_t>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

SAME_TYPE
(
    Tale<BindBack<MakeFunctionAlias>::Mold>
    ::Mold<void*, void**>
    ::Flow<Tale>
    ::Flow<Trip>
    ::Road<Tale<std::function>::Mold>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::map<size_t, std::function<void(int, int*, void*, void**)>>>

template<typename...Elements>
using MakeMap = Tale<BindBack<MakeFunctionAlias>::Mold>
    ::Mold<void*, void**>
    ::Flow<Tale>
    ::Flow<Trip>
    ::Road<Tale<std::function>::Mold>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<Elements...>;

SAME_TYPE
(
    Trip<Tale<MakeMap>::Mold>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::map<size_t, std::function<void(int, int*, void*, void**)>>>

template<typename...Elements>
using MakeNestedMap = Trip<Tale<MakeMap>::Mold>
    ::Road<BindFront<std::map>::Mold<size_t>::Mold>
    ::Mold<Elements...>;

SAME_TYPE(MakeNestedMap<int, int*>);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif