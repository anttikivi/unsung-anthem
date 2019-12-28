#!/usr/bin/env pwsh

# ---------------------------------------------------------------------------- #
#                         Obliging Ode & Unsung Anthem
# ---------------------------------------------------------------------------- #
#
# This source file is part of the Obliging Ode and Unsung Anthem projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved
#
# ---------------------------------------------------------------------------- #

New-Variable ComposerVersion "0.4.5" -Option Constant
New-Variable ComposerName "Couplet Composer" -Option Constant
New-Variable OdeName "Obliging Ode" -Option Constant
New-Variable AnthemName "Unsung Anthem" -Option Constant

Write-Output "Running the PowerShell wrapper for $ComposerName $ComposerVersion, the build script of $OdeName and $AnthemName"
Write-Output "$ComposerName will be run in configuring mode"

New-Variable GithubUrl "https://github.com" -Option Constant
New-Variable ComposerRepoOwner "anttikivi" -Option Constant
New-Variable ComposerRepoName "couplet-composer" -Option Constant
New-Variable ComposerRepoUrl "$GithubUrl/$ComposerRepoOwner/$ComposerRepoName.git" -Option Constant

New-Variable RootDir "." -Option Constant
New-Variable ComposerDirName "composer" -Option Constant
New-Variable ComposerDir "$RootDir/$ComposerDirName" -Option Constant

New-Variable CleanBuildOption "-c" -Option Constant
New-Variable CleanBuildShortOption "--clean" -Option Constant

New-Variable PresetModeArgument "preset" -Option Constant
New-Variable ConfigureModeArgument "configure" -Option Constant

New-Variable ComposerExecutableName "couplet-composer" -Option Constant

# Clean the script if clean build is enabled

$CleanBuild = ($args -contains $CleanBuildOption) -or ($args -contains $CleanBuildShortOption)

if ($CleanBuild -and (Test-Path "$ComposerDir")) {
  Remove-Item $ComposerDir -Recurse -Force
}

# Set up Couplet Composer

$CloneComposer = -not (Test-Path "$ComposerDir")
$ComposerExecutable = ""

if (Get-Command $ComposerExecutableName -CommandType All -ErrorAction SilentlyContinue) {
  $ComposerExecutable = (Get-Command $ComposerExecutableName -CommandType All | Select-Object -ExpandProperty Definition)
  Write-Output "The installed $ComposerName executable is $ComposerExecutable"
  $InstalledVersion = (& $ComposerExecutable "--version") | Out-String
  if ($ComposerVersion -ne $InstalledVersion) {
    $CloneComposer = $true
  }
} else {
  $CloneComposer = $true
}

$CheckoutRelease = $true

if ($Env:ODE_USE_DEVELOPMENT_COMPOSER) {
  $CheckoutRelease = $false
  $CloneComposer = $true
  Write-Output "The development version of $ComposerName will be installed"
}

if ($CloneComposer) {
  if (Test-Path "$ComposerDir") {
    Remove-Item $ComposerDir -Recurse -Force
  }

  git clone $ComposerRepoUrl $ComposerDir

  if ($CheckoutRelease) {
    Set-Location -Path "$ComposerDirName"
    git checkout tags/$ComposerVersion -b local_install_$ComposerVersion
    Set-Location -Path ..
  }

  pip install $ComposerDir
  $ComposerExecutable = (Get-Command $ComposerExecutableName -CommandType All | Select-Object -ExpandProperty Definition)
  Write-Output "The installed $ComposerName executable is $ComposerExecutable"
}

# Run the script

$Arguments = ""

if ($args -contains $PresetModeArgument) {
  $Arguments = [string]($args += $ConfigureModeArgument)
  Write-Output "Invoking $ComposerExecutable in preset mode with arguments '$Arguments'"
} else {
  $Arguments = [string](@($ConfigureModeArgument) + $args)
  Write-Output "Invoking $ComposerExecutable with arguments '$Arguments'"
}

$ProcessStartInfo = New-Object System.Diagnostics.ProcessStartInfo
$ProcessStartInfo.FileName = $ComposerExecutable
$ProcessStartInfo.RedirectStandardError = $true
$ProcessStartInfo.RedirectStandardOutput = $true
$ProcessStartInfo.UseShellExecute = $false
$ProcessStartInfo.Arguments = $Arguments
$Process = New-Object System.Diagnostics.Process
$Process.StartInfo = $ProcessStartInfo
$Process.Start() | Out-Null
$Process.WaitForExit()
$StandardOutput = $Process.StandardOutput.ReadToEnd()
$StandardError = $Process.StandardError.ReadToEnd()
Write-Host "stdout: $StandardOutput"
Write-Host "stderr: $StandardError"
# Write-Host "exit code: ${Process.ExitCode}"

# $Process = Start-Process $ComposerExecutable -ArgumentList "$Arguments" -PassThru -Wait
exit $Process.ExitCode
