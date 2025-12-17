<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Has`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-has">To Index</a></p>

## Description

`Typelivore::Has` accepts a list of elements and returns a function.

When invoked, the function returns true if the previously provided elements contain all its arguments and returns false if otherwise.

<pre><code>   Es...
-> Args...
-> Args... &sub; Es... ?
   true : false</code></pre>

## Type Signature

```Haskell
Has
 :: typename...
 -> typename...
 -> auto
```

## Structure

```C++
template<typename...>
struct Has
{
    template<typename...>
    alias Mold = RESULT;

    template<typename>
    static constexpr bool Mold_v = RESULT;
};
```

## Examples

We will check whether `int*, void`  is contained in `int, int*, int**, int**`.
Then, we will check whether `int, int**`  is contained in `int, int*, int**, int**`.

```C++
/**** Metafunction ****/
template<typename...Args>
using Metafunction = Has<int, int*, int**, int**>
::Mold<Args...>;

/**** Tests ****/
static_assert(! Metafunction<int*, void>::value);
static_assert(Metafunction<int, int**>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for `substitution failure is not an error`.
It roughly means we are going to create an `if statement` for template instantiation, where the condition will be the legitimacy of an action.
In this case, the action we will be using is accessing a function in an overload set.
This action will fail if the requested function signature is ambiguous.
We will use this behavior to check whether one overload set contains the other.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
It is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

Since arguments are not allowed to have the type `void`, we declare the parameter using `Element*`.

```C++
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
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
```

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/has/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/has.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/has.test.hpp)
