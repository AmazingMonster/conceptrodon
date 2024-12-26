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
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    // Since arguments are not allowed to have the type `void`,
    // which shall be a valid argument for `AreDistinct`,
    // we declare the parameters using `Elements*`.
    : public Label<Elements*, I>...
    {
        // We bring every `lark` from its base class
        // to the current scope.
        using Label<Elements*, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization
        // before the primary template.
        template<typename, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // This function checks if an element
        // is in the previously provided list.
        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Element*`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        template<typename Element>
        struct Hidden<Element, decltype(lark(std::declval<Element*>()))>
        { static constexpr bool value {true}; };

        // We check every element using a fold expression.
        // It returns true if and only if each element
        // appears only once in the list.
        static constexpr bool value
        {(...&&Hidden<Elements>::value)};
    };

    static constexpr bool value
    {Detail<std::index_sequence_for<Elements...>>::value};
};

/*****************/
/**** Example ****/
/*****************/

static_assert(AreDistinct<int, int*, int**, void>::value);
static_assert(! AreDistinct<int, int*, int**, void, int*>::value);