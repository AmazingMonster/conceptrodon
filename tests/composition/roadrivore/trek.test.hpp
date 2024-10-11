// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_COMPOSITION_ROADRIVORE_TREK_H
#define CONCEPTRODON_TESTS_COMPOSITION_ROADRIVORE_TREK_H

#include <functional>
#include <map>
#include "conceptrodon/descend/descend/mouldivore/delay.hpp"
#include "conceptrodon/descend/descend/mouldivore/defer.hpp"
#include "conceptrodon/mouldivore/bind_front.hpp"
#include "conceptrodon/roadrivore/trek.hpp"
#include "conceptrodon/descend/roadrivore/memorize.hpp"
#include "conceptrodon/mouldivore/trek.hpp"
#include "conceptrodon/emissary.hpp"
#include "conceptrodon/mouldivore/bind_back.hpp"
#include "conceptrodon/descend/descend/descend/mouldivore/yore.hpp"
#include "conceptrodon/descend/descend/descend/roadrivore/past.hpp"
#include "conceptrodon/mouldivore/mold_diverge.hpp"
#include "conceptrodon/roadrivore/road_deviate.hpp"
#include "conceptrodon/descend/descend/roadrivore/delay.hpp"
#include "macaron/judgmental/same_type.hpp"
#include "macaron/judgmental/equal_value.hpp"

#include "macaron/judgmental/amenity/define_same_type.hpp"
#include "macaron/judgmental/amenity/define_equal_value.hpp"

namespace Conceptrodon {
namespace Roadrivore {
namespace CompositionTests {
namespace TestTrek {




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

template<typename...Elements>
using MakeFunctionAlias = void(Elements...);

SAME_TYPE
(

    Trek<Mouldivore::BindFront>
    ::Flow<Mouldivore::Trek>
    ::Snow
    <
        Mouldivore::Trek<Mouldivore::BindBack<MakeFunctionAlias>::Mold>
        ::Flow
        <
            Mouldivore::Yore<std::function>
            ::Road
        >
        ::Flow<Mouldivore::MoldDiverge>
        ::Flow
    >
    ::Road<std::map>
    ::Mold<void*, void**>
    ::Mold<size_t>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

template<typename...Elements>
using MakeFunctionAlias = void(Elements...);

SAME_TYPE
(
    
    Memorize
    <
        Trek<Mouldivore::BindFront>
        ::Flow<Mouldivore::Trek>
        ::Road
    >
    ::Flow<Mouldivore::Defer>
    ::Flow
    <
        Mouldivore::Trek<Mouldivore::BindBack<MakeFunctionAlias>::Mold>
        ::Flow
        <
            Mouldivore::Yore<std::function>
            ::Road
        >
        ::Road
    >
    ::Road<std::map>
    ::Mold<size_t>
    ::Mold<void*, void**>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




/******************************************************************************************************/
#define SUPPOSED_TYPE   \
    std::map<size_t, std::function<void(int, int*, void*, void**)>>

template<typename...Elements>
using MakeFunctionAlias = void(Elements...);

SAME_TYPE
(
    Mouldivore::Trek<Mouldivore::BindBack<MakeFunctionAlias>::Mold>
    ::Flow
    <
        Mouldivore::Yore<std::function>
        ::Road
    >
    ::Flow<Mouldivore::MoldDiverge>
    ::Flow
    <
        Memorize
        <
            Trek<Mouldivore::BindFront>
            ::Flow<Mouldivore::Trek>
            ::Road
        >
        ::SubRoad
    >
    ::Mold<void*, void**>
    ::Road<std::map>
    ::Mold<size_t>
    ::Mold<int, int*>
);

#undef SUPPOSED_TYPE
/******************************************************************************************************/




}}}}

#include "macaron/judgmental/amenity/undef_same_type.hpp"
#include "macaron/judgmental/amenity/undef_equal_value.hpp"

#endif