#ifndef CONCEPTRODON_OMENNIVORE_TEST_FLATTEN_H
#define CONCEPTRODON_OMENNIVORE_TEST_FLATTEN_H

#include "conceptrodon/omennivore/flatten.hpp"
#include "conceptrodon/shuttle.hpp"
#include "conceptrodon/capsule.hpp"
#include "conceptrodon/reverie.hpp"
#include "conceptrodon/phantom.hpp"
#include "macaron/judgmental/valid.hpp"
#include "macaron/judgmental/invalid.hpp"

#include "macaron/judgmental/amenity/define_valid.hpp"
#include "macaron/judgmental/amenity/define_invalid.hpp"

namespace Conceptrodon {
namespace Omennivore {
namespace TestFlatten {

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


INVALID(Flatten<Tester>::Mold<Shuttle<>, Capsule<>, Shuttle<>, Capsule<>, Shuttle<>>::value);
VALID(Flatten<Tester>::Mold<Shuttle<>, Capsule<>, Shuttle<>, Capsule<>, Shuttle<1>>::value);
INVALID(Flatten<Tester>::Mold<Shuttle<>, Capsule<>, Shuttle<>, Capsule<>, Reverie<>, Shuttle<>>::value);
VALID(Flatten<Tester>::Mold<Shuttle<>, Capsule<>, Shuttle<>, Capsule<>,  Reverie<>, Shuttle<1>>::value);
VALID(Flatten<Tester>::Mold<Shuttle<>, Capsule<>, Shuttle<>, Capsule<>,  Reverie<std::tuple>>::value);


}}}

#include "macaron/judgmental/amenity/undef_valid.hpp"
#include "macaron/judgmental/amenity/undef_invalid.hpp"

#endif