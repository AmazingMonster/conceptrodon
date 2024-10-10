// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_COMPOSITION_MOULDIVORE_TRIP_H
#define CONCEPTRODON_TESTS_COMPOSITION_MOULDIVORE_TRIP_H

#include <functional>
#include <map>
#include "conceptrodon/mouldivore/bind_front.hpp"
#include "conceptrodon/mouldivore/trip.hpp"
#include "conceptrodon/descend/descend/descend/mouldivore/past.hpp"
#include "conceptrodon/mouldivore/conceal.hpp" 
#include "conceptrodon/mouldivore/bind_back.hpp"
#include "conceptrodon/descend/descend/mouldivore/delay.hpp"
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
    Past
    <
        Trip<Conceal<std::function>::Mold>
        ::Road<BindFront<std::map>::Mold<size_t>::Mold>
        ::Mold
    >
    ::Road<Conceal<BindBack<MakeFunctionAlias>::Mold<void*, void**>::Mold>::Mold>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

SAME_TYPE
(
    Past<BindFront<std::map>::Mold<size_t>::Mold>
    ::Road
    <
        Trip<Conceal<BindBack<MakeFunctionAlias>::Mold<void*, void**>::Mold>::Mold>
        ::Road<Conceal<std::function>::Mold>
        ::Mold
    >
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

SAME_TYPE
(
    Trip<BindFront<std::map>::Mold>
    ::Flow<Delay>
    ::Flow
    <
        Trip
        <
            Conceal
            <
                Trip<BindBack<MakeFunctionAlias>::Mold>
                ::Flow<Conceal>
                ::Flow
                <    
                    Past<Conceal<std::function>::Mold>
                    ::Road
                >
                ::Mold
            >::Mold
        >
        ::Road
    >
    ::Mold<size_t>
    ::Mold<void*, void**>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/



}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif