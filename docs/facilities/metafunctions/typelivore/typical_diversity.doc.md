<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::TypicalDiversity`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-typical-diversity">To Index</a></p>

## Description

`Typelivore::TypicalDiversity` accepts a set of nonrepetitive elements and returns a function.
When invoked, the function appends the arguments to the previously provided set such that the resulting list:

- contains every element from the previously provided set and the arguments;
- doesn't contain repetitive elements;
- preserves the relative order of every element;

The resulting list will be held inside a `Capsule`.

<pre><code>   Es...
-> Args...
-> Capsule&lt;(make set)&lt;Es..., Args...&gt;&gt;</code></pre>

## Type Signature

```Haskell
TypicalDiversity
 :: typename...
 -> typename...
 -> typename
```

## Structure

```C++
template<typename...>
struct TypicalDiversity
{
    template<typename...>
    alias Mold
    {
        using type = RESULT;
    };

    template<typename...>
    using Mold_t = RESULT;
};
```

## Examples

We will use `TypicalDiversity` to append `int, int*, int**` to `int*, void`:

```C++
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
```

## Implementation

This function used to be a helper class for `Typelivore::MakeSet`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

In general, `TypicalDiversity` is a simplified version of `Typelivore::AreOverlapping` as we won't worry about short-circuit here.
After instantiating the first two layers, `TypicalDiversity` has two lists of elements to work with.
We will implement the function using recursion over the length of the second list:

- **Base Case**: When only one element exists, the result is:

  1. The first list if the element is already in the first list
  2. or the list made by appending the element to the end of the first list if it is not already present.

- **Recursive Case**: Pop the first element from the second list. We invoke `TypicalDiversity` with:

  1. The first list if the element is already in the first list
  2. or the list made by appending the element to the end of the first list if it is not already present.
  
  Then, we invoke the first layer by the popped second list.

To check if an element is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'element' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, elements in the first list must be nonrepetitive.

To 'inherit' fundamental types, we wrap every element into `std::type_identity`.

Here's the entire implementation:

```C++
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
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIADs/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2BlwuwLMgQiyG8WFuJkCbgIAE9ngB9AjEJiEBSw7AgkF/Pa3NxMNIKLz0L6HIEETAsNIGamw%2BFIxisTAAOg52JBE2IXgchOJpPosKsVzxAIlgPFdwAkrT6GxBExGhSDkD8ZKAUCQdT5crMIzEc9mGwOWyZQwFM8HJh0NgFYwCFjAjirjy%2BQRbgAVJF4US0e54ABuCRKCJAtzSXlitD9twm6BAICNmGReCwgkICMZFqtmBtdodgmd2DNuKSouBvx2twASvmNlkQwKlCAQbcO7ddXT9YbmSbMLdc9bHEZ7TTHaQu/3WWb6xNx4qnVyrp342iPbdlMRUEQALKedDtzsmCvHtcdrxZIzT54wwL3deJlACfCNMTni%2BMz8XzsJpN4AoyKxEwSjIqgVDfquv4wR2/7JsyaYZo4iI5paI4RMAi6OtipA/rBnY%2BmkfpiIGIbEGG%2BG/tiSZBmIXiYFOVEXkRJEBsGoZZkx0EEd6vr%2BmRnGoXCw75tShYTsWZpTqJDiYdhggrpcsE0QhzxJt29KDtuu6oAetBHnC84EApTpli6GnMiKn6nvc1litWtwWKBg5Eq2n6ab2cIpgOQ7oWJ8lFgQSlru6/I6fuh5oXmcljkFIUnmePEXlemG3oOsKPvBaAMG%2BOQfsla5QcpvFPgBQEgWBEHFaVF7wSmSGOlm0UYXFknBS6eGFaVrECRxFHNd11EWSAdHeIxMJDReRIkmSBoif5BamQo5nYNxJW8TNQrzW4snict0l%2BTFo5YfFLrMapKb2RtMJJHZgSVh5NI9gy3kzqaHLLQll7XsAtz6eg96PhFelRXCB2cudD3lvdj2/JqUrw3c2CqKwdKDt80oI2quJimCEJQhlcI5VsaTLudDnXEcAqzeSmNXJ5r1Msas6Q66lxhZ6W1zddWMEnumAtFQXgMHJAiqmcOrPVpfYsx9bKXMQwAliCqU3gLQsi2LDBA3xxF9eRlFwhEBB7FOQaoOmSlJgDjKK8rq280jBy3EIXhpMUtrzmSnr05cat/W7HuZF7Hw%2B7r3PCsbghm7cFvplOJuJzHexctDlP4nWYe0L7lKq79WdCp6mX/YLTDC6LjSMkntwm7HdepyNV3p1WVN3F6Hy5zjbotI4yDIqBShtBA8EKKyA/Om43s51OQee%2Bg08ddgywihwqy0Jw/i8H4HBaKQqCcG41jWPG6ybBlYI8KQBCaGvqwANYBJIbIaAAHGYZgAJyf1w/hv6/XAkhJGkBvDgkheAsAkBoDQpAd57wPhwXgCgQAwJvrvNepA4CwBgIgEA6wCBRgIOQSgaBaR0ASFEVknBVCvwAGwAFpaGSFuMAZAyBbhSDZGYXgtpCAkHTHofgggRBiHYFIGQghFAqHUOg0guguCkAAO7ojSJwHg69N7b1vvvTgAB5LwBCDG3AgrcGhDCmEsLYRw5%2BZhbgQA8GQ%2BgxAYSX2WLwNBWhVgQCQKQ4iTjiEQF8eQxIwApBmD4HQakFFKCxG0bECIrRwzcF4PE5gxAES6NiNoMSajeCkKXLohgtAkl7ywLELwwAiS0FoMg5JpAsAsEMMAcQsj8DEACiGWpe9MCqAbNSXJ5BBD1G0bGWI6J0keCwNotEeBIF1PIrEEOjxGlGFjEYW%2BqwqAGGVgANXeIo3RxoBlCOEP6MR0gTlSLUNo%2BR%2BgmkoGPpYfQeBYjIMgKsVAZMci1PoQmTKphLDWDMPA8ixB0wfHgKsOwAVnAQFcNMPwCiwgRGGFUUYCjijZAEAivQmLGgLBGIkBR0Ltb9CmJ4ToegSWNDJYMFFix0W2EmO0ClBRiXMoJWiolUKz5bAkBojgW9YHaIQaYuhjDmGsPYZw2xEBcB8OceYQIXA3HXw2asBAmAmBYESBAB%2BIBJCBDZJ/QIwCNCSDMJIWh0D/C0M/voTg4DSCQOVWyWhXBaGv0/gA2h/hJC/xNbQ4VsiEFIJQWq9BXicHeLwQYwhASglOMoWwTgrQWBBiSPQpgtxIRNI4Z/NkXAX48LfPwxMCiTkiPEOIy5ShrmyN0OE5RxJckCqFXA3gCD9GGM9CYsxEqc0GBvFwAtRaNB2IcX4hILjAhmFVR4jBMbE0JATagRxoxc1GBHVwGBNAc6hhiXEhJ6SBmpMSZk7JDgBn5MdIU4p2iykVKqTUgZDSmktNKXgdpclOnaJ6X07YV8TbDNkaM8ZCJJnbD3jMuZV8FlLJpO%2BzCGy%2BDbIUHszAByjl1MrWciQFzZBXJkXvRtdz1kAqsE80Zby9X7y%2BQIH5fyHwUaBSChIYKsA0ahfUGFfg4W5RxUi3KnKlgYsyFi3IrLEXpHE/i%2BlhKqU8dJcywTPReO0pE4yuY5L8jSe03SioCmVVrA2Hy4zoD20is4GK8xzDN1/RHYWl%2Bdj5VEEVa49x6rSCau1aMWjoCnUuoLealIn8gGBAtVa/1wb4GcDDaglDWDcH4PjRQQJa6p3EGTdsNNFiWAKCDOwoMjmtITBLQqgRFbZBVvORI%2BQdbiM6BAMEZtqjkltq0SGvRcajF9rywVorJX9QTAnRl4JM7AjzsSz4sb/i0vLsSIVj2yJiuf2RKVggyJVBMIifu6JEBYmyLPSeupx2MlZJyXUm9gg70lN4I%2BypYgX11LfasqD92v0dIhbI/9yADGAd4MB0Be8wOJMg9MsFsHeDwaUMspD6zI2oaYLs/ZhzGDHOq3hmthGGs3Oa2R4wjybDUchXRxotSdj/hY5YYFnbQXgq42p7WLgBNSb0MiwzXLcWyZyKpvFORNNEqZzSlTbPiVKZF/MeTXP2UDFU/pwX/KTPnyVxZzrsWOCmP64VuOQ3qQjblaW9zyqpuRo1VqnVlABWBZAF/NkgRAj%2BD/v66BDukiepi52uLthw0LuWPqyQ/hjWAKSNA1%2Bkgf5cHfmYINoDAjq694giNniBXcM9zopPfvViGxyAaoAA)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/typical_diversity/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/diversity.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/typical_diversity.test.hpp)
