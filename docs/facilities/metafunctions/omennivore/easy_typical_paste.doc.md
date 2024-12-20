<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Omennivore::EasyTypicalPaste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#omennivore-easy-typical-paste">To Index</a></p>

## Description

`Omennivore::EasyTypicalPaste` accepts a list of packed vessels.
It concatenates them together and uses the first vessel to hold the result.

<pre><code>   Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>...&gt;, Vessel<sub><i>1</i></sub>&lt;Items<sub><i>1</i></sub>...&gt;, ..., Vessel<sub><i>n</i></sub>&lt;Items<sub><i>n</i></sub>...&gt;
-> Vessel<sub><i>0</i></sub>&lt;Items<sub><i>0</i></sub>..., Items<sub><i>1</i></sub>..., ..., Items<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
TypicalPaste :: typename... -> typename
```

## Structure

```C++
template<typename...>
struct TypicalPaste
{
    using type = RESULT;
};
```

## Examples

- We will paste `std::tuple<int>`,  `std::tuple<float, float*>` and `std::tuple<double>` together:

```C++
using SupposedResult_0 = std::tuple<int, float, float*, double>;

using Result_0 = EasyTypicalPaste
<
    std::tuple<int>, 
    std::tuple<float, float*>,
    std::tuple<double>
>::type;

static_assert(std::same_as<Result_0, SupposedResult_0>);
```

- We will paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
using SupposedResult_1 = std::integer_sequence<int, 0, 1, 2, 3>;

using Result_1 = EasyTypicalPaste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>::type;

static_assert(std::same_as<Result_1, SupposedResult_1>);
```

- We paste `Warehouse_0<Con_0>`,  `Warehouse_1<Con_1, Con_2>` and `Warehouse_2<Con_3>` together:

```C++
template<template<typename...> class...>
struct Warehouse_0;

template<template<typename...> class...>
struct Warehouse_1;

template<template<typename...> class...>
struct Warehouse_2;

template<typename...>
struct Con_0;

template<typename...>
struct Con_1;

template<typename...>
struct Con_2;

template<typename...>
struct Con_3;

using SupposedResult_2 = Warehouse_0<Con_0, Con_1, Con_2, Con_3>;

using Result_2 = EasyTypicalPaste
<
    Warehouse_0<Con_0>, 
    Warehouse_1<Con_1, Con_2>,
    Warehouse_2<Con_3>
>::type;

static_assert(std::same_as<Result_2, SupposedResult_2>);
```

- We paste `Stockroom_0<Seq_0>`,  `Stockroom_1<Seq_1, Seq_2>` and `Stockroom_2<Seq_3>` together:

```C++
template<template<auto...> class...>
struct Stockroom_0;

template<template<auto...> class...>
struct Stockroom_1;

template<template<auto...> class...>
struct Stockroom_2;

template<auto...>
struct Seq_0;

template<auto...>
struct Seq_1;

template<auto...>
struct Seq_2;

template<auto...>
struct Seq_3;

using SupposedResult_3 = Stockroom_0<Seq_0, Seq_1, Seq_2, Seq_3>;

using Result_3 = EasyTypicalPaste
<
    Stockroom_0<Seq_0>, 
    Stockroom_1<Seq_1, Seq_2>,
    Stockroom_2<Seq_3>
>::type;

static_assert(std::same_as<Result_3, SupposedResult_3>);
```

## Implementation

We will implement `Omennivore::EasyTypicalPaste` by uniting `Cotanivore::TypicalPaste`, `Sequnivore::TypicalPaste`, `Stockivore::TypicalPaste`, and `Warehivore::TypicalPaste` into one function.
To do so, we need to detect the underlying vessels of the parameter pack in the template head of `Omennivore::EasyTypicalPaste` to produce partial specializations.
Hence, we create the following helper classes.

```C++
// Detect packed `Mold`
template<typename>
struct IsMoldful
{ static constexpr bool value {false}; };

template<template<typename...> class Container, typename...Elements>
struct IsMoldful<Container<Elements...>>
{ static constexpr bool value {true}; };

// Detect packed `Road`
template<typename>
struct IsRoadful
{ static constexpr bool value {false}; };

template
<
    template<template<typename...> class...> class Warehouse,
    template<typename...> class...Containers
>
struct IsRoadful<Warehouse<Containers...>>
{ static constexpr bool value {true}; };

// Detect packed `Rail`
template<typename>
struct IsRailful
{ static constexpr bool value {false}; };

template
<
    template<template<auto...> class...> class Stockroom,
    template<auto...> class...Sequences
>
struct IsRailful<Stockroom<Sequences...>>
{ static constexpr bool value {true}; };
```

We will leave the functionality of `Sequnivore::TypicalPaste` to the primary template.
In this way, we won't need to test whether the underlying vessels are `std::integer_sequence`s.
Here is the entire implementation.

```C++
template<typename...Packages>
struct EasyTypicalPaste
: public Sequnivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsMoldful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Cotanivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRoadful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Warehivore::TypicalPaste<Packages...>
{};

template<typename...Packages>
requires (...&&IsRailful<Packages>::value)
struct EasyTypicalPaste<Packages...>
: public Stockivore::TypicalPaste<Packages...>
{};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwA7KSuADJ4DJgAcj4ARpjEIGb%2BGqQADqgKhE4MHt6%2BehlZjgLhkTEs8Ylmkly2mPYlDEIETMQEeT5%2BQfWNOS1tBGXRcQlJKbat7Z0FdQpTQxEjlWM1XACUtqhexMjsHOYAzBHI3lgA1CaHbsjz6FhUV9gmGgCCRydnmJfXXo60hAAnk8Xu8zMcGKcvBcrm5iIZgJgFCC3qCAPQAKixGPOHlaDDwADcSOwQAAVQFpPCiWjKJjzb7YjFo0HMNgKNJMPa41D4okky6BKyot4ETAsNIGMWwgiUxisTAAOmVKNe82IXgc5wpVJpdIZgqsgQAIldhe83mi0ecLPTvm47SBQaCxRKpZgZXK2d86cgANaYdyyJhLYiq9WagjaynUsT66XXX0BoOCEORMOHZ6ooWg85585eLJGc6ytLfK7G85JwMeVOhs3Ok0NkWvK3nABKmGQOyyhPtjudovFkqY0tR11z%2BddI4TblL8rYysVT3Op3pCh5dfTr1Ik7z0/dnrL3qXK7XCg3tdaoZse5LXoVS%2Bw9DYgjVpEub3z9%2BPj%2BVz/FRgCAsBRdy/KcH0XZUAHkCAQBJkXHLM1QIDUtR1WNaXpWcrzTBJ3muADXwINVT0zD9cJvWEiKAkCyOwD9YPg4gFHoxtzW/QsImAH9y0OSsML1bCPXAvNYTvb9KO3aiXyA0jlQ/GjBDolVyIk/MmIQ09RJ%2BbAQBAedm3eJtDnNRtTRbTFsXOIRMAARy8AliWIUlBLjYTziZFk3m9DkuW%2BWyHKcgUTBzFsD1HD1rnnE9VOQiN0JjISDVCo1TVMwdW2tW0lFxAdwuHQ9osgn0uWTQKvEYPZw1QyNo11dyGVhat0AqqqouQ1K7y44t5x%2BSsWrayEorMkyzMta1O27FiiX7JQnQKt1IudCcdIi2cmD%2BVB6NXAwLxs%2BzKuGnc73WqKHS2nbzw3Ia9lvHTNqIJcADU2jwJhYnod9P1eb9Hu25VXuId7PswECwN%2BiDfygxVNJYlb4tqxKGqwprrluzACLcIGQa%2B1i4o/DGrGuHGPvoFTl3I844fxynOrCyG8x6ni%2BorerMPjETGZ%2BNx1LzDGsdJ0H5MVD8hfJ2mngh79vxp7TuaefTDIy7N0vG14zpW3m1sK5biuhzAP3%2Bq69puw72pOnWltnGKFSNy64t29cDoc9r7u5222G1S2PZK7V3b%2Bh3FXFzHQJ%2BwOnsBt6ybB0DTpKpcaYR0EEqjNzUdnAXYTJHdzhDkWpZdo67uzmw8%2Bj0GKcLuW4vY7qixZuV%2BvZ5KxwV1bue/LPrhzj95lHakAH1RHmbOCOwCB84UdYlz71pHGQYfsLHp5J4riWZ4JvnqbgrSVR0xWDLlIzQrVzLT8yqysRsoh/X5Fz9PTznPOxbzXl8zluRaVA7%2Bc8sGZdLrG2Cda5vFTi3RqYpDQXxVhaLKNo7R5XmplTW%2BsFylX9IGb%2B/piCoFQCwGqaE05JUgedQat8/S4PwaqLqOlma8WbuQn%2BlC8EENgTA9WbYpo9lmkg9gKCgFc3ElbGc51UEXUjnTJ2F4TbO2wSw/BPtvziPEcbR211ZH7XkVQlgAcpyCNhGoqRGjlQCzDqdAx1wjFnlNkuImcc1ogNhrveGSEU5I2ISjTmsJtGsKxmY%2BihMKE6OJm4exgSd7MUlpmOudCG4MLZp7b4T9hJ3mEZ3fMvjFE%2BPNsdWmhNcl3WiQxbeNdlwH0zErY%2B7CxrnybJZJk5wADqbRMAIHvq5EhGdGSv1ZAqPy3IWkuXaX/aBi1RFHnQWxMBHiIHdOgbUyy2VEEOmQeMoqc4/YtSGW07YShCF1RSWjNw2zWkID2R1WJ3N6Gs34lWMqgYdnnMLCNcyJ8Jodi7DwvsfCFpwM1uObWHtLFzhBUkzRxTpEbieRcpR%2BjrZiLBU4mx64IXNLORcvR%2B4kUGwhUuKS%2BFzEiI2eC9RtjlQEuIODeOuKYIuMQuPdxRC5neOuDCl5WNKUFypuypQoTKVVypmUmhDNOLxNuZWJJLLUkVKBTLfMvLMawi5fkzc150yCpKTpWW9L5bfkPsrUaZ8WwXwadZAAkgoAAsp4dAVAvC0BfliN%2BbZjSYDFFqT%2ByZLgADYNA2toOgEwfrAEIsmd6A5WpLUBrtQ69i5x%2B4L1XAIBkqg0jEHOLEPBjrCRiEqoaKgYh9ljUFMa/5YKcVTLJc7SlH5SWKiUgQZEMSZnMujba%2B1tBlXBnrIRWSghikiosAm%2Be1Jk0MFTemzN2bzi5u8P/CwtUPQlo4ZfRplq6SIk7U65k6JrRuo9VGL1gZfUaE3R6ENQ4w1oIjS2lCbaFDns7fGxNY60ATrFGmjNWbPCzrzQuwttBi1q1Le8jWFbr0SIBsY02Rd2r20kSHZtiMH1PrjejQp50kNsTvalEdA9kDjsnd%2Bmdc782pSXRw0D7DLTroUO2VATBY2Oq8nu84B6uxHoeegU9DGmPBo0KGiZN6FSRqjJavjzGX2jsI%2B%2B4j07f1kYA0W5dIHV3rOWoCixkGVHIszFCtFirpbwuE5s2lMHUUUp7emBlYnzgScY1JtlGKXndq3HvOmQ78NJrk5%2BqdP6c3/sNJRldiy4FXxxBJkMtBt2sY%2BRxz13HePRYE0JklJU7NRboM%2B7Mw7X2yZTX5kjimgupUA8Bs01H1YAqxtp0zqig4opkdWrRwTWHGexZB6x%2BmTGKgxrZu94CssxfQ2Etr1CMOu2GoO3DQpvNvsK5gL9CnAvzuCxqVTlX1PhcadgekgIjlQLi%2BBnTTikxMERMhpldU9sKAO107xbwQDnDSF4T6Y6KrBQfuSB7qTExlQu0iaZxk0pgd0%2BZ87l3VQuQcngFyG4ICnjMD68wPr22Buff9/0gPkP6SU%2Bsa7Wpbv3a8X9k5APLvA%2Be6997hG8SGA6Y/X7xzIdA9ASD7baW9ZmarYqVnV23gw68HDpE5xEcqmR6jhzTHMfk%2Bx1DypIB8eE6jMTw7ZCKds8809l7b2ASEaeYzn7pOWea8HblznV76tnbN9Dw6IuEdI5R8j4bsv%2BeH2V62m7%2B31fNTN1T3XtOb7MKN77rHfocfA66mF9ETI4/x5dY0skSIm07sT/HjPu6zXXwAGJw/mOcbAqhWCSh6c60E9ChBeDSEUQMnYFAOoIIPDQzc7hK2r/QWEEQCAfioLQRjPfzh94HxiD86BtigxBDR149D6%2BN%2Bb83NXzO27pO/G3gyHfzrd8LnedfBBN%2BwmH6OXv/fRwYilrvgg6B2%2Bl9hOPvXlykJVLLGB/Lg91wJAIBAdfCgFTv%2BbW4HPrQE3qkDZNXrXugEASAU8ATtPhFgdO%2BjxkXiXvQGnhXvElXjXpkHXkiPPlwK3lfvpN3pgIiMQIPEoFNtVNcN3h%2BKAXUOcGYB%2BIcFPurLPrgcAYPPgWzEvibivh3GvoQSAMQaQeQZhl3oILQTvjpOvhEFgKoKIZQedPQWYBftIYIbIUtgocXOdMwbhoroaplG/h/u0N/oIb/mwP/rCFAZwYTOAdgZAewU3lwDAWBvAWSO0sQEgcXm6GXlnidvVpWrFBZs1trvenVIqs3mDhBtbuZk1ubmEVqBEc4dPiooEX%2BMEfEeAhESoSkWkTDHZrWJEbkadrEYNrMoUckdVnkUqOzuAoUTkVUSUbzgUQIIPLoawRgXYUoA4Q3hwWYM3BEYJtcIUaARURRK0YwZuG0SwZlGwb0U3v0dwT7svkIvwQqi5koEUW4CMVIdzEkW5jYVMTkVqnsRsZgIPDkdsa0boZ1PodUurEYReJ/qYdfiAOYecfSFYY4RcbYVgd0dYccbAZwo0jntsO0AgIXt4aXmgVbiSiCt1tgAZrUbMlkiwEUY0QEV1o1j1uSqEeAqiZwVETpvCdiYib1nZgSQ0QIliZIhSfZOidSaZgiSri7IScUUyaSSyYFBcUSRybSWUcytye0bMZ0X8TgfMW0c3ASUMWEvSaAdyfQdyZMUKTMS2HMfPocIvssbwasXKpkuNmiTKdyUMQxOHPqcwjomybKXZIcUqaodzJSTkjaTcQjM/q8i2I8UoCYT/n/p8dcNYYcL8RAQGS4aZBwJsLQJwP4LwH4BwFoKQKgJwLzJYNYAmmCdyEcDwKQAQJoOGZsH6AEGYIqIEDUAABylkpAACc/gZgGgPqpZgZkZHAkgvALAEgGgqQsZ8ZiZHAvACgIAqQOZcZ4ZpAcAsAMAiAIA2wBAr2PeFAEAaAEodACQUQConAqgpZPqAAtD6pIOcMAMgIRlIIqGYLwIGIQCQHgNfnUPwIICIGIOwFIDIIIIoCoOoMOaQLoHUAAO7whpCcA8ARlRkxm5kJmcDQR/CznnCoBUDnAbnbm7n7mHnnDHn9EQAeBLn0AZqZnrC8BDlaCbAQBICLlUhYXkCUAkXLmJDABSCME0DAEISUCxCgWxARBtCAgAW8CsXMDECAjQSxDaCcacWkCLnETQQMC0AcUflYCxBeDAAOi0BAbCVYAsAIjiDSUi4OCzT9kflLZfJijCXEFNnxkAixDwi8UeBYCgWoR4BtncC8B9jEBZpKBuqqVGAAhGC5mbB94XYKDPR4CYDfnQTHjCW3nCA0iPnSBhWvlqCgVfn6AIgoDWDWD6B4CxD9mQCbCoBpBNA6Vbl3AVimApmWC1m8CoCOXAxYAZUQCbB2CcY5AuAMBBj5B%2BB1BhBLAVBVCFCZDZACAzCtXpA9VNDDCdVjBzAND1UCADDTCeBdB6B1VaVTULAjWjCJBzALD9XzXLUdWrUSC1XpmPlAUcDRmkBdllWcBwWbk7l7kHlHmSAnli64AXnYXggbB4VeWbDwRMZjA1WkAFmSCHCKiVmHCBCSAaCSA1B%2BoaD%2BA%2BqVn6CcAtmkBtmHBcCKg%2BpcD1mVmlkY3%2BC1D%2BDA0%2BqnWgU9l9kDnZleWjkTlEVTmQV/DkULn4KkUrlrkcBtAsCEiBBblMBOzFhcCVmKio3xnnlECVV6BhX3niBPnRVKCxUfm6CMG/lMD/n2VHUnVnVgUcAQUzl/DQWwVs0c1c0808R80C2Kgt7oWM1UWXDghmC4Xk3DmEXEWW1kXzmUVYUgD62c1rhGB81cCpD0VigsRMUsVsW8XCXcXsX8WCUODCWiVATiWSWgUyVyUKVKX2WkAqVqX7Dxn4AuRaV9g6VC2qD6X7BZlGWgWmXmWAiWXZ14XAx2VZmOXOWYCuVqXcQU0%2BXAB%2BUBVBUhXp3i0RUSBRWyAxXvnxny0JWeVFVWCWCpXpXwBZU5U5B5UFX8TT3WClUJkVVXlIgL29CTV%2BAQCuCbVtVNUrUrBrWDXFA5An1X29UMDn1dXjV9BLWDC30LVNDTWLDlC7XrVv2zWzCTCDCP1jX7U7B7B7Xw3HUgUfk9nnCe2G3e3G382C2PX4Ai3W0o1234V5mkBfVYCJC/VNmI3I383g2BD42BCBCHAQ2SC7l1Dq0k22Bk04OEVU1IDTmzn01u3M1sCcBs2IUsAKCEiEaEgm3ujzBnnoOXnXnPnhUPlD1yOj1xUgCBmK3K2AVQNq3E3gW01RgwXwPEAsCCPCOiPiORQF4W2YUJCYOHDYMU3U08NkCu3O1jAiM16DxiOVmDwSNN4CNRV0CB39kQDMUfkR1h3p3hN8UCVCXp1x2CAJ1SU52YCyXyViBp1ZmZ3uW10Z2aWOAF2gV6XdgGXp3l0fmV3sU13WX13CVN3YGt3uXt0O18AGBd3%2BWBXBWMChWyAS2RVKMy1j06CqOT3GDJWz2mXVWL25WcBoht7r0lXdnb1VV70f0NVH1NW33tU/0X3dXX19UAMDVFD30gOX2rOv0zUtXzUTWLXNDbXbNP1AMXNzV/3tAnOQMKAHWQNNnaOwMXX%2BPnBCMiOzrmNiiWNPUYM4XvUO2fWYDfWENHUkNJD82HCHD%2BApC1AdkouBD1lE2/O9nMODkfV/UgCSCBAnkUNcBSCVnkPA1cDBBNmHAwPdmcBQsEVHWnm4vMv4usObCOVZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/descend/omennivore/easy_paste.hpp)
- [unit test](../../../../tests/unit/metafunctions/omennivore/easy_typical_paste.type.test.hpp)
