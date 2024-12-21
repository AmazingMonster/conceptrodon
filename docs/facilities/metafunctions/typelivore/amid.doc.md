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
using SupposedResult = int***;

using Result = Amid<int, int*, int**, int***>::Page<3>;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAHKQADqgKhE4MHt6%2BASlpGQKh4VEssfFJdpgOmUIETMQE2T5%2BgVU1AnUNBMWRMXGJtvWNzbltwz1hfWUDCQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeB9gmGgCCG1s7mPuHyAoE6FhUl9d3twSYLGSBn%2BBzcBDOyUYrCeABViJgmAplphSLtwZDmGxdgBpTAXfxXW5vYheBy7YJMWK0H4mADsFn2t12zN2byYjmQuzQDDemFUyWIuyYx1Quzw6DOtAguLOc12AFpLrs4QikfCDlZbnSACIaml/AFA9mYUHoqFsAB0Vuw9DYggU3yJBBJZJuLHFNPpPxZaMNwJNhzNmIDhJuPuJpIIu21mHqdH2Xtpuv8mt%2BYZZ/0B/tB6QAXpgAPoEK0WgCSjvTzIjZJjcephze6BAIDCWFUBaUAEcvIxVqDSyXvgTvSyAPSj3YAdSeyHhxqFDF2qAAbnFaKgmOhWbGl1R9gA2DTiyUmQ9ohDEJbABBihgIOKEQyrC0j5kgXbJLzRU6cilU0E2gCjAEAoqKNs2YT/MAxBiAW3JsoIOZ4PmRaouWw4EoOTIsnSqY%2Bj645Tk80TEGEwC7Jgq7EGcB5HhK1JnlQl4sGKIG7NEiIzgYCgKGiooEPeXLLPCgismgkIvth%2BG7F46RGOSlKYPWbiAXaIFge8EGCJg0GwfB9SIQ2yGFgQaFDtgEH0YOKavgmyaprZmZGiCRkoVG6GhuGzqRrsAAS4pYAwtm4bZBETtOQoKAA1ueM6oICdBxHxuw0AwW6GLRx4MRo57sqFY4Tlg2wNJgvFMB%2BDTQv8gqoHuZq0eBLbabptBwQICEEEhblmcOh6SZW%2BGEaWe78F4aWogJTzwgQyyLvVtWsqSN6nnRJ5nngvGTRRtrAflzKEQtrZ8rspa3rFuynG8/XScyslkWiEJPAc2q7EVtBmntuwQLWTB0DmmkgCwTBRYWR3tl2PYMH2rmYLVJYQKpwEKHM5mWZKECNZBOkwa1%2BmGJ1MOoSd3yJtqcwozZUl2XqWpU052aHMKRAljc0GYEB9oVj6d3ycoTDAE9/gvf5HyMKCrPwhzIHWRZIAfZTdxJjTaajgAVOrGua6OPxq%2BrMLYEIMIa9rty65rWv6ncZibFDjzPG43KrMkIEVj8PPkUIXjJKkSjoAASqVXjvc8L2QRrytu3J5EB0iwfPbsboeockGomHqeCOr6cEOHBLNnzAugv4Q4OU67J4MgBaIkojQYwDCjQpXDqHDHQembsnve2kmD%2B4H72XBTqYcAstCcAArLwfgcFopCoJwbjWNYrJLCsT3WzwpAEJoQ8LFFICj5IFoaJIXC0v4GijxoZj7vuZgJEkI8cJIvAsBIGgaKQk/T7PHC8AoIDv5vKeQ9SBwFgDARAIAlgEE/KZCgEA0AJXoMQCI0JOCqASPueU%2B5JC7GAMgTkUgLRmF4N3QgJBxR6H4IIEQYh2BSBkIIRQKh1BANILoLgpAADuMFkicB4MPMeE8t4z04AAeWODA3cux0GYOwbg/BuxCFmC%2Bh4RBSUNhcDmLwQBWgFgQCQAg5IiUyBwMMcYkAwApBmD4HQaqf8IDRGEdEMIDQzh8N4M45g1FRHRG0NUQB68EFqVEQwWgbjWFYGiF4YAbgxC0D/twXgWAgZGHEBEvA8IairgSdPPk1RjhrHXljB%2B09TgkVcR4LAwjnR4Bfok0gVFohdxjCk4ApwjBbwWFQAwwAFAADU8CYE4aIjE7iGHCFEOIehVD5BKDUMI9h%2BhDDGAXpYfQeBoh/0gAsVAztMgJPlI2Z6phLDWDMF/KipEsBbIgAsdojhnAQFcKMPwHCQhTFKOUPQPtChZE8C0b5BQHkMF6J8gYHD7m1AmC8vQkLOgTFBf0eIELoX/NyCi7oiKZjIrucvVYEgBEcHHh/YR39pEYKwTgvBBCD7KIRvgIggoNFaI3p0hY95NwDFuaQXekh/AWgAJz%2BFpJII%2BZhJCHnPvuAV%2BhOBP1IC/fwXALT7i4PuBIAqEhqv3lwUeQr9wktYd/X%2B/9WVAL0eA/RkCJHHHIJQMxSCUFsE4A0Fgy5aTynKsVeSXABUWmVbkhl5CmwcJmTQqZ0gZlMPmaw3Q1juFMF4YkwlxLP68G/uI6BxwpGuvdZ6rkBgfV%2BoDSo%2BKRikH7GtmYFlOjgFWodXEO18Cy3mNzR671liBVcHfjQd6cR7GONYZ41xYzh3eN8f4sZQTgIhLCcIyJ0TYm0HiWM5Jyy0nT3wJkxw2ThF5OQAUsZxThFlJgtRSpaxp41LqevRpzSATrrIp0vgPT%2BmDOGaM%2BpYbJl0MjbIaNLDp5xqWR0k5Vg1llJuTsvZ7VOCHPeMc1ZFhznpsueKUq8A7lKX8ZkFwaUYVvLSlir5HCfnAoI/kdIwLiPgtsNhjoDAugjDRa8uj9hgVMcmCUJFsLUU5FY2yRoNGcWLGWPizRsqiVCKNZwIUxA3Ueq9YW8ivr/WHy%2BrgMhTK141rZaQDlWB4jcofvKxVfqj60j1bSU%2BkhxXYI4WmkRP9bCmtrRa%2BAVqoEwKbQ25BqCOCurkSwBQy5OTLlU/6N4JCg1XMobIcNv7xkAYWXkBNSb%2BGSdTaSsRNqowLUCzg4LoXdjhb9ZFqMEBVHlvUdbfwunzUgIMS2pBPnmsDFC97AspWCzlcrvJ7BNi%2B3EAHU4lx1FR1jbOD4vxDgp3xWCaE8Jm7MBRJiXEhJ6812pMvUkjJOHd2sP3Ye%2Bpx7WGnoqRgHbG9SI3t4HepQLTH0dIa90/mb6hkjMYGM79tCJB/sYXMwDOg8jKZQEh9ZmzMMzxgzyTgo5wJgbORcuIVyMPbLYzhx5zyWN6Hedx7FgKqOZAo2RzIwnYX0Y43xgFELKdQsxR8njGLmP8d4wz/HJHcViboSm6TX9ZMFd2EVsLEXjRvA0zFytSr6u6PZQiQzlBCWmZAGYP1/h/CjwvsfN%2B6vaTqsNfz5zf8AF6d5aPQVo8EhXwFZIAVp9hVcECA/fwfP02cG0Xph%2BxCDdu%2Bc25hYVF0jOEkEAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/amid.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/amid.test.hpp)
