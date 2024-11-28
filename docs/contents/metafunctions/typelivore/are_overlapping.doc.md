<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreOverlapping`

## Description

`Typelivore::AreOverlapping` accepts a set of nonrepetitive elements and returns a predicate.
When invoked, the predicate returns true if the list created by appending arguments to the previously provided set contains repetitive members and returns false otherwise.

<pre><code>   Elements...
-> Arguments...
-> IsMathematicalSet(Elements..., Arguments...) ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping ::   typename...
                 -> typename...
                 -> auto
```

## Structure

```C++
template<typename...>
struct AreOverlapping
{
    template<typename...>
    alias Mold
    {
        static constexpr bool value
        {RESULT};
    };

    template<typename...>
    static constexpr bool Mold_v 
    {RESULT};
};
```

## Examples

We will showcase three examples.

Check whether `int*, void` and `int, int*, int**` overlap:

```C++
template<typename...Args>
using Metafunction = AreOverlapping<int*, void>
::Mold<Args...>;

static_assert(Metafunction<int, int*, int**>::value);
```

Check whether `int*, void` and `int, int**, int**` overlap:

```C++
static_assert(Metafunction<int, int**, int**>::value);
```

Check whether `int*, void` and `int, int***, int**` overlap:

```C++
static_assert(! Metafunction<int, int***, int**>::value);
```

## Implementation

The name `AreOverlapping` is probably a bit misleading.
This function used to be a helper class for `Typelivore::AreUnique`.
It becomes a standalone function since its functionality is intuitive enough that it might be helpful on other occasions.

After instantiating the first two layers, `AreOverlapping` has two lists of elements to work with.
The first list must be a set, meaning repetitive elements are prohibited. The reason for this will be apparent later on.
For the function to return true, the second list must satisfy two properties:

- Every element in the second list is not contained in the first.
- The second list does not contain repetitive elements.

To check if an element is in the first list, we use a method described in `Typelivore::SetContains`.
Namely, we will create a class that inherits every 'element' we would like to check against and use `std::is_base_of` to inspect whether an argument is a base of our class, subsequently determining if it is one of the elements our class inherited early on.

Since inheriting the same type multiple times is illegal in C++, elements in the first list must be nonrepetitive.

We will implement `AreOverlapping` using recursion over the length of the second list:

- **Base Case:** When only one element exists, the function returns true if the element is in the first list and returns false otherwise.

- **Recursive Case:** Pop the first element from the list.
The function returns true if the element is in the first list.
Otherwise, we append the element to the first list and pass the result back to `AreOverlapping`.
Then, we invoke the second layer by the popped second list.

To 'inherit' fundamental types, we wrap every element into `std::type_identity`.

Here's the entire implementation:

```C++
template<typename...>
struct Capsule;

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
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAArBqkAA6oCoRODB7evgGp6ZkCoeFRLLHxSbaY9o4CQgRMxAQ5Pn6BdpgOWQ1NBCWRMXGJyQqNza15HeP9YYPlw0kAlLaoXsTI7Bzm/mHI3lgA1Cb%2Bbl6OtIQAnifYJhoAgjt7B5jHpwRXKZgA%2BgTETEIClu9yeZl2DH2XiOJzcyDG6CwVBBj1BBEwLBSBnRsM%2B32YbAAdMSUQ8xsQvA5Dm4mCkFF56CcrKjHujMdjMLivoxWJhiYSAJIMBTfByYdDYehsQTA/x3R7kykEQ4PYiYADyADc4gYUikwsBQSBDikvNFLshDgiQCA8b88FhBNdYUKRV10RKpYwCLLsPzQSYAOzMh6HMNW/5Kw4AEUwjTooPDx2DiaT4bZWKYOI%2B3IJfJJctTaYjFKpymIqCIAFlPOgi2mgxZDl4MkZDnb3tHDprUA6mcno0z60HB/4Q6CAPQTw4AJS66wy2upTCUIHrGY5XPxvMOrtFjiMkox3tI7dzvP5c7GR%2BlPtJScVZYr1drw5Tj2LYanxwAbBpY/GtAmH%2BhwAO50LQEaoCkhxqsgC5ZKeTDIAgeCYJqBpWggJAEAAtMgeAbF4hCEvWSYtphHYnF21ooAI%2BB1MwQEfp%2BsJkZ%2BtF4AoPzRCuvyoMipy0XaPwOt6zqnHu7oGje3q3KQqoatqxC6vqRi3DampiF4mCnuxxYAYCtB6Sxn7hopWo6rSamGpJwr7uKskyvyp5Sd0h5eoI96sXKNp2n5GKZuihzlpWqA1rQdanFeBBOT6/q%2Bba3JDiyoYcY0jiWmgwroqoKTEIc0SoJ43baW8jacdxCi8j8mpbrp3a9lFdyBqOIZJiOKVPI834WHxy6ruugWbjm25sLu9nSR5x5eYWpkllGoUvpFLqTe5wBxd5YaNvpzatsAZ7fJ2EboDa2UMVkYi7Wx81mZVPF8T8AmwsJ3KiY6jifKtbrrZtcqnhZymqQaGkgFp3gNbtSY9g6pBQ%2BGNJ0gynJ2T9HpxQoLkTWjMmeQQW0NoldpdWZu1jFmeBZQIYyYHlBVFSV4M6cmFgMJWJ02lxPzVWwtX1aeMPNZ1Y5vm1AbzRuWYo24dp5vyGMExRbYRegx1LeFr6nBjCV3CLqKtV1k4AFQm6bZsTsbJsACrYEIVumxbPVm87RuO91YIQlCMKnNlmwpHec3u5L2Yy%2BeRLEqqwC%2BqCSsHVWcZMFQXiQoxx2A1Zeog6cYQEEbAtNaSNoq7CkeYwWuvjgqGWUz8K5KM0EDx40Scp1ksI56eOd54cXdG6DTOYEsXXk5ltcKPXBCNwnLfdAI7eCJ3ggm4vud94lA9D3rZLV8gY8TxAYBgIcTeJ8ns8MPPBAr6b19r9gmllZvFgcCstCcAkvB%2BBwWikKgnBuNYawVo1gbHKuCHgpACCaBfisAA1iAH8/hCQAA5kGBg0D%2BJIGh/BmGQWYAAnPg/QnBJC8BYBIDQyQv4/z/hwXgCgQDJCgd/F%2BpA4CwBgIgEAawCCmivhQCAaBMR0DiBEXknBVDIJ/LhH8khDjAGQJaKQhIzC8HFIQEgDo9D8EECIMQ7ApAyEEIoFQ6gWGkF0FwUgoEAQpE4DwV%2B79P7QN/pwdU5w%2BGHAEocSR0jZHyMUYcZRZhDgQA8MI%2BgBUdhcCWLwZhWgVgQCQEI/UkTyCUBSSI%2BIwApBmD4HQdExAGEQGiC46IYQmhXHsbwcpzBiBXHVNEbQ7pqmkCEbedUDBaBVPMVgaIXhgA0loLQBh3BeBYBYIYYA4hemEWktqUZP9abznRK0nONQXGXGiACepHgsAuP%2BHgchYzSDKSKkoWMkyjCXCMNAlYVADBRwAGpoVAuqfErSdHCFEOIQxXyTFqBcZY/QUyUCAMsPoPA0QGGQBWNBRiozcIImoqYSw1gzA0OUsQMSMKIArE6OfFwDB3CeDaHoEIcwygVD0GkDIjFJh%2BCsbSooDABhUuGFYgljFegTFJXkTlNRpL1BmGyoY8ROUzAZXocmzRRULHFfikBmwJCOI4B/Ug1DeC0J8VImRciFFKMkCo0JuANFRPAbEyBdyVgIEwEwLA8Q8WkHgZIJB%2BD/CBkkBoSQZhJB/g0AkH8RC34cFIaQch/guCEh/FwH8yD8HINjQkSQXAEjup/BqlxtD6GMKtSwxJnCkncI8ecdJgjUARNEeIjgTQWCakDLhJghx9hTKCfgwkUalkMU0adKxXy9G/OkP8pQgLzG6DyTY2k1TVXqs1a4jg7jeHnC8VQQ4tb62NubQYNsXB22dtCeE1JcRjjgjMJa%2BJrCi2ZLSQI69wx10NpbUYXdXBkg0FoIU4ppTzG1Mqa0399TGnNIcK09p3pOndJcX0gZQyRmtImVMmZP98BwUcAslxyz4KrJOeskNP8tk7KuHsrYP9DnHIgWc9ImBLmIYNHcvgjyFAvMwG8j5Jz%2B0/IMUO2QAKzE/3HSC25qKrAQq2biuF/ssiIuRf4aMwn0WYriNirA4nqi1CyESkluRGVBGJXK6lTLCj0r5Tp5ljF9McrU0KhgPKWgmelYK8%2BtmLPitsJK%2BzEq%2BguZVasdYyqYnELVc48x2qH2bqfQdXdHbCQaBNd281kbz3WtILa%2B1wwnUhrDRG9t3rAxpsDIGfwPq/UpszSFzgOamH0fYVwnhfCy13uIGItgnBa3%2BJYAoTUlpNRRY5GMNR8WtF9tkAOrjRj5Ajr4zofIk67FjJncFmhbiS3Km8W1uRHWuvdl61LMYB6K1HoS/4JL%2Ba2HJIO1khrF3Ilg2QHqWqu6fh9YILXYgLBZH5I/XEL9ZSKn1P/X9hpTSWknLA4ICDPTkOYH6YMsQcGTkIeuSR8ZczujofMZh84WwIG4c2VCwjxGDnYvI7wSjFyMS0duadh5TBnmvPeYwT5I3OMSG48YybQL8jbuMOCmwYn4ASYRZwCc1p5OWAxVqrFOKBdWcJRAVwUqrEUtKGKmlRmsiK4KHSrI3mBXqeFX0TXXKegisparzzvLtPStNyr%2BVPmFBKoMQtsrS2OBrre%2B1zr3Wdvoj2xAU1RAEsxLicl1LDrKCqqyyAAhhJ/D%2BASEkFNlC4%2BBjjS7rVFXbC5ovUsOBAQfwdq4AQorhCfyBi4OgqxIb/CLYz3QvNCTVWqPT/OkP%2BaVjKQyM4SQQA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/are_overlapping.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/are_overlapping.test.hpp)
