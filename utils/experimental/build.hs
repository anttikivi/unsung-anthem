#!/usr/bin/env stack
{- stack
  --resolver lts-8.23
  runghc
  --package shelly
  --package optparse-applicative -}

{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE ExtendedDefaultRules #-}
{-# OPTIONS_GHC -fno-warn-type-defaults #-}

import Options.Applicative
import Data.Semigroup ((<>))
import Shelly
import qualified Data.Text as T
default (T.Text)

main = shelly $ do
  echo "Hello, World!"
