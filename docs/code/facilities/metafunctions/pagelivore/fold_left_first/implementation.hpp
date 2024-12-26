/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct FoldLeftFirst
{
    template<auto...Variables>
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Initiator, auto Variable>
    struct ProtoPage<Initiator, Variable>
    {
        static constexpr auto value 
        { Operation<Initiator, Variable>::value };
    };

    // Fold twice.
    template<auto Initiator, auto First, auto Second>
    struct ProtoPage<Initiator, First, Second>
    {
        static constexpr auto value {
            Operation<
            Operation<
                Initiator, First
            >::value, Second
            >::value
        };
    };

    // Recursive Case:

    // Fold twice, handle the first three parameters,
    // and recurse using the rest.
    template<auto Initiator, auto First, auto Second, auto...Others>
    struct ProtoPage<Initiator, First, Second, Others...>
    {
        static constexpr auto value {
            ProtoPage<
                Operation<
                Operation<
                    Initiator, First
                >::value, Second
                >::value, Others...
            >::value
        };
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
    { A-B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldLeftFirst<Subtract>::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 3, 4, 3>::value == -9);