module Week06 where

import Prelude hiding (cycle, sqrt)
import Week05 hiding (generateMatch)

sumF :: (Integer -> Integer) -> Integer -> Integer -> Integer
sumF f a b
  | a > b     = 0
  | otherwise = f a + sumF f (a + 1) b

fac :: Integer -> Integer
fac n
  | n <  0    = error "negative parameter"
  | n == 0    = 1
  | otherwise = n * fac (n - 1)

sumFac :: Integer -> Integer -> Integer
sumFac a b = sumF fac a b

type Strategy = [Move] -> Move

generateMatch :: Strategy -> Strategy -> Integer -> Match
generateMatch _  _  0 = ([], [])
generateMatch sA sB n = step (generateMatch sA sB (n - 1))
  where
    step :: Match -> Match
    step (movesA, movesB) = (sA movesB : movesA, sB movesA : movesB)

iSort :: [Integer] -> [Integer]
iSort []     = []
iSort (x:xs) = ins x (iSort xs)
  where
    ins :: Integer -> [Integer] -> [Integer]
    ins n []          = [n]
    ins n xs@(x':xs')
      | n <= x'       = n : xs
      | otherwise     = x' : ins n xs'

iSort' :: (a -> a -> Bool) -> [a] -> [a]
iSort' p []     = []
iSort' p (x:xs) = ins' p x (iSort' p xs)
  where
    ins' :: (a -> a -> Bool) -> a -> [a] -> [a]
    ins' p n []          = [n]
    ins' p n xs@(x':xs')
      | p n x'           = n : xs
      | otherwise        = x' : ins' p n xs'

sumSqr :: Integer -> Integer -> Integer
sumSqr a b = sumF (\x -> x * x) a b

fixedPoint :: (Float -> Float) -> Float -> Float
fixedPoint f x0 = fpIter x0
  where
    fpIter :: Float -> Float
    fpIter x
      | isCloseEnough x x' = x'
      | otherwise          = fpIter x'
      where x' = f x

    isCloseEnough :: Float -> Float -> Bool
    isCloseEnough x x' = (abs (x' - x) / x) < 0.001

sqrt :: Float -> Float
sqrt x = fixedPoint (\y -> (y + x / y) / 2.0) 1.0
