<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreDistinct`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-distinct">To Index</a></p>

## Description

`Typelivore::AreDistinct` accepts a list of elements. It returns true if no two elements in the list are the same and returns false if otherwise.

## Type Signature

```Haskell
AreDistinct
 :: typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are distinct. Then, we will append `int*` and check again.

```C++
static_assert(AreDistinct<int, int*, int**, void>::value);
static_assert(! AreDistinct<int, int*, int**, void, int*>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we will create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.

In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
This is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

```C++
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
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
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/are_distinct/implementation.hpp)
- [Source code](../../../../conceptrodon/metafunctions/typelivore/are_distinct.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/are_distinct.test.hpp)
