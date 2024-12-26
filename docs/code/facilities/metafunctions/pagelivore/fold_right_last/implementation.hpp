/************************/
/**** Implementation ****/
/************************/

template<template<auto...> class Operation>
struct FoldRightLast
{
    template<auto...Variables >
    struct ProtoPage {};

    // Base Case:

    // Fold once.
    template<auto Variable, auto Initiator>
    struct ProtoPage<Variable, Initiator>
    {
        static constexpr auto value
        { Operation<Variable, Initiator>::value };
    };

    // Fold twice.
    template<auto First, auto Second, auto Initiator>
    struct ProtoPage<First, Second, Initiator>
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

    // Recursive Case:

    // Write out the last two folds, handle the first two parameters,
    // and recurse using the rest to obtain the initiator.
    template<auto First, auto Second, auto...Others>
    struct ProtoPage<First, Second, Others...>
    {
        static constexpr auto value
        {
            Operation<First,
            Operation<Second,
                FoldRightLast<Operation>
                ::template ProtoPage<Others...>
                ::value
            >::value
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
    { A - B };
};

/**** Metafunction ****/
template<auto...Args>
using Metafunction 
= FoldRightLast<Subtract>
::Page<Args...>;

/**** Test ****/
static_assert(Metafunction<1, 3, 4, 3>::value == -1);