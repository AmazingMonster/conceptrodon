<!-- Copyright 2024 Feng Mofan
SPDX-License-Identifier: Apache-2.0 -->

# `Varybivore::SolitaryIsSame`

<p style='text-align: right;'><a href="../../../facilities/metafunctions.md#varybivore-solitary-is-same">To Index</a></p>

## Description

`Varybivore::SolitaryIsSame` accepts two variables.
It returns true if they are the same and returns false otherwise.

<pre><code>   Left, Right
-> Left `same as` Right ?
   true : false</code></pre>

## Type Signature

```Haskell
SolitaryIsSame
 :: auto...
 -> auto
```

## Structure

```C++
template<auto, auto>
struct SolitaryIsSame
{
    static constexpr bool value
    {RESULT};
};

template<auto, auto>
constexpr bool SolitaryIsSame_v
{RESULT};
```

## Examples

```C++
static_assert(! SolitaryIsSame<1, 1.0>::value);
static_assert(SolitaryIsSame<1, 1>::value);
```

## Implementation

We will use partial template specialization to detect if the two arguments are identical.

If two arguments are identical, the compiler will select the partial specialization instead of the primary template.

```C++
template<auto, auto>
struct SolitaryIsSame
{ static constexpr bool value {false}; };

template<auto Variable>
struct SolitaryIsSame<Variable, Variable>
{ static constexpr bool value {true}; };
```

[*Run this snippet on Godbolt.*](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1DIApACYAQuYukl9ZATwDKjdAGFUtAK4sGISdKuADJ4DJgAcj4ARpjEEgAcpAAOqAqETgwe3r7%2B0ilpjgIhYZEsMXFciXaYDhlCBEzEBFk%2BfgG2mPaFDPWNBMUR0bEJtg1NLTntCmP9oYNlw5UAlLaoXsTI7BwA9ABU%2BweHR8cH2yYaAIJ7BwDUAJIsSfRsgkzdN4dnl9cnvydfF3OFwImEeBhBJgAzG4mF4iKQbrCiFDsEDpsQvA4bkJPIRGgBPO4KISsTBAkwAdgsN2mbzwyBuaAY00wqiSxBuUVQnhuADcxF5MDdKRYqGIlJSACJQ6lSmXky4gsFvMnQpGoG4ANUaeCYUXoKLRBAxWJxtDxxEJxNJULc2uIuv1mAR9sdBshqMuIppDUcDKZLLZHK5PP53iFIuNgrlkNlFOlsYVVz%2BvwBP12N2wqlYTyFnyB6ZTpyTtL9AH0mAolE0IGAwNjcWMrSS2LauAiuAA6DQokAgMOCpbyy6l%2BkVquxAgQM0W5s26Htm5cXv9gWYIexjgrWicACsvD8HC0pFQnDc1msNLWGwjZkhPFIBE0W5WAGsQLvJN34mYzABOP8uF3DR4niLgKQpaQdw4SReBYCQNA0UhD2PU8OF4BQQCQp8jy3Ug4FgGBEBANYCCSOFyEoNBHjoWJwlJThVHiAA2ABaZjJBuYBkAZKROzMXhMHwIgHXQPR%2BEEEQxHYKQZEERQVHUXDSF0dsAHdiCYJJOB4bc9wPZ8T04AB5OFyIIG5UCoG4mLYjiuJ4pcvzMG4IA8Gj6A5cx7yWXgcK0FYICQaiklosgKAgEKwpAYApDMPg6BBYhMIgKJDKiUICR03gMuYS1jKibQahwh9qJeAhjIYWh8UMrAoi8YAYVoWhMO4XgsBYQxgHEZT8GIYq8F5TBWuPVkajhLYH1CEFoOPc0ok0y0PCwQzjTweC2tIIbiC5JRJVBLrzSMZ8VioAxgAUTU8EwNTjKSRhsrk4RRHEWSJPkJQ1EM1T9C6lAL0sfQ8CiTDIBWVAkm6VrWOmdAoUlUxLGsMxUO20ThvgFZqlqZwIFcCY/HbYI5lKco9HydIBAJ8nUkphgBlJxYOi6OoZmp9tse6XomgZoYKlGPp2YFnmSb5iQsevTZxf0fTkMMtCbJY9jOO43jnNc3BCBIYU7y4XzHxOlYEEwJgsDiCA338SFOz/SFII0SQzEkZjEN3Zi/xlmC4JAe9O2YrhmPiP8wOYz8gNt5i5eUtCMKwg3cMCoigpIsyKIiqLPPothOEaFheQpVimEZAwjCXP9Oy7UbhJIPAxPbd6pNe6R3oUr7lN0eKNK07K9I4fco9QkzU4sqzFbszjkBL4Ay4r7tXPc0LPJ1yEzH1/y8OTjPYkoyLUA84ZJ66rhAKQmhaCSlK0uU3Kss2m/8sK4rHrKxgKqqmreswerGrEFrHo6w6Wxjx9QGkNEaglVDjRBI9aanRDLzUWviZaQC/IOg2g%2Bbau1MD7U6kYI6oAE58HOpda6t17qHgfA3F6Mlm6yFbkpY8HdfrHURlYQG81QYWxPJDDI0NYbw1YcjVGsR0acKxp0AauN8aeFaHoYmJQxbtgpt0IWyiMi8wWPzTmrNBYyJyBzCROMegzA0WTDmbM9GE2FrMBRmjpYKEljJXu/cUK8AVrZZWxcuoz0rhrauXldZr0NqQY2pthhcOgrBUg8FITlwdhSXcf4IKQkds7SQ7ZXFGXQrYOO69E7wGTqRcyO8t7ECzlsXO9kWAKF5AyXkx9OzgmGgQQS/ja7iVkI3GhT16HfR9qQLu2k2rOIMtHIeZE4SWWsqoKpNS6kNKadMeee9F6xGXpCIJhDN4rLCiUnZnl%2BzICSEkMs9S/xlkWQQMsMzm6JViJfdKmVLSPXvviAqRUHDPz3uVSq1Vapfwak1P%2Bm0AF4JQaQEBtQwGGTGsgCaMDBBwOUgggkyDVpoMepg1I2CDp4NCAQgKRCmAXSujdO6D1NpUOkhIWh8lPoMJ0P0qe/0kbsOBmI7hUNODbFhiythFgUZuLRrXDGYNmaSL8HjBg7hLFyOlaYpmaiqayqUbTboCqtGGK5hY7IVjtECG5jY%2BYZjrFC1pCLWxZiJbrClnrT2Lj5acBsrM2pfIFkqiWRATWIll56z8sE0JZtKC9yifBf8nZISQl3MBdJiFI0UkDgPNxnBY7YWCe%2BSQu4bbgQpIheIkhAKVF/JHaCkJRmD2yXk3uAkk1ZP9QnFY200jOEkEAA%3D%3D%3D)

## Links

- [Example](../../../code/facilities/metafunctions/varybivore/solitary_is_same/implementation.hpp)
- [Source code](../../../../conceptrodon/varybivore/is_same.hpp)
- [Unit test](../../../../tests/unit/metafunctions/varybivore/solitary_is_same.test.hpp)
