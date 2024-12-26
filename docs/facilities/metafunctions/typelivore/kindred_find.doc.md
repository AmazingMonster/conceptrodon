<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredFind`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-find">To Index</a></p>

## Description

`Typelivore::KindredFind` accepts a list of elements and returns a function.
When invoked by predicates, the function returns the index of the first element that satisfies all predicates, or `-1` if it cannot find the element.

<pre><code>   E<sub>0</sub>, E<sub>1</sub>, ..., E<sub>n</sub>
-> Preds...
-> (...&&Preds&lt;E<sub>0</sub>&gt;::value) ? 0 : (
   (...&&Preds&lt;E<sub>1</sub>&gt;::value) ? 1 : (
            &vellip;
   (...&&Preds&lt;E<sub>n</sub>&gt;::value) ? n : -1
   ))</code></pre>

## Type Signature

```Haskell
KindredFind
 :: typename...
 -> template<typename...> class...
 -> auto
```

## Structure

```C++
template<typename...>
struct KindredFind
{
    template<template<typename...> class...>
    alias Road = RESULT;

    template<template<typename...> class...>
    static constexpr std::make_signed_t<size_t>
    Road_v {RESULT};
};
```

## Examples

We will find the indices of `int**` and `void` in list `int，int*，int**，int***`.

```C++
/**** IsIntDoubleStar ****/
template<typename Element>
struct IsIntDoubleStar
: public std::is_same<Element, int**> {};

/**** IsVoid ****/
template<typename Element>
struct IsVoid
: public std::is_same<Element, void> {};

/**** Metafunction ****/
template<template<typename...> class...Args>
using Metafunction = KindredFind<int, int*, int**, int**>
::Road<Args...>;

/**** Tests ****/
static_assert(Metafunction<IsIntDoubleStar>::value == 2);
static_assert(Metafunction<IsVoid>::value == -1);
```

## Implementation

We will implement `KindredFind` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<typename...>
struct KindredFind
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    { static constexpr auto value {-1}; };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First>
struct KindredFind<First>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr ((...&&Predicates<First>::value))
                { return 0; }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};

template<typename First, typename Second, typename...Others>
struct KindredFind<First, Second, Others...>
{
    template<template<typename...> class...Predicates>
    struct ProtoRoad
    {   
        static constexpr auto value 
        {
            []() -> std::make_signed_t<size_t>
            {
                if constexpr
                ((...&&Predicates<First>::value))
                { return 0; }

                else if constexpr
                ((...&&Predicates<Second>::value))
                { return 1; }

                else if constexpr
                (
                    KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + KindredFind<Others...>
                    ::template ProtoRoad<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<typename...> class...Agreements>
    using Road = ProtoRoad<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGe1wAyeAyYAHI%2BAEaYxBJcGqQADqgKhE4MHt6%2BekkpjgJBIeEsUTFccbaY9nkMQgRMxAQZPn5cFVVptfUEBWGR0bHxCnUNTVmtQ109RSUDAJS2qF7EyOwcAPQAVFvbO7t7G2smGgCCm9sA1AAimAmujMh4mArnO4cnZ/ufu2/HR79mAGZgshvFhziYAW4CABPW4AfQIxCYhAUEOwf3MQIYIK8YIhbmQQ3QWCoaIx7y%2BlO%2Bfw%2BG3OAEkWAl6GxBExqi9tj9aVSvj8/gRMEyDIL8TDbsw2AA6GVkk5DYheBznADSwXQxEw6AAYuqMQB2Kwnc4m86C4XszBioXMy1i2GMViYGVStHnEFMBQKF3KTX4USC1EA9HG00KpUEc6%2B1BEABKqCY6D%2BpvBhvOE0cyHdAiGmFUCWI5yYXiI5wAbmIvJhUxYALRcEz6y4Qiyp5sAo2/UMm8220WQ3siq0Dh2S52y4Pugxel3HYCaoWMAhBkPHFNeFJGc7xxPggGXKPEGOoHdJyFzhes5cuskdg3tzsCm1D%2B0Sp3nXXEIZy47h5VqhgNS1XVAPxT9v2DA1OxTQc7QHZ84KhUcnRvScPRnGVfS1PAAyeH8Uz/SNozjBMk27GtTWTFMwzqTNswYXN80LYtSwrbxqyo6ia04rjKIAVisPjLggWZzlrN0iRAEAWCYABrTA4RSYAQnQBF8RSAAvBSCHw3iU0baC9N4vAqHoxiC3OKAbzMAA2cwbKw/1LSDNxwJ04MpLYqtZlmHijMotNNQIJYGHODQWzbck1386jKiUPyYoM84gpCsSGw7SLyL0xthN8rKAofHicpbKKYIQ/soXK4ckLfaUJ2wKdPW9GUL0wRdBBXHiN2CYBt1IvcD2Ik9SPxVr2uveqSpOYq72mk5YIq8VHTYD88C/AhSDNZCVqETA0EAzalrHF0AHkCAQaJOvlREI1VdU/RAs9XLWoZNt2/b0E2s6Lq/VDVwMniFuqoHX2W8dXTQ6dmqlRycOc3STUIw9j1PIq0xNBLEdonCzMFJiixLVBy0rDj8oxw1MeokwBOp3KxIkgh0CkmT5MUvBlK1NTIU07SEaMgGyaMkzcbzAtKb0qzZVs%2BzYdwly3LRTySZ88XeKSlLiFC8KMuKubopi004urYX9vM4hVa4yXXWl2zZfhyF3oEM9sCV9iVcF7LAswYLNfOdLW11rt9YN84jfOE2czxsWPd4iALaMgCgJ1PVIW%2By6/vjvSpKB5GSMTfE7cDDOY/812q3OMAwAhA960z008uDg2krrriNdCsxwUsO7AIelO3DT37JpLozs6q3PhvzyFC6eYvG5Dk0y%2BHAPh/0ptSvn0PaHileAtbNu0oiwOm6bETKZmwzycKvWyotRaqtB476sajCpTGq8ruD7qt1PAbx9R895xtXfhnWavw16gJpLyakFILjYFUKwZk1ZXiQKgVyKKmJgSgg4iOeEiJkTLh/CgrYDIFD0kEJcRYER6CdELMg%2Ba98cFg3ONgFkS4fxI3pKQ8hlDqHDD%2BCAc4CQvBUJxpJEAeAFCKSdPiFh41NrBAIFsN0ANwGPhgcQzhAA1VAeB0Cci2D8EGjCxzMNYYIdhN1lRaJ0WRY4AihEiKzGIiRUi2AyLMRtcsNjlEU1UVFWk5wACy3smBUC8NiDkdDjhGMqrfYG21wZunQtDY4xBgAfy/r1YJdQwkRLSL/ROvdQKQgUfIwQGwymKIqeHcpGwfxSX/m4VJ6SQFqNODsc4AAVJ4y59EHD%2BBmHCcImrRAIBAbJoTwkODSPiThZCCAUOEbw%2BoisQBeWwe2A8ZhfKgMGcgYZXpRnjJCbk6ZAhZkKG0bo1Z6yBrVzSjszsHB5i0E4HxXgfgOBaFIKgTgbhrDWHTIsZYHFAQ8FIAQTQzz5iyRAHxSQUoNAAA4zBmAAJxoq4HxZFSKuD6n1NIV5HBJC8BYBIDQ8RPnfN%2BRwXgCgQDxEhV855pA4CwBgIgEAiwCBCI2hQCAaAmR0GiKEJ0nBVBIpsrWGykhzjAGQFmKQUozC8GwkQYgui9D8EECIMQ7ApAyEEIoFQ6hmWkF0K0AA7kiBInAeAvLeR8qFPzOAnRLLy84qBTISqlTKuVCq/YIo7hADwQr6CFkxFwWYvAmVaHmBAJAgqEjCrIPypNKaQDACkGYPgdBBRfkoBEZ1ERgj1GhHa3gJbmDEGhCdCI2g9pMvBYKq8J0GC0HLWarAEQvDADcGILeFbSBYBkkYcQXa1qNrwGWJ4zq8x7RLKscFCjKjOtoHgCISIa0eCwM6xEeAyXcF4DO4gERkiYGuKO4A66jBQvmFQAw6TNGPEtSdCUQ7tXCFEOIA1n7jVqGdRa/QhhjAAssPoDd9LIDzFQAkao9KOC1iJNXUwlhrBmGpSejVWAoMiTaFO5wEBXCjBaKQQIwRejFH6K0HIqQBAkeyMkOjDAph9FKPhs5NRhiNE8M0PQdgCNccmBR6Y1HbDcYY%2BMbjrGqOlHmAoYFKwJAOo4O80gVLeA0vOD66Vsr5WKqDZZXAhASCdwBFGmNd75gXUTP0PDsLJAAilGigEBKNCSDMJIGyFK%2BI2TRfoTgJLSBkvM1KGyXAbJIrRbimy8KsUuZsup51NK6UMohXe1lHKE1cvdSWcglB03htFWwTg9QWBln1LWJgjUtxcDRVKLgiLVX4HVZq1on7dU/ukH%2BpQAGzW6Bzdapgtqj0qbUxpl1HA3U8pLJ671krdM1d6nVhriLLKhuTeGsz2zLPMvjYm1AYboj5YFYdzb/QPRGDq%2BUGgtB830ogEWs1Vay1DpezWutDaHBDpbUuNtHbnXdt7f22gg6j3DqFCB8d3z8CammTOhD3z53IEXUOldRLvnrs3WWndqxvn7sPeCk9Z6lCXqhz1DLD6mBPpfW%2BxgH7ZCdf1d12Q/7TXfIG8B29qGrDgax7hmDcG0gIaQ4zFDYGLAYc01h3Rs7oMceqC4QCkmyOARkzMGjTHqgq9o9UdXYmBOcZoTxzIpHDfVGN/r9jEwRi8bGOJ4ThQ2PKYWEsJTUaAuqadWarTOm/WXeW/VxrGgjMtdM5G6N6W9vWcwLZmIeGiVBZC/V9z%2Bo%2BJovxQCDzXnJCtAmyl2waXY0srZZy7lvKTuFZFWKjgZW/UsAUGWLMZYVtDiGM1kz2GtWM%2B/czw18hevs50CAAEpAhsjftZ78byXXW5cjF67T9fG/N9b85SMIazsprMwCSPxf9soE3%2BGyvh/%2BhN4SAkOELe0VwjbwQOEqgZW5ru5dQtxbS01re%2B/2t9bG0/cO629tTtGHTAHtPtAdBDcFEdKHPHXgWHKdBHOdVQBdQUNHQQVdM1LHLdaEXHPdDVQnY9aIEnC9SHMdCnPbPgR9S5Wnd9cHDrXvCQFnI1QfQDEfLnUDNDPnSDeAQXeDTgNYSSHndDTDaIbDOXPDc3NIJXdwO3UjcjJ3WTRjXINIHXLXNIK3fjSoQTY3FXCQgQS3ETZ3KTLoHQ6TAwhQj3BTN3fVMbb3alTgRfWVBvJvcsVfQMdfYzdVMzCzKPONGPOPSgFTJPEAdFKUAEAEPibFXPClMI/USLJLH3TgVLRlKzUgBzPiZzPFfUClJFSQTFLgFFWyT3AEWwzTRInw6FT3FVeIuw2lconyUgE9FIZwSQIAA%3D%3D)$Done$

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_find.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_find.test.hpp)
