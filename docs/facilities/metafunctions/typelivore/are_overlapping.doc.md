<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreOverlapping`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-are-overlapping">To Index</a></p>

## Description

`Typelivore::AreOverlapping` accepts a set of nonrepetitive elements and returns a predicate.
When invoked, the predicate returns true if the list created by appending arguments to the previously provided set contains repetitive members and returns false otherwise.

<pre><code>   Es...
-> Args...
-> Es... `overlaps` Args... ?
   false : true</code></pre>

## Type Signature

```Haskell
AreOverlapping
 :: typename...
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
/**** Metafunction ****/
template<typename...Args>
using Metafunction = AreOverlapping<int*, void>
::Mold<Args...>;

/**** Test ****/
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

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAHKSuADJ4DJgAcj4ARpjEIIFcpAAOqAqETgwe3r4BwemZjgLhkTEs8YnJtpj2JQxCBEzEBLk%2BfkG19dlNLQRl0XEJSSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BwA9ABU%2BweHR8e72yYaAIJ7BwDUACKYqa6MyHiYCjeHZ5fXJ39H3wu5yBZgAzBFkN4sDcTKC3AQAJ5PAD6BGITEIClh2GBwN%2BuxubiYqQUXnonwOgIImBYqQM1Nh8KRjFYmAAdBzscDxsQvA5CcTSfRYVZLnj/hKAeLbgBJWn0NiCJgNCn7QH4yX/QHA6ny5WYRmIp7MNgctkyhgKJ4OTDobAKxgELGgnGXHl8gg3C7ETAAeQAbgkDKlUhFgMCQDdUl5YrQ8MgbuN0CAQEbMMi8FhBIQEYyLVbMDa7Q7BM7sGbcQB2UUXG51xNoj33TDNOjA%2Bsw6vtjv13V0/WG5km9mcl3dnsN3n85TEVBEACynnQ457JmrNy8mSMNzTMNBdxu/tQmZFnbuIpXa/PoJreO2NwASoX1plAwKlCAV336Qa4Wnhzc%2BbWo4Rj2jSjqkDuQ6smaT7jGBipOlylwdu606zguS6Xl2KETjc2z3iYABsGgPK2tDERoNwAO50LQDaoKkNw%2BsgL7ZJBTDIAgbz%2BmGiYICQBAALSvBsXiEGyK4dpufG7rCB5JimaAMPgDRiFJ9aMhpE6KSAeAKMisRMEoyKoFQjK6WmGZZo4iJ5pawFhghjrYqQ3p%2BoGxDBqGRjYim/piF4mCQdpPZkRitAhbheH1u5AZBsSPnhnCQGFtSxbgaWZqQalDhOSWBDIbWeF%2BamzIpt%2B%2Bo3DOc6oIutDLnCcEEM5WWjtgFXMheYrRT2syOAmynjJgqipMQNyxKgniHoFmCdhYun6ciCissi/qDk8kFHieY6VteNYdle3VAj894WMZc1Eh%2BX40v2DJ/tBbCAQ5aX5ZlhVjr1aGejVmENfZBZ5aBBVFYdOHFROMnbnJ%2B4NsmKACKp2Tqb1h1wqFqEEPDS1GSZZkWVjnUopmjo5gDjnA%2B9rlej68VeYlYalQF3jBTCqN4dt6CkBj9ZEiSZK/m4uXpa1TrZc9gMgcAougyVLpE7%2BB0lezdb9fGNxDdSo3jZN03M0F80MHOcMpktK1sGtG2s5zXJ7cdYP7bivWVfdTLGjBHKi2WK5Q8ANz1ege4Hr9dVYXCXsVmON5Vo7PVXJqkrqocNwAGJ4MQ4w3NgqisHSc1fNKCd/NqPzJ/OLZMFQXgMHlAiqqcOq3T%2BVvDma3rAN7ly%2B/7FdVzXKryTTHkJSGjNwhEBC7Ftx6Na6FwpgHjLtwokc4tHcf4jcAAq7yegXbrNANyLGUorQQOXzR97XDCMhPkET1PNwP7sTOzUsx2F0XJxJ7cQiFojWcc7ynzpST%2BX8pRxzVsgY%2BChT4EHPr3au19b6CHvoIfYaDJ4v3liAfWmB37rxOvHcBxwf77G3txYggds653JPvYhJD6HckPvGGBcCIBgDAD3S%2BSCGgoIIJgg4gjsEdVwW/EUHAVi0E4P4XgfgOBaFIKgTgbhrDWETGsDYc1zCgh4KQAgmhJErAANYBEkGyDQgQzBmAAJw2K4P4SxyRKyVmkNIjgkheAsAkBoDQpB5GKOURwXgCgQB%2BIMQoyRpA4CwBgIgEAawCDRgERQCAaBaR0ASFEVknBVCBCIkJIikgbjAGQAmKQbIzC8FtIQEgmY9D8EECIMQ7ApAyEEIoFQ6hImkF0Ckai6JUicB4FImRcjDFKM4L6LwSSZk3DMjcPJBSiklLKTcCpZgbgQA8Bk%2Bg40dFcCWLwCJWgVgQCQOk0MezyCUEuZkxIwApBmD4HQakGdKCxAmbECILQETDN4N85gxAES%2BliNoNK/zSDpMQr6BgtA/k9KwLELwwAiS0FoKE7gvAsAsEMMAcQiL06vUDJixRI1nzUkhRPOoEy4yxHRMCjwWAJlojwN4rFpBPKTSUA8XFRg4xGEMSsKgBgO4ADU3jUV9MaSFjThCiHEG0uVnS1ATL6foPFKA1GWH0HgWIoTIArEYg0TFQkkzyVMJYawZhAmeWICTA1EAVh2Fes4CArgph%2BBSGECIQxKgjBSEULIAhPV6CDQ0eYwxEhjDqK6xoEw2ieA6HoF118%2BitEjf66NtgE2hrGAmzNixDmrHWJsCQoyOCyP8RMoJiz8mFOKaU8p5jNkQFwLU/ZYJDnHKFSsBAmAmBYESE60gpjJCgjZDY0EriNCSDMJIEiGh/BERsfoTgnjSDeN0WyIiXAiKBBsckIi/hJAOKnURatPSgkhLCfooV0S4nnISTM5JNy0moF2VknJHAWgsH9JWISTANYGG3FwGxbIuAWOqapOpyYUhyuaYq6QyqlCqp6boZ5AziT/IrVWgJvAgnTNmZ6BZSyG3Abxes8DkGqLbI/VchIMIwRmCOXeyJZyLn0fuW%2Bu5eyUAgcefYvxNBaBvNCRAT5PTAW/MhdJ4FoLwUOEhdCx0sL4UTKRSitFGLIU4rxQSxR%2BAWKOBJRM8lrFKUcupe4xRdKGUIiZVsRRrL2V6K5RkTAvL9NhnvSKpg4rJXSsYLK2QiHWnIdkCq7piiMMasFZaqwOq6WOqNakE1nAzVYwtdqiwNqCN2odfAZ1sbr4uBUnmkIKlC0BrSBkYNOQk35EDXViNvqFg1dTQ0dNia8heu6HG7r1Xs2zEmI1vrI2BhtajeWktWiZvuLwzWzgdblnFMhJRsDEGLFbPbUQTtujWMnKMaQftg6RgjvcRurd4HZ2Vn8DYlxoI50LtPZewJnAb3hPvTE%2BJiTX2pN41%2BtgnBf0rJYAof0CZ/SbZ/OMaDHb6nwdCwq8L7T5CoeizoEAoJSBYaGVi3D4yr1TJfXM0jYOIdQ5h/qTOdHP37dBId77nH6c8a43xyHIY1pgeRLDggyJVBFJeaJhI4nJOKLkwivRkuFMQo5SpwQamEWGcwMi1FYgdMcr0/ypz2KiV5VMz08zMyth6Os7SvV9nHMsvta53g7meU0m84K9jfBRUKAlZgKVMqOUIZRxICLHSMdqux3F4wOXdX6qK0otL2RMXbEUgl61tqEj2qwCl/rpX3XlbG3oH15RpvNeKNkCr4bshDZTSVrrubc8xp6AIQbU2s0ppr71lvcwm9FudZostxaFtE/exwRZFPIeHmp9SWnu2SBMYOz29jfaB1DsoBWq7IBbFslBKCfwjjT2%2BM35Wfdb2CMfdsLeo7SwTEgEkP4SdXAXG%2BMCJIexXArFmAve40EA/j/BLY6citVSj9Jkf9z8VhPJMhnBJAgA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/typelivore/are_overlapping/implementation.hpp)
- [Source code](../../../../conceptrodon/typelivore/are_overlapping.hpp)
- [Unit test](../../../../tests/unit/metafunctions/typelivore/are_overlapping.test.hpp)
