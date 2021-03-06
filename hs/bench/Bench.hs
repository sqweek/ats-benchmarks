module Main where

import           Criterion.Main
import           Lib

main :: IO ()
main =
    defaultMain [ bgroup "collatzATS"
                      [ bench "2223" $ nf collatzATS 2223
                      , bench "10971" $ nf collatzATS 10971
                      , bench "106239" $ nf collatzATS 106239
                      ]
                , bgroup "collatzC"
                      [ bench "2223" $ nf collatzC 2223
                      , bench "10971" $ nf collatzC 10971
                      , bench "106239" $ nf collatzC 106239
                      ]
                ]
