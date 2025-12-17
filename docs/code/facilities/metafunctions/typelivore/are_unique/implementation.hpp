/**********************/
/**** Dependencies ****/
/**********************/

#include <type_traits>

/**** Capsule ****/
template<typename...>
struct Capsule;

/**** AreOverlapping ****/
template<typename...InspectedElements>
struct AreOverlapping
: public std::type_identity<InspectedElements>...
{
    struct Detail
    {
        template<typename...>
        struct ProtoMold
        { using type = void; };
    };

// Recursive Case:
    template<typename InspectingElement, typename...RestElements>
    struct ProtoMold
    {
        // `Detail` will stop recursion, achieving short-circuit.
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>,AreOverlapping>::value, 
            Detail, 
            AreOverlapping<InspectedElements..., InspectingElement>
        >::type::template ProtoMold<RestElements...>::type;

        static constexpr bool value {std::is_same_v<type, void>};
    };

// Base Case:
    template<typename InspectingElement>
    struct ProtoMold<InspectingElement>
    {
        using type = std::conditional
        <
            std::is_base_of<std::type_identity<InspectingElement>, AreOverlapping>::value, 
            void,
            Capsule<InspectedElements..., InspectingElement>
        >::type;
        
        static constexpr bool value {not std::is_same_v<type, void>};
    };

    template<typename...Elements>
    using Mold = ProtoMold<Elements...>;
};

/************************/
/**** Implementation ****/
/************************/

template<typename FirstElement, typename...RestElements>
struct AreUnique
{
    static constexpr bool value 
    {
        ! AreOverlapping<FirstElement>
        ::template Mold<RestElements...>
        ::value
    };
};

/*****************/
/**** Example ****/
/*****************/

static_assert(AreUnique<int, int*, int**, void>::value);
static_assert(! AreUnique<int, int*, int**, void, int*>::value);