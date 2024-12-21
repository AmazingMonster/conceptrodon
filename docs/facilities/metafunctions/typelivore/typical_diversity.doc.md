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
template<typename...>
struct Capsule;

template<typename...Args>
using Metafunction = TypicalDiversity<int*, void>
::Mold<Args...>;

using SupposedResult = Capsule<int*, void, int, int**>;

using Result = Metafunction<int, int*, int**>::type;

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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSZqQADqgKhE4MHt6%2BASlpGQKh4VEssfGJtpj2jgJCBEzEBNk%2BfoF2mA6Z9Y0ExZExcQlJCg1NLbntY31hA2VDiQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACex9gmGgCCd/cEmCzJBi/HbgSXyYysmAAdMCbk9RsQvA4Dm4mMkFF56McrA8ni83h9MF8fn9mGxgYCAJIMBR/ByYdDYehsQQKUEPcGQggHAAqvzwoloABE8AA3OLpH4gA7JLzRC7IA6jdAgEDYzAAfTwWEEVy%2BRJJnReFKpjAItP82HxTxMAHZkY8HgB6S0HABKnTW6T50KYShATwOnoOaPeTE%2BJzluMwB3VpMcRkpr11pG9v3%2BeOB9tGkeperp9y9koIEKhymIqCIAFlPOgPV7TebM5mvOkjLG/kd/Jys9KUAJ8LVmLQy1XG24e72vVKZXgFPLoq6FagqF8B4Oq8PZXHFcrHD81cSw2FgCndTdSHP517Wcl2WJuXziALrg8j%2BWDTKeWIvJgY4feyez1zefyrm/b3eLJshyF6/uuJyhpq5K7jS%2BIxpBXQRjqgjpvONwynKGGvL6LwHHmBaoMWtClicSYEDBepGg%2BS5/EiA6mpydEolaNoWJOLpugOPoYlicZBiGm6atuFGoUO2aMnh%2BZFiWG4aohO7IQQomehW74HDW271sGxzNouaAMB2mRiGps4AXei6juOk7ytOpkZoBmaLnKK66qqEGCfJIkGgeZkOUBp4gT%2BV6qr5aHUU%2B3ivkcoWDjCcIIpi7lyVqFEKFR2D/vZd5xfCiJJWG0GKWlwLwR54YKVGKEGiZ1FykxWVHCajH%2BOaXHYTxAZ8QC%2BKpcp6m1sABxEegjbNvh0nEV8qXpfVDGzVaABUS3LStlpPJay3MtgQjMsta2LSth37RajxmDsDB7F4hxfGcdBubczHPO1fqJd8XUJoC6YMlCOUJfNT3oi9vE4t1wL3MQwD6g99waXWhaYA0VBeBdnajf5X6gcF4FuGEBALTGPKoEq6YysNXzg5DM0tcaDyw4NQheMkqRKOgSYIkyOkuvFeU44I%2BMHITSoxrjwt8wtoLU49dN2pguUc02Q0I0wSMo5kXwiwcuP81r4u1XG/2jH67Lyq6ShNBAi4KACJv6m4bO0AQMYM0zaTkvbSkGosSIcMstCcAArLwfgcFopCoJw/aWNYkqrOs2lnTwpAEJoPvLAA1iA/tmICJpmJIAAc%2Bf%2BxoACcWcaAAbPngR%2Bxwki8CwEgaBopDB6H4ccLwCggC3ychz7pBwLAMCICAqwECKjsUBAaBvHQcQRACnCqPnFcALQV5IBzAMgEpSICZi8OShAkEqej8IIIhiOwUgyIIigqOo/ekLoXCkAA7sQsKcDwvsB0HKcw6cAAPJnEngcacBwV7r03tvXeBx95mAOBADwc96DECOAnRYvA%2B5aGWBAJAs9TzoPIJQIh894jACkEkGgDt%2BSUGiIA6IYRGiXB/rwZhzBiCXGAdEbQmp2GkFnqmYBDBaBsOflgaIXhgAwloLQbu3BeBYBYIYYA4hJF4GIEJPkijQ6YFUA6F4gjcbVEARcaIX9uEeCwIA7MeBG5KNIJeaIrtOSvDURcIwKdlhUAMJDAAangTA79gE4kERfYQHIb7SEiQ/NQgDX76DUSgaw1h9B4GiN3SAyxUDJE7IoteUodKmCjpYMw7dLzECVLLeAywOhdGcBAVwEw/BvxCLMUo5Q9DM0KFkTwrQekFE7P0LpQw34NM7D0cYAzcgTOqEJOo0xRmDHiBM6YrS9CGyaCs%2BYaz6mxw2BIP%2BHBA6t0AR3KBq8N5bx3nvSQB9kG4BPhg7YXBsFJx8csBAmAmBYHiBAdOCR/CAhLv4E0kgNCJEkBXZu/sK4l30JweupBG7%2BC4ICCuXAq4l3zti/2kguD%2BzBRXc5z8O5dx7p8/u%2BCR4ELHmAs4pCZ6oDQQvJeHBGgsB5CaNeTADh7DUQgkugIMX6I7KfaUb9IlX3ELfOJSgEnP10EkT%2B38lEnLOW3XgHdQETzOBAqgBwuU8r5QKgwdYuAirFcg1BxC4iYP8GYD5uCB70vISQ6eHqhgmt5YKowVquAt1oS8K8DCmEsO4YIzhrDeH8IcII4RupRHiMAVImRciFGCJUZ4zYod8DaK6LowBBijGbETqY2uocLFWMuDYvNODqmOMTi4txHijBeNADSvg/iFBBJCWExgETZCypiXfeQiqn6hxVck7xpSrCWAyVkupYd8mZEKcUps87rAVJ1VUmp2TAVVBqJkFwBlNntIMrs7pb9emdgvfkAUmRr3jOPYshg0zmizLaW%2BxpH7lmdNWVsjZ37gO9BffslYawjnvKRacgB5LODGuINy3l/L/WDStaKwEGgnkSteVgnBXzSA/L%2BUMI9tcUVopFVCk0xKTQmn8NCzeb9tVAM7rYKlrraXwHpePSezLvXEEXmwTgXLYEsAUDyCUPIsMYlGEffDZ9pUjuiRIWJsh4lTp0HkNVyR2GaoQ%2B3EBjKmSQPE1vST0mBZyZeqMW1rL7UEf8P4F1PjB6EMcxQwTXn0EgGk0zeUsmS7ynkwQE2KHN58DoKG7uEBGHPxjVGpxSWeF8IEU4pNggU0SPzZgaRsixBZqcTmjtDbSAFp0bU5%2BpbkBnHLbwSt5jMm1vrXYptgjW1KHcaojt253N%2BKYIE4JoTwlOJlWp%2BVmnJ2JLyBa4waTF0WMPbktdAhFGWmHNu8plS4jVKwCt39nYz3uFA5e9AEGhlPoEA%2Bu9z7AN7K2Qsv9n6H2TO6ABkoQH1m9De59uYN6DnQZvoZslxmODIZYBJqTMnbMvHsxAZ5RBnPvKIzS75vz/mUBOVRkAZgRUuf9sXQlzcXMmirmDnVnBKW92IxnSQJoD50a4FIEutGwVcBNHB/wRmqcce4ycw%2BlP2No7wcsS86RnCSCAA%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/diversity.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/typical_diversity.test.hpp)
