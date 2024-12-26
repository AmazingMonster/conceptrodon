/**********************/
/**** Dependencies ****/
/**********************/

#include <utility>
#include <cstddef>

/**** Label ****/
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };

/************************/
/**** Implementation ****/
/************************/

template<typename...Elements>
struct Has
{
    template<typename...InspectingElements>
    struct ProtoMold
    {
        template<typename, typename>
        struct Detail {};

        template<size_t...I, size_t...J>
        struct Detail<
            std::index_sequence<I...>,
            std::index_sequence<J...>
        >
        // We create two overload sets and combine them through inheritance.
        : public Label<Elements*, I>...,
          public Label<InspectingElements*, sizeof...(Elements) + J>...
        {
            // We bring every `lark` from its base class to the current scope.
            using Label<Elements*, I>::lark...;
            using Label<
                InspectingElements*,
                sizeof...(Elements) + J
            >::lark...;

            // We will do SFINAE on the second parameter.
            // The default argument `void` ensures
            // the compiler checks the specialization
            // before the primary template.
            template<typename, typename=void>
            struct Hidden
            { static constexpr bool value {true}; };

            // We ask the compiler to access a `lark` that
            // declares a parameter of type `Element`.
            // If the compiler can access the `lark`,
            // this specialization will be used.
            // Otherwise, the primary template will be used.
            // This function checks if both overload sets
            // contain the same element.
            template<typename Element>
            struct Hidden<
                Element,
                std::void_t<decltype(lark(std::declval<Element*>()))>
            >
            { static constexpr bool value {false}; };

            // This function returns true if `Elements...`
            // contains every element from `InspectingElements...`
            static constexpr bool value {(...&&(Hidden<InspectingElements>::value))};
        };

        static constexpr bool value 
        {
            Detail<std::index_sequence_for<Elements...>,
            std::index_sequence_for<InspectingElements...>>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;

    template<typename...Args>
    static constexpr bool Mold_v {ProtoMold<Args...>::value};
};

/*****************/
/**** Example ****/
/*****************/

/**** Metafunction ****/
template<typename...Args>
using Metafunction = Has<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(! Metafunction<int*, void>::value);
static_assert(Metafunction<int, int**>::value);