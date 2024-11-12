<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::AreBoundedByClosedInterval`

## Description

`Varybivore::AreBoundedByClosedInterval` accepts two variables, indicating a closed interval, and returns a predicate.
When invoked, the predicate returns true if all the arguments are within the closed interval;
otherwise, the predicate returns false.

<pre><code>   Min, Max
-> V<sub>0</sub>, V<sub>1</sub>, ..., V<sub>n</sub>
-> (Min &le; V<sub>0</sub> &le; Max) && (Min &le; V<sub>1</sub> &le; Max) && ... && (Min &le; V<sub>n</sub> &le; Max)</code></pre>

## Type Signature

```Haskell
AreBoundedByClosedInterval ::   auto...
                             -> auto...
                             -> auto
```

## Structure

```C++
template<auto, auto>
struct AreBoundedByClosedInterval
{
    template<auto...>
    alias Page
    {
        static constexpr bool value
        {RESULT};
    };
    
    template<auto...>
    static constexpr bool Page_v
    {RESULT};
};
```

## Examples

```C++
// Create a closed interval [1, 4].
template<auto...Args>
using Metafunction
= AreBoundedByClosedInterval<1, 4>
::Page<Args...>;

static_assert(Metafunction<1, 2, 3, 4>::value);
static_assert(! Metafunction<1, 2, 3, 4, 5>::value);
```

## Implementation

We will implement `AreBoundedByClosedInterval` using only `<`, meaning <code>Variable &in; [Lower, Upper]</code> is expressed as:

```C++
(not (Variable < Lower)) && (not (Upper < Variable))
```

Here's the entire implementation:

```C++
template<auto Lower, auto Upper>
struct AreBoundedByClosedInterval
{
    template<auto...Variables>
    struct ProtoPage
    {
        static constexpr bool value
        { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
    };

    template<auto...Agreements>
    using Page = ProtoPage<Agreements...>;

    template<auto...Variables>
    static constexpr bool Page_v 
    { (...&&(not (Variables < Lower) && not (Upper < Variables))) };
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIIEapAAOqAqETgwe3r566ZmOAuGRMSzxiVy2mPbFDEIETMQEuT5%2BQTV12Y3NBKXRcQlJKQpNLW351WN9A%2BWVEgCUtqhexMjsHASYLKkG2yaBbkxeRADUoagA7gkWqwzopGcn53Kpqbf36IfYJhoAgmNiF4HGd/sRMHcvA9MOgLABPNy0DKwgCSggSADcxH9/iYAOxWAFnElnba7faYQ7HU6oAB0DIAas08ExYvQFD9caSzkCQQQzspiKgiMomMAqcTSQSif8eTyZo5kGc0AwxphVKliGdYqhPGdsd5JXL5SSZWcIAy6eYAGy2iAMEUW5nEVnszAKM7Ui7XT7Q9CLL1mO3Bs6OgUQN4fYhQh5eo5nF1ujmLVNe/EAEUOsp5BKzgVl3NJ5L2TAORxe9IZ/2AEJ2jAInMCvylJK8mSMgvFmHjGcFwtF3epNbrbEECitXILuKLJJLlOplatSbZHK5rd5TSVKoE6s12t1%2BrFEoA%2BpivRvzZaGbb7eHnSzVx7424fTcY19A7fQ/fI%2B8/XG3oru6Cipl%2BmbZjOEHTgCuIAPQAFRIchKFwfByEACrYEIGHIWhAKIShRH4XiBFwWcbgQmWPZMCqyJKOgZwRNsxCGl6/gWCkZySCY/gZtaALztRi60la4LAE2Lb/O2ETAGcACymBNFQ0IONkM6BH24KQl8sIIkiKLoOiLGGtSXE8c2uIgCAx5Ukc4kTjelkwaRgJbngyAnkwChKC0ECKcpqn1NS1RnGYTzBNxPzWYaXiYIskEAoqHleT5CQEBAYBgApSlMCpDBqQIIVPOFZyRdIZz%2BNFICxfF2YcMstCcP4vB%2BBwWikKgnBuNY1i8qs6w9uYgQ8KQBCaA1ywANYBGYdL4mYkgABxLf4GgAJz%2BGYGg2ktwRNRwki8CwEgaCkbUdV1HC8AoIApON7UNaQcCwDAiAgKsBCpKc5CUGgux0AkUSsJsqhLTaAC0NqSGcwDIMqUh0mYvCwoQJB4Ogej8IIIhiOwUgyIIigqOoj2kLo1RXMQTCpJwPCNc1rUTZ1nAAPKnN9AqoFQZxg5D0Ow/DZyI2YFoeAD9DasNXCLLwD1aMsEBIP9qSA2QFAQCrasgMAUjhTQtAsbdECxMzsQRM08J07w5vMMQ8Ks7E2iYA41ukP9Y4EKzDC0FbZNYLEXjAMctC0Ld3C8FgLCGMA4j%2B3gEJqZiHrMxqLunJso3MbUzO0HgsTU/bHhYMzBCuidEekMnxC6koGY7DHedGBNyxUAYEmMngmBXKzHxtaN2PCKI4gE4PxNqMzFP6DHKC9ZY%2Bj57dkDLKgqT1OHENjN8mmmJY1jbbwqDV66WBLxAyx2C79QuA8kx%2BNUYQRIMFTDNUhRZAId8FBkH8MHMQxVC6FfHo4xWieHaHoS%2BhUGigP/i/QBMwJjgKmLYWBT95ivwvgNDYSx9CM1IBdQ%2BnBebgyhjDOGCNJBIwtLgNGUszAjVlmNFuywECYCYFgRI59SAzUkIEOk61Aj4kkBoSQi0bRnX8DadaeDDrHSSFwOkNouC7XWktFR/hJBcH8IIm0BDmZXRundZhj1FZvSVh9DmP0NZa0lsDNgnBmgsExPiCGtFkAGE7FwdadJFEdVRkQE%2BWNZC4xHtIMeSgJ5k10OFKmNNrYMw4C1fRZMrrsy%2BqcM43NnjEGca49xni5LeN8XSDQYtUASwSEGQIZgmHyyehY2xCRfqawqarSWIAnEuIhh4mO3iuApANkbSgpsya20tm7cZ9tHbO1dpXD2DZva%2B2ZgHIOIcw5uyjo3TYHV8CJ0cMncO/jVDp22G7bOB0Op5wLpbYuOy5blzdtXWumB67RyME3UApi%2BDtwUJ3buvdGBu0HqE/G4TZDj1Jh1GJ09m67ysPPa5Z8V5r2yBvLehwMzwv3pdY%2BGMU7LyAdAm%2B7hkH3xCA8OBCw34/3qF/GlRRshUtfkS%2BovQkF5HJVAtlaCygAMgaA%2BlqDZjoP5TLFYawcHioOskwhLMOA5LyW4uiMdhY%2BL8TQ/AgTqkyzliw0gbCOHDG4QdI6pATqBB8aI/EOj8T4kCGIyQ0NqhysMbYYx9SzHwAsZ9TmLSmnEHsZsJxAsWAKExMqTExTKRjBRlq9GmNqgguHmCwm8hIlQp0EkUgcTaYR0SbKgxbMrFcx5iGmGYaI0GmjdRMY5TKn0MCIEOpLdnrKzaWrf1HaOkRveGebxJ4Y0EC8rk6GfA6DDJNmbC29tJkzodk7K%2BbsFmCCWX7XZmBA7BzEBsyuWyPn3NIHs4BhzU4nOQBnc5GJLm8GuYXREGBD1lzwBXUazyURvMbrJVtbdxR/K7j3PuwKQkpokOComGbJ7ZsKbPPeiLF7wBRevTgcEt6wYRRYA%2BnU8Wn0Q6y7IJKhWPz5fA7%2BjLP5krI7/ZlCDajAIEOysBnLIF0egYxmjAq%2BhCsQf0UVpHxUKGwfjAtTNUnEPLWcStkaa3bDrRAWh2rpYttMaw9hnDKCJLNSdMwPim3%2BDWlos6Tb8S7RSZdTgRj7r6t4fiJGNquBSHWtawRXB8SyMCKJ8z10TEK0ScjMzRDvOeuWNXTIzhJBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/are_bounded_by_closed_interval.hpp)

- [unit test](../../../../tests/unit/varybivore/are_bounded_by_closed_interval.test.hpp)
