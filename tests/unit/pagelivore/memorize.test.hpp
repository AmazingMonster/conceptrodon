// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_TESTS_UNIT_PAGELIVORE_MEMORIZE_H
#define CONCEPTRODON_TESTS_UNIT_PAGELIVORE_MEMORIZE_H

#include "conceptrodon/descend/pagelivore/memorize.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Pagelivore {
namespace UnitTests {
namespace TestMemorize {

template<auto...>
struct Tester
{
    template<auto...>
    struct ProtoPage
    {
        template<typename...>
        struct ProtoMold
        {
            template<auto...>
            struct ProtoPage
            {
                template<typename...>
                struct ProtoMold
                {

                    template<template<typename...> class...>
                    struct ProtoRoad
                    {

                        template<auto...>
                        struct ProtoPage
                        {
                            static constexpr bool value {false};
                        };
                        
                        template<>
                        struct ProtoPage<1>
                        {
                            static constexpr bool value {true};
                        };

                        template<auto...Agreements>
                        using Page = ProtoPage<Agreements...>;
                    };

                    template<>
                    struct ProtoRoad<std::tuple>
                    {
                        static constexpr bool value {true};
                    };

                    template<template<typename...> class...Agreements>
                    using Road = ProtoRoad<Agreements...>;

                    template<auto...>
                    struct ProtoPage
                    {
                        static constexpr bool value {false};
                    };
                    
                    template<>
                    struct ProtoPage<1>
                    {
                        static constexpr bool value {true};
                    };

                    template<auto...Agreements>
                    using Page = ProtoPage<Agreements...>;
                };
        
                template<typename...Agreements>
                using Mold = ProtoMold<Agreements...>;
            };

            template<auto...Agreements>
            using Page = ProtoPage<Agreements...>;
        };
        
        template<typename...Agreements>
        using Mold = ProtoMold<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};


INVALID(Memorize<Tester>::SubPage<>::Mold<>::SubPage<>::Mold<>::SubPage<>::Page<>::value);
VALID(Memorize<Tester>::SubPage<>::Mold<>::SubPage<>::Mold<>::SubPage<1>::Page<>::value);
INVALID(Memorize<Tester>::SubPage<>::Mold<>::SubPage<>::Mold<>::Road<>::SubPage<>::Page<>::value);
VALID(Memorize<Tester>::SubPage<>::Mold<>::SubPage<>::Mold<>::Road<>::SubPage<1>::Page<>::value);
VALID(Memorize<Tester>::SubPage<>::Mold<>::SubPage<>::Mold<>::Road<std::tuple>::Page<>::value);


}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif