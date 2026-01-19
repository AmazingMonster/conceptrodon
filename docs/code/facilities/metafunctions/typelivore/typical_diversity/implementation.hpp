/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Tyy ****/
template<typename Element>
struct Tyy
{
    using type = Element;
};

/**** Capsule ****/
template<typename...>
struct Capsule;

/************************/
/**** Implementation ****/
/************************/

template<typename...InspectedElements>
struct TypicalDiversity: public Tyy<InspectedElements>...
{

// Recursive Case:
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        using type = std::conditional
        <
            std::is_base_of<
                Tyy<InspectingElement>,
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
                Tyy<InspectingElement>,
                TypicalDiversity
            >::value, 
            Capsule<InspectedElements...>, 
            Capsule<InspectedElements..., InspectingElement>
        >::type;
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
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
using Metafunction = TypicalDiversity<int*, void>
::Mold<Args...>;

/**** SupposedResult ****/
using SupposedResult = Capsule<int*, void, int, int**>;

/**** Result ****/
using Result = Metafunction<int, int*, int**>::type;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);