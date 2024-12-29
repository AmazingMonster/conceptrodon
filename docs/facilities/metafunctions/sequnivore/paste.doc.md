<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Sequnivore::Paste`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#sequnivore-paste">To Index</a></p>

## Description

`Sequnivore::Paste` accepts a list of packed sequences.
It concatenates them together and uses the first sequence to hold the result.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Vs<sub><i>n</i></sub>...&gt;
-> Seq<sub><i>0</i></sub>&lt;Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

`Sequnivore::Paste` can also handle `std::integer_sequence`. The function `static_cast` integers to fit into the first sequence.

<pre><code>   Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>...&gt;, Seq<sub><i>1</i></sub>&lt;Type<sub>1</sub>, Vs<sub><i>1</i></sub>...&gt;, ..., Seq<sub><i>n</i></sub>&lt;Type<sub>n</sub>, Vs<sub><i>n</i></sub>...&gt;
-> Seq<sub><i>0</i></sub>&lt;Type<sub>0</sub>, Vs<sub><i>0</i></sub>..., Vs<sub><i>1</i></sub>..., ..., Vs<sub><i>n</i></sub>...></code></pre>

## Type Signature

```Haskell
Paste
 :: template<typename...>
```

## Structure

```C++
template<typename...>
using Paste = RESULT;
```

## Examples

Here, we paste `std::integer_sequence<int, 0>`,  `std::index_sequence<1, 2>` and `std::index_sequence<3>` together:

```C++
/**** SupposedResult ****/
using SupposedResult = std::integer_sequence<int, 0, 1, 2, 3>;

/**** Result ****/
using Result = Paste
<
    std::integer_sequence<int, 0>, 
    std::index_sequence<1, 2>,
    std::index_sequence<3>
>;

/**** Test ****/
static_assert(std::same_as<Result, SupposedResult>);
```

## Implementation

`Sequnivore::Paste` is implemented as a shortcut to the member `type` of [`Sequnivore::TypicalPaste`](./typical_paste.doc.md).

```C++
template<typename...Args>
using Paste = TypicalPaste<Args...>::type;
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGIAKwAzKSuADJ4DJgAcj4ARpjEIAAc/qQADqgKhE4MHt6%2BAcEZWY4C4ZExLPGJKbaY9qUMQgRMxAR5Pn5BdQ05za0E5dFxCcmpCi1tHQXdEwNDldVjAJS2qF7EyOwcAPQAVAeHR8cnezsmGgCC%2B4cA1AAimGmujMh4mAq3R%2BdXN6f/xx%2Blwu1yOtyECC8BAI9C%2BhyBBEwLDSBkRJkCbiYUNQADo8ejsCCJsQvA5wZDofR0VYriC/ntbgAVACeaTwoloyiYE0wcIOCKRKKYaIxBFZjFYmDxOIJRIIJLJLLZHK5PNuJgA7FYNfdqSC6TtbhZubzMUoQPqrojkajMOi3GLnsw2LcucgANaYdBCTAARy8rztgUJV2JpIITNZ7LEqpFbjdnu9foDDC2stpWpBt2zty8WSMt0dvPR91dTA9Xp9/sDeozusCNOBv0NACVMMgNlkAG6mk0W2lWwW2/UYrM561CuNYojSgm3ZAGBSfKspraXUhj7MT4cY6e4/HB%2BeL5fJwM2Te3PfSgBqrTwTFi9EuClI6quOcv2Jvd4f9AsL4vItnSlPEAHkCAQBIFBHENn3lcNI2VGNuTjFdA2BDFb2Ie9H0wZ9Z2DV80NTTArEwn9cP/AjsFfcDIOIBRqP1TN3xzPMImAQtxXVQJSyVaNORQu1WOze0Lw/Yi13tLCcKfRi8VfGTf1I%2BSZUI8SczoqDZxEnjsBAEAi1rYEdWMkFt2FYSMLcQCh0s%2B0gMlV8rwPbAj25E9qxI9dbJtezRXFYDnK/Vz3KXcFTxI89dMcl1GR8mLAslJlosuD8XJxJTcOfV8LwyrK/wAxKnUlaUtIYmC5QVCN%2BJVIT7UkvD7XixSKLk6iiMirYyLcRkbFuAqVI625ytU9MTMbD92ILIseL4qM6p5C8xN0iSuqajEWtuOZHGQAB9UQJmajDsAgQbn2WaVXx29kDpQ46CTOtqVMu1yN1WzSIO0/FdIJAyjIbZj60bOkATBwFQbuABJG0kUYFpGj5M5IfB8GgXMuy41ikCcUuYhgGg4MQWmzjY2LXjEIEsn7TxgnqP%2B8UzN%2BVGIeZu5sFUVgUV5b4UZZ5GB2BMxAgiBcvCwHi3DQEi0gIQnYPMEXU28CX7ShOhCGZca%2BfBLw0mKL02wULxaAjXmrhJ3X9cyQ2PhNiMS22gh0AMiJEWABI9qULy0wxN3Xw0V8uFfMxX0CWVAcF%2BlbiN%2B2kaBS3Y9NuayyW2lR10iYXZAN3MA94gvfW%2B1/duDQCVyzPnddhgsFUQufaDNxg9uMxy4vLPq9r%2BvV0b8OifTwlI6bUE7kZD4zfhOVhVujyEgICAO5ABRJT27l7STggiL1g30A3gllmpDhVloTh/F4PwOC0UhUE4GzLGsbb1k2YthZ4UgCE0I/VndAJJBxDQkhmDMAATmAVwfwACkhcA1BqaQJ8OCSF4CwCQGhA4XyvjfDgvAFAgEDh/S%2BR9SBwFgDARAIB1gEDSFCcglA0DIjoAkKIkpOCqCSAANgALRsMkLcYAyBkC3CkDiMwvAvSEBIHgF2wd%2BCCBEGIdgUgZCCEUCodQBDSC6GDgAd2IEwNInAeDH1PufT%2B19OCgShFQiMqAqC3FYZw7hvD%2BGCL/mYW4EAPD0PoMQdUr9li8HwVoVYEAkB0LZN4mhEAwkMMSMAKQocaCmygpQWIpjYgRFaMyAxvB0nMGIMyUCsRtDtnwW/OhbBBCgQYLQLJ6isCxC8MATEtBaA4O4LwLALBDDAHEHUvAxASl4B7G0q%2BmBVDtihNsN%2Bud4FX1oHgWIuj8keCwKY%2BUeBkHtNID2YgsQbaPC6UYeZRhP6rCoAYAm153haNAk6bJSjhAcgUdIGR8glBqFMZo/Q3SUDWGsPoBZODICrFQLLHIbSOFZxLKYe%2BlgzAYJ2dhLAQKICrDsIM5wEBXDTD8MHMIERhhVFGMHYo2QBA4r0KSxoCwRiJGDuihwfRJjtE8J0PQDLGj9DaDSoldLbDMopfS5lPKlhcDRU/LYEgjEcDPqQdBvBMF2PYVwnhfCBFCLcRAXA4ifGKzFQE05qxIJMCwIkVFpAf6SECDiYBgRYEaEkGYSQbDUH%2BDYcA/QnBEGkGQYELgOI2FcDYUkYBUC2H%2BEkOA21bC5WmMwdg3B79TlENISE8hljqEUCiagLxjDmEcFaCwLsGoOFMHcgWLgwCcT%2BtGfgIgSK9CvLkeIRRryVEfPUboUOOi9HZOlbK%2BVZiOAWMoVCW4NilUOJ4Qubpgiq01vcZ48JCRfGBDMP4pNBDgmhJzcusgWboneJQAYIwlauCB0SYiBiKS0kZPyfc3JmTCnFIcPc8p8Mqk1NMfUxpzTWn3M6d03pV98ADMZcM0xYyJmInuTM0x8zFmZJWdsK%2B6zNlvx2XspQBygMcWTecpglzrm3MYPcptTyJAvNkO2tRV8u3fJOTCqwlgAWxBRSCsFAgIVQt4kx6w8KFWIskR8eAaL6gYr8FimugqQg1xFcS9ImQyW5FZQUElSnqUEsWApjlTKBgyd0wILlgwtO0vZQK1TuL%2BXzFM7yqVawNiSrFZ6mVJj1GKvsSq8tnFK3Vv/u47V9bV36s3UEo1mATWjHNfA71vqq0Oo1P4YBMDAiOudZG2N7nOAJrwcm4hZCKFWMiYevNbBOCFscSwBQXYBFdl87aCYoi60SKkQ85tzyHk0c%2BSAYIPb9HtP7W5jB5iM3WNsaoSr1Xav1cshMRdu6YmrsCBuwJhC00lf3bQhbR6av6z2nV4Be0GsED2hNl5dAr04IgKk9Rj771bLuwUopJS305oqQQT9tSQOYAaU0sQ/6tmAaOShjp/TBkQfUVBjsMGtlwfUQhpZzJkNrOwuh3gmH9lIlwycrdfALkKCuZgG5dytnkfkZRzr7zaM6B6wx4wfyWMIfY9fTjDA2k7A7nxuFCKEhIpE8CnoEmXDScs3ofFFQzPqZKDkGTVKcjyb5YZpoFn8hWaV8ZhX5n9Oi6FTZiXdnnMKAlQowbmXhscDsZNmrtwDs4mOwF5ruq/EGq3eFyLZrpWxZACAnEgRAj%2BAgZG1BfuNTBrNwq7LthE2reWN/EAkh/A2ugRqVBSRJBgK4IAswMb4GBCGxHrBoWv4uZEeHodLuwvbKgjkePQA%3D)

## Links

- [Example](../../../code/facilities/metafunctions/roadrivore/paste/implementation.hpp)
- [Source code](../../../../conceptrodon/sequnivore/paste.hpp)
- [Unit test](../../../../tests/unit/metafunctions/sequnivore/paste.test.hpp)
