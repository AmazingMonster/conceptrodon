-- Copyright 2024 Feng Mofan
-- SPDX-License-Identifier: Apache-2.0

module FunctionalNature where

-- Typename has no value in Haskell.
-- Its value lies in C++.
-- In C++, Typename is typename
data Typename

-- In C++, Auto is auto
data Auto

-- C++ parameter pack is a list-like structure.
-- In C++, Ellipsis is ...
data Ellipsis a = Empty | Cons a (Ellipsis a)

-- In C++, Template is template<*...> or template<* class...>
-- In the following demonstration, we will omit 'class' for simplicity.
data Template a

-- C++ template instantiation
-- instantiation :: template<a...> -> a... -> typename
instantiation :: Template a -> a -> Typename
instantiation = undefined

-- A metafunction in C++ is also a template.
-- refocus :: (a...->b) -> template<a...>
refocus :: (Ellipsis a -> b) -> Template (Ellipsis a)
refocus = undefined

-- An imaginary value of the type 'C++ parameter pack'(Ellipsis) is produced during every metafunction invocation.
-- invokeWith :: a -> a...
invokeWith :: a -> Ellipsis a
invokeWith = undefined

-- Representation of Fun in Haskell
-- fun :: typename... -> template<typename...>... -> auto... -> template<auto...>...
fun :: Ellipsis Typename -> Ellipsis (Template (Ellipsis Typename)) -> Ellipsis Auto -> Ellipsis (Template (Ellipsis Auto))
fun = undefined

-- Let's typecheck!
-- n :: typename... 
n :: Ellipsis Typename
n = undefined

-- ie :: template<typename...>... 
ie :: Ellipsis (Template (Ellipsis Typename))
ie = undefined

-- r :: auto... 
r :: Ellipsis Auto
r = undefined

-- g :: template<typename...>... -> auto... -> template<auto...>...
g :: Ellipsis (Template (Ellipsis Typename)) -> Ellipsis Auto -> Ellipsis (Template (Ellipsis Auto))
g = fun n

-- h :: auto... -> template<auto...>... 
h :: Ellipsis Auto -> Ellipsis (Template (Ellipsis Auto))
h = fun n ie

-- i :: template<auto...>... 
i :: Ellipsis (Template (Ellipsis Auto))
i = fun n ie r

-- j :: template<typename...>... -> auto... -> template<auto...>...
-- First, in C++, the set of metafunctions is contained by the set of templates.
---- We redirect our focus to the template nature of 'h'; 
-- Second, we instantiate 'h' with 'r,' which turns 'h' into a C++ class;
-- Third, we wrap 'h' into an imaginary parameter pack;
-- Forth, we instantiate 'fun' with the pack;
j :: Ellipsis (Template (Ellipsis Typename)) -> Ellipsis Auto -> Ellipsis (Template (Ellipsis Auto))
j = fun -- Forth
    (
        invokeWith -- Third
        (
            instantiation -- Second
            (
                refocus h -- First
            ) r
        )
    )





