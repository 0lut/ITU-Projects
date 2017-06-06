module Week09 where

import Prelude hiding (Rational, either, elem, maybe)
import Data.Char (toUpper)

--
-- TYPE INFERENCE EXAMPLES
--

nand x y = not (x && y)

limitedLast s n = if (length s > n) then s !! (n - 1) else (last s)

capitalize s = toUpper (s !! 0) : drop 1 s

-- foo1 x y = if x then y else x + 1

foo2 f g x = (f x, g x)

f (x, y) = (x, ['a' .. y])

g (m, zs) = m + length zs

h = g . f

--
-- TYPE CLASS EXAMPLES
--

elem :: Eq a => a -> [a] -> Bool
elem _ []     = False
elem x (c:cs) = if x == c then True else elem x cs

data Rational = Fraction Integer Integer

instance Eq Rational where
  Fraction n1 d1 == Fraction n2 d2 = n1 * d2 == n2 * d1

instance Show Rational where
  show (Fraction n d) = show n ++ "/" ++ show d

instance Ord Rational where
  Fraction n1 d1 <= Fraction n2 d2 = n1 * d2 <= n2 * d1

qSort :: Ord a => [a] -> [a]
qSort []     = []
qSort (x:xs) = qSort smaller ++ [x] ++ qSort larger
  where
    smaller = [a | a <- xs, a <= x]
    larger  = [b | b <- xs, b >  x]

--
-- ALGEBRAIC TYPE EXAMPLES
--

data Expr = Lit Integer
          | Add Expr Expr
          | Mul Expr Expr

eval :: Expr -> Integer
eval e = case e of
   Lit n     -> n
   Add e1 e2 -> (eval e1) + (eval e2)
   Mul e1 e2 -> (eval e1) * (eval e2)

instance Show Expr where
  show e = case e of
      Lit n     -> show n
      Add e1 e2 -> show e1 ++ "+" ++ show e2
      Mul e1 e2 -> show e1 ++ "*" ++ show e2

data BinTree a = Nil | Node a (BinTree a) (BinTree a)
                 deriving Show

depth :: BinTree a -> Int
depth Nil            = 0
depth (Node _ t1 t2) = 1 + max (depth t1) (depth t2)

sumTree :: Num a => BinTree a -> a
sumTree Nil            = 0
sumTree (Node n t1 t2) = n + sumTree t1 + sumTree t2

--
-- Maybe AND Either TYPE EXAMPLES
--

errDiv :: Integer -> Integer -> Maybe Integer
errDiv m n
  | n == 0    = Nothing
  | otherwise = Just (m `div` n)

maxList :: Ord a => [a] -> Maybe a
maxList [] = Nothing
maxList xs = Just (foldl1 max xs)

mapMaybe :: (a -> b) -> Maybe a -> Maybe b
mapMaybe g Nothing  = Nothing
mapMaybe g (Just x) = Just (g x)

maybe :: b -> (a -> b) -> Maybe a -> b
maybe n f Nothing  = n
maybe n f (Just x) = f x

isFalse :: Either Integer [a] -> Bool
isFalse (Left  0)  = True
isFalse (Right []) = True
isFalse _          = False

either :: (a -> c) -> (b -> c) -> Either a b -> c
either f g (Left x)  = f x
either f g (Right y) = g y

join f g (Left x)  = Left (f x)
join f g (Right y) = Right (g y)
