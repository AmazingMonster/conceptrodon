<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::Find`

## Description

`Varybivore::Find` accepts a list of variables and returns a function.
When invoked by predicates, the function returns the index of the first variable that satisfies all predicates, or `-1` if it cannot find the variable.

<pre><code>   Arguments...
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
Find ::   auto...
       -> template<auto...> class...
       -> auto
```

## Structure

```C++
template<auto...>
struct Find
{
    template<template<auto...> class...>
    alias Rail
    {
        static constexpr std::make_signed_t<size_t>
        value {RESULT};
    };

    template<template<auto...> class...>
    static constexpr std::make_signed_t<size_t>
    Rail_v {RESULT};
};
```

## Examples

We will find the indices of `2` and `-1` in list `0, 1, 2, 3`.

```C++
template<auto I>
struct IsTwo
: public std::bool_constant<I == 2> {};

template<auto I>
struct IsMinusOne
: public std::bool_constant<I==-1> {};

template<template<auto...> class...Args>
using Metafunction = Find<0, 1, 2, 3>
::Rail<Args...>;

static_assert(Metafunction<IsTwo>::value == 2);
static_assert(Metafunction<IsMinusOne>::value == -1);
```

## Implementation

We will implement `Find` using recursion over the total number of parameters.

- **Base Case:** Handle several amounts directly.
- **Recursive Case:** Check several parameters at the front of the list.
If a match is found, then its index is returned.
Otherwise, drop the checked parameters and call itself with the rest.

Here's a simplified version of it:

```C++
template<auto...>
struct Find
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
    { static constexpr auto value {-1}; };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First>
struct Find<First>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
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

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};

template<auto First, auto Second, auto...Others>
struct Find<First, Second, Others...>
{
    template<template<auto...> class...Predicates>
    struct ProtoRail
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
                    Find<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value != -1
                )
                { 
                    return 2 + Find<Others...>
                    ::template ProtoRail<Predicates...>
                    ::value; 
                }

                else
                { return -1; }
            }()
        };
    };

    template<template<auto...> class...Agreements>
    using Rail = ProtoRail<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKzSrgAyeAyYAHI%2BAEaYxCAAnADspAAOqAqETgwe3r4B0umZjgKh4VEssfHJtpj2JQxCBEzEBLk%2BfoG19dlNLQRlkTFxiSkKza3t%2BV3j/YMVVaMAlLaoXsTI7BzmAMxhyN5YANQmO24EAJ6pmAD6BMRMhAqn2CYaAIK7%2B4eYJ2fI43QWCoLzenw%2BBEwLFSBkhpzcTC8RAAdKjQR9xsQvA4jgAxMLoMEmJJWD5HclHSHQ2GYeFUmFMOFnREotE7bBHA5MBQKVHI5TETD4USQ57ssEUo6Y7EEI4C1BEABKj1oEopxIsUuajmQnIE40wqlSxCOLNQRwAbmIvL8NQBaLjEgAip01ztdRLJFPpNLpUIZTIRSNQfJenIMPL572AgqhjAIYteXvJXkyRiOyrofydcuICtQmdVZ2jsbYgl5bNeO1JnySLurnvePsZtOZwbxeGI43R72lOPxDEJZ3xXYIPY1avJzcD09bQdZyLDXMjqIFQrwIswicnWqxOPlSpVO416uTkq1jI3eoYBqNJrNluttrPkonL/P5JM/is/idECWRx2mGgIgCALBMAA1rcmTAOE6B3PCmQAF63GO4rvh%2Bb7vB%2BOEUngVDXrexpHFAoZmAAbOY5FrsKLZim4I7duyoFWt4mBLEsO64a%2BJJHIKBDrAwRwaK6Jx1o23E4XUShcZJYmavxgmAY61ZiS6GHns6/6yZ%2B4kNme7r6eC2Hev6vpnLO8JmqG7LhtyFbIiWmBxuWPaSqmYTABmKrZrm%2BaFvCTkuQmNlVjWhnhRCZktlZ7aMQQpCmu2QiYGgg6JdZqIAPIEAgcTbhi9wyh2g7wvFiUpWl6CJTleVdqFRIkjulkWdFgaZYutnLg5NEbnRbkUn2soHgWR4Gbxn4abMOqEZCd5JUQj5sScGlYXJJzfl%2Bf4AUBtkgWBkHQXgsFCghZzIahA2SWt614QRaVEcQOncaRaIUVRvWbvR8UvCxT4cc9uEnopxBCSJqnuh8gNSbQShHPhs2Gsa0Mfq9i7vRRn39WclUCEO2B/WxAMaUDvEg0JKluuJUMkzDcMIw9c3I7TqMo9xA5Dm4tX5Q1LPcaBs5%2BYedDwljoq8yZt3noTNpHGAYCnDmDps5KnF8zxbrqzh5NHGYJyWCVnPc/VlYqzhAttb8I0BWcYtbhLUsfjLraa5Lt2Q8ZjtHNJtJa7pCmYAJoPKaJHvrVpatuzx9Y1tHHo027LXnJbsULkuEYOUFZYJldRweemha%2BdbR7FjGznZw5oJGRFjYAPQAFSN03ze12CDeNwAKtgQgd03rcfO3zct42XwMAcXjHPCaWbKkOfocZScPgAkj2Q1HEvCgdwA7qgYIgEcqReNEtBXvt0SoJ4NyM4YaFuEv2aK7rYYTnpkVNinbaLSv89rxvACyYRUxZXCHvA%2BR8T66jPhfWgV99TNEEPCb%2B9YnTK1si/GOjYk6L2DKFOyK5HLEGAAVd4%2BcvJ/0DkwKgXgx4NF8hzeEGhEpcESmYRKOweygRtm4d4hDK7imroVS8yAbj2TiAQCA5DmhUJodkRBm8d6/RAKxWWitH5mE4kZaaG4RE8jERIih0iHCyLOP/QBChgGtgJkop8D8dhKy4BomsHAVi0E4P4XgfgOBaFIKgTgbhrDWClGsDYtozA7B4KQAgmhnErAggUZEGhJBcCSDsDQ/gNAUXImYAAHNk/QnBJC8BYBIDQjDPHeN8RwXgCgQCMKiV45xpA4CwBgIgEAawCCHwShQCAaBoR0DiBEVgWxVDZPInacikgjjAGQLqKQyIzC8HXEQYgeB0B6H4IIEQYh2BSBkIIRQKh1ANNILoZhW8HipE4DwFxbiPHRJ8ZwLKSIulHFQARUZ4zJnTNmUceZesIAeH6fQE0uwHG8HqVoFYEAkB9NSAMsgPS4UIpAMAKQrCaC0EhF2Sg0QHnRDCC0C41zeAEuYMQC4WVojaFSvUiJfTs7ANoMSk5WBoheGAAiWgsMSWkCwOBIw4hWWdlpXgC0W4HmGlSkiLYESwiQlcSck%2B0QHgUo8FgB59w8DFO4LwcVxBz5KCdFCQwwAT5GGiSsKgBgiEADU8CYC3lla4niImbOEKIcQez3WHLUA8s5%2BhTUoACZYfQeBog1MgCsVAs9sg1I4HaQEitTCWGsGYCp%2BrVlYEjf%2BboornAQFcFMPwzCQhhCGJUEYzCihZAEMWvQNaGjzGGPEZhdh82NAmG0TwHQ9DtqMQIPorRm2VtbbYLt9a21dpHYsBxqx1ibAkLcjg7jSDlN4JUo4nyJlTJmXMyQCySK4EICQfW4SlgQstSsPKTAsDxFzXEyQOxkQJB2EkSQiSzCSHIqU/w5EEj5I4IU0gxTwnInIlwci2SEjZMg4ELg/hX3kTXQ8yp1TamRMtU01pML2kvKROQSgyKQVDLYJwFoLALRJDtEwOy6YuAJGRFwBJSz8ArLWRs2Q2yvXSB9UoP1JzdCsIuUwK5url2rvXY8jgzzOlIjeQRCjVGaN0a8gxpjCSSJAvhSCs96jL0NOhbC1AwK4iEd6SZnTIwlPUa5EYBjXBGGYuxTUiAeKTlkqJbyzzFKqU0ocLyhl8YmUsu8WyjlXKeW6r5SawVWwwsiqMeK%2BN3ipXIBlby%2BVdQHnKtVRcdV8WIWrJ1RE/VhrMDGoFWazyWHrVMDtQ6p1LreXuu47s3jshfXHO8UJwNFqU1WFDcqnN0bY36k4ImggQ4nQDbTRmuIWaJVRrzQOvwhbByTtIGW8oLaG0ZFrTkHt%2BRq37abeWhYVaVsNCHd2vIJaru9Gned3bU7%2BibdmMO57o6l3zpCT9xVknUOcFNMQSj1HaN2bU4x5jGgj1sdPWCi9mHDPXswLekYubFXAdA4xxJSRENJBSZIL9kzmFSbQ7YDDkLGnNLaR0rp5niODOGeR0H3yWAKAtLqC06maTjFYyerNnGtmeva/s%2BQ/Hus6BADsUgImxM3MA4Dk5lTZOvPeSDlg7POfc953RWUgLLMIrPTsJH1OjMoCNyCxnVuRhc9SKkG4POEg3D5wQERbPeN0Bc7i/FhKKXef95S6ltLAsmcZQwZlDzwucrEFFiJ/LTVCoS4KJLEqTlpYy9FrLirvG5aJQVzVxXeVlYyBV2L1WLWGb4DahQ9rHXOsYC1rjouJAdYOZL/1Mu%2BvGBDTYYb8BRsNHjbXECs3LDpo3ZmtZS3c39oaC4DbR37vbYrbOtIp3sibcbdkGdl35%2BPbe8vvtdQO03b32Oj7t3e2vc%2Bzt77c6FDBMXXOgH9yVfA4o9rrnlo9eigN8eismeuCsjlCqjujvesutjiAGYIxjsDsP4OkkkqUvAUkFBihh/lUpTnUleqQI%2Bv4C%2Bv4NkhRAkJIMkKgVwLLoqjsO/hUpwAZmAYBoshgXQVgebisPqpkM4JIEAA%3D)

## Links

- [source code](../../../../conceptrodon/varybivore/find.hpp)
- [unit test](../../../../tests/unit/varybivore/find.test.hpp)
