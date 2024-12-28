/**** ConformedMetafunction ****/
template<typename...>
struct ConformedMetafunction
{
    template<auto...>
    struct ProtoPage
    {
        template<template<typename...> class...>
        struct ProtoRoad
        {
            template<template<auto...> class...>
            struct ProtoRail
            { static constexpr bool value {true}; };

            template<template<auto...> class...Sequences>
            using Rail = ProtoRail<Sequences...>;
        };

        template<template<typename...> class...Containers>
        using Road = ProtoRoad<Containers...>;
    };

    template<auto...Variables>
    using Page = ProtoPage<Variables...>;
};

/**** Test ****/
static_assert
(
    ConformedMetafunction<>::Page<>::Road<>::Rail
    <
        ConformedMetafunction<>::Page
    >
    ::value
);