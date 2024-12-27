/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct KindredFoldRight {};

// Base Case:

// Fold once.
template<auto Variable>
struct KindredFoldRight<Variable>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            { Operation<Variable, Initiator>::value };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Fold twice.
template<auto First, auto Second>
struct KindredFoldRight<First, Second>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value 
            { 
                Operation<First,
                Operation<Second,
                    Initiator
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

// Recursive Case:

// Write out the last two folds, handle the first two parameters,
// and recurse using the rest to obtain the initiator.
template<auto First, auto Second, auto...Others>
struct KindredFoldRight<First, Second, Others...>
{
    template<auto Initiator>
    struct ProtoPage
    {
        template<template<auto...> class Operation>
        struct ProtoRail
        {
            static constexpr auto value
            {
                Operation<First,
                Operation<Second,
                    KindredFoldRight<Others...>
                    ::template Page<Initiator>
                    ::template Rail<Operation>
                    ::value
                >::value
                >::value
            };
        };

        template<template<auto...> class...Agreements>
        using Rail = ProtoRail<Agreements...>;
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A - B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= KindredFoldRight<1, 3, 4>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<3>::Rail<Subtract>::value == -1);