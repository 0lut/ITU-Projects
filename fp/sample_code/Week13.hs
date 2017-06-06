module Week13 where

import Prelude hiding (Just, Maybe, Nothing)

-- FUNCTORS

fmapIO :: (a -> b) -> IO a -> IO b
fmapIO f p = do x <- p
                return (f x)

reverseLine = fmapIO reverse getLine

data Box a = Box a
             deriving Show

instance Functor Box where
  fmap f (Box x) = Box (f x)

data Maybe a = Nothing | Just a
               deriving Show

instance Functor Maybe where
  fmap f (Just x) = Just (f x)
  fmap f Nothing  = Nothing

-- APPLICATIVE FUNCTORS

instance Applicative Box where
  Box f <*> Box x = Box (f x)

  pure x = Box x

addBoxed :: Num a => Box a -> Box a -> Box a
addBoxed v1 v2 = ((+) <$> v1) <*> v2

instance Applicative Maybe where
  Just f  <*> v = fmap f v
  Nothing <*> _ = Nothing

  pure x = Just x

add :: (Num a, Applicative f) => f a -> f a -> f a
add v1 v2 = (+) <$> v1 <*> v2

add2 :: (Num a, Applicative f) => f a -> f a
add2 = add (pure 2)

-- MONADS

bindIO :: IO a -> (a -> IO b) -> IO b
bindIO p q = do x <- p
                q x

readUserFile :: IO String
readUserFile = bindIO getLine readFile

catUserFile :: IO ()
catUserFile = bindIO (bindIO getLine readFile) putStr
-- catUserFile = getLine >>= readFile >>= putStr

instance Monad Box where
  Box x >>= f = f x

  return x = Box x

twiceBoxed :: Num a => a -> Box a
twiceBoxed x = Box (x * 2)

instance Monad Maybe where
  Nothing >>= f = Nothing
  Just x  >>= f = f x

  return x = Just x

twice :: (Num a, Monad m) => a -> m a
twice x = return (x * 2)
