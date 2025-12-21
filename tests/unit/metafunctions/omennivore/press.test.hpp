// Copyright 2024 Feng Mofan
// SPDX-License-Identifier: Apache-2.0

#ifndef CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_PRESS_H
#define CONCEPTRODON_OMENNIVORE_UNIT_TESTS_TEST_PRESS_H

#include "conceptrodon/metafunctions/omennivore/press.hpp"

#include "conceptrodon/utilities/capsule.hpp"
#include "conceptrodon/utilities/shuttle.hpp"
#include "conceptrodon/utilities/vehicle.hpp"
#include "conceptrodon/utilities/carrier.hpp"
#include "conceptrodon/utilities/reverie.hpp"
#include "conceptrodon/utilities/phantom.hpp"
#include "conceptrodon/utilities/forlorn.hpp"
#include "conceptrodon/utilities/travail.hpp"
#include "conceptrodon/utilities/lullaby.hpp"
#include "conceptrodon/utilities/halcyon.hpp"
#include "conceptrodon/utilities/persist.hpp"
#include "conceptrodon/utilities/pursuit.hpp"
#include "conceptrodon/utilities/sunrise.hpp"
#include "conceptrodon/utilities/morning.hpp"

#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace UnitTests {
namespace TestPress {

struct Operation
{
    template<typename...>
    struct ProtoMold
    {
        template<auto...>
        struct ProtoPage
        {
            template<template<typename...> class...>
            struct ProtoRoad
            {
                template<template<auto...> class...>
                struct ProtoRail
                {
                    template<template<template<typename...> class...> class...>
                    struct ProtoFlow
                    {
                        template<template<template<auto...> class...> class...>
                        struct ProtoSail
                        {
                            template<template<template<template<typename...> class...> class...> class...>
                            struct ProtoSnow
                            {
                                template<template<template<template<auto...> class...> class...> class...>
                                struct ProtoHail
                                {
                                    template<template<template<template<template<typename...> class...> class...> class...> class...>
                                    struct ProtoCool
                                    {
                                        template<template<template<template<template<auto...> class...> class...> class...> class...>
                                        struct ProtoCalm
                                        {
                                            template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...>
                                            struct ProtoGrit
                                            {
                                                template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...>
                                                struct ProtoWill
                                                {
                                                    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...>
                                                    struct ProtoGlow
                                                    {
                                                        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...>
                                                        struct ProtoDawn
                                                        {
                                                            static constexpr bool value {true};
                                                        };

                                                        template<template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...> class...Agreements>
                                                        using Dawn = ProtoDawn<Agreements...>;
                                                    };

                                                    template<template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...> class...Agreements>
                                                    using Glow = ProtoGlow<Agreements...>;
                                                };

                                                template<template<template<template<template<template<auto...> class...> class...> class...> class...> class...Agreements>
                                                using Will = ProtoWill<Agreements...>;
                                            };

                                            template<template<template<template<template<template<typename...> class...> class...> class...> class...> class...Agreements>
                                            using Grit = ProtoGrit<Agreements...>;
                                        };

                                        template<template<template<template<template<auto...> class...> class...> class...> class...Agreements>
                                        using Calm = ProtoCalm<Agreements...>;
                                    };

                                    template<template<template<template<template<typename...> class...> class...> class...> class...Agreements>
                                    using Cool = ProtoCool<Agreements...>;
                                };

                                template<template<template<template<auto...> class...> class...> class...Agreements>
                                using Hail = ProtoHail<Agreements...>;
                            };

                            template<template<template<template<typename...> class...> class...> class...Agreements>
                            using Snow = ProtoSnow<Agreements...>;
                        };

                        template<template<template<auto...> class...> class...Agreements>
                        using Sail = ProtoSail<Agreements...>;
                    };

                    template<template<template<typename...> class...> class...Agreements>
                    using Flow = ProtoFlow<Agreements...>;
                };

                template<template<auto...> class...Agreements>
                using Rail = ProtoRail<Agreements...>;
            };

            template<template<typename...> class...Agreements>
            using Road = ProtoRoad<Agreements...>;
        };

        template<auto...Agreements>
        using Page = ProtoPage<Agreements...>;

        struct Slash
        {
            template<typename...>
            struct ProtoMold
            {
                static constexpr bool value {false};
            };
            
            template<>
            struct ProtoMold<std::true_type>
            {
                static constexpr bool value {true};
            };
        };

        template<typename...Agreements>
        using Mold = Slash::template ProtoMold<Agreements...>;
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

VALID
(
    Press<Operation>
    ::Mold
    <
        Capsule<>,
        Shuttle<>,
        Vehicle<>,
        Carrier<>,
        Reverie<>,
        Phantom<>,
        Forlorn<>,
        Travail<>,
        Lullaby<>,
        Halcyon<>,
        Pursuit<>,
        Persist<>,
        Sunrise<>,
        Morning<>
    >::value
);

VALID(Press<Operation>::Mold<Capsule<>, Capsule<std::true_type>>::value);
INVALID(Press<Operation>::Mold<Capsule<>, Capsule<>>::value);

}}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif