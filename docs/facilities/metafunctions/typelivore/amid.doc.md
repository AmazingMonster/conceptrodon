<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::Amid`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-amid">To Index</a></p>

## Description

`Typelivore::Amid` accepts a list of elements and returns a function. When invoked by an index, the function returns the element at the index from the list.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>I</sub>, ..., E<sub>n</sub>
-> I
-> E<sub>I</sub></code></pre>

## Type Signature

```Haskell
Amid
 :: typename...
 -> template<auto...>
```

## Structure

```C++
template<typename...>
struct Amid
{
    template<auto>
    alias Page = RESULT;
};
```

## Examples

We will pick the element at index `3` out of the list `int, int*, int**, int***`.

```C++
/**** SupposedResult ****/
using SupposedResult = int***;

/**** Result ****/
using Result = Amid<int, int*, int**, int***>::Page<3>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will label each element by its index in the list and collect them into a roster.
When provided with an index, we instruct compilers to pull its corresponding element from the roster.

First, we need to create a label class:

```C++
template<typename Treasure, typename Key>
struct Label
{ 
    static constexpr auto idyl(Key) -> Treasure;
};
```

We can pull out the variable of a given index by asking `decltype` the return type of `idyl` if invoked by the corresponding `Key`.
For this purpose, we will convert an index into a type via `std::integral_constant`.
So, the final mapping will be as follows:

<pre><code>std::integral_constant&lt;I&gt; -> Element<sub>I</sub></code></pre>

Now, we will assemble an overload set and instruct compilers to pull the element out when provided with an index. Here's the entire implementation:

```C++
template<typename...Elements>
struct Amid
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set of `idyl` through inheritance.
    : public Label<Elements, std::integral_constant<size_t, I>>...
    {
        // We bring every `idyl` from its base class to the current scope.
        using Label<Elements, std::integral_constant<size_t, I>>::idyl...;
    };

    template<size_t I>
    struct Hidden
    {
        // We ask the compiler to find an `idyl` that
        // declares a parameter of type `std::integral_constant<size_t, I>`.
        // If found, the return type of such `idyl` is the element
        // of index I in the list.
        using type = decltype
        (Detail<std::make_index_sequence<sizeof...(Elements)>>::idyl(std::integral_constant<size_t, I>{}));
    };

    template<auto...Agreements>
    using Page = Hidden<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxCAAbLGkAA6oCoRODB7evnrJqY4CQSHhLFEx8baY9vkMQgRMxASZPn5cFVXptfUEhWGR0XEJCnUNTdmtQ109xaUDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimImujMh4mArnO4cnZ/ufu2/HR79mAGZgshvFhziYAW4vI5aIQAJ4Q7B/cxAhggrxgiFuZBDdBYKiI5HvHbnAJMKK0F7bH4ETAsRIGWlYghw27MNjnAAqxEwTAUS0wpHOLLZrEw5wA0pgEQCkSchsQvA5SeTKsiAOwWcEnc6684TRzIc5oBhDTCqRLEc5MaGoc54dBw2gQKVw2bnAC0iK5PL5AohVhOJnVlwDRNOX0j3z%2BHw25wAkvT6GxBExqlStj9Y1Gvj8/rSk2nMMzWYwxQA6SvYZOMAgKQnygiK5XHFgOjWB4564V0hlFkuitgNrt6hVKghXTB1OjgzXB0MAzt/bsFvtMyGpABemAA%2BgRK%2BX48Pu2Plddp7QsbiQCBglhVDulABHLz3YuQ%2BMHwmy5d6tZrc4AHVxWQX1aWtBhzlQAA3aJaFQJh0H1KcoKocFYg0B0nRMDDhQQYhFmABB7QYBBokIQwVnLX9dRAc5Ei8CJYSNMkKSxas6VrBQhWvW9BEwYBiDEHcTQmQQrzwbc9yFI8f1lL8dT1YNO27bt/yA8UImIYJgHOTBYOIOF0Mwx1L1wqgCJYe063OCI%2BRAgwFGeIg8JApYeUEfU0FuajFNU84vFSIwVTYyEOJTOseIIdAb2CWlBOE0S6nEjdJN3AgZO/bBYtMr9Fxo2cFyXPye0Ldc3C3dKE2PUcm3Hc4AAkHSwBgCuUgq1IA4DrQUABrVzjVQek6GiYU7RoBgkMMYysLMjQ8LTDq/wArAQXqJ5rXo%2BoxVpK1UDQkVxRwjReLigShNoESBDEggJKkjLqp/DDfJHfz1PjND%2BC8SahQIMjzh5Aglkgw7UP1JViOO2bjvtZz/sqTjxJKzqwbvc0ExIgbYSGF7/N1QKdOFUtwQBS5zlW2hDqW3UIGp1TzyYOgr2im8WCYXrdzRh9n1fNF3wqtL9oPCBwq42Ysrp7scqdCBTv4hLLqSwxbtS%2B7Mp/OcQ3F5G9XF/KSvnMMgxK1dGX5m0iAPY5BMwRG6xq/Ggt05QmGAI7Sca5rGCxa2eTthQ8uykAqf134QyN35iRzV4YxJbBVFYBlxRjqPo8zcMUWBUF3exAQVkSe2f2NiMLiELxElyTB0AAJSeLxKYzA4/gJ4Ky4rlIq9r/kG4hMm4u2CPY4uLv64nFPjhb3SR57j3W3bSE4qFful8ELYV4IAfZRvF23axAFv2Kkuti5J4x%2BpP4DTwZAdz5JQGlllmQAUMUb/rSFp4etvK5ruvKcRPXOwcHmLQTgABWXgfgOBaFIKgTgbhrDWH1IsZYR1AQ8FIAQTQQD5i9RAKAyQ5YNAAA4zBmAAJxkK4KA4hRCuDqnVNIEBHBJC8BYBIDQGhSCQOgbAjgvAFAgE4ZgqBQDSBwFgDARAIBFgEAYhlCgEA0DDXoMQUIYpOCqCIbED0sRJDnGAMgI0UhyxmF4FXQgJAHR6H4IIEQYh2BSBkIIRQKh1AiNILoVoAB3ISiROA8GAWAiBWCYGcAAPLQjkWDTR2jdH6MMecYxZhzgQA8Mo0aKIuCzF4MIrQ8wIBICUYkEaZAFFFJKSAYAUgzB8DoLtAREAIghIiMEeocJ/G8BacwQyYSIjaEwA4DppAlERTCQwWg7T3FYAiF4YAbgxC0AEdwXgWA2ZGHEFMvAPIHB4Fgks6B5oBnQlWOgs6TDoGwi0m0jwWAQlNjwGw5ZpADIRA7tcNZwBYRGCwfMKgBhgAKAAGqPC8WEtkQybHCFEOIRxkKXFqBCZ4/QhhjAIMsPoPAEQBGQHmKgAu6QlkelxL3UwlhrBmB4QZbSWBsUQHmHYAZ1QXCTVGC0UggRgi9BKP0VouQ0gCFZTkFI/KGBTD6DEcYCMdkCE6CMTwzQ9AMulTUYY3ROXTB5bYVVgrxiqrFdyiV9LkErAkIEjg4CuEhN4ecGJOi9EGKMQQ5JIt8BECtJk7JGCfnzDIohfodLSC4MkACcsZCAQMI0JIMwkgMIaFAbEMh%2BhOAsNIGwgEXByyxC4LEIhZDaGxHwVQsNCRuG8F4fwwRXqRH5MkQU6RkToTkEoOUlRai2CcHqCwaC6oPRMGNAYYKXAyHlgzQc11liYqtEhXYmF0g4VKARe43QNSfFMD8css1FrS2hI4BE2R0JolaLtf2lFiTh2jpSWk4pKjwSAjMJ63Joi60tuiE2xRQ1r39DWkYIdXBOE0EptEBpTT3FdLaUMsDPS%2BmMqGSM2sYyJkhOmbM%2BZtBFlDNWSijZ0D8DbMcHskJhzkDHKGWckJlyhKGRuasaB9zHnoJeW8ukWGdI/L4P8oFIKwWMAhbIGdDi52yHhW46By7kXfNJVYdFlzaW4vxddTgRLookrRRYClZaqUOiePAelUqmUQFcDq9lk19UzF5cK6oRm%2BXVFM5qpV1RZWNHlWMNojKOh6vVeKxV2rnNsomA0WzhqFhLBNVkpN5rgnuOtbauJ37dJDpHYQlJuALHurQQ%2B71pBfVYBiAGphKa03DsjeqUBZD6EAijTGyQrRt3ltsJWx9Nb4B1pkXIt9L7VHqI4J2uJLAFDQSNNBBLZshhmPHdS6xfHoUCacfIBdImdAgABKQVd66Anha3Va8JDaJz7Rtb1/rg3htFiGJej9JTb0AgBBl6tYjCnnZUe1h7/QBsVx3ENshO4RsEB3KoXRtTAPEGA801phkIOg7hL0/pgynlwcEAhyZOHMAzLmQspZ6DMPrJoysrZbmCPuKIyRp5ZH3EUeuRgbHGDtL0d4IxpQ7yWPfNu3812nHMCgvBU86d02JCCecfNxFS3xOorJdJzFsmYHydNJwNY15JPkspdEal2mcWueVcy9wvn/Amc8waoVeR0hWYs%2BkQLiq9Pua6EZ%2BzFuAu67M1qy3WvdWTDtzyo1IWHGbsizwzg%2B29F9YG%2BcD75ZvvJfG5drJOTMvZf9WagrIByHliu6A6h1WOFXfVDmy1UXOAVqEZloNoDQ10PVBwohkhKFcBIWYBITCATe7LbnqteSzWmOzz7vhzfsHPKA%2BkEAkggA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/amid/implementation.hpp)
- [Source code](../../../../conceptrodon/descend/typelivore/amid.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/amid.test.hpp)
