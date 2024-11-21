<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::ReconformedLeftInterview`

## Description

`Typelivore::ReconformedLeftInterview` accepts a list of elements.
Its first layer accepts another list of elements and returns a function.
When invoked by predicates, the function first binds the second list to the front of every predicate;
then, it returns the index of the first element that satisfies all newly formed predicates, or `-1` if it cannot find the element.

This function internally is the flattened version of `Typelivore::LeftInterview`.

<pre><code>   Arguments...
-> LeftSides
-> Predicates...
-> Found ?
   index : -1</code></pre>

## Type Signature

```Haskell
ReconformedLeftInterview ::   typename...
                -> typename...
                -> template<typename...> class...
                -> auto
```

## Structure

```C++
template<typename...>
struct ReconformedLeftInterview
{
    template<typename...>
    alias Mold
    {
        template<template<typename...> class...>
        alias Road = RESULT;

        template<template<typename...> class...>
        static constexpr std::make_signed_t<size_t>
        Road_v {RESULT};
    };  
};
```

## Examples

We will find the indices of `int**` and `void` in list `int, int*, int**, int**`.

```C++
template<typename...Args>
using Metafunction = ReconformedLeftInterview<int, int*, int**, int**>
::Mold<Args...>;

static_assert
(Metafunction<int**>::Road<std::is_same>::value == 2);
static_assert
(Metafunction<void>::Road<std::is_same>::value == -1);
```

## Implementation

`Typelivore::ReconformedLeftInterview` is implemented upon `Typella::UnconformedLeftInterview`.
The latter is a flattened version of `Typelivore::LeftInterview`.

Here's a simplified version of it:

```C++
template<
    template<typename...> class,
    typename,
    typename...
>
struct UnconformedLeftInterview
{ static constexpr auto value {-1}; };

template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First
>
struct UnconformedLeftInterview<Predicate, Interviewer, First>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else
            { return -1; }
        }()
    };
};


template<
    template<typename...> class Predicate,
    typename Interviewer,
    typename First, typename Second, typename...Others
>
struct UnconformedLeftInterview<
    Predicate,
    Interviewer,
    First, Second, Others...
>
{
    static constexpr auto value 
    {
        []() -> std::make_signed_t<size_t>
        {
            if constexpr 
            (Predicate<Interviewer, First>::value)
            { return 0; }

            else if constexpr 
            (Predicate<Interviewer, Second>::value)
            { return 1; }

            else if constexpr
            (
                UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value != -1
            )
            { 
                return 2 + UnconformedLeftInterview<
                    Predicate, 
                    Interviewer, 
                    Others...
                >::value; 
            }

            else
            { return -1; }
        }()
    };
};

template<typename...Elements>
struct ReconformedLeftInterview
{
    template<typename Interviewer>
    struct ProtoMold 
    {
        template<template<typename...> class Operation>
        using Road = UnconformedLeftInterview
        <Operation, Interviewer, Elements...>;

        template<template<typename...> class Operation>
        static constexpr auto Road_v 
        {
            UnconformedLeftInterview
            <Operation, Interviewer, Elements...>::value
        };
    };

    template<typename...Agreements>
    using Mold = ProtoMold<Agreements...>;
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCAAnAmkAA6oCoRODB7evnppGY4CoeFRLLHxXLaY9kUMQgRMxAQ5Pn6BdpgOWQ1NBCWRMXGJyQqNza15VWN9A2UVEgCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACex9gmGgCC27v7mEcnyGPoWFQ3d48PBEwLBSBkBxzcfwOUIOgOBoMw4IIlxSjFYmAAdJibgc9kwFApSJDoUiUcw2ISHtCYcjUWxMei/r8HmNiF4HAc5Aw0Ax%2BMQ2OhgpgqAQAJKCOIANzwmAA7oyAOwWA4zRzIHECMaYVQpYgHJhnVAHCViLyvEyKgC0XHNABFjkrbfbGQCgSCmGCTkSobC3R63CTaRisf5sDiDPiDspiJh8KJART7lSA2TXmLAcQpbK4gmkzSUwcAGJ4YhjRkhv4stkEDlcgS8/mC4VpyXSuUnKMxvBxzCkA7NjOt7OF4ul8sPc1WSnQlVd9UMTXa3X6ohGk1mqdQideqlHACsVl3NogiwOFuxnxAIBYTAA1pgAPoZYDhdD3gjgjIALwf77HiZ3m6KtuAFQngVBzguOpHBuIFQhAHaxu6CInP2mYykORYlr%2B2CXsa3iYIswEgROBzRgQawMAcGj2kc8p2uOMGwTUShEQBJFkRRp7Wv4Dp0axtFHoRMGOjxCp2qJDH/PcPrwuC24yUhiJ5mi9LYriEYIV2SE5sSylsH24oDlmZDyXpryYWMvbJmiBxCF0AjoFZZn0gA8gQCBxAoZa3MyBCsuynLcvWMaNqKhloXJMGad2OlQqhg4mTBFkEL2dnco5BxuR5JaqeOf5bjBM5qtykFLgaq74dB/6AZO1U7iY%2B4NYJp7ngQ6CXted6Pngz4xm%2BH54N%2B/V/rBBV1bBYEQYCi5VbBVLwdGiF%2BvFxm9slNy4WuQnjcRiqkZg5HEJR1E8QJzo7QBzGvJNJXTVB/HzdFikoeFCWpfZDDoBtIB4aa21zdC7EHZx3G8fRUkA1CV0HDdGp3cQD3QhAiMAYFdYkA2QphemEWeoxkNUk98azQTIErehZAk6TO5ZZ5uUXXN32/a8YBgMcNpcSjBz/ZDJFc1SHFHQcZhHJYNZBRjIVY%2BTkUMwTRM9lT1PQuTQ78yBtM5Vi%2BMA0za40VzjqSQTV2G3tguUVaBt8TrAnHtuIm1Y750KX61l0pi2D0GwgheX%2BlbsgASh9wUCtLr2ygqtVJq6sknO7qYRxTTJ1QH1ZRqgRAALKeOgStjbBrvIf6sfPf6znBqG6kKJlKLEO6WQp7BXgZEYByB6gTB5%2Bz4vo3yUtNkn/Hgi5dcNwIvaq5TXtAowBAKKp5YSRDIFF4ipduxXDIhmGeI16PcTjwwTcgUVU1alBy6Gh3Xf3hKStUgXkNozykth4POOtobJwH/XdST0nIcM8fbz0XjhH6%2BtbbO2EnxZe8kN7FwTvSe4wBoyz19ifKELcwjAAODnWg3d/AcwztnXO4IUFoJAQvSuTpxywKdg8AA9AAKlYWw9hjC/gsNYQAFWwEIHhbDOFMPYaI5hwipJPC5C8N4pxzhXBTn8Ne8ct73GIMAP2Pl7jYLblnA6TAqBeC5HUN4HNg4S37u/bGLZI4nDCClGGghmG9nsawlxTjmEp0vPgr6Jw1EaLAbQqSRV7x7ziO%2BB4EA9GNEMcYxudiPHfRvr4twF4QB4AUI%2BNEetKrsx7mYQiy8QlhOaH8KJ%2BjYndAEOCCUqA8C%2BPAckj8bVLwZKyWwHJppTE9ytIUiwHBli0E4LuXgfhuC8FQJwCElhrDKlWOsM0Zh/A8FIAQTQAzlg3hALueU6J/AAA4ABs8p/DHI0Ack5CRAhDI4JIXgLAJAaA0KQMZWhSCTI4LwBQIBnlrI4FoZYcBYAwEQCAVYBAUhnHIJQNAwI6BxAiGiTgqgjkWkOZIA4wBkBqikOiMwvBOxEGIPUvQ/BBAiDEOwKQMhBCKBUOof5Og9AynrikTgPBBnDNGes95nAXJnEhdWVA4EUWHLRRirFOLJB4oOBADwcL6C6m2FwRYvA/kAtIBAJAsKUjwrIBQCAOq9UgGAFIMwfA6Dpm%2BRAaIPLohhCaJcdlvB7XMGIJcFy0RtBdD%2BSs2FICXIMFoE6xlpAsDRC8MANwYhaDfPGWGoEhhgDiFDfgaM3QJSYDjW8rUXQzibBWfYmoPKLjRHru6jwWAeV%2BTwA8%2BNmbiDRHSJgG0iajAXCMOs5YVADAaIAGqtgPmMlZZLhCiHENS0ddK1A8t0FUAwnbTAzMsPoPA0RvmQGWKgFIdQ40Wk%2BOzJdVhLBmDeagBtxKsAbuPNUWoWQXCfUmH4KoIQwiDHKMMKoBRMgCCffkdIP6GBzCGJUW9PqejjBaJ4NoehOhVPqJB4DH7QMzAmNBqYthENvvmJ%2B5YCh5kbCWPoLlLyeUfIOKK8VmLsUHFxSLCAuBCAkFFss1Vqyu3LA8l3YYN6tmSH8OiK58pJAaEkGYSQhynm7kOckG5dzSAPOWeiQ5XBDn7ISPs1Tu5JBcF3Fcw5pHQ0fK%2BT89jjLAUgq1WCgVUKDVGsVYitgnAmgsAlPKC0TBd5ty4AkdEXB0Q5vwESklVRR0UondIKdSgZ2ht0OallTA2XjM5RwEZhmz18ps0K8CLm3Mea87gnzfmAuyvlbqxVLGClqq7Zq7VqAFXZjs/V8rwxcvudxEYHzXBnk0FoFaygtrQ2usdc60gw33Weu9Q4Ub/q56BuDTy8Nkbo20FjaNrA1522bDeWm8Dmbs0EtUHmwEo2i03LeaW8tlxK3bbVcSutKyG1NqUK2zbyacE1Z7Uwftg7SSjbC%2BOqlkXZDToZW8uL%2Bgk0oGsNYVd674Bbp3VkPdB6iFHusKeiZF76lZoR2B%2BDD73DoefUET6SGFhfoA3UP9lPChZHJ5%2B/HdRehodyCTuDzOsOlBA7ByDNPMOzGwzzlVKw1iEZFzctLryJmcD1HyPLnmOuFd8/5jQsrGNEpYyq6r5nOOYG4/EG9cn7kBF86J%2BUen5QnLExJnT6WZefNsKZ9VAzNWWaQOCwV0LDXNb1Y5zYLn0UHBYAoCUaoJRFfhGMAlQWSAhZpWOylEhge0ui2DplgQEtJY5cR1L3KjOZYhWcA4wq5csCDyHsPRpI9ITGKV33FXtj%2BDYy7wFdWGv6phQ34YYeUgpDvj5%2B8UeCChL5Oii1fXPIDbtQ691o3xseq9T6mb9WA1BpDTtzAEao0xrjSsjbSaU07eLHt3Hobc3IHzad8U53eCXcdTd6t93RtPeba9w/H3zN8F7QoAdsoh3/ayDhZA4J6g6zoBCQ6Low4rqlrXqI67qcCMIXjo4npnrY5Xp44c73oQCuD86vrc7Ib/p06/rE5EGAYM4oY1DgYCAs5QZs6wZUHwa0EUG859D86ob9BC6EEi74Zi5UopZS5kay6B4YqV7h416Ah14Max5KpLLa5mYAp64G6UApbyYPJmC%2Bb%2BD%2BC7i7iibdbnL%2BDyhqb268qO7fK/IcakB8ZmDKZcD%2BBmCHL2EJAqYOEaDyi57%2BD54ZaO6t4pb4omHGYKEbKkANoZDOCSBAA%3D%3D)

## Links

- [source code](../../../../conceptrodon/typelivore/reconformed_left_interview.hpp)
- [unit test](../../../../tests/unit/metafunctions/typelivore/reconformed_left_interview.test.hpp)
