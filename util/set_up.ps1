#!/usr/bin/env pwsh

# ---------------------------------------------------------------------------- #
#                         Obliging Ode & Unsung Anthem
# ---------------------------------------------------------------------------- #
#
# This source file is part of the Obliging Ode and Unsung Anthem projects.
#
# Copyright (c) 2020 Antti Kivi
# All rights reserved
#
# ---------------------------------------------------------------------------- #

New-Variable ComposerVersion "0.7.0" -Option Constant
New-Variable ComposerVersionTag "v$ComposerVersion" -Option Constant
New-Variable ComposerName "Couplet Composer" -Option Constant
New-Variable OdeName "Obliging Ode" -Option Constant
New-Variable AnthemName "Unsung Anthem" -Option Constant

Write-Output "Running the set-up PowerShell wrapper for $ComposerName $ComposerVersion, the build script of $OdeName and $AnthemName"

New-Variable GithubUrl "https://github.com" -Option Constant
New-Variable ComposerRepoOwner "anttikivi" -Option Constant
New-Variable ComposerRepoName "couplet-composer" -Option Constant
New-Variable ComposerRepoUrl "$GithubUrl/$ComposerRepoOwner/$ComposerRepoName.git" -Option Constant

New-Variable RootDir "." -Option Constant
New-Variable BuildDirName "build" -Option Constant
New-Variable ComposerDirName "composer" -Option Constant
New-Variable BuildDir "$RootDir/$BuildDirName" -Option Constant
New-Variable ComposerDir "$BuildDir/$ComposerDirName" -Option Constant

New-Variable ComposerExecutableName "couplet-composer" -Option Constant

# Set up the required directories

if (Test-Path "$ComposerDir") {
  Remove-Item $ComposerDir -Recurse -Force
}

if (-not (Test-Path "$BuildDir")) {
  New-Item -Path $RootDir -Name $BuildDirName -ItemType "directory"
}

# Set up Couplet Composer

Set-Location -Path "$BuildDir"

git clone $ComposerRepoUrl $ComposerDirName

if ($Env:ODE_USE_DEVELOPMENT_COMPOSER) {
  Set-Location -Path "$ComposerDirName"
  git checkout tags/$ComposerVersionTag -b local_install_$ComposerVersionTag
  Set-Location -Path ..
} else {
  Write-Output "The development version of $ComposerName was installed"
}

pipenv install $ComposerDirName
