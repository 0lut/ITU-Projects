module Week10 (
  Nat,
  add,         -- Nat -> Nat -> Nat
  sub          -- Nat -> Nat -> Nat
) where

import Prelude hiding ((++))

(++) :: [a] -> [a] -> [a]
[]     ++ ys = ys
(x:xs) ++ ys = x : (xs ++ ys)

update :: [a] -> Int -> a -> [a]
update []     _ _ = error "index out of bounds"
update (_:xs) 0 y = y : xs
update (x:xs) n y = x : update xs (n - 1) y

data Nat = Zero | Succ Nat
           deriving Show

add :: Nat -> Nat -> Nat
add n        Zero = n
add Zero     n    = n
add (Succ m) n    = Succ (add m n)

sub :: Nat -> Nat -> Nat
sub n         Zero      = n
sub Zero      _         = error "subtract from zero"
sub (Succ n1) (Succ n2) = sub n1 n2
