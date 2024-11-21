<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Prefix`

## Description

`Prefix` accepts an element and an index. It constantly evaluates to `true`.

<pre><code>Element, Index -> true</code></pre>

## Structure

```C++
template<typename, size_t>
concept Prefix = REQUIREMENT;
```

## Examples

This concept works as an enumerator of arguments when expanded alongside an index sequence.
In the following example, We will use `Prefix` to count out the first three arguments and return the fourth one.

```C++
template<typename>
struct Midst {};

template<size_t...I>
struct Midst<std::index_sequence<I...>>
{
    // We use `Prefix<I> auto...` to enumerate unwanted arguments.
    static constexpr auto idyl(Prefix<I> auto..., auto target, auto...)
    { return target; }
};

template<auto...Args>
constexpr auto TheFourth_v
= Midst<std::make_index_sequence<3>>::idyl(Args...);

static_assert(TheFourth_v<0, 1, 2, 3, 4> == 3);
static_assert(TheFourth_v<0, 1, 2, -3, 4> == -3);
```

## Implementation

```C++
template<typename, size_t>
concept Prefix = true;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGEgJykrgAyeAyYAHI%2BAEaYxBIapAAOqAqETgwe3r4ByanpAqHhUSyx8VyJdpgOGUIETMQEWT5%2BXIFVNQJ1DQRFkTFxCbb1jc05bcM9fSVlCQCUtqhexMjsHOYAzGHI3lgA1CYbbsgKBOhYVIfYJhoAgje3BJgsSQZPh24EAJ5JjKyYpD2aQAXpgAPoEK4PNAMVZJAh7ZTETA0VQHDYAET2BGIXkwhysdweAHoAFTkimUqnEkmUvYAFWwQnpQj2lJpdzJVO5FI59yJZi2sN2mHRbi8jlohC%2BUKJdyeLze%2BKO31%2BzDYstup1xDj2AFk8OhTgcAOxWE0YgkPB4K15Md5HEHgggAOjdAElNdqvLqDUbIY6ziAQGEsKowUoAI542HKtzut0uqEba5Es0PPaZvbE4l7ADqoq8SgOADYNEiUXhVB9PSm9kwJahEyYy9jUHtGD44vbCwwAO6GJ7oevEYBdwQKJN3LNA%2BqOZB7GGnTCqJLEeuNvaGr60CAV1E1q4boiJwENojYhrATAEM%2BNxNzDNZkxmvbIgjLBiX0c3gmmy1ppaGyEvyjzPHaDpuOeTZurco4KJqS5PKu67QQyCCYAAYksjQIGCABu1qYvqhqnB8pzoMGLBMAA1uCoYrhGmDRowqwfBsybYMG267nBwCTm6j7AdadynPaeDIGCTAKEojQQPSGHYcsBB4YRRyJHsXCAmYgIbICkhHocQFYhsQkgWJ85STJcQEPJik4SpBEfBpWl7DpewALR6XsBl1kZRmeaZBIcAstCcAArLwfgcFopCoJwbjWNYQI4asByCjwpAEJoIULDRIDhRoLpmGY/gABwaP44VlSWGySGYJqSCW%2BicJIvAsAkiTRbF8UcLwCggIk2UxSFpBwLAMCICASwEEkErkJQaAvHQcQRP8nCqDVHklpIezAMgC5SMVvCYPgRDEIaej8IIIhiOwUgyIIigqOoI2kLoWl9sQTBJJwPChRFUU5XFnAAPISnNCKoFQeybSW227fth2SMVewQB4y30OumxcHMvDDVoCwQEgS1JCtZAUBApPkyAwBSDpNC0E8xADRA0TA9EYQNF8f28JzzDEF8oPRNo1TDZlS1sIIoMMLQPNvVg0ReMAUG0LQA3cLwWDUUY4gK3gyI1PhmAa7FK7VBKayZWETxhW9UrRN9gseFgwM4ngHWa6QxvENEqSYBizyGMAUpGDlCxUAY/EAGp4Jgfag2qvOPcIojiA913yEoajAx9%2BjBygSWWPoeDRANkALKg8IZBrHkUUZpiWNYZg9T7F1YOXEALB0jjOBArhjK0QQMOg0wDOUeRpL3mSeC0egpFPGRj6UgxaT3tQjE0s/jLYmD2NP3SNMvsxr5vg96GJR9hP0K/lN3qX3QDHCRaQ3W8L1sNbTte0HZpKNmGjXAhASDpQ2LjfG4cFgYSYFgeIXdSD5UkBsF0/gNiNQ0PVJqGgNDhRLIEO2bVSAdTAS6EsXASxlXKuQ8KkguDhVQc1N%2BIM%2Bq2EGllcOY1JrE2mhDealNqZYzWmwTgDQWD4RNB5Jgi4DBGE0v4F0XAXRmzOiQS6WlM63XTtITOz0c5vV0DpL6P1eZPxfkw3q4NZoSj2NDEcYiJFSJ2MHORCilFowxmTLGoCzB43YSNImJNUCYziAtKmQTPGDFEeIjyTijBtAqHwOgzNWbszevzbmyd0mC2FqLBwydJaMAIDLOWwNFbK1VurZO2tg561ivgQ2jhjamxOqoC2Txk42z3sDB2TsvguzWLFd2ntMo%2Bz9koQOOsQ5hFAP4vgUcFCx3jonRgycNFp3uto2QujXqxQMfnMOjcrDFwdp3Su1cBC13rpiQ5zdW5xHbibeA3c95iwyC4Ee58tIhGvjMVek8Cgz2yEPBeALj5/PXl0M%2B28h4QoYIfXoPzx4XyhUC5FUxEW3wkPfZYqwsUtWfkDN6H8okOOkc4toriNCAJUdjDKviCa5VINA2BlAn6EOIfIjBJp6EmhNHVMwTVaGv2Br1fqbCGVEy4UgGakNQkCNWutDgojv4sAUPhBc%2BEKVKlOCdGlaiU6aI2SnbZucQB6SMb9TWpjCU9TBrwqGMNlW7VVeqvYmr5HaoROjcJ5NQGmQgbM7h8qKaLR9VjEA6qkhJAIm0MEnqpLEBYDtRJTM4gpI5lzQWmTM1CxFmLfJQSpZFNlvLOpmAlYqzEJUr21TdYDK1gbV5TTgbm2QJbDpggun21Lr0/pbsLrDN4KM/2EyanTI4ZHJgMc44JyTl7NZd0JCbKetnHZOgzX7OMEXGwJynlxXOQwDWxIKKFybpYFu7826GkeRXXe%2B83n9w%2BdCvQ3zihIq0iC6enz/nTzBRPWF8Lv0Ac3n%2BtFoxn2n3RW%2BzFuNFg4sfvisxIrOB2JVWqjVWqezGggEA86oDwF%2BMJlAzAMDBjwIIe1EApUXQbA2OFQqtDsG0ZNBQ4VRLOBiqGpAhBIBJDyN5RoNoGCuAbBLOFE0ZgaH4o2Da9%2BHHCOMrtmYWTzCA1Ee9mmt5kggA%3D)

## Links

- [source code](../../../conceptrodon/prefix.hpp)
