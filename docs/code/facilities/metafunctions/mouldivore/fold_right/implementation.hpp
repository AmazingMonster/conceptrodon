/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct FoldRight
{
    template<typename Initiator>
    struct ProtoMold
    {
        template<typename...Elements >
        struct Detail {};

        // Base Case:

        // Fold once.
        template<typename Element>
        struct Detail<Element>
        {
            using type = Operation<Element, Initiator>;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    Initiator
                >
                >;
        };

        // Recursive Case:

        // Write out the last two folds, handle the first two parameters,
        // and recurse using the rest to obtain the initiator.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            =   Operation<First,
                Operation<Second,
                    typename Detail<Others...>
                    ::type
                >
                >;
        };

        template<typename...Agreements>
        using Mold = Detail<Agreements...>::type;
    };
        
    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};

/*****************/
/**** Example ****/
/*****************/

#include <type_traits>

/**** Subtract ****/
template<typename A, typename B>
struct SubtractHelper
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

template<typename...Args>
using Subtract = SubtractHelper<Args...>::type;

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= FoldRight<Subtract>
::Mold<std::integral_constant<int, 3>>
::Mold<Args...>;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>
>;

/**** Test ****/
static_assert(Result::value == -1);