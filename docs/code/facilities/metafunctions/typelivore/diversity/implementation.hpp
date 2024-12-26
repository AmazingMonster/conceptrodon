/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Capsule ****/
template<typename...>
struct Capsule;

template<typename...InspectedElements>
struct TypicalDiversity: public std::type_identity<InspectedElements>...
{

// Recursive Case:
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = std::conditional
        <
            std::is_base_of<
                std::type_identity<InspectingElement>,
                TypicalDiversity
            >::value, 
            TypicalDiversity, 
            TypicalDiversity<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;
    };

// Base Case:
    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<
                std::type_identity<InspectingElement>,
                TypicalDiversity
            >::value, 
            Capsule<InspectedElements...>, 
            Capsule<InspectedElements..., InspectingElement>
        >::type;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Diversity
{
    template<typename...Agreements>
    using Mold = TypicalDiversity<Elements...>
    ::template ProtoMold<Agreements...>
    ::type;
};

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Diversity<int*, void>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int*, void, int, int**>;

/**** Result ****/
using Result = Metafunction<int, int*, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);