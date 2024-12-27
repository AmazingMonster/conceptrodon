/************************/
/**** Implementation ****/
/************************/

template<auto...Variables>
struct KindredFoldLeftFirst {};

// Base Case:

// Fold once.
template<auto Initiator, auto Variable>
struct KindredFoldLeftFirst<Initiator, Variable>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Fold twice.
template<auto Initiator, auto First, auto Second>
struct KindredFoldLeftFirst<Initiator, First, Second>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<auto Initiator, auto First, auto Second, auto...Others>
struct KindredFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<auto...> class Operation>
    struct ProtoRail
    {
        static constexpr auto value {
            KindredFoldLeftFirst<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::template Rail<Operation>
            ::value
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

/**** Subtract ****/
template<auto A, auto B>
struct Subtract
{
    static constexpr auto value
    { A-B };
};

/**** Metafunction */
template<template<auto...> class...Args>
using Metafunction 
= KindredFoldLeftFirst<1, 3, 4, 3>::Rail<Args...>;

/**** Test ****/
static_assert(Metafunction<Subtract>::value == -9);