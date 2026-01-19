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

/**** TypicalDiversity ****/
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

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
using MakeSet = TypicalDiversity<>
::ProtoMold<Elements...>
::type;

/*****************/
/**** Example ****/
/*****************/

#include <concepts>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** SupposedResult ****/
using SupposedResult = Capsule<int, int*, int**>;

/**** Result ****/
using Result = MakeSet<int, int*, int**, int**>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);