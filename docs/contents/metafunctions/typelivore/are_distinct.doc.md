<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Typelivore::AreDistinct`

## Description

`Typelivore::AreDistinct` checks if its arguments are distinct.

<pre><code>Elements... -> AreDistinct ? true : false</code></pre>

## Type Signature

```Haskell
AreDistinct :: typename... -> auto
```

## Structure

```C++
template<typename...>
struct AreDistinct
{
    static constexpr bool value 
    {RESULT};
};
```

## Examples

We will check if `int, int*, int**, void` are distinct. Then, we will append `int*` and check again.

```C++
static_assert(AreDistinct<int, int*, int**, void>::value);
static_assert(! AreDistinct<int, int*, int**, void, int*>::value);
```

## Implementation

We will use a technique called SFINAE, which stands for 'substitution failure is not an error.'
It roughly means we are going to create an 'if statement' for template instantiation, where the condition will be the legitimacy of an action.
In this case, the action we will be using is accessing a function in an overload set.
The compiler will select different partial template specializations depending on if it can find the requested function.

We will use `Label` to create an overload set for `lark`.
We add a second parameter in the template head to distinguish identical elements.
It is essential since inheriting the same class multiple times is an error.
Unfortunately, using this error for SFINAE is impossible based on my testing.

```C++
template<typename Element, size_t I>
struct Label
{ static constexpr void lark(Element); };
```

Here's the entire implementation:

```C++
template<typename...Elements>
struct AreDistinct
{
    template<typename>
    struct Detail {};

    template<size_t...I>
    struct Detail<std::index_sequence<I...>>
    // We create an overload set through inheritance.
    // Since arguments are not allowed to have the type `void`,
    // we declare the parameter using `Element*`.
    : public Label<Elements*, I>...
    {
        // We bring every `lark` from its base class to the current scope.
        using Label<Elements*, I>::lark...;

        // We will do SFINAE on the second parameter.
        // The default argument `void` ensures
        // the compiler checks the specialization before the primary template.
        template<typename, typename=void>
        struct Hidden
        { static constexpr bool value {false}; };

        // We ask the compiler to find a `lark` that
        // declares a parameter of type `Element`.
        // If the compiler finds the `lark,`
        // this specialization will be used.
        // Otherwise, the primary template will be used.
        // This function checks if an element
        // is in the previously provided elements.
        template<typename Element>
        struct Hidden<Element, decltype(lark(std::declval<Element*>()))>
        { static constexpr bool value {true}; };

        // We check every element in the previously provided elements.
        static constexpr bool value
        {(...&&Hidden<Elements>::value)};
    };

    static constexpr bool value
    {Detail<std::index_sequence_for<Elements...>>::value};
};
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAMykrgAyeAyYAHI%2BAEaYxCCSAJykAA6oCoRODB7evnppGY4CoeFRLLHxABy2mPZFDEIETMQEOT5%2BgXaYDlmNzQQlkTFxCckKTS1teVy2EwNhQ%2BUjlQCUtqhexMjsHOb%2BYcjeWADUJv5uXo60hACeZ9gmGgCCewdHmKfnyOPoWFT3jxezwImBYKQMILObgINxSjFYH2w9DYglIxwyAC9MAB9AjHACSAOe42IXgcx2CTFitEBJgA7BZ0U1HMhjmgGONMKoUsRjgA3VB4dDHAzEADWECRoMYBBWZ0Z9IAIvLacDQeCmJDzjC4cw2AA6Q1SlEEBREp4ksl4p7ETCKvDjA4EWkMwHHd3HEFgiGYKE6%2BFsc0epmk8mKzBNOinV105X%2BKzPN0er0arVuTE4giG/WE/wPZ7By1hiNMOhQn4gEBhLCqbFKACOXkY2yh%2BOzALzSfdAHpu8cAOofZC2zUfQzHVB8uK0VBMYVKPEEBDEDbABDHMIIOKEQzbfVd46945CA5j4jAHwyhTHZofBioPFiGcAd0wwqIxwQTCnnq3nthHwmAAbBoApCsBGikAeR6vscWCHLev4fCkzQIiCvJeBkRinCBxoygAVBB%2B4Fh6IDHCkXjRNcrKUtSUJ4YICj4WiubYO2JHuvSCZPMGwZHoOxzRMQYTAMcmBTsQNw4RoopihBxxUCuLAbqaglMEobIGAo14fkuQ6bLagjomgcLETxvHuphIkUlStT0ciV7MQS9yVrJ7bxqq5kWfxHzPnQtBwagx4AGL4hETzYBODBIei3QCMKKHEGhcRmRZPZ9gAKn%2BfxMF4tCPuel5GRBYHoPJjAKJsmBmhxvFHnpbKoGCdBxGyW7IGKOl/gocLIHgYh4BimpZIJmD8LaMU8ngLDNFJKY%2BqlaXzaOfoAXqmBov661nIqpVBmlRZ4gAEkKWAMAewZcUyw2suynLcry0SoJ4/JiE20YWFQYhKEq8rRnG3EXR6Pk3goYoxWgzX0LyH40AwwpMNJsnyUumpA%2BlcHdKK1U3uRqFsOhE5UP%2BcLSQxzogYt3l9vixMNZDKQtbycPoF1gEgbJUEgejh59kuDror1/XXEN9THH5tABbExyYW%2BVN1X2ADyenEH5SibX%2BU0zZJnrqj64v%2BaNMtKOg8t8ZlCAC1QXgMD0Ahtd0nUbsT461NKgg80eAthJNtp8k4mG0FJPKTkKb5iQ5jFm8mesrdqa0Isc5P7RZh3HCdvyMPZ7sEGi8H5QBECyRAFYgPnfJiNnJqEXmEArPXKe8Vd4w3Y1HIgg9gnPQFFfeIBDIEKSvqxn9v0eYmtXmwOQ7teD4lxFJbsmhu0UNTy4kBwoQfkSu/tYMKS9XtH7otyybf3TyXcvb3TY81xEDtmYQHmEBGdnVXV4uSAN%2BYHKI/j15f6KoJ6ANPngW6AgL6PW7q9PuB4uLhkjDSc4pdqxcjrJgRszYcTjQ/lHQ0HZsCVh/mPQG/9AbPG7PhahNDaHdkBFQ6hGVsBCAyjQ%2BhlDaFcPwhwoELwzD7Ftu8T4bh2TbBSKac0gIwHIGxOpJQLQIA2jtA6RwttnTnDCLnFeBAnJaOoWiPaeZiFvV/sAi0zJwFyO0nEAgEAwBgGOMo%2B0jp1FQi0WifRnjBAGP5IKdA3jdFfx/nKeMHA1i0E4AAVl4H4DgWhSCoE4G4aw1h0QbC2IBARPBSAEE0OEtYYoQBAX8PqSolQ6QaCAlEjQGh/BmEqGYRIyRIkcEkLwFgEhamkDiQkpJHBeAKBAJBPJ8TwmkDgLAGAiAQAbAIBRXOFAIAMyZhEBEnBVCVCAgAWiApIY4wBkCsikPqMwvA3yEBIEKPQ/BBAiDEOwKQMhBCKBUOoMZpBdAzGfElFInAeAROibE/JiTOCK0uAsomxxNk7L2Qco5xwTlmGOBADwUNWp7C4CsXgoytBrAgEgFZ0NyCUCJSMYAUgzB8DoOhIZEBogguiGEWa/zeBMuYJJRW0RtDdFGTkyGJpFYMCDiCrA0QvDADcE%2BIZ3BeBYBmkYcQHz8C2h6FOGVCSuTdEuDsHJWjagguuEJWaHgsAgsHtNVlpAJJPSUOGBVwBrhGHyWsKgBhgAKAAGp4EwM%2BRWuorW3OEKIcQTyg2vLUCCr5%2BhDDGFSZYfQeBohDMgGsVAEisgyu2T8HaphLDWDMH0iSwksAprrjUOoWQXDwymH4GYIQFhlAqPkdImQBC1pbYULIgwm0jBmF0O2DQ5gdv7W7QdfQWg9uGPEftw7PDtD0C3Sdjbp0SDWAoDJ2w136CBT0kF/ToVbN2fsw5xzJCnJRbgS5vJMXYtyS6tYW45wjHLUUyQpTEj%2BDpJIDQkgzCSBAhoKJQEWmcHaaQTp/guD6iAlwIClREiVDg1EyQXAomfqAnuj5/TBnDPvWM/F0yCWzIhZcElyymqM2hmstgnBmgsD5HSbZiMELYS4IkfU0HNX4CICWm5sh7mhukOGpQkaPm6CpT8pgfzZWAo4DErDfSwWkbxKgF2xAGNMZYwYNjHGuMorRVRjFAizB3txeM4jZKyBLKsyAejjHtmsYpYkLgkEaD5TiHShlHz2UstlaQXznLuW8qtQKmUQqRXKswOKyV0qrXytjUqhJKreV4HVSCrVyAdVWv1a0hJRqkqSVNTsBJFrOn%2BZtekO0oJEsiRdXwd1XqfV%2BoDf5oNgnHnCdkBG95CSJMxudXmqwCajVlrTRmyBnBs0EDKv4RUQ2C1FriCW6q8B11jvqNW9w87phBHhlOpYM7UitvqCO47XbigrsO4ujbvQ525DrRW1LAgJ3zFKKu2d/QztLre4sZtWL1ibC3QD1pCnem8APfZrTmlY2Ir0/qDQl6eMkFONkszD7SBPqwPEctrTwOQY47%2Buk6G6R0n8H%2BgDqHFMQ84LhkZ9XJkzLmQs8jVmaM7Ho3ClgCg%2BSsj5Ox/UPpxjnOR3xmY7WQ2deefIUTvWdABFIFJmTAKd3yeBdh5T8zLhQs5/s7nvP%2BQC6F3iVFlGmao/8P4dHBGJmErN8Smz9uRi85SCkbE/PEjYmN3IjTezqUeeIF5xlzLJJWsCzcLlPKHChaaoK4VNxRXRYlVKyWMqckJcVSVuVeBVWOHSx8zL2X/O5cNUmwrNxivmuEuVnJlW7U1cVXVm3bqmAeu9b6/1jBA0CclxILrLzZdRoVzpuN%2BaRtJrG4kibHJODdgrAtywhaIfFrDpPgdm2ICuDOw29712ZgFDbdkHbj2D/1AO/9p7477sLtHZWl7cxz99tmF94/i6H9Xf%2B%2Buzdjy5Ng/3ZwG8X3PXHnPnI3UccYJHa9C3LFHFDHLHF9OTfHEAJpfUS3KJGpVDWpS3OkeDanUFAZWwPDczeuUgIpfwICTjLgJpcnZpICOkLgSpGYVpfwdXJTAg4guTM5PAnDfDPFNYCSDIZwSQIAA%3D%3D%3D)

## Links

- [source code](../../../../conceptrodon/descend/typelivore/are_distinct.hpp)
- [unit test](../../../../tests/unit/typelivore/are_distinct.test.hpp)
