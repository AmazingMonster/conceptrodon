/************************/
/**** Implementation ****/
/************************/

template<template<typename...> class Operation>
struct ClassicFoldRight
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
            using type = Operation<Element, Initiator>::type;
        };

        // Fold twice.
        template<typename First, typename Second>
        struct Detail<First, Second>
        {
            using type
            =   Operation<First,
                typename Operation<Second,
                    Initiator
                >::type
                >::type;
        };

        // Recursive Case:

        // Write out the last two folds, handle the first two parameters,
        // and recurse using the rest to obtain the initiator.
        template<typename First, typename Second, typename...Others>
        struct Detail<First, Second, Others...>
        {
            using type
            =   Operation<First,
                typename Operation<Second,
                    typename Detail<Others...>
                    ::type
                >::type
                >::type;
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
struct Subtract
{
    using type
    = std::integral_constant<int, A::value - B::value>;
};

/**** Metafunction ****/
template<typename...Args>
using Metafunction 
= ClassicFoldRight<Subtract>
::Mold<std::integral_constant<int, 3>>
::Mold<Args...>::type;

/**** Result ****/
using Result = Metafunction
<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>
>;

/**** Test ****/
static_assert(Result::value == -1);