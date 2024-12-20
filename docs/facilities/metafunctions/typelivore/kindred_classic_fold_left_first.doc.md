<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::KindredClassicFoldLeftFirst`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#typelivore-kindred-classic-fold-left-first">To Index</a></p>

## Description

`Typelivore::KindredClassicFoldLeftFirst` accepts a list of elements and produces a function.
When invoked by an operation, the function left-folds the list with the first element as the initiator.
The type result of the operation is used for continuation.

<pre><code>   Initiator, E<sub>0</sub>, E<sub>1</sub>, E<sub>2</sub>, ..., E<sub>n</sub>
-> Operation
-> Operation&lt;
   Operation&lt;
        &vellip;
   Operation&lt;
   Operation&lt;
       Initiator, E<sub>0</sub>
   &gt;::type, E<sub>1</sub>
   &gt;::type, E<sub>2</sub>
        &vellip;
   &gt;::type, E<sub>n</sub>
   &gt;::type</code></pre>

## Type Signature

```Haskell
KindredClassicFoldLeftFirst ::  typename...
                      -> template<template<typename...> class...>
```

## Structure

```C++
template<typename...>
struct KindredClassicFoldLeftFirst
{
    template<template<typename...> class>
    alias Road = RESULT;
};
```

## Examples

We will left-fold 1, 3, 4 and 3 using subtraction.
The process can be described as follows:

```C++
   ((1-3)-4)-3
-> (-2-4)-3
-> (-6)-3
-> -9
```

```C++
template<typename A, typename B>
struct Subtract
{
    using type
    = std::integral_constant<int, A::value-B::value>;
};

template<template<typename...> class...Args>
using Metafunction 
= KindredClassicFoldLeftFirst<
    std::integral_constant<int, 1>,
    std::integral_constant<int, 3>,
    std::integral_constant<int, 4>,
    std::integral_constant<int, 3>
  >::Road<Args...>;

using SupposedResult
= std::integral_constant<int, -9>;

using Result = Metafunction<Subtract>;

static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

We will implement `KindredClassicFoldLeftFirst` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:**
  1. Left-fold several parameters;
  2. Use the result as the initiator and perform recursion to fold the rest.

Here's a simplified version of it:

```C++
template<typename...Elements>
struct KindredClassicFoldLeftFirst {};

// Base Case:

// Fold once.
template<typename Initiator, typename Element>
struct KindredClassicFoldLeftFirst<Initiator, Element>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = Operation<Initiator, Element>::type;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Fold twice.
template<typename Initiator, typename First, typename Second>
struct KindredClassicFoldLeftFirst<Initiator, First, Second>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = Operation<
          typename Operation<
            Initiator, First
          >::type, Second
          >::type;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};

// Recursive Case:

// Fold twice, handle the first three parameters,
// and recurse using the rest.
template<typename Initiator, typename First, typename Second, typename...Others>
struct KindredClassicFoldLeftFirst<Initiator, First, Second, Others...>
{
    template<template<typename...> class Operation>
    struct Detail
    {
        using type 
        = KindredClassicFoldLeftFirst<
            typename Operation<
            typename Operation<
                Initiator, First
            >::type, Second
            >::type, Others...
        >::template Road<Operation>;
    };

    template<template<typename...> class...Agreements>
    using Road = Detail<Agreements...>::type;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIACcXKQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcBJgsaQa7JoFuBACeaYysmAB0d9j0bIIKx9gmGgCCE8ReDgDUAGkIuhiJh3AYFFlkAAxTzoUKYKgEaF4YgTP4mADsVkxABFjlZPu8PgB6El/CxMJR/NxU9jE4lkv6w2joP4CLY3Ym7faHTDHU4XK5sP4ASQY2SYRDIf3Ol2YIoee0YBFexO%2BvwIgOBoPBVKhLPhiORqImAvFkulpD%2BSqeqsCbyJ2OJf1dsr2Byl/JOPM9Rx9QoVtzurz%2ByAhCj%2BAHlLsQpTk1Z83X8Nf9cZgWnQXW6sYSPsnk14skZZUKMUmC67jrjo7H4wJzRLHFKSNbbSrXiAQHLvXnk1j8YE89nXb6%2BQKx16J4HrncuQ6wxG5x9gKDlc9E/m3UWIsA/gAlVBMNnVv7pzO0AUrtd2hRzzvdoUEhl459Ez5Mw2ygDueE53I9ccA3la4xSbPAWxlHsg2ZU0CGtaDQKETA0AYdBN1TLUgTQ3U3AjP9DQRJEUTRe03AtZsrVg0jrWQ1D0IdF8%2BzdSd/VOQCp2A4Vg3nbBF31WsEnrBhN2TTCzwzJgswrKtnRkgsdxLHtyy3StTxjITGgFEdK1LECRQ0uMtJOHTdLAy1W2os15LUh0ux7WiUIEdCbILB8ezfVSMVfIcGXk1jvXY3lOMFfSeNDcN9WXVdMHXAgXkY%2BTFL3Q9jwxQIa3PKTLxOa9Ytve87MfS5PIHUqP3JfcUI2LIADdMBpOkQD80lyS/Ahfy2a0EEMdB6FlBAGpoUiBrXP40laa5djRUhGXJXq/lBZAaoa5KBoa0EJi5T4AunMLzMoyzEJFEiJgQmcRTo5zzrCucowIQa0Qwggfn%2BbCQTBPD9QIuEiJNUjGwsmVTvgv4rrQ617seu8Q0Sj5cx03afQ4tjjvChdIshQSjITOGxJezUJIvHSEdc101uU0ycwy7UcM%2B/CYV%2B40Qe0smCzR7HhNZryzI5wyuZMtmzIoiCqJZoXqeweyhUc%2BiqdsqXiswSGHoSGHtp5yX7JRhrUoYtx%2BeMt5fPksqTfh/ydYnK2uKDQq%2BMx9W8rihLHS8ta9fSzLJKzXKYpd%2B3pZK82zeHD8ACpI6j6OY5JRlo7%2BAAVTAJkjaO44jmOs6jjOLfhsxAgicMvCwdK3FQrY0nizcAOC1GLoaj4bu4ilnterUhC8WIXqYBwmJ0imn1NmmJnQLsIl2VcxAAfVQuZBAFCfrQ%2BLtarELxMAAWgsVf1%2B9Y3hx8sOPiRoK/UCtH7f4yFl2IYBXeJNaAFlJKoLwGAcHIVNPd7cIZwjmZwW5vjMeIAJ6YCnrQWeAh55kSXn8LgrxZryVHuPQQEC4xQLni0BeJx4GBCQTpVBYD0GQOgQwWBi9BDWkkIQlBBBQHgLIdgwwcDqF/AIXjdKis9ZXjvurNUIdPhrU7mkYoYIqoKC8LQVURIR4MLQZPTB5DKF4PYZvJIgjj4exTtIrUp4X4tDfh/YybhO7dzjH3RiQivgtEcMgae%2BoEgEAgMQhQ1xHEJTcJIvRtEvBiMyBI3RMjXjLAJBwVYtBOD%2BF4H4DgWhSCoE4G4aw1gUzrE2A1cwgQeCkAIJoCJqwADWAQAAcNx/AADZSmVKkP4TElTJBJECA0/QnBJC8BYBIDQGhSBxISUkjgvAFAgF6fk%2BJETSBwFgDARAIB1gEDSF4eCFAIBoH2HQBIURricFUDUzejS/jAGQMgBBkgbhmF4GCQgJA8Bj1SPwQQIgxDsCkDIQQigVDqAmaQXQqRvxxjSJwHgkTomxIKYkzgUZllLK1KgKgfw9mVIOZII5JyzkXL%2BBADwGz6DEAxAXLgyxeDjK0KsCASB1lpE2WQVZVKaUgGAFIMwfA6DTRGRAWIELYgRFaGcYFvAeXMGIGcKMsRtAoXGbk9ZdoowMFoPyn5WBYheGALSWgtARncF4FgFghhgDiCVaiSVeB6paoSZgVQ1VdgCvIOgqJPzaB4FiHGEVHgsAQpengLp2rSD1WILEQJ6Y9VGCdUYApqwqAGHvgANTwJgb8Gk4m5MecIUQ4g3mps%2BWoCFfz9D6pQKkyw%2BhnUjMgKsVAVcchas3qPasphLDWDMAM/1xA7kp3gKsOwJrnAQFcNMPwqQwgRGGFUUYqRijZAEAOvQk7GgLBGIkcY9Qe1NEmO0TwnQ9Dds/gIfobQF1jqXbYddM7xjrsPUsIlawNhbAkKCjgMS%2BkQsGYi/ZhzjmnKkJiiAuAbn4uyUSklEbViDWPKMCAxSQCSECDcZpmJJAaEkGYSQlSelVKSG0jgHTSBdJyTcWp1SkilK4JU/wkguD%2BGaZU59PzBnDNGXkiNUzZkUvmTC5Z5BKD0rxdstgnBWgsFqpiTeTB%2BIli4EkG4XAbgWvwNKO5ehU3PIzdILNSgc0/N0CygFTAgXaofU%2B/pvBBnQsWcs9kCLBPCdE%2BJvcknpOyaxTi6leKCWBDMMSpjEzyWUtQLihIXG1n%2Bdc6MazInIpGEk1wXpNAZFq0oFyn5Qq%2BW2pSyKsVEqHC2plSqOVCqIXKtVeqzVtrdX6sNQk/AS1HBmohZa612xcngIdQkp1Lq%2BXuu2Akr1Prcn%2BsDUoYNFXdzMajUwWN8bE3yltcp9Nry1OyGzd8hJ2n83hobVYYt7Wy2QcSVWmBnBa0MPrUWiwzaTOtvbbtrtK7d1%2BD7WhM9IQ0KXvHekTIU7ciboKBOz786R2LHezuxo%2B6N35EHT0VdYO3vHrmFMH7kP4eDEB4u%2B9N7Mno4dUZl9nA/jhds5F%2BzUmZMaCxX%2B6U7mgPebJaBzA4HEh7YdThvDUmNANI0P4EjKRJMaFqMZyFQzbCMdJZM6ZcyFmwqCzxrZOyOCCcOSwBQtVTm1Qc3yCYVz5O3Pue8tNLyJCLY%2BRplbOgQDBF0/pkFWGcd0ahRxuFVniAsEV8r1X6uvTomxSFml7nAhedF75lAPu8XS5D6MFXYjp5q6SNPDXBBHHO8aay%2BLaJEvct5SKtLmfRXislTl/zsr5WKqq5gFVaqxCld9eV0N3WdXGs/nVn5DXlo2t9S1iF7XXVnC656ttfXeADaDXsEb4afN8GjQoONCak2zdkCphbevlu5vN%2Bt4wZ2S2xBu/txoWqSSoM202ltCQ21YG3yDnILgnuI70MOioaO/slByM9udORYfbru6D09N/l29D3Re1HI9bdb/CHYA%2BYQAq9LtDJO9a9bHcFO3DgfHJPVFJXFXP4GPG4ePcnbXADQlAPEDUgMDLARnB9FnEAMwKTQIdnJDQIRpQIQIZpLgGpWjAZTgBjMZAgkpCjG4GDLgQIUpcjAufwDQSpFDLDQIeA1goXQPB9S5FgkzNgmnQpP1NWS/SQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/kindred_classic_fold_left_first.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/kindred_classic_fold_left_first.test.hpp)
